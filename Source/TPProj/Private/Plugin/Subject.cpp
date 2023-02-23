#include "Plugin/Subject.h"

#include "Plugin/Observer.h"


void Subject::addObserver(Observer* observer)
{
	if(observer != nullptr)
	{
		observers_[numObservers_] = observer;
		numObservers_++;
	}
}

void Subject::removeObserver(Observer* observer)
{
	for (int i = 0; i < numObservers_; i++)
	{
		numObservers_--;
		if (observers_[numObservers_] == observer)
		{
			for(int j = 0; j < numObservers_; j++)
			{
				observers_[j] = observers_[j++];
			}
		}
	}
}

void Subject::notify()
{
	//for (int i = 1; i <= numObservers_; i++)
	//{
	//	observers_[i]->onNotify();
	//}
}

