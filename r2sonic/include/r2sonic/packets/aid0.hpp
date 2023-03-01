#pragma once

#include "packets_defs.hpp"
#include "packet.hpp"

#include <sections/h0.hpp>
#include <sections/a1.hpp>
#include <sections/m0.hpp>

PACKETS_NS_HEAD

/*!
 * \brief An interpreter class that represents the Acoustic Image (AID) packet
 * \details
 * This class has accessors which will return a pointer to each sub-section
 * of the received packet.
 *
 * R2Sonic's details on this packet type:
 *
 * The acoustic image data contains real-time beamformer 8-bit magnitude data
 * (beam amplitude) that has been scaled to 8-bits by a user-selected
 * brightness value, and compressed in range by an adjustable amount to
 * reduce network bandwidth and processing. The data is called "samples"
 * before compression and "bins" after compression. For example, 7200 samples
 * of beamformer data (M0_TotalSamples) may be compressed to 600 bins
 * (M0_TotalBins). The number of beamformed data samples normally extends
 * somewhat further than the user's range setting. The AIH0 sonar command
 * sets an upper limit to the number of compressed output bins. It's not a
 * precise compression factor, so the number of bins is usually somewhat less
 * than the AIH0 value. The maximum data rate with no compression is about
 * 17.5 megabytes per second (assuming 256 beams).
 *
 * When the operator enables acoustic image mode, each sonar ping outputs
 * numerous 'AID0' packets containing: one H0 header section, one A1 beam
 * angle section, and many M0 data sections. The section order may change in
 * the future, so plan for that in your data acquisition.
 *
 * Each M0 section contains a subset of the ping data. Its header indicates
 * its size position to help you assemble the full ping array.
 *
 * You may wish to detect missing M0 data sections (perhaps a lost UDP
 * packet), and then fill the gap with zeros or perhaps data from the
 * previous ping (to reduce visual disturbances), and then increment an error
 * counter for network health monitoring purposes.
 *
 * The acoustic image data is basically in polar coordinates, so you may wish
 * to geometrically warp it into the familiar wedge shape for display.
 * Consider using OpenGL or Direct3D texture mapping
 *
 *
 * \note Some packets are optional.  See the member function defitions
 * for details
 */
class AID0 : public Packet{
public:
  using Packet::Packet; // default to parent constructor
  /*!
   * \brief Gets the OPTIONAL (once per ping) sections::H0 Section associated with the AID0 packet
   * \note This section is OPTIONAL and is only present for the first packet
   * for any given ping
   * \return The Packet's sections::H0 Section;
   */
  sections::H0 h0() const{
    typeErrorCheck();
    return sections::H0( SectionsStartBit() );
  }
  /*!
   * \brief Gets the OPTIONAL (once per ping) sections::A1 Section associated with the AID0 packet
   * \note This section is OPTIONAL and is only present for the first packet
   * for any given ping
   * \return The Packet's sections::A1 Section;
   */
  sections::A1 a1() const{
    typeErrorCheck();
    return sections::A1( h0().end() );
  }

  sections::M0 m0() const{
    typeErrorCheck();
    return sections::M0( a1().end() );
  }

  bool isFirstInSeries() const{
    return h0().exists();
  }


protected:
  char * nominalType() const{
    return "AID0";
  }
};



PACKETS_NS_FOOT
