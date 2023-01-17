#pragma once

#include <rclcpp/rclcpp.hpp>
#include <r2sonic/packets/all.hpp>
#include <package_defs.hpp>
#include <conversions.hpp>
#include <mutex>

NS_HEAD

class R2SonicNode : public rclcpp::Node
{
public:
  R2SonicNode();
  void publish(packets::BTH0 r2_packet);

  struct Parameters{
    struct{
      std::string detections;
      std::string bth0;
    } topics;
    struct{
      int bathy;
    } ports;
    std::string sonar_ip;
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
  struct{
    msg_mtx<acoustic_msgs::msg::SonarDetections> dectections;
  } msg_buffer_;

};


NS_FOOT
