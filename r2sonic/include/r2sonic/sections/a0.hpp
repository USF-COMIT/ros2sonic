#pragma once
#include "sections_defs.hpp"
#include <sections/section.hpp>

SECTIONS_NS_HEAD


/*!
 * \brief An interpreter for Section A0: bathy point angles, equally-spaced (present only during "equi-angle" spacing mode)
 */
class A0 : public Section{
public:
  /*!
   * \brief A datatype represnting the fixed length portion of the A0 message
   */
  struct Body{
    BE_f32 AngleFirst;  //!< [radians] angle of first (port side) bathy point, relative to array centerline, AngleFirst < AngleLast
    BE_f32 AngleLast;   //!< [radians] angle of last (starboard side) bathy point
    BE_f32 MoreInfo[6]; //!< reserved for future use
  }__attribute__((packed));

  using Section::Section;  // default to parent constructor
  char * nominalType() const{
    return "A0";
  }
  /*!
   * \brief returns a pointer to the fixed size portion of the message (the Body).
   * \return the Body of the Section
   */
  Body * body(){
    existanceErrorCheck();
    return reinterpret_cast<Body*>(start_bit_+sizeof(SectionInfo));
  }
}__attribute__((packed));

SECTIONS_NS_FOOT

