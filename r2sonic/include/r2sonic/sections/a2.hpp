#pragma once
#include "sections_defs.hpp"
#include <sections/section.hpp>

SECTIONS_NS_HEAD
/*!
 * \brief An interpreter for Section A2:
 * 16-bit bathy point angles, arbitrarily-spaced
 * (present only during "equi-distant" spacing mode)
 */
class A2 : public Section{
public:
  /*!
   * \brief A datatype represnting the fixed length portion of the A2 message
   */
  struct Body{
    BE_f32 AngleFirst;  //!< [radians] angle of first (port side) bathy point, relative to array centerline, AngleFirst < AngleLast
    BE_f32 ScalingFactor;
    BE_f32 MoreInfo[6]; //!< reserved for future use
  }__attribute__((packed));

  using Section::Section;  // default to parent constructor
  char * nominalType() const{
    return "A2";
  }
  /*!
   * \brief returns a pointer to the fixed size portion of the message (the Body).
   * \return the Body of the Section
   */
  Body * body() const{
    existanceErrorCheck();
    return reinterpret_cast<Body*>(start_bit_+sizeof(SectionInfo));
  }
  /*!
   * \brief [radians] angle[n] = A2_AngleFirst + (32-bit sum of A2_AngleStep[0] through A2_AngleStep[n]) * A2_ScalingFacto
   * \param beam_no
   * \return [radians] angle[n] = A2_AngleFirst + (32-bit sum of A2_AngleStep[0] through A2_AngleStep[n]) * A2_ScalingFacto
   */
  BE_u16 * AngleStep(u16 beam_no) const{
    existanceErrorCheck();
    return & reinterpret_cast<BE_u16*>(start_bit_+sizeof(SectionInfo)+sizeof(f32))[beam_no];
  }

}__attribute__((packed));

SECTIONS_NS_FOOT

