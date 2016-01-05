#include <sstream>
#include "blob.hpp"
#include "tag.hpp"

static void
get_tag_name_and_attrs (std::stringstream& fh, tag_t & tg) {
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
get_tag_content (std::stringstream& fh, tag_t & tg) {
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
  blob_t * blb = new blob_t(strm.str());
  tg.add_content(blb);
}

static void
handle_tag (content_list_t & content, std::stringstream& strm) {
  tag_t * tg = new tag_t;
  get_tag_name_and_attrs (strm, *tg);
  get_tag_content (strm, *tg);
  content.push_back(tg);
}

content_list_t
blob_t::split () {
  std::stringstream strm(this->val);
  content_list_t cntnt;
  while (strm.good()) {
    char c;
    strm.get(c);
    if (c == '<') {
      handle_tag (cntnt,strm);
    }
  }
  return cntnt;
}
