#include <sensor_msgs/Image.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui.hpp>

class ImageCannyConverter
{

public:
  ImageCannyConverter(ros::NodeHandle& nodehanle);
  ~ImageCannyConverter();
  void imageCallback(const sensor_msgs::ImageConstPtr& msg);
  
private:
  ros::NodeHandle& nh_;
  image_transport::ImageTransport it_;
  image_transport::Subscriber image_sub_;
  image_transport::Publisher image_pub_;

};
