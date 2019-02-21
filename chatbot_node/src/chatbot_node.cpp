#include <ros/ros.h>
#include <chatbot_node/reply_msg.h>
#include <message_ui/sent_msg.h>
#include <string>
#include <ros/console.h>

using namespace std;

chatbot_node::reply_msg msg;
ros::Publisher chatter_pub;


//Add your code here

void chatterCallback(const message_ui::sent_msg::ConstPtr& msg_from_ui)
{
  msg.header = msg_from_ui->header;
  if (msg_from_ui->message.compare("Hello") == 0)
    msg.message = "Hello Raju";
  else if((msg_from_ui->message.compare("What is your name?") == 0))
    msg.message = "My name is MRSD Siri";
  else if((msg_from_ui->message.compare("How are you?") == 0))
    msg.message = "I'm fine. Thank you!";
  else
  {
    msg.message = "Hmm.. I'm not sure.";
  }
  
  chatter_pub.publish(msg);
}

int main(int argc, char **argv) {

  ros::init(argc, argv, "chatbot_node");
  ros::NodeHandle n;

  chatter_pub = n.advertise<chatbot_node::reply_msg>("reply_msg", 1);
  ros::Subscriber sub = n.subscribe("sent_msg", 500, chatterCallback);

  ros::Rate loop_rate(20);

  while(ros::ok()) {
    ros::spinOnce();
    loop_rate.sleep();
  }

  return 0;
}