#include "event.h"
#include "node.h"
#include "link.h"
#include "topology.h"
#include "context.h"


Event::Event(double t, EventType e, void *h, void *d)
  timestamp(t), type(e), handler(h), data(d)
{}

void Event::Dispatch()
{
  switch (type) { 
  case ADD_NODE:
    ((Topology*)handler)->AddNode((Node*)data);
    break;
  case DELETE_NODE:
    ((Topology*)handler)->DeleteNode((Node*)data);
    break;
  case ADD_LINK:
    ((Topology*)handler)->AddLink((Link*)data);
    break;
  case DELETE_LINK:
    ((Topology*)handler)->DeleteLink((Link*)data);
    break;
  case CHANGE_NODE:
    ((Topology*)handler)->ChangeNode((Node*)data);
    break;
  case CHANGE_LINK:
    ((Topology*)handler)->ChangeLink((Link*)data);
    break;
  case ROUTING_MESSAGE_ARRIVAL:
    ((Node*)handler)->ProcessIncomingRoutingMessage((RoutingMessage*)data);
    break;
  default:
    cerr <<"Unknown event type\n";
    exit(-1);
  }
}


ostream & Event::Print(ostream &os) const
{
  os <<"Event(type="<<
    type==ADD_NODE ? "ADD_NODE" :
    type==DELETE_NODE ? "DELETE_NODE" :
    type==ADD_LINK ? "ADD_LINK" :
    type==DELETE_LINK ? "DELETE_LINK" :
    type==CHANGE_NODE ? "CHANGE_NODE" :
    type==CHANGE_LINK ? "CHANGE_LINK" :
    type==ROUTING_MESSAGE_ARRIVAL ? "ROUTING_MESSAGE_ARRIVAL" :
    "UNKNOWN" << ", ";
  switch (type) { 
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
}


void Event::Disassociate()
{
  handler=0;
  data=0;
}

virtual Event::~Event()
{
  if (handler) { delete handler;}
  if (data) { delete data;}
}

bool Event::IsLater(const Event *rhs)
{
  return timestamp>rhs.timestamp;
}
