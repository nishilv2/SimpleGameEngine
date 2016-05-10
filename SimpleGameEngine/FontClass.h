#pragma once
#ifndef __FONTCLASS__H
#define __FONTCLASS__H
#include<d3d9.h>
#include<d3dx9.h>
#include<tchar.h>
#define SAFE_RELEASE(p) {if(p){(p)->Release();(p)=NULL;}}

class FontClass
{
private:
	ID3DXFont* pfont;
	char* content;
	char* font;
	RECT position;
	int color[3];
	LPDIRECT3DDEVICE9 d3ddevice;
public:
	FontClass();
	~FontClass();
	void draw();
	bool init();
	bool setDevice(LPDIRECT3DDEVICE9 d3ddevice);
	bool setColor(int r, int b, int g);
	bool setPosition(int top, int bottom, int left, int right);
	bool setContent(const char* content);
	bool setFont(const char* font);
};
#endif // !__FONTCLASS__H