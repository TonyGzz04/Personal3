#!/usr/bin/env python3

import rospy
from turtlesim.msg import Pose
from turtlesim.srv import SetPen
from geometry_msgs.msg import Twist


previous_x = 0

def call_set_pen_service(r, g, b, width, off):
    try:
        set_pen = rospy.ServiceProxy("/turtle1/set_pen", SetPen)
        response = set_pen(r, g, b, width, off)
        # rospy.loginfo(response)
    except rospy.ServiceException as e:
        rospy.logwarn(e)


def pose_callback(msg: Pose):
    cmd = Twist()

    limit = [9.0,2.0,9.0,2.0]   # límites de izq, der, arriba, abajo

    if msg.x > limit[0] or msg.x < limit[1] or msg.y > limit[2] or msg.y < limit[3]:
        cmd.linear.x = 1.0
        cmd.angular.z = 1.4
    else:
        cmd.linear.x = 5.0
        cmd.angular.z = 0.0
    pub.publish(cmd)
    
    # la variable global se ponga para que se corra la función call sólo si es necesario
    global previous_x 
    if msg.x >= 5.5 and previous_x < 5.5:
        rospy.loginfo("Set color to red!")
        call_set_pen_service(255, 0, 0, 3, 0)
    elif msg.x < 5.5 and previous_x >= 5.5:
        rospy.loginfo("Set color to green!")
        call_set_pen_service(0, 255, 0, 3, 0)
    previous_x = msg.x
    


if __name__ == '__main__':
    rospy.init_node("turtle_controller")
    rospy.wait_for_service("/turtle1/set_pen")

    call_set_pen_service(255, 0, 0, 3, 0)

    pub = rospy.Publisher("/turtle1/cmd_vel", Twist, queue_size=10)
    sub = rospy.Subscriber("/turtle1/pose", Pose, callback=pose_callback)
    rospy.loginfo("Node has been started.")

    rospy.spin()
