#ifndef _topology
#define _topology

#include <deque>

#include "node.h"
#include "link.h"

class Topology
{
 private:
  deque<Node*> nodes;
  deque<Link*> links;

  deque<Node*>::iterator FindMatchingNodeIt(const Node *n);
  deque<Link*>::iterator FindMatchingLinkIt(const Link *l);
  
 public:
  Topology();
  virtual ~Topology();

  Node *FindMatchingNode(const Node *n);

  void AddNode(Node *n);
  void DeleteNode(const Node *n);
  void ChangeNode(const Node *n);

  Link *FindMatchingLink(const Link *l);

  void AddLink(Link *n);
  void DeleteLink(const Link *n);
  void ChangeLink(const Link *n);

  void DrawTopology() const;

  ostream & Print(ostream &os) const;
}  ;


inline ostream & operator<<(ostream &os, const Topology &t) { return t.Print(os);};


#endif

