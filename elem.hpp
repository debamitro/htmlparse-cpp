#ifndef _ELEM_HPP
#define _ELEM_HPP

#include <list>

class elem_t;
typedef std::list<elem_t *> content_list_t;
class elem_t {
public:
  virtual void dump (int level) {}
  virtual void expand () {}
  virtual content_list_t split () { return content_list_t (); }
  virtual bool is_blob () const { return true; }
};

#endif // _ELEM_HPP
