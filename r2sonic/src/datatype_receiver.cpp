#include "datatype_receiver.hpp"

NS_HEAD

DatatypeReceiver::DatatypeReceiver()
{

}

void DatatypeReceiver::receiveImpl(const boost::system::error_code &error, size_t bytes_transferred){
  auto m_hdr = reinterpret_cast<const sections::MiniHeader*>(&recv_buffer_);
  std::cout << m_hdr->DataStreamID << std::endl;
  //auto hdr = m_hdr->swapEndian();
  sections::H0 h0( startBit() + sizeof(sections::MiniHeader) );
  return;
}

NS_FOOT
