#include"FpsClass.h"

float FpsClass::CurrentTime = timeGetTime()*0.001f;
float FpsClass::LastTime = 0.0f;
int FpsClass::FrameCount = 0;
float FpsClass::Fps = 0.0f;
FpsClass::FpsClass()
{
	CurrentTime = timeGetTime()*0.001f;
	LastTime = 0.0f;
	FrameCount = 0;
	Fps = 0.0f;
}
FpsClass::~FpsClass()
{
}
float FpsClass::GetFps()
{
	CurrentTime = timeGetTime()*0.001f;
	if ((CurrentTime - LastTime) > 1.0f)
	{
		Fps = FrameCount / (CurrentTime - LastTime);
		FrameCount = 0;
		LastTime = CurrentTime;
		return Fps;
	}
	else
	{
		FrameCount++;
		return Fps;
	}
}