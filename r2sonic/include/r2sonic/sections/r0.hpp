#pragma once
#include "sections_defs.hpp"
#include <sections/section.hpp>

SECTIONS_NS_HEAD


/*!
 * \brief An interpreter for Section R0: 16-bit bathy point ranges
 */
class R0: public Section
{
public:
  using Section::Section;  // default to parent constructor
  char * nominalType() const{
    return "R0";
  }
  /*!
   * \brief the scaling factor for the intensities reported in
   * \return a pointer to the scaling factor
   */
  BE_f32 * scaliningFactor() const{
    return reinterpret_cast<BE_f32*>(start_bit_+sizeof(SectionInfo));
  }
  /*!
   * \brief Returns a pointer to the range at beam_no
   * \param beam_no the beam you want the range for
   * \return a pointer to the range at beam_no
   */
  BE_u16 * range(u16 beam_no) const{
    return & reinterpret_cast<BE_u16*>(start_bit_+sizeof(SectionInfo)+sizeof(f32))[beam_no];
  }
  /*!
   * \brief Returns the raw range value
   * \param beam_no the beam you want the range for
   * \return the raw (unscaled) range value
   */
  u16 getRange(u16 beam_no) const{
    return range(beam_no)->get();
  }
  /*!
   * \brief computes the scaled range/2-way travel time for a given beam
   * \param beam_no the beam you want the range for
   * \return the scaled range (seconds two-way) as a machine endian float32
   */
  f32 getScaledRange(u16 beam_no) const{
    return float( getRange(beam_no) ) * scaliningFactor()->get();
  }
}__attribute__((packed));

SECTIONS_NS_FOOT

