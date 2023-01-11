#pragma once
#include <sections/sections_defs.hpp>

SECTIONS_NS_HEAD

struct G0Body{
  BE_f32 G0_DepthGateMin;    //!< [seconds two-way]
  BE_f32 G0_DepthGateMax;    //!< [seconds two-way]
  BE_f32 G0_DepthGateSlope;  //!< [radians]
};
/*!
 * \brief simple straight-line depth gates
 */
class G0 : public Section{
public:
  using Section::Section;  // default to parent constructor
  bool typeMatches(){
    return isType("G0");
  }
  G0Body * body(){
    existanceErrorCheck();
    return reinterpret_cast<G0Body*>(start_bit_+sizeof(SectionInfo));
  }
}__attribute__((packed));

SECTIONS_NS_FOOT

