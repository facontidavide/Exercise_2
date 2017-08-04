#include <canny_transform/CannyTransform.hpp>


const char* WINDOW_NAME = "EdgeDetection";
//#define DEBUG_WINDOW


  ImageCannyConverter::ImageCannyConverter(ros::NodeHandle& nodehanle)
    : nh_(nodehanle), it_(nodehanle)
  {
    // Subscribe to input video feed and publish output video feed
    image_sub_ = it_.subscribe("/cv_camera/image_raw", 1,
      &ImageCannyConverter::imageCallback, this);
    image_pub_ = it_.advertise("/canny_converter/output_video", 1);

#ifdef DEBUG_WINDOW
    cv::namedWindow( WINDOW_NAME );
#endif

  }

  ImageCannyConverter::~ImageCannyConverter()
  {
#ifdef DEBUG_WINDOW
    cv::destroyWindow( WINDOW_NAME );
#endif
  }

  void ImageCannyConverter::imageCallback(const sensor_msgs::ImageConstPtr& msg)
  {
	using namespace cv;
	  
    cv_bridge::CvImagePtr image_ptr;
    cv::Mat image_gray;
    
	//NOTE: you might want to make th thresholds configurable an NOT
	//hardcoded. To do that you can use either a rosparam or command line arguments.
	const int LOW_THRESHOLD = 30;
	const int KERNEL_SIZE = 3; 
	const int RATIO = 3; 

    try
    {
      image_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
    }
    catch (cv_bridge::Exception& e)
    {
      ROS_ERROR("cv_bridge exception: %s", e.what());
      return;
    }
  
    cvtColor( image_ptr->image, image_gray, COLOR_BGR2GRAY );
    blur(  image_gray, image_gray, Size(3,3) );
    Canny( image_gray, image_ptr->image, LOW_THRESHOLD, LOW_THRESHOLD*RATIO, KERNEL_SIZE );
    image_ptr->encoding = sensor_msgs::image_encodings::MONO8;

   
#ifdef DEBUG_WINDOW
    imshow( WINDOW_NAME, image_ptr->image );
    waitKey(3);
#endif
    
    image_pub_.publish(image_ptr->toImageMsg());
  }


