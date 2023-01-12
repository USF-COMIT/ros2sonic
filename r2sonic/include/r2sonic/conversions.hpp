#ifndef CONVERSIONS_HPP
#define CONVERSIONS_HPP

#include "packets/bth0.hpp"
#include "acoustic_msgs/msg/sonar_detections.hpp"

NS_HEAD

namespace conversions{
  void i02PingInfo(acoustic_msgs::msg::PingInfo * ping_info_msg,
                   const sections::H0 & h0_msg);
  void bth02SonarDetections(acoustic_msgs::msg::SonarDetections * detections_msg,
                            const packets::BTH0 & bth0_msg);
}

NS_FOOT

#endif // CONVERSIONS_HPP
