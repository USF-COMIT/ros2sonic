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
  setupParam(&sonar_ip,node,"sonar_ip","131.247.136.111");
  setupParam(&tx_frame_id,node,"tx_frame_id","r2sonic_tx");
  setupParam(&rx_frame_id,node,"rx_frame_id","r2sonic_rx");
}

R2SonicNode::R2SonicNode():
  Node("r2sonic_node")
{
  parameters_.init(this);
  msg_buffer_.dectections.pub =
      this->create_publisher<acoustic_msgs::msg::SonarDetections>(parameters_.topics.detections,100);
}

void R2SonicNode::publish(packets::BTH0 r2_packet){
  msg_buffer_.dectections.lock();

  conversions::bth02SonarDetections(&msg_buffer_.dectections.msg,r2_packet);
  msg_buffer_.dectections.msg.header.frame_id = getParams().tx_frame_id;
  msg_buffer_.dectections.pub->publish(msg_buffer_.dectections.msg);

  msg_buffer_.dectections.unlock();
}

NS_FOOT
