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
  setupParam(&sonar_ip,node,"sonar_ip","10.226.208.220");
  setupParam(&tx_frame_id,node,"tx_frame_id","r2sonic_tx");
  setupParam(&rx_frame_id,node,"rx_frame_id","r2sonic_rx");
}

R2SonicNode::R2SonicNode():
  Node("r2sonic_node")
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

void R2SonicNode::publish(packets::BTH0 r2_packet){
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
