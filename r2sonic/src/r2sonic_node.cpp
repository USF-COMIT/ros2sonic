#include "r2sonic_node.hpp"

NS_HEAD

template<typename T>
void setupParam(T * variable,rclcpp::Node *node , std::string topic, T initial_val){
  node->declare_parameter(topic, initial_val);
  *variable =
      node->get_parameter(topic).get_parameter_value().get<T>();
}

// a explicit overload for string is required for casting to work correctly
void setupParam(std::string * variable,rclcpp::Node *node , std::string topic, std::string initial_val){
  setupParam<std::string>(variable,node,topic,initial_val);
}

void R2SonicNode::Parameters::init(rclcpp::Node *node){
  setupParam(&topics.detections,node,"topics/detections","~/detections");
  setupParam(&topics.bth0,node,"topics/bth0","~/raw/bth0");
  setupParam(&ports.bathy,node,"ports/bathy",65500);
  setupParam(&ports.acoustic_image,node,"ports/acoustic_image" ,65503);
  setupParam(&sonar_ip,node,"sonar_ip","10.0.0.86");
  setupParam(&interface_ip,node,"interface_ip","10.226.212.146");
  setupParam(&tx_frame_id,node,"tx_frame_id","r2sonic_tx");
  setupParam(&rx_frame_id,node,"rx_frame_id","r2sonic_rx");

  RCLCPP_INFO(node->get_logger(), "Listening on interface  : %s", interface_ip.c_str());
  RCLCPP_INFO(node->get_logger(), "Sending sonar comands on: %s", sonar_ip.c_str());
}

template <typename T>
bool send_udp_message(packets::CmdPacket<T> message, const std::string& destination_ip,
            const unsigned short port) {

  using namespace boost::asio;
  io_service io_service;
  ip::udp::socket socket(io_service);
  auto remote = ip::udp::endpoint(ip::address::from_string(destination_ip), port);
  try {
    socket.open(boost::asio::ip::udp::v4());
    socket.send_to(buffer(reinterpret_cast<char*>(&message),
                          sizeof(packets::CmdPacket<T>)),
                          remote);

  } catch (const boost::system::system_error& ex) {
    return false;
  }
  return true;
}

R2SonicNode::R2SonicNode():
  Node("r2sonic")
{
  parameters_.init(this);

  if(shouldAdvertise(getParams().topics.detections)){
    msg_buffer_.dectections.pub =
        this->create_publisher<acoustic_msgs::msg::SonarDetections>(parameters_.topics.detections,100);
  }

  if(shouldAdvertise(getParams().topics.bth0)){
    msg_buffer_.bth0.pub =
        this->create_publisher<r2sonic_interfaces::msg::RawPacket>(parameters_.topics.bth0,100);
  }

}

//void R2SonicNode::publish(packets::Packet &r2_packet){
//  publish(reinterpret_cast<packets::BTH0>(&r2_packet));
//  publish(reinterpret_cast<packets::AID0>(&r2_packet));
//}

void R2SonicNode::publish(packets::BTH0 &r2_packet){
  if(!r2_packet.isType()){
    return;
  }

  msg_buffer_.dectections.lock();
  msg_buffer_.bth0.lock();

  if(shouldPublish(msg_buffer_.dectections.pub)){
    conversions::bth02SonarDetections(&msg_buffer_.dectections.msg,r2_packet);
    msg_buffer_.dectections.msg.header.frame_id = getParams().tx_frame_id;
    msg_buffer_.dectections.pub->publish(msg_buffer_.dectections.msg);
  }

  if(shouldPublish(msg_buffer_.bth0.pub)){
    conversions::packet2RawPacket(&msg_buffer_.bth0.msg,&r2_packet);
    msg_buffer_.bth0.msg.frame_id = getParams().tx_frame_id;
    msg_buffer_.bth0.pub->publish(msg_buffer_.bth0.msg);
    msg_buffer_.bth0.pub->get_subscription_count();
  }

  msg_buffer_.dectections.unlock();
  msg_buffer_.bth0.unlock();
}

void R2SonicNode::publish(packets::AID0 &aid0_packet){
  if(!aid0_packet.isType()){
    return;
  }


}

bool R2SonicNode::shouldAdvertise(std::string topic){
  return topic != "";
}

bool R2SonicNode::shouldPublish(rclcpp::PublisherBase::SharedPtr pub){
  if(!pub){
    return false;
  }
  return pub->get_subscription_count() > 0;
}

NS_FOOT
