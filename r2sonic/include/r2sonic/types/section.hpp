#pragma once

#include "types_defs.hpp"

TYPES_NS_HEAD

struct SectionInfo{
  char name[2];
  u16  size;
};

/*!
 * \brief a common base class for all r2 sonic message section definitions
 * \note accessors with a get* prefix will return a machine-endian value
 * accessors without the get prefix will return a reference to the raw data
 * which will be in big-endian order as per the r2sonic spec
 */
class Section{
public:
  /*!
   * \brief Section
   * \param start_bit
   */
  Section(char* start_bit){start_bit_= start_bit;}
  /*!
   * \brief getSize returns the size of the message in system-endian order
   * \return the size of the section in system endian order
   */
  u16 getSize(){
    return revPrimative<u16>(info()->size);
  }
  /*!
   * \brief info gets the reference to the common section info
   * \return a reference to the common section info
   */
  SectionInfo * info(){
    return reinterpret_cast<SectionInfo*>(start_bit_);
  }
  /*!
   * \brief end returns a pointer to one bit beyond the current section (the first bit of the next seciton)
   * \return the pointer to the next section
   */
  char * end(){
    return start_bit_+getSize();
  }

protected:
  char * start_bit_; //!< a pointer to the first bit in the message
};

TYPES_NS_FOOT
