#include <string>
#include <map>
#include <list>
#include <iostream>
#include <fstream>
#include <sstream>

typedef std::string tag_name_t;
typedef std::map<std::string, std::string> attr_list_t;

class elem_t {
public:
  virtual void dump() {}
};

class blob_t : public elem_t {
  std::string val;
public:
  virtual void dump() {
    std::cout << val << "\n";
  }
};

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

class htmldoc_t {
  content_list_t content;
  void populate (char * fname);
  void handle_tag (std::ifstream & fh);
public:
  htmldoc_t (char * fname) { populate(fname); }
  void dump () {
    for (auto itr : content) {
      itr->dump();
    }
  }
};

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

int main (int argc, char ** argv) {
  if (argc > 1) {
    htmldoc_t obj(argv[1]);
    std::cout << "Start dump\n";
    obj.dump();
    std::cout << "End dump\n";
  }
  return 0;
}
