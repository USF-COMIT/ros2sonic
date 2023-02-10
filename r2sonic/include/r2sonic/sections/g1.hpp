#pragma once
#include "sections_defs.hpp"
#include <sections/section.hpp>

SECTIONS_NS_HEAD

/*!
 * \brief simple straight-line depth gates
 */
class G1 : public Section{
public:
  /*!
   * \brief A structure representing the 2 byte gate information
   */
  struct Gate{
    BE_u8 RangeMin; //!< [seconds two-way] = RangeMin * G1_ScalingFactor
    BE_u8 RangeMax; //!< [seconds two-way] = RangeMax * G1_ScalingFactor
  }__attribute__((packed));

  using Section::Section;  // default to parent constructor
  char * nominalType() const{
    return "G1";
  }
  /*!
   * \brief Returns a poniter to the raw scaling factor
   * \return a poniter to the raw scaling factor
   */
  BE_f32 * ScalingFactor() const{
    existanceErrorCheck();
    return reinterpret_cast<BE_f32*>(start_bit_+sizeof(SectionInfo));
  }
  /*!
   * \brief Get's the Gate at the specified beam
   * \param beam_no
   * \return a pointer to the unscaled Gate
   */
  Gate * gate(u16 beam_no){
    existanceErrorCheck();
    return & reinterpret_cast<Gate*>(start_bit_+sizeof(SectionInfo)+sizeof(BE_f32))[beam_no];
  }
}__attribute__((packed));

SECTIONS_NS_FOOT

