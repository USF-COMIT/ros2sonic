#include <r2sonic/datatype_receiver.hpp>
#include <r2sonic/r2sonic_node.hpp>

int main(int argc, char *argv[])
{
  rclcpp::init(argc, argv);

  auto node = std::make_shared<r2sonic::R2SonicNode>();

  std::vector<std::thread> threads;

  r2sonic::DatatypeReceiver<r2sonic::packets::BTH0> bth0_rec(node.get());
  threads.push_back(
    std::thread([&] { bth0_rec.receive(node->getParams().interface_ip,node->getParams().ports.bathy); })
  );

  r2sonic::DatatypeReceiver<r2sonic::packets::AID0> aid0_rec(node.get());
  threads.push_back(
    std::thread([&] { aid0_rec.receive(node->getParams().interface_ip,node->getParams().ports.acoustic_image); })
  );

  rclcpp::spin(node);
  rclcpp::shutdown();

  for(auto &th : threads){
    th.join();
  }
}
