#include "messages.h"

#if defined(GENERIC)
ostream &RoutingMessage::Print(ostream &os) const
{
  os << "RoutingMessage()";
  return os;
}
#endif


#if defined(LINKSTATE)


ostream &RoutingMessage::Print(ostream &os) const
{
  os << "RoutingMessage(ttl="<<ttl<<", srcnode="<<srcnode<<", seqno="<<seqno<<", link="<<link<<")";
  return os;
}

RoutingMessage::RoutingMessage()
{}

RoutingMessage::RoutingMessage(const Node &src, const Link &l, const unsigned t, const unsigned s)
  : srcnode(src), link(l), ttl(t), seqno(s)
{}

RoutingMessage::RoutingMessage(const RoutingMessage &rhs)
  : srcnode(rhs.srcnode), link(rhs.link), ttl(rhs.ttl), seqno(rhs.seqno)
{}

RoutingMessage & RoutingMessage::operator=(const RoutingMessage &rhs)
{
  return *(new(this)RoutingMessage(rhs));
}
#endif


