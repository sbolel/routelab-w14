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

deque<Node*>::iterator Topology::FindMatchingNodeIt(const Node *n)
{
  for (deque<Node*>::iterator i=nodes.begin();
	   i!=nodes.end(); ++i) { 
    if ((**i).Matches(*n)) {
      return i;
    }
  }
  return nodes.end();
}

Node * Topology::FindMatchingNode(const Node *n)
{
  deque<Node*>::iterator i=FindMatchingNodeIt(n);
  if (i!=nodes.end()) { 
    return *i;
  } else { 
    return 0;
  }
}



deque<Link*>::iterator Topology::FindMatchingLinkIt(const Link *l)
{
  for (deque<Link*>::iterator i=links.begin();
	   i!=links.end(); ++i) { 
    if ((**i).Matches(*l)) {
      return i;
    }
  }
  return links.end();
}

Link *Topology::FindMatchingLink(const Link *l)
{
  deque<Link*>::iterator i=FindMatchingLinkIt(l);
  if (i!=links.end()) { 
    return *i;
  } else { 
    return 0;
  }
}

void Topology::AddNode(Node *n)
{
  if (FindMatchingNode(n)) {
    ChangeNode(n);
  }  else {
    nodes.push_back(n);
  }
}
  
void Topology::DeleteNode(const Node *n)
{
  deque<Node*>::iterator i=FindMatchingNodeIt(n);
  if (i!=nodes.end()) { 
    delete *i;
    nodes.erase(i);
  }
}

void Topology::ChangeNode(const Node *n)
{
  deque<Node*>::iterator i=FindMatchingNodeIt(n);
  if (i!=nodes.end()) { 
    **i=*n;
  }
}

void Topology::AddLink(Link *l) 
{
  if (FindMatchingLink(l)) {
    ChangeLink(l);
  }  else {
    links.push_back(l);
  }
}

void Topology::DeleteLink(const Link *l)
{
  deque<Link*>::iterator i=FindMatchingLinkIt(l);
  if (i!=links.end()) { 
    delete *i;
    links.erase(i);
  }
}


void Topology::ChangeLink(const Link *l)
{
  deque<Link*>::iterator i=FindMatchingLinkIt(l);
  if (i!=links.end()) { 
    **i=*l;
  }
}


void Topology::DrawTopology() const
{
  
}


  
