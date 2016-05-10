#include"FontClass.h"

FontClass::FontClass()
{
	this->d3ddevice = NULL;
	this->pfont = NULL;
}
FontClass::~FontClass()
{
	SAFE_RELEASE(this->pfont);
}
bool FontClass::init()
{
	if (FAILED(D3DXCreateFont(this->d3ddevice, 30, 0, 0, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, 0, _T(this->font), &this->pfont)))
	{
		return false;
	}
	else
	{
		return true;
	}
}
bool FontClass::setColor(int r, int g, int b)
{
	this->color[0] = r;
	this->color[1] = g;
	this->color[2] = b;
	return true;
}
bool FontClass::setContent(const char* content)
{
	strcpy_s(this->content, 20, content);
	return true;
}
bool FontClass::setDevice(LPDIRECT3DDEVICE9 d3ddevice)
{
	this->d3ddevice = d3ddevice;
	return true;
}
bool FontClass::setPosition(int top, int bottom, int left, int right)
{
	this->position.bottom = bottom;
	this->position.top = top;
	this->position.left = left;
	this->position.right = right;
	return true;
}
bool FontClass::setFont(const char* font)
{
	strcpy_s(this->font, 20, font);
	return true;
}
void FontClass::draw()
{
	this->pfont->DrawTextA(0, _T(this->content), -1, &this->position, DT_CENTER, D3DCOLOR_XRGB(this->color[0], this->color[1], this->color[2]));
}