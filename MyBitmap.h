// MyBitmap.h: interface for the CMyBitmap class.
//
///////////////////////////////////////////////

#pragma once

class CMyBitmap : public CBitmap  
{
public:
	BOOL LoadBitmapImage(char *filename);
	CMyBitmap();
	virtual ~CMyBitmap();

};
