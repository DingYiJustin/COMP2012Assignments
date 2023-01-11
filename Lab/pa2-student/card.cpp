#include "card.h"

#include "util-common.h"

//// TODO: Complete the member function defintion of the cardd classes

//Card
Card::Card(const std::string& name):name_(name){ }

std::string Card::name()const{return name_;}

//Location Card
LocationCard::LocationCard(Location* location):Card(location->name()),location_(location){}

LocationCard::~LocationCard(){}//delete location_;}

bool LocationCard::IsWildCard() const
{
    return false;
}


bool LocationCard::CanIndustryBeOverbuilt(const PlayerNetwork* network,
                              const Industry* to_be_overbuilt) const
{
    if(to_be_overbuilt==nullptr)
        return false;
    return (to_be_overbuilt->location()->name() == location_->name());//&&(location_->HasIndustryType(to_be_overbuilt->industry_type()));
}

CardType LocationCard::card_type() const
{
    return card_type_;
}

//Wild Location Card
WildLocationCard::WildLocationCard():Card("Wild Location"){}

WildLocationCard::~WildLocationCard(){}

bool WildLocationCard::IsWildCard() const
{
    return true;
}


bool WildLocationCard::CanIndustryBeOverbuilt(const PlayerNetwork* network,
                              const Industry* to_be_overbuilt) const
{
    if(to_be_overbuilt == nullptr)
        return false;
    return true;
}

CardType WildLocationCard::card_type() const
{
    return card_type_;
}

//IndustryCard
IndustryCard::IndustryCard(IndustryType industry_type):Card(ToString(industry_type)),industry_type_(industry_type){}

IndustryCard::~IndustryCard(){}

bool IndustryCard::IsWildCard() const
{
    return false;
}


bool IndustryCard::CanIndustryBeOverbuilt(const PlayerNetwork* network,
                              const Industry* to_be_overbuilt) const
{
    if(to_be_overbuilt == nullptr || network == nullptr)
        return false;
    if(network->HasEstablished())
        return (to_be_overbuilt->industry_type() == industry_type_) && network->IsCovering(to_be_overbuilt->location());
    return (to_be_overbuilt->industry_type() == industry_type_);
}

CardType IndustryCard::card_type() const
{
    return card_type_;
}

//WildIndustryCard
WildIndustryCard::WildIndustryCard():Card("Wild Industry"){}

WildIndustryCard::~WildIndustryCard(){}

bool WildIndustryCard::IsWildCard() const
{
    return true;
}


bool WildIndustryCard::CanIndustryBeOverbuilt(const PlayerNetwork* network,
                              const Industry* to_be_overbuilt) const
{
    if(to_be_overbuilt == nullptr || network == nullptr)
        return false;
    int size = (network->industries_of_type(to_be_overbuilt->industry_type())).size();
    if(network->HasEstablished())
        return (size!=0) && network->IsCovering(to_be_overbuilt->location());
    return false;
}

CardType WildIndustryCard::card_type() const
{
    return card_type_;
}

//// TODO ends
