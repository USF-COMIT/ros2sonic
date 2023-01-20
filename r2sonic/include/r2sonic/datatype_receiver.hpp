#ifndef DATATYPERECEIVER_HPP
#define DATATYPERECEIVER_HPP
#include "package_defs.hpp"
#include "udp_receiver.hpp"
#include <packets/all.hpp>
#include "acoustic_msgs/msg/sonar_detections.hpp"
#include <conversions.hpp>
#include <r2sonic_node.hpp>



NS_HEAD
template<typename PKT_T>
class DatatypeReceiver: public UdpReceiver
{
public:
  DatatypeReceiver(R2SonicNode * node_ptr);
  virtual void receiveImpl(const boost::system::error_code& error, size_t bytes_transferred);
private:
  R2SonicNode * node_ptr_;
};

NS_FOOT

#endif // DATATYPERECEIVER_HPP
