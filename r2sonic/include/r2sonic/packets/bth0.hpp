#pragma once
#include <packets/packet.hpp>
#include <sections/h0.hpp>
#include <sections/r0.hpp>
#include <sections/a0.hpp>
#include <sections/a2.hpp>

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
};

PACKETS_NS_FOOT
