#include "../include/cv_bridge_converter.h"
#include <highgui.h>
#include <cv.h>

void SigintHandler(int sig)
{
  ROS_INFO_STREAM("CvBridge Converter Node Is Shutting Down");
  shutdown();
}

Mat loadFrame(const sensor_msgs::ImageConstPtr& msg)
{
  try
  {
    cv_bridge::CvImagePtr tempResult = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::TYPE_8UC3);
    Mat result = tempResult->image.clone();
    return result;
  }
  catch (cv_bridge::Exception& e)
  {
    ROS_ERROR("cv_bridge exception: %s", e.what());
  }
}

Mat loadDepthFrame(const sensor_msgs::ImageConstPtr& msg)
{
  try
  {
    cv_bridge::CvImagePtr tempResult = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::TYPE_16UC1);
    Mat result = tempResult->image.clone();
    return result;
  }
  catch (cv_bridge::Exception& e)
  {
    ROS_ERROR("cv_bridge exception: %s", e.what());
  }
}

void imageCallbackRGB(const sensor_msgs::ImageConstPtr& msg)
{
  // Load full color frame
  Mat frameRGB = loadFrame(msg);
  //ROS_INFO_STREAM("RGB Image callback");
  image_second = frameRGB;
  
  waitKey(30);
}

void depthCallback(const sensor_msgs::ImageConstPtr& msg)
{
  // Load full color frame
  Mat depth = loadDepthFrame(msg);
  ROS_INFO_STREAM("Depth image callback");
  depth_second = depth;

  waitKey(30);
}

