// MyASock.cpp : implementation file
//

#include "stdafx.h"
#include "MyASock.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyASock

CMyASock::CMyASock()
{
	m_pParent = NULL;
}

CMyASock::~CMyASock()
{

}

// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CMyASock, CAsyncSocket)
	//{{AFX_MSG_MAP(CMyASock)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CMyASock member functions

void CMyASock::OnReceive(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class

	if(m_pParent)
	{
		m_pParent->PostMessage(Recv_Mesg_Type, 0, 0);
	}
	
	CAsyncSocket::OnReceive(nErrorCode);
}

int CMyASock::SendMesg(const char *pch, const int nSize, LPSOCKADDR psa)
{
	int nBytes;
	nBytes=SendTo(pch,nSize,psa,sizeof(SOCKADDR),0);
	if(nBytes==SOCKET_ERROR )
	{
//		AfxMessageBox("SendMesg:SendTo error!");
		return -1;
	}
	else
		return nBytes;
}

int CMyASock::RecvMesg(char *pch, const int nSize, CSockAddr &psa)
{
	int nBytes;
	int nFromSize = sizeof(SOCKADDR);
//	if(psa == NULL)
//	{
//		psa = CSockAddr();
//	}
	nBytes=ReceiveFrom(pch,nSize,psa,&nFromSize);
	if(nBytes==SOCKET_ERROR )
	{
//		AfxMessageBox("RecvMesg:ReceiveFrom error!");
		return -1;
	}
	else
		return nBytes;
}

void CMyASock::InitSock(int nPort)
{
	//Create the socket
	int n = 0;
	while(!Create(nPort,SOCK_DGRAM))
	{
		nPort ++ ;
		n ++;
		if(5==n)
		{
			AfxMessageBox("InitSock:Create error!");
			return;
		}
	}
}

void CMyASock::SetWndMesg(CWnd *pWnd, UINT Mesg_Type)
{
	m_pParent = pWnd;
	Recv_Mesg_Type = Mesg_Type;
}
