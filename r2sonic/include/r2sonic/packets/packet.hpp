#pragma once
#include <packets/packets_defs.hpp>
#include <sections/miniheader.hpp>

PACKETS_NS_HEAD

/*!
 * \brief The DataFormat class is a common base class for the R2Sonic
 * up/downlink data formats as definned in the R2Sonic data formats pdf
 * \note accessors with a get* prefix will return a machine-endian value
 * accessors without the get prefix will return a reference to the raw data
 * which will be in big-endian order as per the r2sonic spec
 */
class Packet{
public:
  /*!
   * \brief Constructor
   * \param the start bit of the datagram you want to read
   */
  Packet(char* start_bit){start_bit_= start_bit;}
  /*!
   * \brief returns a pointer to the miniHeader
   * \return a pointer to the miniHeader
   */
  const sections::MiniHeader * miniHeader(){
    return reinterpret_cast<const sections::MiniHeader*>(start_bit_);
  }
  /*!
   * \brief returns a pointer to the start bit used to define the packet
   * \return a pointer to the start bit of the packet
   */
  char * startBit(){
    return start_bit_;
  }
  /*!
   * \brief gets the size of the entire DataFormat Packet reported by the MiniHeader
   * \return the size of the DataFormat Packet
   */
  u16 getSize(){
    return miniHeader()->PacketSize.get();
  }
  /*!
   * \brief end returns a pointer to one bit beyond the current DataFormat Packet (the first bit of the next Packet)
   * \return the pointer to the next packet
   */
  char * end(){
    return startBit() + getSize();
  }
  /*!
   * \brief Returns the starting bit of the data sections of the packet (just after the mini header)
   * \return a pointer to the first section of the packet after the mini header
   */
  char * SectionsStartBit(){
    return startBit() + sizeof(sections::MiniHeader);
  }

private:
  char * start_bit_; //!< a pointer to the first bit in the message
};

PACKETS_NS_FOOT
