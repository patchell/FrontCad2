#pragma once

////////////////////////////////////////////////////
// CStaticPreview window

class CStaticPreview : public CStatic
{
	CScale m_Scale;
	CCadLibObject* m_pLibObj;
public:
	CStaticPreview();
	virtual ~CStaticPreview();
	CCadLibObject* GetLibObj() { return m_pLibObj; }
	void SetLibObj(CCadLibObject* pObj) { m_pLibObj = pObj; }
	CScale GetScale() { return m_Scale; }
	void SetScale(CScale scale) { m_Scale = scale; }
	void DestroyLibObj() { 
		if (m_pLibObj) 
		{ 
			delete m_pLibObj; 
			m_pLibObj = 0; 
		} 
	}
protected:
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	DECLARE_MESSAGE_MAP()
};

