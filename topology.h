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

  deque<NODE*>::iterator FindMatchingNodeIt(const NODE *n);
  deque<LINK*>::iterator FindMatchingLinkIt(const LINK *l);
  
 public:
  Topology();
  virtual ~Topology();

  NODE *FindMatchingNode(const NODE *n);

  void AddNode(NODE *n);
  void DeleteNode(const NODE *n);
  void ChangeNode(const NODE *n);

  LINK *FindMatchingLink(const LINK *l);

  void AddLink(LINK *n);
  void DeleteLink(const LINK *n);
  void ChangeLink(const LINK *n);

  void DrawTopology() const;

  ostream & Print(ostream &os) const;
}  ;

template <class NODE, class LINK>
inline ostream & operator<<(ostream &os, const Topology<NODE,LINK> &t) { return t.Print(os);};


template <class NODE, class LINK>
Topology<NODE,LINK>::Topology()
{};

template <class NODE, class LINK>
Topology<NODE,LINK>::~Topology()
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
deque<NODE*>::iterator Topology<NODE,LINK>::FindMatchingNodeIt(const NODE *n)
{
  for (deque<NODE*>::iterator i=nodes.begin();
	   i!=nodes.end(); ++i) { 
    if ((**i).Matches(*n)) {
      return i;
    }
  }
  return nodes.end();
};

template <class NODE, class LINK>
NODE * Topology<NODE,LINK>::FindMatchingNode(const NODE *n)
{
  deque<NODE*>::iterator i=FindMatchingNodeIt(n);
  if (i!=nodes.end()) { 
    return *i;
  } else { 
    return 0;
  }
};



template <class NODE, class LINK>
deque<LINK*>::iterator Topology<NODE,LINK>::FindMatchingLinkIt(const LINK *l)
{
  for (deque<LINK*>::iterator i=links.begin();
	   i!=links.end(); ++i) { 
    if ((**i).Matches(*l)) {
      return i;
    }
  }
  return links.end();
};

template <class NODE, class LINK>
LINK *Topology<NODE,LINK>::FindMatchingLink(const LINK *l)
{
  deque<LINK*>::iterator i=FindMatchingLinkIt(l);
  if (i!=links.end()) { 
    return *i;
  } else { 
    return 0;
  }
};

template <class NODE, class LINK>
void Topology<NODE,LINK>::AddNode(NODE *n)
{
  if (FindMatchingNode(n)) {
    ChangeNode(n);
  }  else {
    nodes.push_back(n);
  }
};
  
template <class NODE, class LINK>
void Topology<NODE,LINK>::DeleteNode(const NODE *n)
{
  deque<NODE*>::iterator i=FindMatchingNodeIt(n);
  if (i!=nodes.end()) { 
    delete *i;
    nodes.erase(i);
  }
};

template <class NODE, class LINK>
void Topology<NODE,LINK>::ChangeNode(const NODE *n)
{
  deque<NODE*>::iterator i=FindMatchingNodeIt(n);
  if (i!=nodes.end()) { 
    **i=*n;
  }
};

template <class NODE, class LINK>
void Topology<NODE,LINK>::AddLink(LINK *n) 
{
  if (FindMatchingLink(l)) {
    ChangeLink(l);
  }  else {
    links.push_back(l);
  }
};

template <class NODE, class LINK>
void Topology<NODE,LINK>::DeleteLink(const LINK *l)
{
  deque<LINK*>::iterator i=FindMatchingLinkIt(l);
  if (i!=links.end()) { 
    delete *i;
    links.erase(i);
  }
};


template <class NODE, class LINK>
void Topology<NODE,LINK>::ChangeLink(const LINK *n)
{
  deque<LINK*>::iterator i=FindMatchingLinkIt(l);
  if (i!=links.end()) { 
    **i=*l;
  }
};


template <class NODE, class LINK>
void Topology<NODE,LINK>::DrawTopology() const
{
  
}

#endif

