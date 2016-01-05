#include <sstream>
#include "tag.hpp"

void
tag_t::expand () {
  for (auto itr = content.begin(); itr != content.end(); itr++) {
    if ((*itr)->is_blob()) {
      content_list_t blobparts = (*itr)->split();
      for (auto & itr2 : blobparts) {
        content.insert(itr,itr2);
      }
      itr = content.erase(itr);
      itr--;
    }
  }
}
