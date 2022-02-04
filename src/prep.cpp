//
// Created by larscg on 21.10.20.
//
#include <random>
#include "ros/ros.h"
#include "std_msgs/Int64.h"


std::random_device rd; // obtain a random number from hardware
std::mt19937 gen(rd()); // seed the generator
std::uniform_int_distribution<> distr(0, 15000); // define the range
ros::Publisher pub;

void publish() {
    ros::Rate loop_rate(10);
    while(ros::ok()) {
        int randomInt = distr(gen);
        std_msgs::Int64 msg;
        msg.data = randomInt;
        pub.publish(msg);
        ros::spinOnce();
        loop_rate.sleep();
    }
}


int main(int argc, char** argv) {
    ros::init(argc, argv, "prep");
    ros::NodeHandle n;
    pub = n.advertise<std_msgs::Int64>("prep_topic", 10);
    publish();
    ros::spinOnce();
    return 0;
}