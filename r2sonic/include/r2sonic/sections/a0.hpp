#pragma once
#include <sections/sections_defs.hpp>

SECTIONS_NS_HEAD

struct A0Body{
  BE_u16 SectionSize; //!< [bytes] size of this entire section
  BE_f32 AngleFirst;  //!< [radians] angle of first (port side) bathy point, relative to array centerline, AngleFirst < AngleLast
  BE_f32 AngleLast;   //!< [radians] angle of last (starboard side) bathy point
  BE_f32 MoreInfo[6]; //!< reserved for future use
};
/*!
 * \brief bathy point angles, equally-spaced (present only during "equi-angle" spacing mode)
 */
class A0 : public Section{
public:
  using Section::Section;  // default to parent constructor
  bool typeMatches(){
    return isType("A0");
  }
  A0Body * body(){
    return reinterpret_cast<A0Body*>(start_bit_+sizeof(SectionInfo));
  }
}__attribute__((packed));

SECTIONS_NS_FOOT

