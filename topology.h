#ifndef _topology
#define _topology

#include "node.h"
#include "link.h"

#include <deque>

class Topology
{
 private:
  deque<Node*> nodes;
  deque<Link*> links;
  
 public:
  Topology();
  virtual ~Topolog();

  Node *FindMatchingNode(const Node *n);

  void AddNode(const Node *n);
  void DeleteNode(const Node *n);
  void ChangeNode(const Node *n);

  Node *FindMatchingLink(const Link *l);

  void AddLink(const Link *n);
  void DeleteLink(const Link *n);
  void ChangeLink(const Link *n);

  void DrawTopology() const;

  ostream & Print(ostream &os) const;
}  ;

inline ostream & operator<<(ostream &os, const Topology &t) { return t.Print(os);}

#endif

