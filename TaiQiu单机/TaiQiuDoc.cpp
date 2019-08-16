// TaiQiuDoc.cpp :  CTaiQiuDoc 类的实现
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


// CTaiQiuDoc 构造/销毁

CTaiQiuDoc::CTaiQiuDoc()
{
	// TODO：在此添加一次性构造代码

}

CTaiQiuDoc::~CTaiQiuDoc()
{
}

BOOL CTaiQiuDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO：在此添加重新初始化代码
	// （SDI 文档将重用该文档）

	return TRUE;
}




// CTaiQiuDoc 序列化

void CTaiQiuDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO：在此添加存储代码
	}
	else
	{
		// TODO：在此添加加载代码
	}
}


// CTaiQiuDoc 诊断

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


// CTaiQiuDoc 命令
