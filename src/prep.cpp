//
// Created by larscg on 21.10.20.
//
#include <random>
#include "ros/ros.h"
#include "prep_pkg/encryptedMessage.h"
#include "prep_pkg/dataCheck.h"

std::vector<int> seq_def = {68, 97, 115, 95, 109, 97, 99, 104, 116, 95, 100, 111, 99, 104, 95, 108, 97, 117, 110, 101};
std::vector<int> seq;
std::vector<int> seq_old;
std::random_device rd; // obtain a random number from hardware
std::mt19937 gen(rd()); // seed the generator
std::uniform_int_distribution<> distr(-10000, 10000); // define the range
std::uniform_int_distribution<> w_dirstr(0, 6);
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

void publish(ros::NodeHandle& n) {
    ros::Rate loop_rate(1);
    while(ros::ok()) {
        int which = w_dirstr(gen);
        //ros::param::get("/which_seq", which);
        //if (which > 7 || which < 0) {which = default_seq;}
        std::string sequence = "seq" + std::to_string(which);
        try {
            ros::param::get(sequence, seq);
        } catch (...) {
            seq = seq_def;
        }
        prep_pkg::encryptedMessage msg;

        int key;
        ros::param::get("key", key);
        if (key < -48 || key > 30) {
            int temp_key = distr(gen);
            ros::param::set("key", temp_key);
            ROS_WARN("Key value out of valid range [-32|30], your's was %d. Set it to %d instead.", key, temp_key);
            continue;
        }
        msg.key = distr(gen);
        for (auto& c : seq) {
            msg.secret.push_back(c + key);
        }
        pub.publish(msg);

        loop_rate.sleep();
        ros::spinOnce();
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
    publish(n);
    ros::spinOnce();
    return 0;
}