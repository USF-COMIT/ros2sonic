#ifndef CONVERSIONS_HPP
#define CONVERSIONS_HPP
#include "package_defs.hpp"
#include "packets/all.hpp"
#include "acoustic_msgs/msg/sonar_detections.hpp"
#include "acoustic_msgs/msg/raw_sonar_image.hpp"
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

  /*!
   * \brief Populates a r2sonic_interfaces::msg::RawPacket with relavent data from packets::Packet
   * \param raw_packet_msg [output]
   * \param pkt [input]
   */
  void packet2RawPacket(r2sonic_interfaces::msg::RawPacket * raw_packet_msg,
                        const packets::Packet *pkt);
  /*!
   * \brief Populates a acoustic_msgs::msg::RawSonarImage message with relavent data from
   * an r2sonic::packets::AID0 packet.
   * \param sonar_image [output] the message to fill with aid0_packet data
   * \param aid0_pkt [input]
   * \return True if the acoustic_msgs::msg::RawSonarImage is fully assembled.
   */
  bool aid02RawAcousticImage(acoustic_msgs::msg::RawSonarImage * sonar_image,
                             const packets::AID0 & aid0_pkt);
}

NS_FOOT

#endif // CONVERSIONS_HPP
