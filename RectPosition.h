#pragma once
#include <windef.h>
#ifndef RECTPOSITION_CLASS
#define RECTPOSITION_CLASS
class RectPosition {
public :
	long iLeftX;
	long iLeftY;
	long iRightX;
	long iRightY;
	RectPosition();
	RectPosition(long, long, long, long);
	~RectPosition();
	void setRect(RECT&) const;
};
#endif // !RECTPOSITION_CLASS
