#pragma once

#include "assembly_defs.hpp"

#include <packets/all.hpp>

ASSEMBLY_NS_HEAD

template <typename T>
class Assembly{
public:
  Assembly();
  bool addPacket(T packet);

protected:
  std::vector<T> packets;
};

ASSEMBLY_NS_FOOT
