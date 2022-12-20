#pragma once
#include <types/types_defs.hpp>
#include <types/section.hpp>

TYPES_NS_HEAD


/*!
 * \brief Section R0: 16-bit bathy point ranges
 */
class R0: public Section
{
  using Section::Section;  // default to parent constructor

  f32 * ScaliningFactor(){
    return reinterpret_cast<f32*>(start_bit_+sizeof(SectionInfo));
  }
  u16 & range(u16 beam_no){
    return reinterpret_cast<u16*>(start_bit_+sizeof(SectionInfo)+sizeof(f32))[beam_no];
  }
  u16 getRange(u16 beam_no){
    return revPrimative(range(beam_no));
  }
}__attribute__((packed));

TYPES_NS_FOOT

