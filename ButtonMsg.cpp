// ButtonMsg.cpp : implementation file
//

#include "stdafx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

////////////////////////////////////////////////////
// CButtonMsg
//----------------------------------------
// This is a special version of CButton
// for use with a CheckBox object.  It
// will send a message to a specified
// Window when the SetCheck() fuction is
//	called.
//----------------------------------------
CButtonMsg::CButtonMsg()
{
	m_pW = 0;
	m_WMsg = 0;	//window message
	m_ObjMsg = 0;	//sub message
}

CButtonMsg::~CButtonMsg()
{
}


BEGIN_MESSAGE_MAP(CButtonMsg, CButton)
	//{{AFX_MSG_MAP(CButtonMsg)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

////////////////////////////////////////////////////
// CButtonMsg message handlers

void CButtonMsg::SetupMessaging(CWnd *pW, int Wmsg, int Smsg)
{
	//-----------------------------------------
	//	SetupMessaging
	//	This fuction is used to set the parameters
	// for where the message is to be sent.
	// parameters
	//		pW.....Pointer to window to send message to
	//		Wmsg...Message to send
	//		Smsg...Sub Message to send
	//-----------------------------------------
	m_pW = pW;
	m_WMsg = Wmsg;	//window message
	m_ObjMsg = Smsg;	//sub message
}

void CButtonMsg::SetCheck(int nCheck)
{
	//------------------------------------------
	// SetCheck
	//		This function overides the SetCheck
	//	function in the CButton class.
	// parameter:
	//		nCheck....State to set check box to
	//-------------------------------------------
	CButton::SetCheck(nCheck);
	if(m_pW)m_pW->PostMessageA(m_WMsg,m_ObjMsg,nCheck);
}

void CButtonMsg::SetCheck(int nCheck, int Message)
{
	//------------------------------------------
	// SetCheck
	//		This function overides the SetCheck
	//	function in the CButton class.
	// parameter:
	//		nCheck....State to set check box to
	//		Message...Flag, if true, send message
	//-------------------------------------------
	CButton::SetCheck(nCheck);
	if(m_pW && Message)m_pW->PostMessageA(m_WMsg,m_ObjMsg,nCheck);

}
