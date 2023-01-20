#pragma once
#include "sections_defs.hpp"
#include <sections/section.hpp>

SECTIONS_NS_HEAD

/*!
 * \brief An interpreter for Section I1:  16-bit bathy intensity (present only if enabled)
 */
class I1 : public Section
{
public:
  using Section::Section;  // default to parent constructor
  char * nominalType() const{
    return "I2";
  }
  BE_f32 * ScalingFactor() const{
    existanceErrorCheck();
    return reinterpret_cast<BE_f32*>(start_bit_+sizeof(SectionInfo));
  }
  /*!
   * \brief Returns the raw intensity [micropascals] intensity[n] = I1_Intensity[n]) * I1_ScalingFacto
   * \param beam_no the beam you want the raw intensity for
   * \return the raw intensity at beam_no
   */
  BE_u16 * Intensity(u16 beam_no) const{
    existanceErrorCheck();
    return & reinterpret_cast<BE_u16*>(start_bit_+sizeof(SectionInfo)+sizeof(BE_f32))[beam_no];
  }
  /*!
   * \brief Coputes the scaled intesity for the specified beam
   * \param beam_no the beam you want the scaled intesity for
   * \return the scaled intensity at beam: beam_no
   */
  f32 getScaledIntensity(u16 beam_no) const{
    return Intensity(beam_no)->get()*ScalingFactor()->get();
  }

}__attribute__((packed));

SECTIONS_NS_FOOT

