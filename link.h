#ifndef _link
#define _link

#include <new>
#include <iostream>


#include "table.h"

class Context;

class Link {
  double   bw;
  double   lat;
  unsigned src,dest;
  Context  *context;
  

 public:
  Link(const unsigned s, const unsigned d, double b, double l, Context *c);
  Link();
  Link(const Link &rhs);
  Link & operator=(const Link &rhs);
  virtual ~Link();

  virtual void SetLatency(const double l);
  virtual double GetLatency() const;
  virtual void SetBW(const double b);
  virtual double GetBW() const;

  virtual ostream & Print(ostream &os) const;

}

inline ostream & operator<<(ostream &os, const Link &n) { return n.Print(os);}


#endif
