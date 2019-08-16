// rcubeDoc.cpp : implementation of the CRcubeDoc class
//

#include "stdafx.h"
#include "rcube.h"

#include "rcubeDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRcubeDoc

IMPLEMENT_DYNCREATE(CRcubeDoc, CDocument)

BEGIN_MESSAGE_MAP(CRcubeDoc, CDocument)
	//{{AFX_MSG_MAP(CRcubeDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRcubeDoc construction/destruction

CRcubeDoc::CRcubeDoc()
{
	// TODO: add one-time construction code here

}

CRcubeDoc::~CRcubeDoc()
{
}

BOOL CRcubeDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CRcubeDoc serialization

void CRcubeDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CRcubeDoc diagnostics

#ifdef _DEBUG
void CRcubeDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CRcubeDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CRcubeDoc commands
