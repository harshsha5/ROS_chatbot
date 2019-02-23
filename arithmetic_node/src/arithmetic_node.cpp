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
  msg.header = msg_from_ui->header;
  string part1,part2;
  float num1,num2;
  char delimeter(':');
  getline(cin,part1,delimeter);
  getline(cin,part2);
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
      cout<<"Division by zero is invalid";
    else
      msg.answer = num1 / num2;

  }

 
  arithmetic_pub.publish(msg);
}

int main(int argc, char **argv) {

  ros::init(argc, argv, "arithmetic_node");
  ros::NodeHandle n;

  arithmetic_pub = n.advertise<arithmetic_node::arithmetic_reply>("arithmetic_reply", 1000);
  ros::Subscriber sub = n.subscribe("sent_msg", 500, arithmetic_Callback);

  ros::Rate loop_rate(20);

  while(ros::ok()) {
    ros::spinOnce();
    loop_rate.sleep();
  }

  return 0;
}