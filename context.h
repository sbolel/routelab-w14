#ifndef _context
#define _context

#include <new>
#include <string>
#include <iostream>
#include <stdio.h>

#include "topology.h"
#include "eventqueue.h"
#include "table.h"

class SimulationContext : public Topology, public EventQueue
{
 public:
  SimulationContext();
  virtual ~SimulationContext();

  void LoadTopology(const string &file);
  void LoadEvents(const string &file);

  void SendToNeighbors(const Node *src, const RoutingMessage *m);
  void SendToNeighbor(const Node *src, const Node *dest, const RoutingMessage *m);

  void DrawShortestPathTree(const Node *node) const;
  void WriteShortestPathTreeDot(const Node *node, const string &s) const;
  void DrawPath(const Link *l) const;
  void WritePathDot(const Node *src, const Node *dest, const string &s) const;

  ostream &DumpTable(iostream &os, const Node *src) const;

  void DispatchEvent(Event *e);

  ostream &Print(ostream &os);

};

inline ostream & operator<<(ostream &os, SimulationContext &s)
{ return s.Print(os); }



  


#endif
