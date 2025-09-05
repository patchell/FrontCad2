#if !defined(AFX_STATICBITMAP_H__443F2077_C1AA_40B1_BCF7_C261D5FB2CCE__INCLUDED_)
#define AFX_STATICBITMAP_H__443F2077_C1AA_40B1_BCF7_C261D5FB2CCE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// StaticBitmap.h : header file
//

////////////////////////////////////////////////////
// CStaticBitmap window

class CStaticBitmap : public CStatic
{
	COLORREF m_Color;
	CWnd* m_pMaster;
	int m_Msg;
	int m_WMsg;
public:
	CStaticBitmap();
	virtual ~CStaticBitmap();
	void SetColor(COLORREF c){m_Color = c;Invalidate();}
	COLORREF GetColor(void)const {return m_Color;}
	void SetupMessaging(CWnd *pW,int Wmsg,int Smsg);
	void SendChange(void);
	void SetTheMaster(CWnd *W){m_pMaster = W;}
	void SetMsgValue(int m);
	void SetWMsgValue(int m){m_WMsg = m;}
protected:
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	DECLARE_MESSAGE_MAP()
};


#endif // !defined(AFX_STATICBITMAP_H__443F2077_C1AA_40B1_BCF7_C261D5FB2CCE__INCLUDED_)
