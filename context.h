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

  void DrawShortestPathTree(const Node *node) const;

  void DispatchEvent(Event *event);

  ostream &Print(ostream &os) const;

};

inline ostream & operator<<(ostream &os, const SimulationContext &s)
{ return s.Print(os); }



  


#endif
