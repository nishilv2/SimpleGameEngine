#pragma once
#ifndef __FPSCLASS__H
#define __FPSCLASS__H
#include<Windows.h>
class FpsClass
{
private:
	static int FrameCount;
	static float Fps;
	static float LastTime;
	static float CurrentTime;
public:
	FpsClass();
	float GetFps();
	~FpsClass();
};

#endif // !__FPSCLASS__H
