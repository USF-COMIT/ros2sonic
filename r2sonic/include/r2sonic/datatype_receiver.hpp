#ifndef DATATYPERECEIVER_HPP
#define DATATYPERECEIVER_HPP

#include "udp_receiver.hpp"
#include "types/miniheader.hpp"
#include "types/r0.hpp"
#include "types/h0.hpp"

NS_HEAD

class DatatypeReceiver: public UdpReceiver
{
public:
  DatatypeReceiver();
  virtual void receiveImpl(const boost::system::error_code& error, size_t bytes_transferred);
};

NS_FOOT

#endif // DATATYPERECEIVER_HPP
