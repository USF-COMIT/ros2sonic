#pragma once

#include "sections_defs.hpp"
#include <stdexcept>

SECTIONS_NS_HEAD

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
   * \brief returns a chararacter array of length 2 saying the nominal type
   * of the section class
   * \return
   */
  virtual char * nominalType() = 0;
  /*!
   * \brief Return true if your type matches the header
   * \return true if your type matches the header
   */
  bool isType(){
    return strncmp(info()->name,nominalType(),2) == 0;
  }
  /*!
   * \brief states weather that section exists where expected
   * \return true if the requested section exists
   */
  bool exists(){
    return isType();
  }
  /*!
   * \brief getSize returns the size of the message in system-endian order
   * \note this function will return 0 if your type doesn't match SectionInfo.name
   * \return the size of the section in system endian order.  Returns 0 if
   * your type doesn't match indicating a seciton doesn't exist.
   */
  u16 getSize(){
    if( !exists() ){
      return 0;
    }
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
  void existanceErrorCheck(){
    if(!exists()){
      throw std::out_of_range ("requested optional section was not in this packet");
    }
  }
  char * start_bit_; //!< a pointer to the first bit in the message
};

SECTIONS_NS_FOOT
