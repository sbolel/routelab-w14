#include "table.h"

#if defined(GENERIC)
ostream & Table::Print(ostream &os) const 
{
  // WRITE THIS
  os << "Table()";
  return os;
}
#endif

#if defined(LINKSTATE)

#endif

#if defined(DISTANCEVECTOR)

deque<Row>::iterator Table::FindMatching(const unsigned dest) 
{
  deque<Row>::iterator i;

  for (i=m.begin();i!=m.end();++i) {
    if ((*i).dest_node==dest) {
      break;
    }
  } 
  return i;
}

Row *Table::GetNext(const unsigned dest) 
{
  deque<Row>::iterator i=FindMatching(dest);
  if (i==m.end()) { 
    return 0;
  } else {
    return new Row(*i);
  }
}

void Table::SetNext(const unsigned dest, const Row &r)
{
  deque<Row>::iterator i = FindMatching(dest);
  if (i==m.end()) { 
    m.push_back(r);
  } else {
    *i=r;
  }
}

Row::Row(const unsigned dest, const unsigned next, const double c) :
  dest_node(dest), next_node(next), cost(c)
{}

ostream & Row::Print(ostream &os) const 
{
  os <<"Row(dest="<<dest_node<<", next="<<next_node<<", cost="<<cost<<")";
  return os;
}

ostream & Table::Print(ostream &os) const 
{
  os<<"Table(rows={";
  for (deque<Row>::const_iterator i=m.begin();i!=m.end();++i) { 
    os <<(*i)<<", ";
  }
  os<<"})";
  return os;
}
    
#endif
