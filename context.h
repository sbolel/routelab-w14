#ifndef _context
#define _context

#include <new>
#include <string>
#include <iostream>

#include "topology.h"
#include "eventqueue.h"
#include "table.h"

class Context {
 private:
  Topology   topology;
  EventQueue eventqueue;

 public:
  Context();
  virtual ~Context();

  void LoadTopology(const string &file);
  void LoadEvents(const string &file);

  void DrawTopology() const;
  void DrawShortestPathTree(const Node *node) const;

  void PostEvent(Event *event);
  Event *GetNextEvent();
}

#endif
