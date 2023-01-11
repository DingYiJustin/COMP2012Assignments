#include "industry.h"
#include <iostream>
#include "player.h"

//// TODO: Complete primary and secondary industries

// PrimaryIndustry

PrimaryIndustry::PrimaryIndustry(IndustryType industry_type, IndustryProperties properties,
                  ResourceType resource_type):IndustryImpl(industry_type, properties, resource_type)
                  {}
//,available_units_(properties.output_units)

bool PrimaryIndustry::CanOverbuild(Industry* other) const 
{
  // static_cast<PrimaryIndustry*>(other)->resource_observer_->HasResource(other->resource_type());
  // ResourceObserver* temp =other->*&PrimaryIndustry::resource_observer_;
  // PrimaryIndustry* temp = dynamic_cast<PrimaryIndustry*>(other);
  // bool test = (temp == nullptr)?false:(temp->resource_observer_->HasResource(this->resource_type())==false);
  if(other == nullptr)
    return false;
  if((other->IsBuilt() == false) || (industry_type_ == other->industry_type() && static_cast<PrimaryIndustry*>(other->impl())->resource_observer_->HasResource(this->resource_type())==false))//(temp->HasResource(resource_type()) == false))
  {
    if(this->properties().tech_level > other->properties().tech_level && industry_type_ == other->industry_type())
      return true;
  }
  else
  {
    if(player() == other->player() && this->properties().tech_level > other->properties().tech_level && industry_type_ == other->industry_type())
      return true;
  }
  return false;
}

//?
bool PrimaryIndustry::IsEligibleForVp() const
{
    if(available_units_ == 0 && IsBuilt())
      return true;
    return false;
}

bool PrimaryIndustry::ProvideResources(int units)
{
  if(available_units_>=units)
  {
    available_units_ -= units;
    if(available_units_ == 0)
        player()->IncreaseExp(properties().exp_increase);
    industry_observer_->UpdateIndustry(this);
    resource_observer_->UpdateResourceCount(resource_type_,-units);
    return true;
  }
  return false;

}

int PrimaryIndustry::available_units() const
{
   return available_units_;
}

void PrimaryIndustry::set_resource_observer(ResourceObserver* rsrc_observer)
{
  resource_observer_ = rsrc_observer;
}

void PrimaryIndustry::ProduceResources()
{
  available_units_ += properties().output_units;
  industry_observer_->UpdateIndustry(this);
  resource_observer_->UpdateResourceCount(resource_type_,properties().output_units);
}

void PrimaryIndustry::RemoveResources()
{
  int gap = available_units_;
  available_units_ = 0;
  industry_observer_->UpdateIndustry(this);
  resource_observer_->UpdateResourceCount(resource_type_,-gap);
}


//Secondary Industry
SecondaryIndustry::SecondaryIndustry(IndustryType industry_type, IndustryProperties properties):IndustryImpl(industry_type,properties){}

bool SecondaryIndustry::CanOverbuild(Industry* other) const
{
  if(other == nullptr)
    return false;
  if( this->properties().tech_level > other->properties().tech_level && industry_type_ == other->industry_type())
  {
    if(other->IsBuilt() == false)
      return true;
    if(player_ == other->player())
      return true;
  }
  return false;

}


bool SecondaryIndustry::IsEligibleForVp() const
{
  if(sold()&&IsBuilt())
    return true;
  return false;
}

bool SecondaryIndustry::Sell()
{
  if(!sold()&&IsBuilt())
  {
    sold_ = true;
    player()->IncreaseExp(properties().exp_increase);
    industry_observer_->UpdateIndustry(this);
    return true;
  }
  return false;
}

bool SecondaryIndustry::sold() const
{
  return sold_;
}

void SecondaryIndustry::set_resource_observer(ResourceObserver* rsrc_observer)
{
  //resource_observer_ = rsrc_observer;
  return;
}

//// TODO ends
