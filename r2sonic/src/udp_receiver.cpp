#include "udp_receiver.hpp"

NS_HEAD

UdpReceiver::UdpReceiver():
  socket_(io_service_)
{

}

void UdpReceiver::wait(){
  socket_.async_receive_from(boost::asio::buffer(recv_buffer_),
  remote_endpoint_,
  boost::bind(&UdpReceiver::receiveHandler, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}

void UdpReceiver::receive(const std::string& host,
                          const std::string& port){

  boost::asio::ip::udp::resolver resolver(io_service_);
  boost::asio::ip::udp::resolver::query query(
        boost::asio::ip::udp::v4(), host, port);
  boost::asio::ip::udp::resolver::iterator iter = resolver.resolve(query);
  remote_endpoint_ = *iter;

  socket_.open(boost::asio::ip::udp::v4());
  socket_.bind(remote_endpoint_);

  wait();

  io_service_.run();

}

void UdpReceiver::receiveHandler(const boost::system::error_code &error, size_t bytes_transferred){
  if (error) {
    std::cout << "Receive failed: " << error.message() << "\n";
    return;
  }
  std::cout << "Received: '" << std::string(recv_buffer_.begin(), recv_buffer_.begin()+bytes_transferred) << "' (" << error.message() << ")\n";

  receiveImpl(error, bytes_transferred);

  wait();
}

char * UdpReceiver::startBit(){
  return reinterpret_cast<char *>(&recv_buffer_);
}


NS_FOOT
