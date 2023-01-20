#pragma once
#include "sections_defs.hpp"
#include <sections/section.hpp>

SECTIONS_NS_HEAD

/*!
 * \brief simple straight-line depth gates
 */
class G0 : public Section{
public:
  /*!
   * \brief A datatype represnting the fixed length portion of the G0 message
   */
  struct Body{
    BE_f32 G0_DepthGateMin;    //!< seconds two-way
    BE_f32 G0_DepthGateMax;    //!< seconds two-way
    BE_f32 G0_DepthGateSlope;  //!< radians
  }__attribute__((packed));

  using Section::Section;  // default to parent constructor
  char * nominalType() const{
    return "G0";
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

