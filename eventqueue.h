#ifndef _eventqueue
#define _eventqueue

#include <deque>
#include <queue>
#include <iostream>

#include "event.h"

class EventQueue {
 private:
  priority_queue<Event *, deque<Event *>, CompareEvents > q;
 public:
  virtual ~EventQueue();
  void   PostEvent(Event *e);
  Event *GetEarliestEvent();
  ostream &Print(ostream &os) const;
};

inline ostream & operator<<(ostream &os, const EventQueue &e) { return e.Print(os);}



#endif
