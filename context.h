#ifndef _context
#define _context

#include <new>
#include <string>
#include <iostream>

#include "topology.h"
#include "eventqueue.h"
#include "table.h"

template <class NODE, class LINK>
class SimulationContext : public Topology<NODE,LINK>, public EventQueue<NODE,LINK>
{
 public:
  SimulationContext();
  virtual ~SimulationContext();

  void LoadTopology(const string &file);
  void LoadEvents(const string &file);

  void DrawShortestPathTree(const NODE *node) const;

  void DispatchEvent(Event<NODE,LINK> *event);
};


template <class NODE, class LINK>
SimulationContext<NODE,LINK>::SimulationContext()
{};

template <class NODE, class LINK>
SimulationContext<NODE,LINK>::~SimulationContext()
{};

template <class NODE, class LINK>
void SimulationContext<NODE,LINK>::LoadEvents(const string &file)
{
  
  FILE *in = fopen((char*)file,"r");
  if (in==0) { 
    cerr << "Can't read events from "<<file<<endl;
    exit(-1);
  }
  while (!feof(in)) {
    char buf[1024];
    char cmd[1024];
    unsigned num;
    unsigned src,dest;
    double l, b;
    double timestamp;
    fgets(buf,1024,in);
    if (strlen(buf)==0){
      continue;
    }
    while (isspace(*buf)) { 
      ++buf;
    }
    if (*buf==0) {
      continue;
    }
    if (toupper(buf[0])=='#') {
      continue;
    }
    sscanf(buf,"%lf %s",&timestamp,cmd);
    if (strcasecmp(cmd,"ADD_NODE")) {
      sscanf(buf,"%lf %s %u %lf %lf",&timestamp,cmd,&num,&lat,&bw);
      InsertEvent(new Event<NODE,LINK>(timestamp,ADD_NODE,this,new NODE(num,bw,lat,this)));
      continue;
    }
    if (strcasecmp(cmd,"DELETE_NODE")) {
      sscanf(buf,"%lf %s %u %lf %lf",&timestamp,cmd,&num,&lat,&bw);
      InsertEvent(new Event<NODE,LINK>(timestamp,DELETE_NODE,this,new NODE(num,bw,lat,this)));
      continue;
    }
    if (strcasecmp(cmd,"CHANGE_NODE")) {
      sscanf(buf,"%lf %s %u %lf %lf",&timestamp,cmd,&num,&lat,&bw);
      InsertEvent(new Event<NODE,LINK>(timestamp,CHANGE_NODE,this,new NODE(num,bw,lat,this)));
      continue;
    }
    if (strcasecmp(cmd,"ADD_LINK")) {
      sscanf(buf,"%lf %s %u %u %lf %lf",&timestamp,cmd,&src,&dest,&lat,&bw);
      InsertEvent(new Event<NODE,LINK>(timestamp,ADD_LINK,this,new LINK(src,dest,bw,lat,this)));
      continue;
    }
    if (strcasecmp(cmd,"DELETE_LINK")) {
      sscanf(buf,"%lf %s %u %u %lf %lf",&timestamp,cmd,&src,&dest,&lat,&bw);
      InsertEvent(new Event<NODE,LINK>(timestamp,DELETE_LINK,this,new LINK(src,dest,bw,lat,this)));
      continue;
    }
    if (strcasecmp(cmd,"CHANGE_LINK")) {
      sscanf(buf,"%lf %s %u %u %lf %lf",&timestamp,cmd,&src,&dest,&lat,&bw);
      InsertEvent(new Event<NODE,LINK>(timestamp,CHANGE_LINK,this,new LINK(src,dest,bw,lat,this)));
      continue;
    }
  }
};

template <class NODE, class LINK>
void SimulationContext<NODE,LINK>::LoadTopology(const string &file)
{
  LoadEvents(file);
  Event<NODE,LINK> *e;
  while ((e=GetNextEvent())) { 
    e->Dispatch();
    e->Disassociate();
    delete e;
  }
};

template <class NODE, class LINK>
ostream & SimulationContext<NODE,LINK>::Print(ostream &os) const
{
  os << "SimulationContext(topology=";
  Topology<NODE,LINK>::Print(os);
  os <<", eventqueue=";
  EventQueue<NODE,LINK>::Print(os);
  os<<")";
  return os;
};

template <class NODE, class LINK>
void SimulationContext<NODE,LINK>::DrawTopology()
{
};

template <class NODE, class LINK>
void SimulationContext<NODE,LINK>::DrawShortestPathTree(const Node *node)
{
};


  


#endif
