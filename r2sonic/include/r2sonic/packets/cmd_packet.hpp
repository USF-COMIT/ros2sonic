#pragma once

#include "packets_defs.hpp"

PACKETS_NS_HEAD

/*!
 * \brief A class that corresponds to an r2sonic command
 * \warning This class is not yet fully implemented
 */
template <typename T>
struct CmdPacket{
  char  packet_name[4];
  char  cmd_name[4];
  T     value;
}__attribute__((packed));

//packets::CmdPacket<BE_u32> power_cmd;
//power_cmd.packet_name[0]='C';
//power_cmd.packet_name[1]='M';
//power_cmd.packet_name[2]='D';
//power_cmd.packet_name[3]='0';
//power_cmd.cmd_name[0]='S';
//power_cmd.cmd_name[1]='P';
//power_cmd.cmd_name[2]='O';
//power_cmd.cmd_name[3]='0';
//power_cmd.value.set(1);
//send_udp_message(power_cmd,parameters_.sonar_ip,65502);

PACKETS_NS_FOOT
