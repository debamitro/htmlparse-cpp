#ifndef _HTMLDOC_HPP
#define _HTMLDOC_HPP

#include <fstream>
#include "tag.hpp"

class htmldoc_t {
  content_list_t content;
  void populate (char * fname);
  void handle_tag (std::ifstream & fh);
public:
  htmldoc_t (char * fname) { populate(fname); }
  void dump () {
    for (auto & itr : content) {
      itr->dump(0);
    }
  }
};

#endif // _HTMLDOC_HPP
