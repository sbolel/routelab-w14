#ifndef _eventqueue
#define _eventqueue

#include <queue>
#include <iostream>
#include "event.h"


class EventQueue {
 private:
  priority_queue<Event *,deque<Event *>,CompareEvents> q;
 public:
  void   InsertEvent(Event *e);
  Event *GetEarliestEvent();

  ostream &Print(ostream &os) const;
};

inline ostream & operator<<(ostream &os, const EventQueue &e) { return e.Print(os);}


#endif
