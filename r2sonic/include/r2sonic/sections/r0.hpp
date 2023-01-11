#pragma once
#include <sections/sections_defs.hpp>
#include <sections/section.hpp>

SECTIONS_NS_HEAD


/*!
 * \brief Section R0: 16-bit bathy point ranges
 */
class R0: public Section
{
public:
  using Section::Section;  // default to parent constructor
  char * nominalType(){
    return "R0";
  }
  BE_f32 * scaliningFactor(){
    return reinterpret_cast<BE_f32*>(start_bit_+sizeof(SectionInfo));
  }
  f32 getScalingFactor(){
    return scaliningFactor()->get();
  }
  BE_u16 * range(u16 beam_no){
    return & reinterpret_cast<BE_u16*>(start_bit_+sizeof(SectionInfo)+sizeof(f32))[beam_no];
  }
  /*!
   * \brief Returns the raw range value
   * \param beam_no the beam you want the range for
   * \return the raw (unscaled) range value
   */
  u16 getRange(u16 beam_no){
    return range(beam_no)->get();
  }
  /*!
   * \brief computes the scaled range/2-way travel time for a given beam
   * \param beam_no the beam you want the range for
   * \return the scaled range (seconds two-way) as a machine endian float32
   */
  f32 getScaledRange(u16 beam_no){
    return float( getRange(beam_no) ) * getScalingFactor();
  }
}__attribute__((packed));

SECTIONS_NS_FOOT

