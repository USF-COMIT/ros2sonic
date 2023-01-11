#include "datatype_receiver.hpp"

NS_HEAD

DatatypeReceiver::DatatypeReceiver()
{

}

void DatatypeReceiver::receiveImpl(const boost::system::error_code &error, size_t bytes_transferred){

  packets::BTH0 bth0(startBit());
  if(bth0.isType()){
    auto h0 = bth0.h0();
    auto freq = h0.body()->Frequency.get();
    auto soundspeed = h0.body()->SoundSpeed.get();
    auto r0 = bth0.r0();
    auto a0 = bth0.a0();
    auto a2 = bth0.a2();
    auto a2_exists = bth0.a2().exists();
    auto range0 = r0.getScaledRange(0);
    auto g0_exists = bth0.g0().exists();
    auto g1_exists = bth0.g1().exists();
    auto q0_exists = bth0.q0().exists();
  }
  return;
}

NS_FOOT
