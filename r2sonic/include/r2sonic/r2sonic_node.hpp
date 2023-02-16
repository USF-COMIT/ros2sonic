#pragma once
#include "package_defs.hpp"
#include <rclcpp/rclcpp.hpp>
#include <r2sonic/packets/all.hpp>
#include <package_defs.hpp>
#include <conversions.hpp>
#include <mutex>
#include <r2sonic_interfaces/msg/raw_packet.hpp>
#include <boost/asio.hpp>
#include <r2sonic/packets/cmd_packet.hpp>

NS_HEAD

/*!
 * \brief The rclcpp::Node representing the connection between ROS and the R2Sonic Unit
 */
class R2SonicNode : public rclcpp::Node
{
public:
  R2SonicNode();
//  void publish(packets::Packet & r2_packet);
  /*!
   * \brief Publishes all ros2 messages corresponding to a received
   * BTH0 Packet.
   * \param r2_packet a r2sonic::packets::BTH0 packet to be converted
   * to corresponding ros2 packets and published
   */
  void publish(packets::BTH0 & r2_packet);

  void publish(packets::AID0 & aid0_packet);

  /*!
   * \brief a Structure that corresponds to the parameters advertised
   * by the R2SonicNode class.
   */
  struct Parameters{
    struct Topics{
      std::string detections;
      std::string bth0;
      std::string aid0;
    } topics;
    struct Ports{
      int bathy;
      int acoustic_image;
    } ports;
    std::string sonar_ip;
    std::string interface_ip;
    std::string tx_frame_id;
    std::string rx_frame_id;
    /*!
     * \brief declares all the parameters and initialized all the stored variables
     * within the struct
     * \param node  A pointer or reference to the node you want to use to
     * initialize the parameters.
     */
    void init(rclcpp::Node * node);
  };

  const Parameters & getParams(){return parameters_;}

protected:

  Parameters parameters_;

  template <typename T>
  struct msg_mtx{
    T msg;
    std::shared_ptr< rclcpp::Publisher<T> > pub;
    std::mutex mtx;
    void lock(){mtx.lock();}
    void unlock(){mtx.unlock();}
  };
  struct MsgBuffer{
    msg_mtx<acoustic_msgs::msg::SonarDetections> dectections;
    msg_mtx<r2sonic_interfaces::msg::RawPacket> bth0;
  } msg_buffer_;

  bool shouldAdvertise(std::string topic);
  bool shouldPublish(rclcpp::PublisherBase::SharedPtr pub);

};


NS_FOOT
