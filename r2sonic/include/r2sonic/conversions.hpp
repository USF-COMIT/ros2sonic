#ifndef CONVERSIONS_HPP
#define CONVERSIONS_HPP

#include "packets/bth0.hpp"
#include "acoustic_msgs/msg/sonar_detections.hpp"

NS_HEAD

namespace conversions{
  void h02Header(std_msgs::msg::Header * header,
                 const sections::H0 & h0_msg);
  /*!
   * \brief converts an r2sonic::packets::I0 to a acoustic_msgs::msg::PingInfo message
   * \param ping_info_msg [output] the message to populate with the h0_msg
   * \param h0_msg [input]
   */
  void h02PingInfo(acoustic_msgs::msg::PingInfo * ping_info_msg,
                   const sections::H0 & h0_msg);
  /*!
   * \brief converts r2sonic::packets::BTH0 to acoustic_msgs::msg::SonarDetections
   * \param detections_msg [output]  The message to populate with the bth0 information
   * \param bth0_msg [input]
   */
  void bth02SonarDetections(acoustic_msgs::msg::SonarDetections * detections_msg,
                            const packets::BTH0 & bth0_msg);
}

NS_FOOT

#endif // CONVERSIONS_HPP
