#!/usr/bin/env python3

import rospy
from turtlesim.msg import Pose
from geometry_msgs.msg import Twist

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

if __name__ == '__main__':
    rospy.init_node("turtle_controller")

    pub = rospy.Publisher("/turtle1/cmd_vel", Twist, queue_size=10)
    sub = rospy.Subscriber("/turtle1/pose", Pose, callback=pose_callback)
    rospy.loginfo("Node has been started.")
    
    

    rospy.spin()
