#pragma once

#include "Common.h"
/* 
Here this isnt the best of ways to solve, as it beats the LSP 
meaning the square shouldnt actually be implemented this way
better way is to implement it as a classfactory
*/

class Rectangle
{
protected:
	int width_, height_;
public:
	Rectangle(const int width, const int height) : width_{ width }, height_{ height } { }

	int get_width() const { return width_; }
	virtual void set_width(const int pWidth) {
		this->width_ = pWidth;
	}
	int get_height() const { return height_; }
	virtual void set_height(const int pHeight) {
		this->height_ =	pHeight;
	}
	int area() const { return width_ * height_; }

};

class Square : public Rectangle
{
public:
	Square(int size) : Rectangle(size, size) {}
	void set_width(const int pWidth) override {
		this->width_ = height_ = pWidth;
	}
	void set_height(const int pHeight) override {
		this->height_ = width_ = pHeight;
	}
};

