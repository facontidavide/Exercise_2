#include <canny_transform/CannyTransform.hpp>


int main(int argc, char** argv)
{
  ros::init(argc, argv, "image_canny_converter");
  ros::NodeHandle nh;
  ImageCannyConverter ic(nh);
  ros::spin();
  return 0;
}
