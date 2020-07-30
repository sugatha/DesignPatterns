#pragma once

#include "Common.h"

class Document
{
public:
	Document() {}

};

/* This doesnt make sense as every guy who wants a printer is also forced to implement the scanner and fax. */

class IMachine
{
public:
	virtual void print(vector<Document*> docs) = 0;
	virtual void fax(vector<Document*> docs) = 0;
	virtual void scan(vector<Document*> docs) = 0;
};

class MyFavouritePrinter  : public IMachine
{
public:
	void print(vector<Document*> docs) override;
	void fax(vector<Document*> docs) override;
	void scan(vector<Document*> docs) override;
};

/* A better way is to segregate the functionality */
class IPrinter
{
public:
	virtual void print(vector<Document*> docs) = 0;
};
class IScanner
{
public:
	virtual void scan(vector<Document*> docs) = 0;
};

class Printer : public IPrinter
{
public:
	void print(vector<Document*> docs) override;
};

class Scanner : public IScanner
{
public:
	void scan(vector<Document*> docs) override;
};

class All_in_One : public IPrinter, IScanner
{
public:
	void print(vector<Document*> docs) override;
	void scan(vector<Document*> docs) override;
};