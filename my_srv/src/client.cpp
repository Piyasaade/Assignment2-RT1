#include "ros/ros.h"
#include "my_srv/Speed.h"
#include <cstdlib>
#include <ostream>
#include <string>
using namespace std;
char speed_choice;
	
int main(int argc, char **argv) {
	ros::init(argc, argv, "enter_a_string_client");
	
	while (1){
		ros::NodeHandle n;
		ros::ServiceClient client = n.serviceClient<my_srv::Speed>("/speed");
		my_srv::Speed speed_srv; 
		cout<<"Enter I to increase the speed or D to decrease it: ";
		cin>>speed_choice;
		//ROS_INFO("speed= %f", speed_srv.response.x);
		speed_srv.request.a = speed_choice;
		if (client.call(speed_srv)) {
		
		
		cout<<"speed = "<< speed_srv.response.x << endl;
		
		}
		 	
		else {
		ROS_ERROR("Failed to call service speed");
		return 1;
		}
		
		}
		return 0;
		}
		

