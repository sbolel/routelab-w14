#ifndef _link
#define _link

#include <new>
#include <iostream>


class Context;

class Link {
  unsigned src,dest;
  Context  *context;
  double   bw;
  double   lat;
  

 public:
  Link(const unsigned s, const unsigned d, Context *c, double b, double l);
  Link();
  Link(const Link &rhs);
  Link & operator=(const Link &rhs);
  virtual ~Link();


  virtual void SetSrc(const unsigned s);
  virtual unsigned GetSrc() const;
  virtual void SetDest(const unsigned d);
  virtual unsigned GetDest() const;
  virtual void SetLatency(const double l);
  virtual double GetLatency() const;
  virtual void SetBW(const double b);
  virtual double GetBW() const;

  virtual ostream & Print(ostream &os) const;

};

inline ostream & operator<<(ostream &os, const Link &n) { return n.Print(os);}


#endif
