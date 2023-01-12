#pragma once
#include <sections/sections_defs.hpp>
#include <sections/section.hpp>

SECTIONS_NS_HEAD

struct H0Body
{
char   ModelNumber[12];
char   SerialNumber[12];
BE_u32  TimeSeconds;
BE_u32  TimeNanoseconds;
BE_u32  PingNumber;
BE_f32  PingPeriod;
BE_f32  SoundSpeed;
BE_f32  Frequency;
BE_f32  TxPower;
BE_f32  TxPulseWidth;
BE_f32  TxBeamwidthVert;
BE_f32  TxBeamwidthHoriz;
BE_f32  TxSteeringVert;
BE_f32  TxSteeringHoriz;
BE_u16  TxMiscInfo;
BE_s16  VTX_Offset;
BE_f32  RxBandwidth;
BE_f32  RxSampleRate;
BE_f32  RxRange;
BE_f32  RxGain;
BE_f32  RxSpreading;
BE_f32  RxAbsorption;
BE_f32  RxMountTilt;
BE_u32  RxMiscInfo;
BE_u16  reserved;
BE_u16  Points;
}__attribute__((packed));

class H0 : public Section{
public:
  using Section::Section;  // default to parent constructor
  char * nominalType() const {
    return "H0";
  }
  const H0Body * body() const{
    return reinterpret_cast<H0Body*>(start_bit_+sizeof(SectionInfo));
  }
};


SECTIONS_NS_FOOT

