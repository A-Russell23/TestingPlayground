#pragma once
#include "Observer.h"

class Subject
{
public:
	void addObserver(Observer* observer);
	void removeObserver(Observer* observer);

protected:
	void notify();
	
private:
	Observer* observers_[10]; //todo - change
	int numObservers_ = 0;
};
