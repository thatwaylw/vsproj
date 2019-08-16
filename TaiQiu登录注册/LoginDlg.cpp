// LoginDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TaiQiu.h"
#include "LoginDlg.h"
#include "RegisterDlg.h"

#include "TaiQiuView.h"

#define VERSION 100
// CLoginDlg �Ի���
#define PWND ((CTaiQiuView *)m_pParent)

IMPLEMENT_DYNAMIC(CLoginDlg, CDialog)
CLoginDlg::CLoginDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLoginDlg::IDD, pParent)
	, m_userid(_T("Victor"))
	, m_passwd(_T(""))
	, m_serverIP(_T("192.168.0.4"))
	, m_serverPT(5239)
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
	DDX_Text(pDX, IDC_SERVERIP, m_serverIP);
	DDX_Text(pDX, IDC_SERVERPT, m_serverPT);
}


BEGIN_MESSAGE_MAP(CLoginDlg, CDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_BN_CLICKED(IDB_REGISTER, OnBnClickedRegister)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDB_DELUSER, OnBnClickedDeluser)
END_MESSAGE_MAP()


// CLoginDlg ��Ϣ�������

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

BOOL CLoginDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	CEdit * pe = (CEdit *)GetDlgItem(IDC_PASSWD);
	pe->SetSel(0, 20);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣��OCX ����ҳӦ���� FALSE
}

void CLoginDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
//	OnOK();
	CString mesg;
	if(m_userid.IsEmpty() || m_passwd.IsEmpty())
	{
		AfxMessageBox("�������û���������");
		return;
	}
	mesg.Format("L%s,%s,%d,", m_userid, m_passwd, VERSION);
	CSockAddr psa = CSockAddr(m_serverIP, m_serverPT);
	PWND->pSock->SendMesg(mesg, mesg.GetLength(), psa);

	SetWindowText("���ڵ�¼PlayNet ...");
	SetTimer(0, 6000, NULL);		// 6���ӻ��޻�Ӧ����Ϊ��ʱ
}

void CLoginDlg::OnBnClickedRegister()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CRegisterDlg dlg;
	dlg.DoModal();
	if(dlg.m_id.IsEmpty())
		return;

	CString mesg;
	mesg.Format("Ra%s,%s,%s,", dlg.m_id, dlg.m_passwd, dlg.m_email);
	CSockAddr psa = CSockAddr(m_serverIP, m_serverPT);
	PWND->pSock->SendMesg(mesg, mesg.GetLength(), psa);

	SetWindowText("����ע��PlayNet ...");
	SetTimer(0, 6000, NULL);		// 6���ӻ��޻�Ӧ����Ϊ��ʱ
}

void CLoginDlg::OnBnClickedDeluser()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);

	CString mesg;
	mesg.Format("Rd%s,%s,", m_userid, m_passwd);
	CSockAddr psa = CSockAddr(m_serverIP, m_serverPT);
	PWND->pSock->SendMesg(mesg, mesg.GetLength(), psa);

	SetWindowText("��������PlayNet ...");
	SetTimer(0, 6000, NULL);		// 6���ӻ��޻�Ӧ����Ϊ��ʱ
}

void CLoginDlg::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_userid.Empty();
//	OnCancel();
	KillTimer(0);
	PWND->m_pLoginDlg = NULL;
	DestroyWindow();
}

void CLoginDlg::OnTimer(UINT nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if(nIDEvent == 0)
	{
		SetWindowText("�޷�����PlayNet!!");
		MessageBeep(MB_ICONQUESTION);
		KillTimer(0);
	}

	CDialog::OnTimer(nIDEvent);
}
