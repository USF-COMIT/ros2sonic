#ifndef CONVERSIONS_HPP
#define CONVERSIONS_HPP

#include "packets/bth0.hpp"
#include "acoustic_msgs/msg/sonar_detections.hpp"
#include "r2sonic_interfaces/msg/raw_packet.hpp"
#include <bits/stdc++.h>

NS_HEAD

namespace conversions{
  void h02Header(std_msgs::msg::Header * header,
                 const sections::H0 & h0_pkt);
  /*!
   * \brief converts an r2sonic::packets::I0 to a acoustic_msgs::msg::PingInfo message
   * \param ping_info_msg [output] the message to populate with the h0_msg
   * \param h0_pkt [input]
   */
  void h02PingInfo(acoustic_msgs::msg::PingInfo * ping_info_msg,
                   const sections::H0 & h0_pkt);
  /*!
   * \brief converts r2sonic::packets::BTH0 to acoustic_msgs::msg::SonarDetections
   * \param detections_msg [output]  The message to populate with the bth0 information
   * \param bth0_pkt [input]
   */
  void bth02SonarDetections(acoustic_msgs::msg::SonarDetections * detections_msg,
                            const packets::BTH0 & bth0_pkt);

  void packet2RawPacket(r2sonic_interfaces::msg::RawPacket * raw_packet_msg,
                        const packets::Packet *pkt);
}

NS_FOOT

#endif // CONVERSIONS_HPP
