#pragma once
#include "packets_defs.hpp"
#include "packet.hpp"
#include <sections/h0.hpp>
#include <sections/r0.hpp>
#include <sections/a0.hpp>
#include <sections/a2.hpp>
#include <sections/i1.hpp>
#include <sections/g0.hpp>
#include <sections/g1.hpp>
#include <sections/q0.hpp>

PACKETS_NS_HEAD

/*!
 * \brief An interpreter class that represents the Bathmetry Data (BHT0) packet
 * \details
 * This class has accessors which will return a pointer to each sub-section
 * of the received packet.
 * \note Some packets are optional.  See the member function defitions
 * for details
 */
class BTH0 : public Packet{
public:
  using Packet::Packet; // default to parent constructor
  /*!
   * \brief Gets the sections::H0 Section associated with the BTH0 packet
   * \return The Packet's sections::H0 Section;
   */
  sections::H0 h0() const{
    typeErrorCheck();
    return sections::H0( SectionsStartBit() );
  }
  /*!
   * \brief Gets the sections::R0 Section associated with the BTH0 packet
   * \return The Packet's sections::R0 Section;
   */
  sections::R0 r0() const{
    typeErrorCheck();
    return sections::R0( h0().end() );
  }
  /*!
   * \brief Requests the OPTIONAL section sections::A0
   * \note This is an optional parameter present only during "equi-angle" spacing mode.
   * make sure sections::A0::exists() == true before accessing
   * \return The Packets's sections::A0 Section
   * \throws std::out_of_range if Section doesn't exist
   */
  sections::A0 a0() const{
    typeErrorCheck();
    return sections::A0( r0().end() );
  }
  /*!
   * \brief Requests the OPTIONAL section sections::A2
   * \note This is an optional parameter present only during "equi-distant" spacing mode.
   * make sure sections::A2::exists() == true before accessing
   * \return The Packets's sections::A2 Section
   * \throws std::out_of_range if Section doesn't exist
   */
  sections::A2 a2() const{
    typeErrorCheck();
    return sections::A2( a0().end() );
  }
  /*!
   * \brief Requests the OPTIONAL section sections::I1
   * \note This is an optional parameter present only if intensity is enabled on the sonar.
   * make sure sections::I1::exists() == true before accessing
   * \return The Packets's sections::I1 Section
   * \throws std::out_of_range if Section doesn't exist
   */
  sections::I1 i1() const{
    typeErrorCheck();
    return sections::I1( a2().end() );
  }
  /*!
   * \brief Gets the sections::G0 Section associated with the BTH0 packet
   * \return The Packet's sections::G0 Section;
   */
  sections::G0 g0() const{
    typeErrorCheck();
    return sections::G0( i1().end() );
  }
  /*!
   * \brief Requests the OPTIONAL section sections::G1
   * \note This is an optional parameter present only if enabled on the sonar.
   * make sure sections::G1::exists() == true before accessing
   * \return The Packets's sections::G1 Section
   * \throws std::out_of_range if Section doesn't exist
   */
  sections::G1 g1() const{
    typeErrorCheck();
    return sections::G1( g0().end() );
  }
  /*!
   * \brief Gets the sections::Q0 Section associated with the BTH0 packet
   * \return The Packet's sections::Q0 Section;
   */
  sections::Q0 q0() const{
    typeErrorCheck();
    return sections::Q0( g1().end() );
  }

protected:
  char * nominalType() const{
    return "BTH0";
  }
};

PACKETS_NS_FOOT
