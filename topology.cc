#include "topology.h"

Topology::Topology()
{}

Topology::~Topology()
{
  for (deque<Node*>::iterator i=nodes.begin();
	   i!=nodes.end(); ++i) { 
    delete *i;
  }
  nodes.clear();
  for (deque<Link*>::iterator i=links.begin();
	   i!=links.end(); ++i) { 
    delete *i;
  }
  links.clear();
}

Node *Topology::FindMatchingNode(const Node &n)
{
  for (deque<Node*>::iterator i=nodes.begin();
	   i!=nodes.end(); ++i) { 
    if ((**i).Matches(n)) {
      return *i;
    }
  }
  return 0;
}

Link *Topology::FindMatchingLink(const Link &l)
{
  for (deque<Link*>::iterator i=links.begin();
	   i!=links.end(); ++i) { 
    if ((**i).Matches(l)) {
      return *i;
    }
  }
  return 0;
}

void AddNode(Node *n)
{
  if (FindMatchingNode(n)
  
  void DeleteNode(const Node *n);
  void ChangeNode(const Node *n);

  void AddLink(const Link *n);
  void DeleteLink(const Link *n);
  void ChangeLink(const Link *n);

  void DrawTopology() const;

  
