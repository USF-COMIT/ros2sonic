#pragma once
#include <sections/sections_defs.hpp>

SECTIONS_NS_HEAD

struct A2Body{
  BE_u16 SectionName; //!< 'A2'
  BE_u16 SectionSize; //!< [bytes] size of this entire section
  BE_f32 AngleFirst;  //!< [radians] angle of first (port side) bathy point, relative to array centerline, AngleFirst < AngleLast
  BE_f32 ScalingFactor;
  BE_f32 MoreInfo[6]; //!< reserved for future use
};

/// \todo implement
struct A2 : public Section
{
  using Section::Section;  // default to parent constructor
  char * nominalType(){
    return "A2";
  }
  A2Body * body(){
    existanceErrorCheck();
    return reinterpret_cast<A2Body*>(start_bit_+sizeof(SectionInfo));
  }
  BE_u16 * AngleStep(u16 beam_no){
    existanceErrorCheck();
    return & reinterpret_cast<BE_u16*>(start_bit_+sizeof(SectionInfo)+sizeof(f32))[beam_no];
  }

}__attribute__((packed));

SECTIONS_NS_FOOT

