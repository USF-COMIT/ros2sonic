#include <r2sonic/datatype_receiver.hpp>

int main(int argc, char *argv[])
{
  r2sonic::DatatypeReceiver rec;
  rec.receive("131.247.136.111","65500");
}
