#if !defined(AFX_MYASOCK_H__2F572A0D_5758_48A4_B82E_10CFDF0131E2__INCLUDED_)
#define AFX_MYASOCK_H__2F572A0D_5758_48A4_B82E_10CFDF0131E2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyASock.h : header file

#include "winsock.h"
#include "afxsock.h"

//	封装了的struct sockaddr_in结构，两者是等价的
#define MAXBUFLEN 888
typedef const struct sockaddr* LPCSOCKADDR;

class CSockAddr : public sockaddr_in {
public:
	// constructors
	CSockAddr()
	{ sin_family = AF_INET;
		  sin_port = 0;
		  sin_addr.s_addr = 0; } // Default
	CSockAddr(const SOCKADDR& sa) { memcpy(this, &sa, sizeof(SOCKADDR)); }
	CSockAddr(const SOCKADDR_IN& sin) { memcpy(this, &sin, sizeof(SOCKADDR_IN)); }
	CSockAddr(const ULONG ulAddr, const USHORT ushPort = 0) // parms are host byte ordered
	{ sin_family = AF_INET;
		  sin_port = htons(ushPort);
		  sin_addr.s_addr = htonl(ulAddr); }
	CSockAddr(const char* pchIP, const USHORT ushPort = 0) // dotted IP addr string
	{ sin_family = AF_INET;
		  sin_port = htons(ushPort);
		  sin_addr.s_addr = inet_addr(pchIP); } // already network byte ordered
	// Return the address in dotted-decimal format
	CString DottedDecimal()
	{ return inet_ntoa(sin_addr); } // constructs a new CString object
	// Get port and address (even though they're public)
	USHORT Port() const
	{ return ntohs(sin_port); }
	ULONG IPAddr() const
	{ return ntohl(sin_addr.s_addr); }
	// operators added for efficiency
	const CSockAddr& operator=(const SOCKADDR& sa)
	{ memcpy(this, &sa, sizeof(SOCKADDR));
		  return *this; }
	const CSockAddr& operator=(const SOCKADDR_IN& sin)
	{ memcpy(this, &sin, sizeof(SOCKADDR_IN));
		  return *this; }
	operator SOCKADDR()
	{ return *((LPSOCKADDR) this); }
	operator LPSOCKADDR()
	{ return (LPSOCKADDR) this; }
	operator LPSOCKADDR_IN()
	{ return (LPSOCKADDR_IN) this; }
};


/////////////////////////////////////////////////////////////////////////////
// CMyASock command target

class CMyASock : public CAsyncSocket
{
// Attributes
public:

// Operations
public:
	CMyASock();
	virtual ~CMyASock();

// Overrides
public:
	void SetWndMesg(CWnd * pWnd, UINT Mesg_Type);
	void InitSock(int nPort);
	int SendMesg(const char *pch, const int nSize, LPSOCKADDR psa);
	int RecvMesg(char *pch, const int nSize, CSockAddr & psa);

	UINT Recv_Mesg_Type;
	
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyASock)
	public:
	virtual void OnReceive(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CMyASock)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
	
	CWnd * m_pParent;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYASOCK_H__2F572A0D_5758_48A4_B82E_10CFDF0131E2__INCLUDED_)
