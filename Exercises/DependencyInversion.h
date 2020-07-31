#pragma once

#include "Common.h"

/* High level module should not depend on Low level module */

class ILogger
{
public:
	virtual ~ILogger() {}
	virtual void Log(const string& s) = 0;
};

class ConsoleLogger : public ILogger
{
public:
	ConsoleLogger() {}
	void Log(const string& s) override
	{
		cout << "LOG: " << s.c_str() << endl;
	}
};

class Engine
{
public:
	float volume = 5;
	int horse_power = 400;
	friend ostream& operator<< (ostream& os, const Engine& obj)
	{
		return os
			<< "volume: " << obj.volume
			<< " horse_power: " << obj.horse_power;
	} // thanks, ReSharper!
};

class Car
{
public:
	unique_ptr<Engine> engine;
	shared_ptr<ILogger> logger;
	Car(unique_ptr<Engine> engine,	const shared_ptr<ILogger>& logger)	: engine{ move(engine) }, logger{ logger }
	{
		logger->Log("making a car");
	}
	friend ostream& operator<<(ostream& os, const Car& obj)
	{
		return os << "car with engine: " << *obj.engine;
	}
};