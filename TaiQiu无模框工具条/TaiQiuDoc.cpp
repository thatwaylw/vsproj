// TaiQiuDoc.cpp :  CTaiQiuDoc ���ʵ��
//

#include "stdafx.h"
#include "TaiQiu.h"

#include "TaiQiuDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTaiQiuDoc

IMPLEMENT_DYNCREATE(CTaiQiuDoc, CDocument)

BEGIN_MESSAGE_MAP(CTaiQiuDoc, CDocument)
END_MESSAGE_MAP()


// CTaiQiuDoc ����/����

CTaiQiuDoc::CTaiQiuDoc()
{
	// TODO���ڴ����һ���Թ������

}

CTaiQiuDoc::~CTaiQiuDoc()
{
}

BOOL CTaiQiuDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO���ڴ�������³�ʼ������
	// ��SDI �ĵ������ø��ĵ���

	return TRUE;
}




// CTaiQiuDoc ���л�

void CTaiQiuDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO���ڴ���Ӵ洢����
	}
	else
	{
		// TODO���ڴ���Ӽ��ش���
	}
}


// CTaiQiuDoc ���

#ifdef _DEBUG
void CTaiQiuDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CTaiQiuDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CTaiQiuDoc ����
