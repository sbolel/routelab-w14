#include "event.h"


Event::Event(double t, EventType e, void *h, void *d) :
  timestamp(t), etype(e), handler(h), data(d)
{}


void Event::Dispatch()
{
  switch (etype) { 
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
  os <<"Event(timestamp="<<timestamp<<", etype="<<
    (etype==ADD_NODE ? "ADD_NODE" :
    etype==DELETE_NODE ? "DELETE_NODE" :
    etype==ADD_LINK ? "ADD_LINK" :
    etype==DELETE_LINK ? "DELETE_LINK" :
    etype==CHANGE_NODE ? "CHANGE_NODE" :
    etype==CHANGE_LINK ? "CHANGE_LINK" :
    etype==ROUTING_MESSAGE_ARRIVAL ? "ROUTING_MESSAGE_ARRIVAL" :
   "UNKNOWN") << ", ";
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
}


void Event::Disassociate()
{
  handler=0;
  data=0;
}


Event::~Event()
{
  if (data) { 
    switch (etype) { 
    case ADD_NODE:
    case DELETE_NODE:
    case CHANGE_NODE:
      delete (Node *) data;
      break;
    case ADD_LINK:
    case DELETE_LINK:
    case CHANGE_LINK:
      delete (Link *) data;
      break;
    case ROUTING_MESSAGE_ARRIVAL:
      delete (RoutingMessage*) data;
      break;
    default:
      cerr <<"Unknown event type\n";
      exit(-1);
    }
  }
}


bool Event::IsLater(const Event *rhs) const
{
  return timestamp>rhs->timestamp;
}



