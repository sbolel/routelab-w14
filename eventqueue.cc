#include "eventqueue.h"

void EventQueue::InsertEvent(Event *e)
{
  q.push(e);
}

Event * EventQueue::GetEarliestEvent()
{
  Event *e;
  e=q.front();
  q.pop();
  return e;
}


ostream & EventQueue::Print(ostream &os) const
{
  os <<"EventQueue(eventlist={";
  for (priority_queue<Event *, deque<Event *>, CompareEvents>::const_iterator i=q.begin();
       i!=q.end(); ++i) {
    os<<**i<<", ";
  }
  os << "})";
  return os;
}

