#pragma once
#include "sections_defs.hpp"
#include <sections/section.hpp>

SECTIONS_NS_HEAD


/*!
 * \brief An interpreter for Section A1: float beam angles, arbitrarily-spaced
 */
class A1 : public Section{
public:

  using Section::Section;  // default to parent constructor
  char * nominalType() const{
    return "A1";
  }
  /*!
   * \brief Gets the angle for a given beam
   * \param beam_no  the beam index you want the angle for
   * \return [radians] angle of beam relative to array centerline, ordered from
   * port to starboard, first angle < last angle
   */
  BE_f32 * BeamAngle(u16 beam_no) const{
    existanceErrorCheck();
    return & reinterpret_cast<BE_f32*>(start_bit_+sizeof(SectionInfo)+6*sizeof(f32))[beam_no];
  }
}__attribute__((packed));

SECTIONS_NS_FOOT

