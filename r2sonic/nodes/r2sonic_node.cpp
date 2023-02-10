#include <r2sonic/datatype_receiver.hpp>
#include <r2sonic/r2sonic_node.hpp>

int main(int argc, char *argv[])
{
  rclcpp::init(argc, argv);

  auto node = std::make_shared<r2sonic::R2SonicNode>();

  r2sonic::DatatypeReceiver<r2sonic::packets::BTH0> bth0_rec(node.get());
  std::thread th([&] { bth0_rec.receive(node->getParams().interface_ip,node->getParams().ports.bathy); });

  rclcpp::spin(node);
  rclcpp::shutdown();

  th.join();
}
