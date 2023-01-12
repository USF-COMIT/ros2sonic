#pragma once
#include <packets/packets_defs.hpp>
#include <sections/miniheader.hpp>
#include <string>

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
  const sections::MiniHeader * miniHeader() const{
    return reinterpret_cast<const sections::MiniHeader*>(start_bit_);
  }
  /*!
   * \brief returns a pointer to the start bit used to define the packet
   * \return a pointer to the start bit of the packet
   */
  char * startBit() const{
    return start_bit_;
  }
  /*!
   * \brief gets the size of the entire DataFormat Packet reported by the MiniHeader
   * \return the size of the DataFormat Packet
   */
  u16 getSize() const{
    return miniHeader()->PacketSize.get();
  }
  /*!
   * \brief end returns a pointer to one bit beyond the current DataFormat Packet (the first bit of the next Packet)
   * \return the pointer to the next packet
   */
  char * end() const{
    return startBit() + getSize();
  }
  /*!
   * \brief Returns the starting bit of the data sections of the packet (just after the mini header)
   * \return a pointer to the first section of the packet after the mini header
   */
  char * SectionsStartBit() const{
    return startBit() + sizeof(sections::MiniHeader);
  }
  /*!
   * \brief Determines if the packet can be instantiated given the current
   * data in the buffer.
   * \return
   */
  bool isType() const{
    return strncmp(miniHeader()->PacketName,nominalType(),4) == 0;
  }


protected:
  virtual char * nominalType() const = 0;
  void typeErrorCheck() const{
    if(!isType()){
      std::string rec = miniHeader()->PacketName;
      std::string nom = nominalType();
      std::string msg = "Attempted to interpret a "+rec+" as a "+nom+" message.";
      throw std::out_of_range (msg);
    }
  }

private:
  char * start_bit_; //!< a pointer to the first bit in the message
};

PACKETS_NS_FOOT
