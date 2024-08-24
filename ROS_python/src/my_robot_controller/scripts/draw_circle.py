#!/usr/bin/env python3

import rospy
from geometry_msgs.msg import Twist

if __name__ == '__main__':
    rospy.init_node("draw_circle")
    rospy.loginfo("Node has been started.")

    # El publisher, con 'Twist' como el tiopo de variable
    pub = rospy.Publisher("/turtle1/cmd_vel", Twist, queue_size=10)

    # Rate de 2 Hz
    rate = rospy.Rate(2)

    while not rospy.is_shutdown():
        # publish cmd vel, no se tienen que llenar todas las variables del Twist, se quedan default
        msg = Twist()   # se declara el tipo de variable
        msg.linear.x = 2.0
        msg.angular.z = 1.0
        pub.publish(msg)    # se publica el msg
        rate.sleep()

