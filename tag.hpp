#ifndef _TAG_HPP
#define _TAG_HPP

#include <string>
#include <map>
#include <list>
#include <iostream>
#include "elem.hpp"

typedef std::string tag_name_t;
typedef std::map<std::string, std::string> attr_list_t;
typedef std::list<elem_t *> content_list_t;
class tag_t : public elem_t {
  tag_name_t name;
  attr_list_t attrs;
  content_list_t content;
public:
  void set_name(const std::string& name) { this->name = name; }
  virtual void dump() {
    std::cout << name << "\n";
    for (auto itr : content) {
      itr->dump();
    }
  }
};

#endif // _TAG_HPP
