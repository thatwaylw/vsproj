// LoginDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TaiQiu.h"
#include "LoginDlg.h"

#include "TaiQiuView.h"

// CLoginDlg �Ի���

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


// CLoginDlg ��Ϣ�������

void CLoginDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
//	OnOK();
	((CTaiQiuView *)m_pParent)->m_pLoginDlg = NULL;
	DestroyWindow();
}

void CLoginDlg::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ����ר�ô����/����û���
	delete this;
//	CDialog::PostNcDestroy();
}
