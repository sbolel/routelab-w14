#ifndef _table
#define _table


#include <iostream>

#if defined(GENERIC)
class Table {
  // Students should write this class

 public:
  ostream & Print(ostream &os) const;
};
#endif


#if defined(LINKSTATE)
class Table {
  // Students should write this class

 public:
  ostream & Print(ostream &os) const;
};
#endif

#if defined(DISTANCEVECTOR)
class Table {

 public:
  ostream & Print(ostream &os) const;
};
#endif

inline ostream & operator<<(ostream &os, const Table &t) { return t.Print(os);}

#endif
