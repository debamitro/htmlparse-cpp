#include <sstream>
#include "blob.hpp"
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

static bool
matches_from_end (std::string str, std::string pat) {
  std::string::reverse_iterator itr_str = str.rbegin();
  std::string::reverse_iterator itr_pat = pat.rbegin();
  for (; itr_pat != pat.rend(); itr_pat++, itr_str++) {
    if (*itr_str != *itr_pat) return false;
  }
  return true;
}

static void
get_tag_content (std::ifstream& fh, tag_t & tg) {
  std::stringstream strm;
  std::string tgend = "</";
  tgend += tg.get_name();
  while (fh.good()) {
    char c;
    fh.get(c);
    if (matches_from_end (strm.str(),tgend)) {
      break;
    }
    else {
      strm << c;
    }
  }
  std::string cntntstr = strm.str();
  size_t tgendlen = tgend.size();
  size_t cntntstrlen = cntntstr.size();
  cntntstr.erase(cntntstrlen-tgendlen,tgendlen);
  blob_t * blb = new blob_t(cntntstr);
  tg.add_content(blb);
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
  for (auto & itr : content) {
    itr->expand();
  }
}
