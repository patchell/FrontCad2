// MyBitmap.h: interface for the CMyBitmap class.
//
///////////////////////////////////////////////

#if !defined(AFX_MYBITMAP_H__9EC7D314_A32A_4352_BB0A_9F9AF0A2573E__INCLUDED_)
#define AFX_MYBITMAP_H__9EC7D314_A32A_4352_BB0A_9F9AF0A2573E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMyBitmap : public CBitmap  
{
public:
	BOOL LoadBitmap(char *filename);
	CMyBitmap();
	virtual ~CMyBitmap();

};

#endif // !defined(AFX_MYBITMAP_H__9EC7D314_A32A_4352_BB0A_9F9AF0A2573E__INCLUDED_)
