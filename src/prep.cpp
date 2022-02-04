//
// Created by larscg on 21.10.20.
//
#include <random>
#include "ros/ros.h"
#include "prep_pkg/encryptedMessage.h"
#include "prep_pkg/dataCheck.h"

std::vector<char> seq = {68, 97, 115, 95, 109, 97, 99, 104, 116, 95, 100, 111, 99, 104, 95, 108, 97, 117, 110, 101};
std::random_device rd; // obtain a random number from hardware
std::mt19937 gen(rd()); // seed the generator
std::uniform_int_distribution<> distr(-32, 30); // define the range
ros::Publisher pub;

bool dataCheck(prep_pkg::dataCheck::Request& req, prep_pkg::dataCheck::Response& res) {
    int element = 0;
    for (auto& c : req.decryptedMessage) {
        if (c != seq[element]) {
            res.answer = "Sorry, you're wrong";
            return true;
        }
        element++;
    }
    res.answer = "That's correct";
    return true;
}

void publish() {
    ros::Rate loop_rate(1);
    while(ros::ok()) {
        prep_pkg::encryptedMessage msg;
        msg.key = distr(gen);
        for (auto& c : seq) {
            msg.secret.push_back(c + msg.key);
        }
        pub.publish(msg);
        ros::spinOnce();
        loop_rate.sleep();
    }
}


int main(int argc, char** argv) {
    ros::init(argc, argv, "prep");
    ros::NodeHandle n;
    pub = n.advertise<prep_pkg::encryptedMessage>("prep_topic", 10);
    ros::ServiceServer check = n.advertiseService("/data_check", dataCheck);
    std::vector<std::string> nodes;
    while(!std::count(nodes.begin(), nodes.end(), "/secret_node")) {
        ros::master::getNodes(nodes);
    }
    publish();
    ros::spinOnce();
    return 0;
}