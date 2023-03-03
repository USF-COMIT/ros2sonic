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
      std::string acoustic_image;
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

  template <typename MSG_T, typename STORAGE_T>
  struct msgMtx_{
    STORAGE_T msg;
    std::shared_ptr< rclcpp::Publisher<MSG_T> > pub;
    std::mutex mtx;
    void lock(){mtx.lock();}
    void unlock(){mtx.unlock();}
  };

  template <typename T>
  using msgMtx = msgMtx_<T, T>;

  template <typename T>
  using msgMap = std::map<u32, T>;  //!< This typedef is useful for messages that need to be assmebled from multiple packets

  template <typename T>
  using msgMtxMap = msgMtx_< T, msgMap<T> >;

  struct MsgBuffer{
    msgMtx<acoustic_msgs::msg::SonarDetections> dectections;
    msgMtx<r2sonic_interfaces::msg::RawPacket> bth0;
    msgMtxMap<acoustic_msgs::msg::RawSonarImage> acoustic_image;
    msgMtx<r2sonic_interfaces::msg::RawPacket> aid0;
  } msg_buffer_;

  /*!
   * \brief removes incomplete messages from the map if they are too old based on
   * the ping_number
   * \param msg_map
   * \param ping_no
   */
  template <typename T>
  void cleanMsgMap(msgMap<T> *msg_map, u32 ping_no);
  bool shouldAdvertise(std::string topic);
  bool shouldPublish(rclcpp::PublisherBase::SharedPtr pub);

};


NS_FOOT
