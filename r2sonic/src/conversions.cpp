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
    ping_info_msg->sample_rate = h0_pkt.body()->RxSampleRate.get();
    auto num_beams = h0_pkt.body()->Beams.get();
    ping_info_msg->tx_beamwidths.resize(num_beams);
    ping_info_msg->rx_beamwidths.resize(num_beams);
    for(size_t i = 0; i<num_beams ; i++){
      ping_info_msg->tx_beamwidths[i] =  h0_pkt.body()->TxBeamwidthVert;
      ping_info_msg->rx_beamwidths[i] =  h0_pkt.body()->TxBeamwidthHoriz;
    }
  }
  void bth02SonarDetections(acoustic_msgs::msg::SonarDetections * detections_msg,
                            const packets::BTH0 & bth0_pkt){
    auto num_beams = bth0_pkt.h0().body()->Beams.get();

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
    return;

  }

  void packet2RawPacket(r2sonic_interfaces::msg::RawPacket *raw_packet_msg, const packets::Packet * pkt){
    raw_packet_msg->data.resize(pkt->getSize());
    raw_packet_msg->data.assign(pkt->startBit(),pkt->end());
  }

  bool aid02RawAcousticImage(acoustic_msgs::msg::RawSonarImage *sonar_image, const packets::AID0 &aid0_pkt){
    if(aid0_pkt.isFirstInSeries()){
      h02Header(&sonar_image->header,aid0_pkt.h0());
      h02PingInfo(&sonar_image->ping_info,aid0_pkt.h0());
      sonar_image->ping_info.ping_no = aid0_pkt.h0().body()->PingNumber.get();
      sonar_image->image.dtype = acoustic_msgs::msg::SonarImageData::DTYPE_UINT8;
      sonar_image->sample0 = 0;
      sonar_image->image.beam_count = aid0_pkt.h0().body()->Beams.get();

      auto total_beams = aid0_pkt.h0().body()->Beams.get();

      sonar_image->tx_delays.resize(total_beams);
      sonar_image->tx_angles.resize(total_beams);
      sonar_image->rx_angles.resize(total_beams);
      for(size_t i = 0 ; i < total_beams ; i++){
        sonar_image->tx_delays[i] = 0;
        sonar_image->tx_angles[i] = aid0_pkt.h0().body()->TxSteeringVert.get();
        sonar_image->rx_angles[i] = aid0_pkt.a1().BeamAngle(i)->get();
      }

      return false;

    }


    if(aid0_pkt.m0().exists()){
      // exit if we are on the wrong ping
      if(sonar_image->ping_info.ping_no != aid0_pkt.m0().body()->PingNumber.get()){
        return false;
      }

      auto m0 = aid0_pkt.m0();


      // initialize on first message.
      auto total_bins = m0.body()->TotalBins.get();
      auto first_bin = m0.body()->FirstBin.get();
      auto bins = m0.body()->Bins.get();
      auto beams = m0.body()->Beams.get();
      auto total_beams = m0.body()->TotalBeams.get();
      auto first_beam = m0.body()->FirstBeam.get();
      auto total_samples = m0.body()->TotalSamples.get();

      size_t data_size = total_bins*total_beams*sizeof(uint8_t);

      if(sonar_image->image.data.size()!=data_size){

        sonar_image->samples_per_beam = total_bins;
        sonar_image->image.data.resize(data_size);
        std::fill(sonar_image->image.data.begin(), sonar_image->image.data.end(), 0.0);
      }

      for(auto beam_idx = first_beam; beam_idx<(first_beam+beams); beam_idx++){
        for(auto bin_idx = first_bin; bin_idx < (first_bin+bins); bin_idx ++){
          //auto data_idx = int(beam_idx)*int(cols)+int(beam_idx);
          auto data_idx = int(bin_idx)+int(total_beams)*beam_idx;
          auto data_ptr = &reinterpret_cast<uint8_t*>(sonar_image->image.data.data())[data_idx];
          uint8_t mag = m0.magnitude(beam_idx,bin_idx)->get();
          *data_ptr = mag;
        }
      }
//      for(size_t i = 0; i<sonar_image->image.data.size() ; i++){
//        auto data_ptr = &reinterpret_cast<uint8_t*>(sonar_image->image.data.data())[i];
//        *data_ptr = 255;//m0.magnitude(beam_idx,bin_idx)->get();
//      }

      if(first_bin+bins >= total_bins){
        auto sampling_rate_scale = double(total_bins) / double(total_samples);
        sonar_image->ping_info.sample_rate *= 1;
        return true;
      }

    }
    return false;
  }
}
NS_FOOT
