#ifndef _messages
#define _messages

#include <iostream>

class RoutingMessage {
 public:
  ostream & Print(ostream &os) const;
};

inline ostream & operator<<(ostream &os, const RoutingMessage &m) { return m.Print(os);}

#endif
