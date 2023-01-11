#pragma once
#include <packets/packet.hpp>
#include <sections/h0.hpp>
#include <sections/r0.hpp>
#include <sections/a0.hpp>
#include <sections/a2.hpp>
#include <sections/i1.hpp>
#include <sections/g0.hpp>
#include <sections/g1.hpp>
#include <sections/q0.hpp>

PACKETS_NS_HEAD


class BTH0 : public Packet{
public:
  using Packet::Packet; // default to parent constructor
  sections::H0 h0(){
    return sections::H0( SectionsStartBit() );
  }
  sections::R0 r0(){
    return sections::R0( h0().end() );
  }
  sections::A0 a0(){
    return sections::A0( r0().end() );
  }
  sections::A2 a2(){
    return sections::A2( a0().end() );
  }
  sections::I1 i1(){
    return sections::I1( a2().end() );
  }
  sections::G0 g0(){
    return sections::G0( i1().end() );
  }
  sections::G1 g1(){
    return sections::G1( g0().end() );
  }
  sections::Q0 q0(){
    return sections::Q0( g1().end() );
  }
};

PACKETS_NS_FOOT
