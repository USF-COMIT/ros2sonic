#ifndef DATATYPERECEIVER_HPP
#define DATATYPERECEIVER_HPP

#include "udp_receiver.hpp"
#include <packets/bth0.hpp>

NS_HEAD

class DatatypeReceiver: public UdpReceiver
{
public:
  DatatypeReceiver();
  virtual void receiveImpl(const boost::system::error_code& error, size_t bytes_transferred);
};

NS_FOOT

#endif // DATATYPERECEIVER_HPP
