#include "link.h"

//// TODO: complete the member function defintions of LinkImpl and LinkProxy

//LinkImpl
LinkImpl::LinkImpl(LinkType link_type, LinkProperties properties):Link(link_type),properties_(properties){}

bool LinkImpl::IsBuilt() const
{
  return adj_!=nullptr;
}

bool LinkImpl::Build(Link* link)
{
  if(link == nullptr)
    return false;
  if(!CanOverbuild(link))
    return false;
  link->BeOverbuilt(this);
  this->adj_ = link->adjacency();
  return true;
}

bool LinkImpl::CanOverbuild(Link* link) const
{
  if(link == nullptr)
    return false;
  return !link->IsBuilt();
}

int LinkImpl::vp() const
{
  return (adj_==nullptr)?0:adjacency()->vp_for_link();
}

LinkProperties LinkImpl::properties() const
{
  return properties_;
}

Player* LinkImpl::player() const
{
  return player_;
}

std::string LinkImpl::player_name() const
{
  if (player_ != nullptr) {
    return player_->name();
  }
  return kEmptyPlayerName;
}

void LinkImpl::set_player(Player* player)
{
  player_ = player;
}

void LinkImpl::set_observer(LinkObserver* observer)
{
  return;
}


//LinkProxy

LinkProxy::LinkProxy(LinkType link_type, Adjacency* adj):Link(link_type,adj){}

bool LinkProxy::IsBuilt() const{return (impl_ != nullptr && (impl_->IsBuilt()));}

bool LinkProxy::Build(Link* link)
{
  if(link == nullptr)
    return false;
  static_cast<void>(link);
  return false;
}

bool LinkProxy::CanOverbuild(Link* link) const
{
  if(link == nullptr)
    return false;
  static_cast<void>(link);
  return false;
}

void LinkProxy::BeOverbuilt(Link* link) 
{
  if(link == nullptr)
    return;
  if (impl_ != nullptr) {
    impl_->BeOverbuilt(link);
  }
  impl_ = static_cast<LinkImpl*>(link);
  link->set_observer(observer_);
  impl_->set_player(link->player());
  if (observer_) {
    observer_->UpdateLink(this); // added on 1st Nov
  }
}

int LinkProxy::vp() const{return (impl_ == nullptr)? 0 : impl_->vp();}

LinkProperties LinkProxy::properties() const
{
  if (impl_ != nullptr) {
    return impl_->properties();
  }
  return {};
}


Player* LinkProxy::player() const
{
  return (impl_ == nullptr)? nullptr : impl_->player();
}

std::string LinkProxy::player_name() const
{
  if (impl_ != nullptr) {
    return impl_->player_name();
  }
  return kEmptyPlayerName;
}

void LinkProxy::set_player(Player* player)
{
  if(player== nullptr)
    return;
  static_cast<void>(player);
}


void LinkProxy::set_observer(LinkObserver* observer)
{
  if(observer == nullptr)
    return;
  observer_ = observer;
  observer_->UpdateLink(this);
}

//// TODO ends
