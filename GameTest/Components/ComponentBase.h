#pragma once

// abstract class, all components will inherit from this
// each component will have a reference/pointer (undecided yet) to the object that has it.
class ComponentBase
{
public:
	ComponentBase();
	~ComponentBase();
	virtual void GetType() = 0;
private:

};

ComponentBase::ComponentBase()
{
}

ComponentBase::~ComponentBase()
{
}