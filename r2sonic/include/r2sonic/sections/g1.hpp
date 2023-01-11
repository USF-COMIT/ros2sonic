#pragma once
#include <sections/sections_defs.hpp>

SECTIONS_NS_HEAD

struct G1Gate{
  BE_u8 RangeMin; //!< [seconds two-way] = RangeMin * G1_ScalingFactor
  BE_u8 RangeMax; //!< [seconds two-way] = RangeMax * G1_ScalingFactor
};
/*!
 * \brief simple straight-line depth gates
 */
class G1 : public Section{
public:
  using Section::Section;  // default to parent constructor
  char * nominalType(){
    return "G1";
  }
  BE_f32 * ScalingFactor(){
    existanceErrorCheck();
    return reinterpret_cast<BE_f32*>(start_bit_+sizeof(SectionInfo));
  }
  G1Gate * gate(u16 beam_no){
    existanceErrorCheck();
    return & reinterpret_cast<G1Gate*>(start_bit_+sizeof(SectionInfo)+sizeof(BE_f32))[beam_no];
  }
}__attribute__((packed));

SECTIONS_NS_FOOT

