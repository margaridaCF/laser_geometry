#include <ros/ros.h>
#include "laser_geometry/laser_geometry.h"

namespace free_cloud_node
{
	ros::Publisher free_cloud_pub;	

	void free_cloud_cb(const sensor_msgs::LaserScan::ConstPtr& laser_scan )
	{
  		laser_geometry::LaserProjection projector;  
  		sensor_msgs::PointCloud2 cloud_out;
  		projector.projectFreeLaser(*laser_scan, cloud_out, -1.0);
  		free_cloud_pub.publish(cloud_out);
	}
}

int main(int argc, char **argv)
{
	ros::init(argc, argv, "free_cloud_node");
	ros::NodeHandle nh;
	
	std::string hokuyo_topic;
	nh.getParam("uav/laser_topic", hokuyo_topic);
	ros::Subscriber laser_scan_sub = nh.subscribe<sensor_msgs::LaserScan>(hokuyo_topic, 1, free_cloud_node::free_cloud_cb);
    free_cloud_node::free_cloud_pub = nh.advertise<sensor_msgs::PointCloud2>("free_cloud", 10);
	
	ros::spin();
}