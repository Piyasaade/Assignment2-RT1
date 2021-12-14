#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "sensor_msgs/LaserScan.h"
#include "my_srv/Speed.h"
#include "std_srvs/Empty.h"
#include <string>
float min_FrontLeft, min_Front,min_FrontRight;
ros::Subscriber sub;
ros::Publisher pub;
ros::ServiceClient client1;
float spd=1.0;




bool my_new_vel (my_srv::Speed::Request &req, my_srv::Speed::Response &res){
	my_srv::Speed speed_srv;
		if (req.a == "I"){
		res.x = spd + 0.2*spd;
		}
		else if (req.a == "D"){
		res.x = spd - 0.2*spd;
		}
		spd=res.x;
		return res.x;
}






void laserCallback(const sensor_msgs::LaserScan::ConstPtr& msg)
// 720/5=144 decomposing the ranges into 5 ranges
	{
	//spd=speed;
	for (int i=145;i<288;i++) // front right
	{
	min_FrontRight=msg-> ranges[i];
	if (min_FrontRight > msg-> ranges[i]);
	min_FrontRight = msg-> ranges[i];
	}
	for (int i=289;i<432;i++) // front 
	{
	min_Front=msg-> ranges[i];
	if (min_Front > msg-> ranges[i]);
	min_Front = msg-> ranges[i];
	}
	for (int i=433;i<576;i++) // front left
	{
	min_FrontLeft=msg-> ranges[i];
	if (min_FrontLeft > msg-> ranges[i]);
	min_FrontLeft = msg-> ranges[i];
	}

	geometry_msgs::Twist my_vel;
	//my_srv::Speed speed_srv;
	//spd=speed_srv.response.x;
	my_vel.linear.x = spd;
	my_vel.angular.z = 0.0;
	if (min_FrontLeft > 1 && min_Front > 1 && min_FrontRight>1){
	my_vel.linear.x = spd;
	my_vel.angular.z = 0.0;
	} 
	else if (min_FrontLeft > 1 && min_Front< 1 && min_FrontRight > 1){
	my_vel.linear.x = spd;
	my_vel.angular.z = 1.5;
	}
	else if (min_FrontLeft > 1 && min_Front>1 && min_FrontRight <1){
	my_vel.linear.x = spd;
	my_vel.angular.z = 1.5;
	}
	else if (min_FrontLeft <1 && min_Front>1 && min_FrontRight >1){
	my_vel.linear.x = spd;
	my_vel.angular.z =-1.5;
	}
	else if (min_FrontLeft > 1 && min_Front < 1 && min_FrontRight <1){
	my_vel.linear.x = spd;
	my_vel.angular.z =1.5;
	}
	else if (min_FrontLeft < 1 && min_Front <1 && min_FrontRight >1 ){
	my_vel.linear.x = spd;
	my_vel.angular.z =-1.5;
	}
	else if (min_FrontLeft <1 && min_Front <1 && min_FrontRight <1){
	my_vel.linear.x = spd;
	my_vel.angular.z =1.5;
	}
	else if ( min_FrontLeft <1 && min_Front >1 && min_FrontRight <1){
	my_vel.linear.x = spd;
	my_vel.angular.z =0.0;
	}
	else{
	my_vel.linear.x = spd;
	my_vel.angular.z =0.0;
	}
	pub.publish(my_vel);
}
	
	
	int main (int argc, char **argv)
{

	ros::init(argc, argv, "turtlebot_subscriber");
	ros::NodeHandle nh;
	ros::NodeHandle n;
	ros::ServiceServer service= n.advertiseService("/speed", my_new_vel);
	pub = nh.advertise<geometry_msgs::Twist> ("/cmd_vel", 1);
	ros::Subscriber sub = nh.subscribe("/base_scan", 1,laserCallback);
	
	ros::ServiceClient client1 = nh.serviceClient<std_srvs::Empty>("/reset_positions");
	std_srvs::Empty srv1;
 	client1.waitForExistence();
	client1.call(srv1);
	
	
	ros::spin();
	return 0;
}
