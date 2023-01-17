#include "datatype_receiver.hpp"

NS_HEAD

template<typename PKT_T>
DatatypeReceiver<PKT_T>::DatatypeReceiver(r2sonic::R2SonicNode *node_ptr){
  (void)static_cast<packets::Packet*>((PKT_T*)0);  // ensure template type is a child of packet.
  node_ptr_ = node_ptr;

}
template<typename PKT_T>
void DatatypeReceiver<PKT_T>::receiveImpl(const boost::system::error_code &error, size_t bytes_transferred){

  PKT_T packet(startBit());
  if(packet.isType()){
    node_ptr_->publish(packet);
  }
  return;
}

template class DatatypeReceiver<packets::BTH0>;

NS_FOOT


//    auto msg = acoustic_msgs::msg::SonarDetections();
//    auto h0 = bth0.h0();
//    auto freq = h0.body()->Frequency.get();
//    auto soundspeed = h0.body()->SoundSpeed.get();
//    auto r0 = bth0.r0();
//    auto a0 = bth0.a0();
//    auto a2 = bth0.a2();
//    auto a2_exists = bth0.a2().exists();
//    auto i1 = bth0.i1();
//    auto range0 = r0.getScaledRange(0);
//    auto g0_exists = bth0.g0().exists();
//    auto g1_exists = bth0.g1().exists();
//    auto q0_exists = bth0.q0().exists();
//    conversions::bth02SonarDetections(&msg,bth0);
//    return;
