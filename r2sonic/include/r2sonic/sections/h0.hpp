#pragma once
#include <sections/sections_defs.hpp>
#include <sections/section.hpp>

SECTIONS_NS_HEAD

struct H0Body
{
char   ModelNumber[12];
char   SerialNumber[12];
u32  TimeSeconds;
u32  TimeNanoseconds;
u32  PingNumber;
f32  PingPeriod;
f32  SoundSpeed;
f32  Frequency;
f32  TxPower;
f32  TxPulseWidth;
f32  TxBeamwidthVert;
f32  TxBeamwidthHoriz;
f32  TxSteeringVert;
f32  TxSteeringHoriz;
u16  TxMiscInfo;
s16  VTX_Offset;
f32  RxBandwidth;
f32  RxSampleRate;
f32  RxRange;
f32  RxGain;
f32  RxSpreading;
f32  RxAbsorption;
f32  RxMountTilt;
u32  RxMiscInfo;
u16  reserved;
u16  Points;
}__attribute__((packed));

class H0 : public Section{
public:
  using Section::Section;  // default to parent constructor
  H0Body * body(){
    return reinterpret_cast<H0Body*>(start_bit_+sizeof(SectionInfo));
  }
};


SECTIONS_NS_FOOT

