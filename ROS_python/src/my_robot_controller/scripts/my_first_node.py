#!/usr/bin/env python3

import rospy

if __name__ == '__main__':
    rospy.init_node("test_node")
    rospy.loginfo("Test node has been started.")

    rate = rospy.Rate(2)  # 2 Hz

    while not rospy.is_shutdown():
        rospy.loginfo("Hello")
        rate.sleep()  # esto es como el punto donde termina para volver a iniciar la frecuencia
        