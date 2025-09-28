#pragma once
class Entity
{
public:
	Entity();
	//virtual void render() const = 0;
	virtual void integrate(double t) {};

protected:

};

