#include <stdio.h>
#include "context.h"



SimulationContext::SimulationContext()
{}

SimulationContext::~SimulationContext()
{}

void SimulationContext::LoadEvents(const string &file)
{
  
  FILE *in = fopen(file.c_str(),"r");
  if (in==0) { 
    cerr << "Can't read events from "<<file<<endl;
    exit(-1);
  }
  while (!feof(in)) {
    char buf[1024];
    char cmd[1024];
    unsigned num;
    unsigned src,dest;
    double lat, bw;
    double timestamp;
    fgets(buf,1024,in);
    if (strlen(buf)==0){
      continue;
    }
    while (isspace(*buf)) { 
      buf++;
    }
    if (*buf==0) {
      continue;
    }
    if (toupper(buf[0])=='#') {
      continue;
    }
    sscanf(buf,"%lf %s",&timestamp,cmd);
    if (strcasecmp(cmd,"ADD_Node")) {
      sscanf(buf,"%lf %s %u %lf %lf",&timestamp,cmd,&num,&lat,&bw);
      PostEvent(new Event(timestamp,ADD_Node,this,new Node(num,bw,lat,this)));
      continue;
    }
    if (strcasecmp(cmd,"DELETE_Node")) {
      sscanf(buf,"%lf %s %u %lf %lf",&timestamp,cmd,&num,&lat,&bw);
      PostEvent(new Event(timestamp,DELETE_Node,this,new Node(num,bw,lat,this)));
      continue;
    }
    if (strcasecmp(cmd,"CHANGE_Node")) {
      sscanf(buf,"%lf %s %u %lf %lf",&timestamp,cmd,&num,&lat,&bw);
      PostEvent(new Event(timestamp,CHANGE_Node,this,new Node(num,bw,lat,this)));
      continue;
    }
    if (strcasecmp(cmd,"ADD_LINK")) {
      sscanf(buf,"%lf %s %u %u %lf %lf",&timestamp,cmd,&src,&dest,&lat,&bw);
      PostEvent(new Event(timestamp,ADD_LINK,this,new Link(src,dest,bw,lat,this)));
      continue;
    }
    if (strcasecmp(cmd,"DELETE_LINK")) {
      sscanf(buf,"%lf %s %u %u %lf %lf",&timestamp,cmd,&src,&dest,&lat,&bw);
      PostEvent(new Event(timestamp,DELETE_LINK,this,new Link(src,dest,bw,lat,this)));
      continue;
    }
    if (strcasecmp(cmd,"CHANGE_LINK")) {
      sscanf(buf,"%lf %s %u %u %lf %lf",&timestamp,cmd,&src,&dest,&lat,&bw);
      PostEvent(new Event(timestamp,CHANGE_LINK,this,new Link(src,dest,bw,lat,this)));
      continue;
    }
  }
}

void SimulationContext::LoadTopology(const string &file)
{
  LoadEvents(file);
  Event *e;
  while ((e=GetEarliestEvent())) { 
    e->Dispatch();
    e->Disassociate();
    delete e;
  }
}

ostream & SimulationContext::Print(ostream &os) const
{
  os << "SimulationContext(topology=";
  Topology::Print(os);
  os <<", eventqueue=";
  EventQueue::Print(os);
  os<<")";
  return os;
}


void SimulationContext::DrawShortestPathTree(const Node *node) const
{
}
