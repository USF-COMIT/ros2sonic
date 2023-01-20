#pragma once
#include "sections_defs.hpp"
#include <sections/section.hpp>

SECTIONS_NS_HEAD

/*!
 * \brief An interpreter for the "H0" Section which describes general ping information.
 */
class H0 : public Section{
public:
  /*!
   * \brief A datatype represnting the fixed length portion of the H0 message
   */
  struct Body
  {
  char   ModelNumber[12];   //!< example "2024", unused chars are nulls
  char   SerialNumber[12];  //!< example "100017", unused chars are nulls
  BE_u32  TimeSeconds;      //!< [seconds] ping time relative to 0000 hours 1-Jan-1970, integer part
  BE_u32  TimeNanoseconds;  //!< [nanoseconds] ping time relative to 0000 hours 1-Jan-1970, fraction part
  BE_u32  PingNumber;       //!< pings since power-up or reboot
  BE_f32  PingPeriod;       //!< [seconds] time between most recent two pings
  BE_f32  SoundSpeed;       //!< [meters per second]
  BE_f32  Frequency;        //!< [hertz] sonar center frequency
  BE_f32  TxPower;          //!< [dB re 1 uPa at 1 meter]
  BE_f32  TxPulseWidth;     //!< [seconds]
  BE_f32  TxBeamwidthVert;  //!< [radians] "allong track" beam width
  BE_f32  TxBeamwidthHoriz; //!< [radians] "across track" beam width
  BE_f32  TxSteeringVert;   //!< [radians] "allong track" beam stearing
  BE_f32  TxSteeringHoriz;  //!< [radians] "across track" beam stearing
  BE_u16  TxMiscInfo;       //!< reserved
  BE_s16  VTX_Offset;       //!< hundredths of a dB] transmit voltage offset at time of ping (divide value by 100 to get dB)
  BE_f32  RxBandwidth;      //!< [hertz]
  BE_f32  RxSampleRate;     //!< [hertz] sample rate of data acquisition and signal processing
  BE_f32  RxRange;          //!< [meters] sonar range setting
  BE_f32  RxGain;           //!< [multiply by two for relative dB]
  BE_f32  RxSpreading;      //!< [dB (times log range in meters)]
  BE_f32  RxAbsorption;     //!< [dB per kilometer]
  BE_f32  RxMountTilt;      //!< [radians]
  BE_u32  RxMiscInfo;       //!< reserved for future use
  BE_u16  reserved;         //!< reserved for future use
  BE_u16  Points;           //!< number of bathy points
  }__attribute__((packed));


  using Section::Section;  // default to parent constructor
  char * nominalType() const {
    return "H0";
  }
  /*!
   * \brief returns a pointer to the fixed size portion of the message (the Body).
   * \return the Body of the Section
   */
  const Body * body() const{
    return reinterpret_cast<Body*>(start_bit_+sizeof(SectionInfo));
  }
}__attribute__((packed));


SECTIONS_NS_FOOT

