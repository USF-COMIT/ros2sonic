#include "assembly/assembly.hpp"

ASSEMBLY_NS_HEAD

template <typename T>
Assembly::Assembly(){
  return;
}

template <typename T>
bool Assembly::addPacket(T packet){
  if(packet.h0.exists()){

  }else{

  }
}


template class Assembly<packets::AID0>;

ASSEMBLY_NS_FOOT
