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
    char b[1024];
    char *buf=b;
    char cmd[1024];
    unsigned num;
    unsigned src,dest;
    double lat, bw;
    double timestamp;
    if (!fgets(buf,1024,in)) {
      break;
    }
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
    //fprintf(stderr,"%s",buf);
    sscanf(buf,"%lf %s",&timestamp,cmd);
    if (!strcasecmp(cmd,"DRAW_TOPOLOGY")) {
      sscanf(buf,"%lf %s",&timestamp,cmd);
      PostEvent(new Event(timestamp,DRAW_TOPOLOGY,this,0));
      continue;
    }
    if (!strcasecmp(cmd,"WRITE_TOPOLOGY")) {
      char file[1024];
      sscanf(buf,"%lf %s %s",&timestamp,cmd,file);
      PostEvent(new Event(timestamp,WRITE_TOPOLOGY,this,new string(file)));
      continue;
    }
    if (!strcasecmp(cmd,"DRAW_TREE")) {
      sscanf(buf,"%lf %s %u",&timestamp,cmd,&num);
      PostEvent(new Event(timestamp,DRAW_TREE,this,new Node(num,this,0,0)));
      continue;
    }
    if (!strcasecmp(cmd,"WRITE_TREE")) {
      char file[1024];
      sscanf(buf,"%lf %s %s",&timestamp,cmd,file);
      PostEvent(new Event(timestamp,WRITE_TREE,this,new string(file)));
      continue;
    }
    if (!strcasecmp(cmd,"ADD_NODE")) {
      sscanf(buf,"%lf %s %u %lf %lf",&timestamp,cmd,&num,&lat,&bw);
      PostEvent(new Event(timestamp,ADD_NODE,this,new Node(num,this,bw,lat)));
      continue;
    }
    if (!strcasecmp(cmd,"DELETE_NODE")) {
      sscanf(buf,"%lf %s %u %lf %lf",&timestamp,cmd,&num,&lat,&bw);
      PostEvent(new Event(timestamp,DELETE_NODE,this,new Node(num,this,bw,lat)));
      continue;
    }
    if (!strcasecmp(cmd,"CHANGE_NODE")) {
      sscanf(buf,"%lf %s %u %lf %lf",&timestamp,cmd,&num,&lat,&bw);
      PostEvent(new Event(timestamp,CHANGE_NODE,this,new Node(num,this,bw,lat)));
      continue;
    }
    if (!strcasecmp(cmd,"ADD_LINK")) {
      sscanf(buf,"%lf %s %u %u %lf %lf",&timestamp,cmd,&src,&dest,&lat,&bw);
      PostEvent(new Event(timestamp,ADD_LINK,this,new Link(src,dest,this,bw,lat)));
      continue;
    }
    if (!strcasecmp(cmd,"DELETE_LINK")) {
      sscanf(buf,"%lf %s %u %u %lf %lf",&timestamp,cmd,&src,&dest,&lat,&bw);
      PostEvent(new Event(timestamp,DELETE_LINK,this,new Link(src,dest,this,bw,lat)));
      continue;
    }
    if (!strcasecmp(cmd,"CHANGE_LINK")) {
      sscanf(buf,"%lf %s %u %u %lf %lf",&timestamp,cmd,&src,&dest,&lat,&bw);
      PostEvent(new Event(timestamp,CHANGE_LINK,this,new Link(src,dest,this,bw,lat)));
      continue;
    }
  }
  fclose(in);
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

ostream & SimulationContext::Print(ostream &os)
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

void SimulationContext::DispatchEvent(Event *e)
{
  e->Dispatch();
  e->Disassociate();
}

void SimulationContext::WriteShortestPathTreeDot(const string &s) const
{
}
