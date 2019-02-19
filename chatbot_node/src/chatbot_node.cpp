#include <ros/ros.h>
#include <chatbot_node/reply_msg.h>
#include <message_ui/sent_msg.h>
#include <string>

using namespace std;

//Add your code here

int main(int argc, char **argv) {

  ros::init(argc, argv, "chatbot_node");
  ros::NodeHandle n;

  //Add your code here
  ros::Publisher chatter_pub = n.advertise<chatbot_node::reply_msg>("reply_msg", 500);

  ros::Rate loop_rate(20);

  while(ros::ok()) {
    chatbot_node::reply_msg msg;
    //msg.header = ;
    //msg.message = ;
    
    chatter_pub.publish(msg);
    ros::spinOnce();
    loop_rate.sleep();
  }

  return 0;
}