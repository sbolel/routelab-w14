#ifndef _context
#define _context

#include <new>
#include <string>
#include <iostream>

#include "topology.h"
#include "eventqueue.h"
#include "table.h"


template <class NODE, class LINK>
class Context : public  Topology<NODE,LINK>, public EventQueue
{
 public:
  Context();
  virtual ~Context();

  void LoadTopology(const string &file);
  void LoadEvents(const string &file);

  void DrawShortestPathTree(const NODE *node) const;

  void DispatchEvent(Event *event);
};

#endif
