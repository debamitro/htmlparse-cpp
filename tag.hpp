#ifndef _TAG_HPP
#define _TAG_HPP

#include <string>
#include <map>
#include <list>
#include <iostream>
#include "elem.hpp"

typedef std::string tag_name_t;
typedef std::map<std::string, std::string> attr_list_t;
class tag_t : public elem_t {
  tag_name_t name;
  attr_list_t attrs;
  content_list_t content;
public:
  void set_name(const std::string& name) { this->name = name; }
  const std::string & get_name() const { return this->name; }
  void add_content(elem_t * cntnt) { content.push_back(cntnt); }
  virtual void expand ();
  virtual bool is_blob () const { return false; }
  virtual void dump(int level) {
    for (int i = 0; i < level+1; i++) std::cout << " ";
    std::cout << "start tag " << name << "\n";
    for (auto itr : content) {
      itr->dump(level+1);
    }
    for (int i = 0; i < level+1; i++) std::cout << " ";
    std::cout << "end tag " << name << "\n";
  }
};

#endif // _TAG_HPP
