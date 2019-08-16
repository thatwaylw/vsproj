// LoginDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "TaiQiu.h"
#include "LoginDlg.h"

#include "TaiQiuView.h"

// CLoginDlg 对话框

IMPLEMENT_DYNAMIC(CLoginDlg, CDialog)
CLoginDlg::CLoginDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLoginDlg::IDD, pParent)
	, m_userid(_T(""))
	, m_passwd(_T(""))
{
	m_pParent=pParent;					//For Modalless
	m_nID=CLoginDlg::IDD;				//For Modalless
}

CLoginDlg::~CLoginDlg()
{
}

void CLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_USERID, m_userid);
	DDX_Text(pDX, IDC_PASSWD, m_passwd);
}


BEGIN_MESSAGE_MAP(CLoginDlg, CDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
END_MESSAGE_MAP()


// CLoginDlg 消息处理程序

void CLoginDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
//	OnOK();
	((CTaiQiuView *)m_pParent)->m_pLoginDlg = NULL;
	DestroyWindow();
}

void CLoginDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	m_userid.Empty();
//	OnCancel();
	((CTaiQiuView *)m_pParent)->m_pLoginDlg = NULL;
	DestroyWindow();
}

BOOL CLoginDlg::Create(void)
{
	return(CDialog::Create(m_nID,m_pParent));
}

void CLoginDlg::PostNcDestroy()
{
	// TODO: 在此添加专用代码和/或调用基类
	delete this;
//	CDialog::PostNcDestroy();
}
