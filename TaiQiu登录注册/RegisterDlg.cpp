// RegisterDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "TaiQiu.h"
#include "RegisterDlg.h"

// CRegisterDlg 对话框

IMPLEMENT_DYNAMIC(CRegisterDlg, CDialog)
CRegisterDlg::CRegisterDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRegisterDlg::IDD, pParent)
	, m_id(_T(""))
	, m_passwd(_T(""))
	, m_passwd2(_T(""))
	, m_email(_T(""))
{
}

CRegisterDlg::~CRegisterDlg()
{
}

void CRegisterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_id);
	DDX_Text(pDX, IDC_EDIT2, m_passwd);
	DDX_Text(pDX, IDC_EDIT3, m_passwd2);
	DDX_Text(pDX, IDC_EDIT4, m_email);
}


BEGIN_MESSAGE_MAP(CRegisterDlg, CDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
END_MESSAGE_MAP()


// CRegisterDlg 消息处理程序

void CRegisterDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if(m_id.IsEmpty() || m_passwd.IsEmpty() || m_passwd2.IsEmpty() || m_email.IsEmpty())
	{
		AfxMessageBox("请填写完所有的项！");
		return;
	}
	if(m_passwd != m_passwd2)
	{
		AfxMessageBox("两次密码不一样，请检查！");
		return;
	}
	OnOK();
}

void CRegisterDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	m_id.Empty();
	OnCancel();
}
