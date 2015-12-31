#ifndef _BLOB_HPP
#define _BLOB_HPP

#include <string>
#include "elem.hpp"

class blob_t : public elem_t {
  std::string val;
public:
  virtual void dump() {
    std::cout << val << "\n";
  }
};

#endif // _BLOB_HPP
