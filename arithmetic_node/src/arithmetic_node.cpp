#include <ros/ros.h>
#include <arithmetic_node/arithmetic_reply.h>
#include <message_ui/sent_msg.h>
#include <string>
#include <ros/console.h>
#include<boost/lexical_cast.hpp>

using namespace std;
using boost::lexical_cast;

arithmetic_node::arithmetic_reply msg;
ros::Publisher arithmetic_pub;

//Add your code here

void arithmetic_Callback(const message_ui::sent_msg::ConstPtr& msg_from_ui)
{ 
  string received_message = msg_from_ui->message;
  if(received_message.find(":")!=string::npos)
  {
  int flag=1;
  double time_rec,time_ans;

  time_rec = ros::Time::now().toSec();
  msg.time_received = time_rec;
  msg.header = msg_from_ui->header;
  string part1,part2;
  float num1,num2;
  size_t f1 = received_message.find(":");
  part1 = received_message.substr (0,f1);
  part2 = received_message.substr (f1+1);
  msg.oper_type = part1;

  part2.erase(part2.begin());   //To remove the beginning "
  size_t found = part2.find_first_not_of("0123456789.");   //Finds the first non numeric character
  string n1 = part2.substr (0,found);
  string n2 = part2.substr (found + 1);   //goes from found + 1 to end 

  n2.erase(n2.end()-1); //To remove the ending "
  num1 = lexical_cast<float>(n1);
  num2 = lexical_cast<float>(n2);
  

  if(part1.compare("Add") == 0)
  {
    msg.answer = num1 + num2;

  }
  else if(part1.compare("Subtract") == 0)
  {
    msg.answer = num1 - num2;

  }

  else if(part1.compare("Multiply") == 0)
  {
    msg.answer = num1 * num2;

  }

  else if(part1.compare("Divide") == 0)
  {
    if(num2==0.0)
      {
        cout<<"Division by zero is invalid";
        flag=0;
      }
    else
      msg.answer = num1 / num2;

  }
  time_ans = ros::Time::now().toSec();
  msg.time_answered = time_ans;
  msg.process_time = time_ans - time_rec;
 if(flag==1)
    {
        arithmetic_pub.publish(msg);
    }
  }
}

int main(int argc, char **argv) {

  ros::init(argc, argv, "arithmetic_node");
  ros::NodeHandle n;

  arithmetic_pub = n.advertise<arithmetic_node::arithmetic_reply>("arithmetic_reply", 1);
  ros::Subscriber sub = n.subscribe("sent_msg", 500, arithmetic_Callback);

  ros::Rate loop_rate(20);

  while(ros::ok()) {
    ros::spinOnce();
    loop_rate.sleep();
  }

  return 0;
}