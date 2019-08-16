// RegisterDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TaiQiu.h"
#include "RegisterDlg.h"

// CRegisterDlg �Ի���

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


// CRegisterDlg ��Ϣ�������

void CRegisterDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if(m_id.IsEmpty() || m_passwd.IsEmpty() || m_passwd2.IsEmpty() || m_email.IsEmpty())
	{
		AfxMessageBox("����д�����е��");
		return;
	}
	if(m_passwd != m_passwd2)
	{
		AfxMessageBox("�������벻һ�������飡");
		return;
	}
	OnOK();
}

void CRegisterDlg::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_id.Empty();
	OnCancel();
}
