#include "../include/cv_bridge_converter.h"
#include "cv_bridge_converter_lib.cpp"

int main(int argc, char** argv)
{
  init(argc, argv, "cv_bridge_converter", init_options::NoSigintHandler);
  NodeHandle n;
  ROS_INFO_STREAM("CV_BRIDGE Converter Node -> is RUN");
  Subscriber imageSubRGB = n.subscribe("/rgb_image", 1, imageCallbackRGB);
  Publisher image_pub = n.advertise<sensor_msgs::Image>("processed_image_bgr8", 2);

  signal(SIGINT, SigintHandler);
  Rate rate(30); // 30Hz

  sensor_msgs::Image im_msg;
  while (ok())
  {
    // Publishing messages
    cv_bridge::CvImage cv_image;
    cv_image.image = image_second;
    cv_image.encoding = "bgr8";
    sensor_msgs::Image ros_image;
    cv_image.toImageMsg(ros_image);
    image_pub.publish(ros_image);
    rate.sleep();
    spinOnce();
  }
  return 0;
}
