#pragma once
#include "sections_defs.hpp"
#include <sections/section.hpp>

SECTIONS_NS_HEAD
/*!
 * \brief An interpreter for Section M0:
 * 8-bit magnitude data (many per ping, you assemble them into complete ping data)
 */
class M0 : public Section{
public:
  /*!
   * \brief A datatype represnting the fixed length portion of the M0 message
   */
  struct Body{
    BE_u32 PingNumber;    //!< pings since power-up or reboot
    BE_f32 ScalingFactor; //!< reserved for future use
    BE_u32 TotalSamples;  //!< range samples (before compression) in entire ping, sample rate is H0_RxSampleRate
    BE_u32 TotalBins;     //!< range bins (after compression) in entire ping (M0_TotalBins <= M0_TotalSamples)
    BE_u32 FirstBin;      //!< first bin of this section
    BE_u16 Bins;          //!< number of bins in this section
    BE_u16 TotalBeams;    //!< beams (always a multiple of 4) (typically columns in your memory buffer)
    BE_u16 FirstBeam;     //!< first beam of this section (always a multiple of 4)
    BE_u16 Beams;         //!< number of beams in this section (always a multiple of 4)
    BE_u32 reserved;      //!< reserved for future use
  }__attribute__((packed));

  using Section::Section;  // default to parent constructor
  char * nominalType() const{
    return "M0";
  }
  /*!
   * \brief returns a pointer to the fixed size portion of the message (the Body).
   * \return the Body of the Section
   */
  Body * body() const{
    existanceErrorCheck();
    return reinterpret_cast<Body*>(start_bit_+sizeof(SectionInfo));
  }
  BE_u8 * magnitude(u16 beam_no, u16 bin_no) const{
    existanceErrorCheck();

    auto beam_idx = beam_no - body()->FirstBeam.get();
    auto bin_idx  = bin_no - body()->FirstBin.get();
    //return & reinterpret_cast<BE_u8*>(start_bit_+sizeof(SectionInfo)+sizeof(Body))[bin_no + beam_no*body()->Beams.get()];
    //return & reinterpret_cast<BE_u8*>(start_bit_+sizeof(SectionInfo)+sizeof(Body))[beam_idx + bin_idx*body()->TotalBeams.get()];
    return & reinterpret_cast<BE_u8*>(start_bit_+sizeof(SectionInfo)+sizeof(Body))[bin_idx + beam_idx*body()->Bins.get()];
  }


}__attribute__((packed));

SECTIONS_NS_FOOT

