#ifndef _node
#define _node

#include <new>
#include <iostream>


#include "table.h"

class Context;

class Node {
  double   bw;
  double   lat;
  unsigned number;
  Graph    *graph;
  

 public:
  Node(const unsigned n, double b, double l, Context *c);
  Node();
  Node(const Node &rhs);
  Node & operator=(const Node &rhs);
  virtual ~Node();

  virtual bool Matches(const Node &rhs);

  virtual void SetLatency(const double l);
  virtual double GetLatency() const;
  virtual void SetBW(const double b);
  virtual double GetBW() const;

  virtual void SendToNeighbors(const RoutingMessage &m);

  //
  // Students will override these
  //
  virtual void ProcessIncomingRoutingMessage(const RoutingMessage &m) {}
  virtual void GetRoute(const Node &destination, RoutingTableEntry *rte) {}

  virtual ostream & Print(ostream &os) const;

}

inline ostream & operator<<(ostream &os, const Node &n) { return n.Print(os);}


#endif
