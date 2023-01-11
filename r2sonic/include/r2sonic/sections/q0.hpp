#pragma once
#include <sections/sections_defs.hpp>

SECTIONS_NS_HEAD

/// \todo implement
class Q0 : public Section{
public:
  using Section::Section;  // default to parent constructor
  bool typeMatches(){
    return isType("Q0");
  }

}__attribute__((packed));

SECTIONS_NS_FOOT

