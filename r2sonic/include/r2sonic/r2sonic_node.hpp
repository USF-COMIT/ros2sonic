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
   * \param Publishes all ros2 messages corresponding to a received
   * BTH0 Packet.
   */
  void publish(packets::BTH0 & r2_packet);

  /*!
   * \brief Publishes all ros2 messages corresponding to a received
   * AID0 Packet.
   * \param Publishes all ros2 messages corresponding to a received
   * AID0 Packet.
   */
  void publish(packets::AID0 & aid0_packet);

  /*!
   * \brief a Structure that corresponds to the parameters advertised
   * by the R2SonicNode class.   All params assoicated with this struct
   * will have the same structure struct.  Example: topics.detections member
   * mapps to param "topics/detections"
   */
  struct Parameters{
    struct Topics{
      std::string detections;       //!< detections topic with type marine_acoustic_msgs::RawSonarDetections
      std::string bth0;             //!< raw bth0 topic r2sonic_interfaces::RawPacket
      std::string acoustic_image;   //!< acoustic image topic with type marine_acoustic_msgs::RawSonarImage
      std::string aid0;             //!< raw aid0 topic with type r2sonic_interfaces::RawPacket
    } topics; //!< a container for the topics.
    struct Ports{
      int bathy;                    //!< the port to listen to bathy
      int acoustic_image;           //!< the port to listen for acoustic image data
    } ports;  //!< a container for the ports
    std::string sonar_ip;           //!< the ip address to send commands to the sonar
    std::string interface_ip;       //!< the interface you want to listen on (0.0.0.0 to listen on all)
    std::string tx_frame_id;        //!< the frame ID of the acoustic center of the transmitter
    std::string rx_frame_id;        //!< the frame ID of the acoustic center of the receiver
    /*!
     * \brief declares all the parameters and initialized all the stored variables
     * within the struct
     * \param node  A pointer or reference to the node you want to use to
     * initialize the parameters.
     */
    void init(rclcpp::Node * node);
  };

  /*!
   * \brief gets a referenence to the r2sonic::R2SonicNode::Parameters
   * \return the parameters associated with the node
   */
  const Parameters & getParams(){return parameters_;}

protected:

  Parameters parameters_;  //!< potected storage for parametrs

  /*!
   * \brief a colleciton of rosmessageg publisher and a mutex grouped for convienence.
   */
  template <typename MSG_T, typename STORAGE_T>
  struct msgMtx_{
    STORAGE_T msg;    //!< the way you want to store the message
    std::shared_ptr< rclcpp::Publisher<MSG_T> > pub; //!< the publisher to publish the message
    std::mutex mtx;   //!< the mutex associated with the message
    void lock(){mtx.lock();}
    void unlock(){mtx.unlock();}
  };

  template <typename T>
  using msgMtx = msgMtx_<T, T>; //!< Typedef for a single message, useful if you don't need to assemble multiple packets

  template <typename T>
  using msgMap = std::map<u32, T>;  //!< This typedef is useful for messages that need to be assmebled from multiple packets

  template <typename T>
  using msgMtxMap = msgMtx_< T, msgMap<T> >; //!< Creates a msgMtx with a map of messages for assembling multiple packets into one ros message

  /*!
   * \brief a container for the messages we want to buffer
   */
  struct MsgBuffer{
    msgMtx<marine_acoustic_msgs::msg::SonarDetections> dectections;
    msgMtx<r2sonic_interfaces::msg::RawPacket> bth0;

    msgMtx<marine_acoustic_msgs::msg::RawSonarImage> acoustic_image;
    std::map<u32,conversions::Aid02RawAiAssembler> acoustic_image_assemblers;
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
  /*!
   * \brief Holds the conditions that determine if the a tiopic should be advertised
   * \param topic the topic you want to test
   * \return true if you should advertise it
   */
  bool shouldAdvertise(std::string topic);
  /*!
   * \brief Checks to see if there are any subscribers to a topic before computing and publishing it
   * \param pub the publisher you want to check
   * \return true if you should publish on that publisher (e.g. has subscribers)
   */
  bool shouldPublish(rclcpp::PublisherBase::SharedPtr pub);

};


NS_FOOT
