#include "topology.h"

template <class NODE, class LINK>
Topology<NODE,LINK>::Topology()
{};

template <class NODE, class LINK>
Topology::~Topology()
{
  for (deque<NODE*>::iterator i=nodes.begin();
	   i!=nodes.end(); ++i) { 
    delete *i;
  }
  nodes.clear();
  for (deque<LINK*>::iterator i=links.begin();
	   i!=links.end(); ++i) { 
    delete *i;
  }
  links.clear();
};

template <class NODE, class LINK>
deque<NODE*>::iterator Topology::FindMatchingNodeIt(const NODE &n)
{
  for (deque<NODE*>::iterator i=nodes.begin();
	   i!=nodes.end(); ++i) { 
    if ((**i).Matches(n)) {
      return i;
    }
  }
  return nodes.end();
};

template <class NODE, class LINK>
NODE *Topology::FindMatchingNode(const NODE &n)
{
  deque<NODE*>::iterator i=FindMatchingNodeIt(n);
  if (i!=nodes.end()) { 
    return *i;
  } else { 
    return 0;
  }
};



template <class NODE, class LINK>
deque<LINK*>::iterator *Topology::FindMatchingLinkIt(const LINK &l)
{
  for (deque<LINK*>::iterator i=links.begin();
	   i!=links.end(); ++i) { 
    if ((**i).Matches(l)) {
      return i;
    }
  }
  return links.end();
};

template <class NODE, class LINK>
Link *Topology::FindMatchingLink(const LINK &l)
{
  deque<LINK*>::iterator i=FindMatchingLinkIt(l);
  if (i!=links.end()) { 
    return *i;
  } else { 
    return 0;
  }
};

template <class NODE, class LINK>
void Topology::AddNode(NODE *n)
{
  if (FindMatchingNode(n)) {
    ChangeNode(n);
  }  else {
    nodes.push_back(n);
  }
};
  
template <class NODE, class LINK>
void Topology::DeleteNode(const NODE *n)
{
  deque<NODE*>::iterator i=FindMatchingNodeIt(n);
  if (i!=nodes.end()) { 
    delete *i;
    nodes.erase(i);
  }
};

template <class NODE, class LINK>
void Topology::ChangeNode(const NODE *n)
{
  deque<NODE*>::iterator i=FindMatchingNodeIt(n);
  if (i!=nodes.end()) { 
    **i=*n;
  }
};

template <class NODE, class LINK>
void Topology::AddLink(const LINK *n) 
{
  if (FindMatchingLink(l)) {
    ChangeLink(l);
  }  else {
    links.push_back(l);
  }
};

template <class NODE, class LINK>
void Topology::DeleteLink(const LINK *l)
{
  deque<LINK*>::iterator i=FindMatchingLinkIt(l);
  if (i!=links.end()) { 
    delete *i;
    links.erase(i);
  }
};


template <class NODE, class LINK>
void Topology::ChangeLink(const LINK *n)
{
  deque<LINK*>::iterator i=FindMatchingLinkIt(l);
  if (i!=links.end()) { 
    **i=*l;
  }
};


template <class NODE, class LINK>
void Topology::DrawTopology() const
{
  
}

  
