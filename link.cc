#include "link.h"

Link::Link(const unsigned s, const unsigned d, double b, double l, Context *c) :
  src(s), dest(d), bw(b), lat(l), context(c) {}

Link::Link()
{}


Link::Link(const Link &rhs) :
  src(rhs.src), dest(rhs.dest), bw(rhs.bw), lat(rhs.lat), context(rhs.context) {}

Link & Link::operator=(const Link &rhs)
{
  return *(new (this) Link(rhs));
}

Link::~Link()
{}

void SetLatency(const double l)
{ lat=l;}

double GetLatency() const 
{ return lat; }

void SetBW(const double b)
{ bw=b;}

double GetBW() const
{ return bw;}

ostream & Link::Print(ostream &os) const
{
  os << "Link(src="<<src<<", dest="<<dest<<", bw="<<bw<<", lat="<<lat<<")";
  return os;
}
