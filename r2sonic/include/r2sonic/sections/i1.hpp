#pragma once
#include <sections/sections_defs.hpp>

SECTIONS_NS_HEAD

/*!
 * \brief 16-bit bathy intensity (present only if enabled)
 */
struct I1 : public Section
{
  using Section::Section;  // default to parent constructor
  char * nominalType() const{
    return "I2";
  }
  BE_f32 * ScalingFactor() const{
    existanceErrorCheck();
    return reinterpret_cast<BE_f32*>(start_bit_+sizeof(SectionInfo));
  }
  BE_u16 * Intensity(u16 beam_no) const{
    existanceErrorCheck();
    return & reinterpret_cast<BE_u16*>(start_bit_+sizeof(SectionInfo)+sizeof(BE_f32))[beam_no];
  }
  f32 getScaledIntensity(u16 beam_no) const{
    return Intensity(beam_no)->get()*ScalingFactor()->get();
  }

}__attribute__((packed));

SECTIONS_NS_FOOT

