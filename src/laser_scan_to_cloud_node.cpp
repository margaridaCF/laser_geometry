#include <ros/ros.h>
#include "laser_geometry/laser_geometry.h"

namespace laser_to_cloud_node
{
	ros::Publisher cloud_pub;	

	void cloud_cb(const sensor_msgs::LaserScan::ConstPtr& laser_scan )
	{
  		laser_geometry::LaserProjection projector;  
  		sensor_msgs::PointCloud2 cloud_out;
  		projector.projectLaser(*laser_scan, cloud_out, -1.0);
  		cloud_pub.publish(cloud_out);
	}
}

int main(int argc, char **argv)
{
	ros::init(argc, argv, "cloud_node");
	ros::NodeHandle nh;
    laser_to_cloud_node::cloud_pub = nh.advertise<sensor_msgs::PointCloud2>("cloud_out", 10);
	ros::Subscriber laser_scan_sub = nh.subscribe<sensor_msgs::LaserScan>("hokuyo_laser_scan", 1, laser_to_cloud_node::cloud_cb);
	
	ros::spin();
}