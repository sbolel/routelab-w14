#ifndef _topology
#define _topology

#include "node.h"
#include "link.h"

#include <deque>


template <class NODE, class LINK>
class Topology
{
 private:
  deque<NODE*> nodes;
  deque<LINK*> links;

  deque<NODE*>::iterator *FindMatchingNodeIt(const NODE *n);
  deque<LINK*>::iterator *FindMatchingLinkIt(const LINK *l);
  
 public:
  Topology();
  virtual ~Topology();

  LINK *FindMatchingNode(const NODE *n);

  void AddNode(const NODE *n);
  void DeleteNode(const NODE *n);
  void ChangeNode(const NODE *n);

  NODE *FindMatchingLink(const LINK *l);

  void AddLink(const LINK *n);
  void DeleteLink(const LINK *n);
  void ChangeLink(const LINK *n);

  void DrawTopology() const;

  ostream & Print(ostream &os) const;
}  ;

template <class NODE, class LINK>
inline ostream & operator<<(ostream &os, const Topology<NODE,LINK> &t) { return t.Print(os);};

#endif

