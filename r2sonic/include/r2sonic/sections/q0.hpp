#pragma once
#include "sections_defs.hpp"
#include <sections/section.hpp>

SECTIONS_NS_HEAD
/*!
 * \brief section Q0: 4-bit quality flags
 */
class Q0 : public Section{
public:
  using Section::Section;  // default to parent constructor
  char * nominalType() const {
    return "Q0";
  }

}__attribute__((packed));

SECTIONS_NS_FOOT

