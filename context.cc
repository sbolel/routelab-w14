#include <stdio.h>
#include "context.h"

Context::Context()
{}

Context::~Context()
{}

void Context::LoadEvents(const string &file)
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
      eventqueue.InsertEvent(new Event(timestamp,ADD_NODE,topology,new Node(num,bw,lat,this)));
      continue;
    }
    if (strcasecmp(cmd,"DELETE_NODE")) {
      sscanf(buf,"%lf %s %u %lf %lf",&timestamp,cmd,&num,&lat,&bw);
      eventqueue.InsertEvent(new Event(timestamp,DELETE_NODE,topology,new Node(num,bw,lat,this)));
      continue;
    }
    if (strcasecmp(cmd,"CHANGE_NODE")) {
      sscanf(buf,"%lf %s %u %lf %lf",&timestamp,cmd,&num,&lat,&bw);
      eventqueue.InsertEvent(new Event(timestamp,CHANGE_NODE,topology,new Node(num,bw,lat,this)));
      continue;
    }
    if (strcasecmp(cmd,"ADD_LINK")) {
      sscanf(buf,"%lf %s %u %u %lf %lf",&timestamp,cmd,&src,&dest,&lat,&bw);
      eventqueue.InsertEvent(new Event(timestamp,ADD_LINK,topology,new Link(src,dest,bw,lat,this)));
      continue;
    }
    if (strcasecmp(cmd,"DELETE_LINK")) {
      sscanf(buf,"%lf %s %u %u %lf %lf",&timestamp,cmd,&src,&dest,&lat,&bw);
      eventqueue.InsertEvent(new Event(timestamp,DELETE_LINK,topology,new Link(src,dest,bw,lat,this)));
      continue;
    }
    if (strcasecmp(cmd,"CHANGE_LINK")) {
      sscanf(buf,"%lf %s %u %u %lf %lf",&timestamp,cmd,&src,&dest,&lat,&bw);
      eventqueue.InsertEvent(new Event(timestamp,CHANGE_LINK,topology,new Link(src,dest,bw,lat,this)));
      continue;
    }
  }
}

void Context::LoadTopology(const string &file)
{
  LoadEvents(file);
  Event *e;
  while ((e=GetNextEvent())) { 
    e->Dispatch();
    e->Disassociate();
    delete e;
  }
}

ostream & Context::Print(ostream &os) const
{
  os << "Context(topology="<<topology<<", eventqueue="<<eventqueue<<")";
  return os;
}

void Context::DrawTopology()
{
}

void Context::DrawShortestPathTree(const Node *node)
{
}

void Context::PostEvent(Event *e)
{
  eventqueue.InsertEvent(e);
}

Event *Context::GetNextEvent()
{
  return eventqueue.GetEarliestEvent();
}


  
