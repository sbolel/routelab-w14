#ifndef _event
#define _event

enum { ADD_NODE, DELETE_NODE, ADD_LINK, DELETE_LINK,  
       NODE_CHANGE, LINK_CHANGE, ROUTING_MESSAGE_ARRIVAL} EventType; 

class Event {
 private:
  double timestamp;
  EventType type;
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

inline ostream & operator<<(ostream &os, const Event &e) { return e.Print(os);}

bool CompareEvents(const Event *lhs, const Event *rhs);

#endif
