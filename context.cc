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
    if (!strcasecmp(cmd,"DUMP_TABLE")) {
      sscanf(buf,"%lf %s %u",&timestamp,cmd,&num);
      PostEvent(new Event(timestamp,DUMP_TABLE,this,new Node(num,this,0,0)));
      continue;
    }
    if (!strcasecmp(cmd,"DRAW_TREE")) {
      sscanf(buf,"%lf %s %u",&timestamp,cmd,&num);
      PostEvent(new Event(timestamp,DRAW_TREE,this,new Node(num,this,0,0)));
      continue;
    }
    if (!strcasecmp(cmd,"DRAW_PATH")) {
      sscanf(buf,"%lf %s %u %u",&timestamp,cmd,&src,&dest);
      PostEvent(new Event(timestamp,DRAW_PATH,this,new Link(src,dest,this,0,0)));
      continue;
    }
#if 0
    if (!strcasecmp(cmd,"WRITE_TOPOLOGY")) {
      char file[1024];
      sscanf(buf,"%lf %s %s",&timestamp,cmd,file);
      PostEvent(new Event(timestamp,WRITE_TOPOLOGY,this,new string(file)));
      continue;
    }
    if (!strcasecmp(cmd,"WRITE_TREE")) {
      char file[1024];
      sscanf(buf,"%lf %s %s",&timestamp,cmd,file);
      PostEvent(new Event(timestamp,WRITE_TREE,this,new string(file)));
      continue;
    }
#endif
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

void SimulationContext::Init()
{
  for (deque<Link*>::const_iterator i=links.begin();i!=links.end();++i) { 
    PostEvent(new Event(-9999999999, CHANGE_LINK,this,new Link(**i)));
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
  delete e;
}

void SimulationContext::WriteShortestPathTreeDot(const Node *src, const string &s) const
{
  // NOT DONE
}

void SimulationContext::WritePathDot(const Node &src, const Node &dest, const string &s) const
{
  FILE *out = fopen(s.c_str(),"w");
  if (out==0) { 
    return;
  } 
  deque<Link> path;
  Node *n=((SimulationContext*)this)->FindMatchingNode(&src);
  if (n==0) { 
    fclose(out);
    return;
  }
  unsigned last=n->GetNumber();
  while (n->GetNumber()!=dest.GetNumber()) {
    if (n->GetNextHop(&dest)==0) {
      break;
    }
    n=((SimulationContext *)this)->FindMatchingNode(n->GetNextHop(&dest));
    if (n==0) {
      break;
    }
    path.push_back(Link(last,n->GetNumber(),0,0,0));
    last=n->GetNumber();
  }
  
  fprintf(out,"digraph path {\n");
  for (deque<Node*>::const_iterator i=nodes.begin(); i!=nodes.end();++i) {
    fprintf(out,"%u\n",(*i)->GetNumber());
  }
  for (deque<Link*>::const_iterator i=links.begin(); i!=links.end();++i) {
    fprintf(out,"%u -> %u [ label=\"%5.1lf\" ];\n",(*i)->GetSrc(),(*i)->GetDest(), (*i)->GetLatency());
  }
  for (deque<Link>::const_iterator i=path.begin();i!=path.end();++i) {
    fprintf(out,"%u -> %u [ color=red ];\n",(*i).GetSrc(),(*i).GetDest());
  }
  fprintf(out,"}\n");
  fclose(out);
}

void SimulationContext::DrawPath(const Link *p) const
{
  WritePathDot(Node(p->GetSrc(),0,0,0),Node(p->GetDest(),0,0,0),string("_path.in"));
  system("dot _path.in > _path.out");
  system("dotty _path.out");
}


void SimulationContext::DumpTable(const Node *src)
{
  cout <<*(FindMatchingNode(src))<< endl;
}


void SimulationContext::SendToNeighbors(const Node *src, const RoutingMessage *m)
{
  deque<Link*> *ll=GetOutgoingLinks(src);
  for (deque<Link*>::const_iterator i=ll->begin();i!=ll->end();++i) {
    PostEvent(new Event(GetTime()+(*i)->GetLatency(),
			ROUTING_MESSAGE_ARRIVAL,
			FindMatchingNode(&Node((*i)->GetDest(),0,0,0)),
			(void*)m));
  }
  delete ll;
}

void SimulationContext::SendToNeighbor(const Node *src, const Node *dest, const RoutingMessage *m)
{
  Link *l = FindMatchingLink(&Link(src->GetNumber(),dest->GetNumber(),0,0,0));

  PostEvent(new Event(GetTime()+l->GetLatency(),
		      ROUTING_MESSAGE_ARRIVAL,
		      FindMatchingNode(dest),
		      (void*)m));
}
					 
