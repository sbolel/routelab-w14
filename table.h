#ifndef _table
#define _table


#include <iostream>

class Table {
  // Students should write this class

 public:
  ostream & Print(ostream &os) const;
};

inline ostream & operator<<(ostream &os, const Table &t) { return t.Print(os);}

#endif
