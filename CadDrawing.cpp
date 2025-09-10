// CadDrawing.cpp: implementation of the CCadDrawing class.
// This is a top level object for a CAD drawing
///////////////////////////////////////////////

#include "stdafx.h"


///////////////////////////////////////////////
// Construction/Destruction
///////////////////////////////////////////////

CCadDrawing::CCadDrawing():CCadObject(OBJECT_TYPE_DRAWING)
{
	m_Error = 0;
	m_BkColor = RGB(255,255,255);
}

CCadDrawing::~CCadDrawing()
{
}

CCadObject* CCadDrawing::Copy()
{
	//-----------------------------------------
	// Copy
	//		This function makes a copy of the
	// drawing and all objects in it.
	//
	// return:
	//		pointer to new drawing
	//-----------------------------------------
	CCadDrawing *pNew = new CCadDrawing();
	pNew->m_BkColor = m_BkColor;
	CCadObject *pO = GetHead();
	while(pO)
	{
		pNew->AddObjectToEnd(pO->Copy());
		pO = pO->GetNext();
	}
	return (CCadObject*)pNew;
}

void CCadDrawing::Draw(CDC *pDC, ObjectMode mode, CPoint Offset, CScale Scale)
{
	//-----------------------------------------
	// Draw
	//		This is the function that draws the
	// Drawing onto the specified device
	// context.
	//	parameters:
	//		pDC.....pointer to display context
	//		mode....Ddrawing Mode
	//		Offset..Offset to add to objects
	//		Scale...Ammount to scale objects by
	//-----------------------------------------
	CCadObject *pCO = GetHead();
	
	while(pCO)
	{
		if(pCO->GetSelected()) 
			mode = ObjectMode::Selected;
		else 
			mode = ObjectMode::Final;
		pCO->Draw(pDC,mode,Offset,Scale);
		pCO = pCO->GetNext();
	}
}

void CCadDrawing::Save(FILE *pO,  int Indent)
{
	//-------------------------------------------
	//	Save
	//		This function is used to save the
	// drawing to a computer file
	//
	//	parameter:
	//		pO.....pointer to file tto save to
	//-------------------------------------------
	char* s = new char[256];
	char* s1 = new char[64];

	CCadObject *pCO = GetHead();
	fprintf(pO, "%sDRAWFILE( %s )\n%s{\n",
		theApp.IndentString(s, 256, Indent),
		CFileParser::SaveColor(s1, 64, m_BkColor, Tokens::BACKGROUND_COLOR),
		s
	);
	while(pCO)
	{
		pCO->Save(pO, Indent+4);
		pCO = pCO->GetNext();
	}
	fprintf(pO,"%s}\n",s);
	delete[]s1;
	delete[]s;
}

void CCadDrawing::Print(CDC *pDC, ObjectMode mode, CPoint Offset, CScale Scale)
{
	//-----------------------------------------
	// Print
	//		This is the draw function for drawing
	//	on the printer.
	//
	//	parameters:
	//		pDC....device context to draw to
	//		mode...drawing mode
	//		Offset.offset to add to objects
	//		Scale.amount to Scale drawing by
	//-----------------------------------------
	CCadObject *pCO = GetHead();
	while(pCO)
	{
		//---------------------------------
		// we really don't give a hang
		// what the mode is
		//---------------------------------
		pCO->Draw(pDC,mode,Offset,Scale);
		pCO = pCO->GetNext();
	}
}

Tokens CCadDrawing::Parse(FILE* pIN, Tokens LookAHeadToken, CCadDrawing** ppDrawing, CFileParser* pParser)
{
    return Tokens(0);
}

int CCadDrawing::CheckSelected(CPoint p, CCadObject **ppSelList, int n,int flag)
{
	//--------------------------------------
	// CheckSelected
	//
	// This function is used to see if
	// there are any objects under the
	// point.  This function returns the
	// first 'n' objects it finds.  It does
	// not actually select anything.
	//
	// parameters:
	//		p......point of interest
	//		ppSelList...pointer to an array of selected objects
	//		n.....maximum number of objects to check for
	//		flag..what kind of objects are inlcuded in list
	//				0-All Objects
	//				1-Unselected Objects
	//				2-Selected Objects
	//	returns:
	//		number of objects that are under the point
	//--------------------------------------------
	int count = 0;
	CCadObject *pCO = GetHead();

	while(pCO && ((count < n) || !n))
	{
		if(pCO->CheckSelected(p))
		{
			switch (flag)
			{
				case CADDRAWUBG_CHECKSEL_FLAG_ALL:
					if(ppSelList) ppSelList[count] = pCO;
					count++;	//increment count
					break;
				case CADDRAWUBG_CHECKSEL_FLAG_UNSEL:
					if (!pCO->GetSelected())
					{
						if (ppSelList) ppSelList[count] = pCO;
						count++;	//increment count
					}
					break;
				case CADDRAWUBG_CHECKSEL_FLAG_SEL:
					if (pCO->GetSelected())
					{
						if (ppSelList) ppSelList[count] = pCO;
						count++;	//increment count
					}
					break;
			}
		}
		pCO = pCO->GetNext();
	}
	return count;
}

CCadLibObject * CCadDrawing::CreatePartFromSelected(char *name)
{
	//------------------------------------------------
	// CreatePartFromSelected
	//		Thhis function is used to create a library
	// part from all of the objects in the drawing that
	// are selected.
	//
	// parameters:
	//		name....name of the new part
	// returns:
	//		pointer to the CCadLibObject that will
	//		represent the new poart.
	//------------------------------------------------
	CCadObject *pObj = GetHead();
	CCadLibObject *pPart;
	if(GetHead() == NULL)
		pPart = NULL;
	else
	{
		pPart = new CCadLibObject;
		pPart->SetName(name);
		while(pObj)
		{
			if(pObj->GetSelected())
			{
				switch(pObj->GetType())
				{
					case OBJECT_TYPE_NONE:
						break;
					case OBJECT_TYPE_LINE:
						{
							CCadLine *pO = new CCadLine;
							*pO = *((CCadLine *)pObj);
							pPart->AddObjectToEnd(pO);
						}
						break;
					case OBJECT_TYPE_RECT:
						{
							CCadRect *pO = new CCadRect;
							*pO = *((CCadRect *)pObj);
							pPart->AddObjectToEnd(pO);
						}
						break;
					case OBJECT_TYPE_ELLIPSE:
						{
							CCadElipse *pO = new CCadElipse;
							*pO = *((CCadElipse *)pObj);
							pPart->AddObjectToEnd(pO);
						}
						break;
					case OBJECT_TYPE_RNDRECT:
						{
							CCadRoundRect *pO = new CCadRoundRect;
							*pO = *((CCadRoundRect *)pObj);
							pPart->AddObjectToEnd(pO);
						}
						break;
					case OBJECT_TYPE_POLY:
						{
							CCadPolygon *pO = new CCadPolygon;
							*pO = *((CCadPolygon *)pObj);
							pPart->AddObjectToEnd(pO);
						}
						break;
					case OBJECT_TYPE_LIBCOMP:
						{
						}
						break;
					case OBJECT_TYPE_HOLEROUND:
						{
							CCadHoleRound *pO = new CCadHoleRound;
							*pO = *((CCadHoleRound *)pObj);
							pPart->AddObjectToEnd(pO);
						}
						break;
					case OBJECT_TYPE_HOLERECT:
						{
							CCadRectHole *pO = new CCadRectHole;
							*pO = *((CCadRectHole *)pObj);
							pPart->AddObjectToEnd(pO);
						}
						break;
					case OBJECT_TYPE_HOLERND1FLAT:
						{
							CCadHoleRnd1Flat *pO = new CCadHoleRnd1Flat;
							*pO = *((CCadHoleRnd1Flat *)pObj);
							pPart->AddObjectToEnd(pO);
						}
						break;
					case OBJECT_TYPE_HOLERND2FLAT:
						{
							CCadHoleRnd2Flat *pO = new CCadHoleRnd2Flat;
							*pO = *((CCadHoleRnd2Flat *)pObj);
							pPart->AddObjectToEnd(pO);
						}
						break;
					case OBJECT_TYPE_TEXT:
						{
							CCadText *pO = new CCadText;
							*pO = *((CCadText *)pObj);
							pPart->AddObjectToEnd(pO);
						}
						break;
					case OBJECT_TYPE_ARC:
						{
							CCadArc *pO = new CCadArc;
							*pO = *((CCadArc *)pObj);
							pPart->AddObjectToEnd(pO);
						}
						break;
					case OBJECT_TYPE_ARCCENTERED:
						{
							CCadArcCentered *pO = new CCadArcCentered;
							*pO = *((CCadArcCentered *)pObj);
							pPart->AddObjectToEnd(pO);
						}
						break;
					case OBJECT_TYPE_ARROW:
						{
							CCadArrow *pO = new CCadArrow;
							*pO = *((CCadArrow *)pObj);
							pPart->AddObjectToEnd(pO);
						}
						break;
				}
			}
			pObj = pObj->GetNext();
		}
	}
	return pPart;
}

CCadPrintRect *CCadDrawing::GetPrintRect()
{
	CCadObject *pObj;
	pObj = GetHead();
	int loop = 0;
	while (!loop && pObj)
	{
		if (OBJECT_TYPE_PRINTRECT == pObj->GetType())
		{
			loop = 1;
		}
		else
			pObj = pObj->GetNext();
	}
	return (CCadPrintRect *)pObj;
}
