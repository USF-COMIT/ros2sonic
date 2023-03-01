#include "conversions.hpp"
NS_HEAD
namespace conversions{
  void h02Header(std_msgs::msg::Header *header, const sections::H0 &h0_pkt){
    header->stamp.sec = h0_pkt.body()->TimeSeconds;
    header->stamp.nanosec = h0_pkt.body()->TimeNanoseconds;
  }
  void h02PingInfo(acoustic_msgs::msg::PingInfo * ping_info_msg,
                   const sections::H0 & h0_pkt){
    ping_info_msg->frequency=h0_pkt.body()->Frequency.get();
    ping_info_msg->sound_speed = h0_pkt.body()->SoundSpeed.get();

    auto num_beams = h0_pkt.body()->Points.get();
    ping_info_msg->tx_beamwidths.resize(num_beams);
    ping_info_msg->rx_beamwidths.resize(num_beams);
    for(size_t i = 0; i<num_beams ; i++){
      ping_info_msg->tx_beamwidths[i] =  h0_pkt.body()->TxBeamwidthVert;
      ping_info_msg->rx_beamwidths[i] =  h0_pkt.body()->TxBeamwidthHoriz;
    }
  }
  void bth02SonarDetections(acoustic_msgs::msg::SonarDetections * detections_msg,
                            const packets::BTH0 & bth0_pkt){
    auto num_beams = bth0_pkt.h0().body()->Points.get();

    h02PingInfo(&detections_msg->ping_info, bth0_pkt.h0());
    h02Header(&detections_msg->header, bth0_pkt.h0());

    detections_msg->two_way_travel_times.resize(num_beams);
    detections_msg->tx_delays.resize(num_beams);
    detections_msg->intensities.resize(num_beams);
    detections_msg->tx_angles.resize(num_beams);
    detections_msg->rx_angles.resize(num_beams);

    u32 angle_sum = 0;
    if(bth0_pkt.a2().exists()){
      angle_sum = bth0_pkt.a2().body()->AngleFirst;
    }
    for(size_t i = 0; i<num_beams ; i++){
      detections_msg->two_way_travel_times[i] = bth0_pkt.r0().getScaledRange(i);
      detections_msg->tx_delays[i]= 0;
      if(bth0_pkt.i1().exists()){
        detections_msg->intensities[i]= bth0_pkt.i1().getScaledIntensity(i);
      }else{
        detections_msg->intensities[i]= 0;
      }
      detections_msg->tx_angles[i] = bth0_pkt.h0().body()->TxSteeringVert;
      if(bth0_pkt.a0().exists()){
        auto first = bth0_pkt.a0().body()->AngleFirst.get();
        auto last  = bth0_pkt.a0().body()->AngleLast.get();
        auto delta = (last - first)/num_beams;
        detections_msg->rx_angles[i] = first + delta * i;
      }
      if(bth0_pkt.a2().exists()){
        detections_msg->rx_angles[i] = angle_sum*bth0_pkt.a2().body()->ScalingFactor.get();
        angle_sum += bth0_pkt.a2().AngleStep(i)->get();
      }

    }

  }

  void packet2RawPacket(r2sonic_interfaces::msg::RawPacket *raw_packet_msg, const packets::Packet * pkt){
    raw_packet_msg->data.resize(pkt->getSize());
    raw_packet_msg->data.assign(pkt->startBit(),pkt->end());
  }

  void aid02RawAcousticImage(acoustic_msgs::msg::RawSonarImage *sonar_image, const packets::AID0 &aid0_pkt){
    if(aid0_pkt.isFirstInSeries()){
      h02Header(&sonar_image->header,aid0_pkt.h0());
      sonar_image->ping_info.ping_no = aid0_pkt.h0().body()->PingNumber.get();
      size_t data_size = aid0_pkt.m0().body()->TotalBins * sizeof(u8);
      sonar_image->image.data.resize(data_size);
      sonar_image->image.dtype = acoustic_msgs::msg::SonarImageData::DTYPE_UINT8;
    }
    if(sonar_image->ping_info.ping_no == aid0_pkt.m0().body()->PingNumber){
      auto m0 = &aid0_pkt.m0();
      //m0->magnitude()
    }
  }
}
NS_FOOT
