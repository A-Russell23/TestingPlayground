﻿#pragma once

class Observer
{
public:
	virtual ~Observer() {}
	//virtual void onNotify(const Entity& entity, Event event) = 0;
	virtual void onNotify(); //todo - sort
};
