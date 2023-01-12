#include "conversions.hpp"
NS_HEAD
namespace conversions{
  void i02PingInfo(acoustic_msgs::msg::PingInfo * ping_info_msg,
                   const sections::H0 & h0_msg){
    ping_info_msg->frequency=h0_msg.body()->Frequency.get();
    ping_info_msg->sound_speed = h0_msg.body()->SoundSpeed.get();

    auto num_beams = h0_msg.body()->Points.get();
    ping_info_msg->tx_beamwidths.resize(num_beams);
    ping_info_msg->rx_beamwidths.resize(num_beams);
    for(size_t i = 0; i<num_beams ; i++){
      ping_info_msg->tx_beamwidths[i] =  h0_msg.body()->TxBeamwidthVert.get();
      ping_info_msg->rx_beamwidths[i] =  h0_msg.body()->TxBeamwidthHoriz.get();
    }
  }
  void bth02SonarDetections(acoustic_msgs::msg::SonarDetections * detections_msg,
                            const packets::BTH0 & bth0_msg){
    auto num_beams = bth0_msg.h0().body()->Points.get();
    i02PingInfo(&detections_msg->ping_info, bth0_msg.h0());

    detections_msg->two_way_travel_times.resize(num_beams);
    detections_msg->tx_delays.resize(num_beams);
    detections_msg->intensities.resize(num_beams);
    detections_msg->tx_angles.resize(num_beams);
    detections_msg->rx_angles.resize(num_beams);

    u32 angle_sum = 0;
    if(bth0_msg.a2().exists()){
      angle_sum = bth0_msg.a2().body()->AngleFirst.get();
    }
    for(size_t i = 0; i<num_beams ; i++){
      detections_msg->two_way_travel_times[i] = bth0_msg.r0().getScaledRange(i);
      detections_msg->tx_delays[i]= 0;
      if(bth0_msg.i1().exists()){
        detections_msg->intensities[i]= bth0_msg.i1().getScaledIntensity(i);
      }else{
        detections_msg->intensities[i]= 0;
      }
      detections_msg->tx_angles[i] = bth0_msg.h0().body()->TxSteeringVert.get();
      if(bth0_msg.a0().exists()){
        auto first = bth0_msg.a0().body()->AngleFirst.get();
        auto last  = bth0_msg.a0().body()->AngleLast.get();
        auto delta = (last - first)/num_beams;
        detections_msg->rx_angles[i] = first + delta * i;
      }
      if(bth0_msg.a2().exists()){
        detections_msg->rx_angles[i] = angle_sum*bth0_msg.a2().body()->ScalingFactor.get();
        angle_sum += bth0_msg.a2().AngleStep(i)->get();
      }

    }

  }
}
NS_FOOT
