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
