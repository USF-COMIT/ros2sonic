#include <r2sonic/datatype_receiver.hpp>

int main(int argc, char *argv[])
{
  r2sonic::DatatypeReceiver rec;
  rec.receive("10.0.1.102","65500");
}
