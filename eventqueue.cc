#include "eventqueue.h"


void EventQueue::PostEvent(Event *e) {
  q.push(e);
}

Event * EventQueue::GetEarliestEvent() {
  if (q.size()>=1) {
    Event *e=q.top();
    q.pop();
    return e;
  } else { 
    return 0;
  }
}

EventQueue::~EventQueue() {
  Event *e;
  while ((e=GetEarliestEvent())) {
    delete e;
  }
}

ostream & EventQueue::Print(ostream &os) const
{
  priority_queue<Event *, deque<Event *>, CompareEvents>::const_iterator i;
  os <<"EventQueue(eventlist={";
  for ( i=q.begin();
       i!=q.end(); ++i) {
    os<<**i<<", ";
  }
  os << "})";
  return os;
}

