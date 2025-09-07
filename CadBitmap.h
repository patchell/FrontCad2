// CadBitmap.h: interface for the CCadBitmap class.
//
///////////////////////////////////////////////
#pragma once

class CMyBitmap;
class CFileParser;

class CCadBitmap : public CCadObject  
{
	CMyBitmap *m_pBM;
	char *m_pFilename;
	inline static int m_RenderEnable = 0;
	int m_MaintainAspectRatio;
	CSize m_Size;
public:
	CCadBitmap();
	CCadBitmap(CCadBitmap &v);
	virtual ~CCadBitmap();
	BOOL Create(CPoint ptPos, char* pFilename, CMyBitmap* pBM);
	virtual CCadObject* Copy();
	static void SetRenderEnable(int e) { m_RenderEnable = e; }
	static int IsRenderEnabled() { return m_RenderEnable; }
	virtual void Move(CPoint p);
	virtual Tokens Parse(FILE* pIN, Tokens LookAHeadToken, CCadDrawing** ppDrawing, CFileParser* pParser);
	virtual void Save(FILE *pO,  int Indent);
	virtual void SetVertex(int Vi,CPoint p);
	virtual int GrabVertex(CPoint p);
	virtual void Draw(CDC* pDC, ObjectMode mode,CPoint Offset=CPoint(0,0),CScale Scale=CScale(0.1,0.1));
	virtual int CheckSelected(CPoint p,CSize Offset);
	virtual CPoint GetReference();
	virtual void AddObject(CCadObject *pO);
	virtual void RemoveObject(CCadObject *pO);
	
	virtual void SetSelected(int Flag=0);
	virtual void AdjustRefernce(CPoint Ref);
	virtual CRect GetRect(void);
	BOOL LoadBitmapImage(char *path);
	char *GetFileName(void){return m_pFilename;}
	void SetBitmap(CMyBitmap *pBM){m_pBM = pBM;}
	CMyBitmap *GetBitmap(void){return m_pBM;}
	void RestoreAspectRatio(void);
	CCadBitmap operator=(CCadBitmap &v);
	virtual void RenderEnable(int e);
	virtual CPoint GetCenter();
	// Moves the center of the object to the spcified point
	virtual void ChangeCenter(CSize p);
	virtual CSize GetSize();
	virtual void ChangeSize(CSize Sz);

	void SetMaintainAspectRatio(int a) { m_MaintainAspectRatio = a; }
	int GetMaintainAspectRatio(void) { return m_MaintainAspectRatio; }
};
