#ifndef _event
#define _event

#include <iostream>
#include <queue>

#include "topology.h"

enum EventType { ADD_NODE, DELETE_NODE, ADD_LINK, DELETE_LINK,  
       NODE_CHANGE, LINK_CHANGE, ROUTING_MESSAGE_ARRIVAL}; 

template <class NODE, class LINK>
class Event {
 private:
  double timestamp;
  EventType etype;
  void  *handler;
  void  *data;

 public:
  Event(double t, EventType e, void *handler, void *d);
  // default copy construct and operator= is OK
  virtual ~Event();

  void Dispatch();
  void Disassociate();

  bool IsLater(const Event *rhs);

  ostream & Print(ostream &os) const;

};

template <class NODE, class LINK>
inline ostream & operator<<(ostream &os, const Event<NODE,LINK> &e) { return e.Print(os);}

template <class NODE, class LINK>
struct CompareEvents : public binary_function<Event<NODE,LINK> *,Event<NODE,LINK> *, bool> {
  inline bool operator ()(const Event<NODE,LINK> *lhs, const Event<NODE,LINK> *rhs) {
    return rhs->IsLater(lhs);
  }
};

template <class NODE, class LINK>
Event<NODE,LINK>::Event(double t, EventType e, void *h, void *d) :
  timestamp(t), etype(e), handler(h), data(d)
{};

template <class NODE, class LINK>
void Event<NODE,LINK>::Dispatch()
{
  switch (etype) { 
  case ADD_NODE:
    ((Topology<NODE,LINK>*)handler)->AddNode((NODE*)data);
    break;
  case DELETE_NODE:
    ((Topology<NODE,LINK>*)handler)->DeleteNode((NODE*)data);
    break;
  case ADD_LINK:
    ((Topology<NODE,LINK>*)handler)->AddLink((LINK*)data);
    break;
  case DELETE_LINK:
    ((Topology<NODE,LINK>*)handler)->DeleteLink((LINK*)data);
    break;
  case CHANGE_NODE:
    ((Topology<NODE,LINK>*)handler)->ChangeNode((NODE*)data);
    break;
  case CHANGE_LINK:
    ((Topology<NODE,LINK>*)handler)->ChangeLink((LINK*)data);
    break;
  case ROUTING_MESSAGE_ARRIVAL:
    ((NODE*)handler)->ProcessIncomingRoutingMessage((RoutingMessage*)data);
    break;
  default:
    cerr <<"Unknown event type\n";
    exit(-1);
  }
};


template <class NODE, class LINK>
ostream & Event<NODE,LINK>::Print(ostream &os) const
{
  os <<"Event(etype="<<
    etype==ADD_NODE ? "ADD_NODE" :
    etype==DELETE_NODE ? "DELETE_NODE" :
    etype==ADD_LINK ? "ADD_LINK" :
    etype==DELETE_LINK ? "DELETE_LINK" :
    etype==CHANGE_NODE ? "CHANGE_NODE" :
    etype==CHANGE_LINK ? "CHANGE_LINK" :
    etype==ROUTING_MESSAGE_ARRIVAL ? "ROUTING_MESSAGE_ARRIVAL" :
    "UNKNOWN" << ", ";
  switch (etype) { 
  case ADD_NODE:
  case DELETE_NODE:
  case CHANGE_NODE:
    os << *((Node*)data);
    break;
  case ADD_LINK:
  case DELETE_LINK:
  case CHANGE_LINK:
    os << *((Link*)data);
    break;
  case ROUTING_MESSAGE_ARRIVAL:
    os <<*((RoutingMessage*)data);
    break;
  default:
    os << "Unknown()";
  }
  os <<")";
  return os;
};

template <class NODE, class LINK>
void Event<NODE,LINK>::Disassociate()
{
  handler=0;
  data=0;
};

template <class NODE, class LINK>
Event<NODE,LINK>::~Event()
{
  if (handler) { delete handler;}
  if (data) { delete data;}
};

template <class NODE, class LINK>
bool Event<NODE,LINK>::IsLater(const Event<NODE,LINK> *rhs)
{
  return timestamp>rhs.timestamp;
};


#endif
