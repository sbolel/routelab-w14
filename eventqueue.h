#ifndef _eventqueue
#define _eventqueue

#include <deque>
#include <queue>
#include <iostream>

template <class NODE, class LINK> class Event;
template <class NODE, class LINK> struct CompareEvents;

template <class NODE, class LINK>
class EventQueue {
  typedef priority_queue<Event<NODE,LINK> *, deque<Event<NODE,LINK> *>, CompareEvents<NODE,LINK> > QTYPE;
 private:
  QTYPE q;
 public:
  virtual ~EventQueue();
  void   PostEvent(Event<NODE,LINK> *e);
  Event<NODE,LINK> *GetEarliestEvent();
  ostream &Print(ostream &os) const;
};

template <class NODE, class LINK>
inline ostream & operator<<(ostream &os, const EventQueue<NODE,LINK> &e) { return e.Print(os);}

template <class NODE, class LINK>
void EventQueue<NODE,LINK>::PostEvent(Event<NODE,LINK> *e) {
  q.push(e);
};

template <class NODE, class LINK>
Event<NODE,LINK> * EventQueue<NODE,LINK>::GetEarliestEvent() {
  if (q.size()>=1) {
    Event<NODE,LINK> *e=q.top();
    q.pop();
    return e;
  } else { 
    return 0;
  }
};

template <class NODE, class LINK>
EventQueue<NODE,LINK>::~EventQueue() {
  Event<NODE,LINK> *e;
  while ((e=GetEarliestEvent())) {
    delete e;
  }
};

template <class NODE, class LINK>
ostream & EventQueue<NODE,LINK>::Print(ostream &os) const
{
  //  QTYPE::const_iterator i;
  os <<"EventQueue(eventlist={";
  for ( i=q.begin();
       i!=q.end(); ++i) {
    os<<**i<<", ";
  }
  os << "})";
  return os;
}



#endif
