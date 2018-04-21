#include <iostream>
#include <ros/ros.h>
#include <string.h>
#include <std_msgs/String.h>
#include <std_msgs/Float64.h>
#include <sensor_msgs/NavSatFix.h>
#include <sensor_msgs/Imu.h>
#include <tf_conversions/tf_eigen.h>
#include <tf/transform_datatypes.h>
#include <math.h>
#define longitude_length 96.486 
#define latitude_length 110.852
#define latitude_origin 21.309959
#define longitude_origin -157.89009
using namespace std;

ros::Publisher pub_node_reporter;
struct pose
{
	double heading;
	double lati;
	double longi;
	double X;
	double Y;
	double time;
	int index;
}wamv_pose;

void initializing(){
	wamv_pose.heading = 0;
	wamv_pose.lati = latitude_origin;
	wamv_pose.longi = longitude_origin;
	wamv_pose.X = 0;
	wamv_pose.Y = 0;
	wamv_pose.time = 0;
	wamv_pose.index = 0;	
}
void cbGps(const sensor_msgs::NavSatFix::ConstPtr& gps){
	wamv_pose.lati = gps -> latitude;
	wamv_pose.longi = gps -> longitude;
	wamv_pose.Y = (wamv_pose.lati - latitude_origin) * 1000 * latitude_length;
	wamv_pose.X = (wamv_pose.longi - longitude_origin) * 1000 * longitude_length;
	//cout << wamv_pose.X << ",  " << wamv_pose.Y << endl;

} 
void cbImu(const sensor_msgs::Imu::ConstPtr& imu){
	tf::Quaternion q(
		imu->orientation.x,
		imu->orientation.y,
		imu->orientation.z,
		imu->orientation.w);
	tf::Matrix3x3 m(q);
	double roll, pitch, yaw;
	m.getRPY(roll, pitch, yaw);
	wamv_pose.heading = 3.14159 - yaw;
	//cout << yaw << endl;
} 
void cbTime(const std_msgs::Float64::ConstPtr& time){
	wamv_pose.time = time->data;
}
void publishData(const ros::TimerEvent& e){

	if(wamv_pose.time != 0){
		std::ostringstream ss;
		ss.precision(std::numeric_limits<double>::digits10);
		ss << "NAME=tony,TYPE=uuv,TIME=" << wamv_pose.time << ",X=" << wamv_pose.X << ",Y=" << wamv_pose.Y << ",SPD=2.4,HDG=" << wamv_pose.heading/3.14*180
			<< ",LAT=" << wamv_pose.lati << ",LON=" << wamv_pose.longi << ",TYPE=KAYAK,MODE=DRIVE,ALLSTOP=clear,index=" << wamv_pose.index <<",DEP=0,LENGTH=4";
		string report= ss.str();

		std_msgs::String node_report;
		node_report.data = report;
		pub_node_reporter.publish(node_report);

		wamv_pose.index += 1;
	}

}
int main(int argc, char** argv)
{
	ros::init(argc, argv, "gazebo_wamv_alpha");
	string node_name = ros::this_node::getName();
	ROS_INFO("[%s] Initializing ", node_name.c_str());

	//Initialize
	initializing();

	ros::NodeHandle nh("~");
	ros::Timer timer = nh.createTimer(ros::Duration(0.5), publishData);
	//Subsriber
	ros::Subscriber sub_gps 	= nh.subscribe("/gps", 1000, cbGps);
	ros::Subscriber sub_imu	 	= nh.subscribe("/imu/data", 1000, cbImu);
	ros::Subscriber sub_time	= nh.subscribe("/DB_TIME", 1000, cbTime);

	//Publisher
	pub_node_reporter = nh.advertise<std_msgs::String>("/NODE_REPORT", 1000);

	ros::spin();
	return 0;
}