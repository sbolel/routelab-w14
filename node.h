#ifndef _node
#define _node

#include <new>
#include <iostream>


#include "table.h"
#include "messages.h"

using namespace std;

class Context;


class Node {
 private:
  unsigned number;
  Context    *context;
  double   bw;
  double   lat;

 public:
  Node(const unsigned n, Context *c, double b, double l);
  Node();
  Node(const Node &rhs);
  Node & operator=(const Node &rhs);
  virtual ~Node();

  virtual bool Matches(const Node &rhs) const;
  
  virtual void SetNumber(const unsigned n);
  virtual unsigned GetNumber() const;

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
  virtual Table *GetRoutingTable() const { return 0;};

  virtual ostream & Print(ostream &os) const;

};

inline ostream & operator<<(ostream &os, const Node &n) { return n.Print(os);}


#endif
