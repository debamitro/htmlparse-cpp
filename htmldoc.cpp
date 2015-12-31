#include <fstream>
#include <sstream>
#include "htmldoc.hpp"

static void
get_tag_name_and_attrs (std::ifstream& fh, tag_t & tg) {
  std::stringstream strm; 
  while (fh.good()) {
    char c;
    fh.get(c);
    if (c == '>') {
      break;
    }
    else {
      strm << c;
    }
  }
  tg.set_name(strm.str());
}

static void
get_tag_content (std::ifstream& fh, tag_t & tg) {
  while (fh.good()) {
    char c;
    fh.get(c);
  }
}

void htmldoc_t::handle_tag (std::ifstream& fh) {
  tag_t * tg = new tag_t;
  get_tag_name_and_attrs (fh, *tg);
  get_tag_content (fh, *tg);
  content.push_back(tg);
}

void htmldoc_t::populate (char * fname) {
  std::ifstream fh(fname);
  while (fh.good()) {
    char c;
    fh.get(c);
    if (c == '<') {
      handle_tag (fh);
    }
  }
}
