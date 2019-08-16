// PlayNetDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "TaiQiu.h"
#include "PlayNetDlg.h"

#include "TaiQiuView.h"

// CPlayNetDlg 对话框
#define PWND ((CTaiQiuView *)m_pParent)

IMPLEMENT_DYNAMIC(CPlayNetDlg, CDialog)
CPlayNetDlg::CPlayNetDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPlayNetDlg::IDD, pParent)
	, m_uid(_T(""))
	, m_info(_T(""))
	, m_talk(_T(""))
{
	m_pParent = pParent;					//For Modalless
	m_nID = CPlayNetDlg::IDD;				//For Modalless
}

CPlayNetDlg::~CPlayNetDlg()
{
}

void CPlayNetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DESKS, m_desk);
	DDX_Control(pDX, IDC_LOBBY, m_lobby);
	DDX_Text(pDX, IDC_UID, m_uid);
	DDX_Text(pDX, IDC_INFO, m_info);
	DDX_Text(pDX, IDC_TALK, m_talk);
}


BEGIN_MESSAGE_MAP(CPlayNetDlg, CDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_BN_CLICKED(IDC_JOIN, OnBnClickedJoin)
	ON_BN_CLICKED(IDC_QUERY, OnBnClickedQuery)
	ON_BN_CLICKED(IDC_QUIT, OnBnClickedQuit)
	ON_BN_CLICKED(IDC_SENDTALK, OnBnClickedSendtalk)
	ON_BN_CLICKED(IDC_REFRESH, OnBnClickedRefresh)
END_MESSAGE_MAP()


// CPlayNetDlg 消息处理程序

void CPlayNetDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
//	OnOK();
}

void CPlayNetDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	PWND->m_pPlayNetDlg = NULL;
	DestroyWindow();
//	OnCancel();
}

BOOL CPlayNetDlg::Create(void)
{
	return(CDialog::Create(m_nID,m_pParent));
}

void CPlayNetDlg::PostNcDestroy()
{
	delete this;
//	CDialog::PostNcDestroy();
}

BOOL CPlayNetDlg::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message==WM_KEYDOWN && pMsg->wParam == VK_ESCAPE)	//Let Esc cant quit, hehe
	{
		return FALSE;
	}
	return CDialog::PreTranslateMessage(pMsg);
}

BOOL CPlayNetDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_ImgList.DeleteImageList();
	m_ImgList.Create(16, 16, ILC_COLOR16, 256, 8);

	m_ImgList.Add(AfxGetApp()->LoadIcon(IDI_ICON0));	//User
	m_ImgList.Add(AfxGetApp()->LoadIcon(IDI_ICON1));	//Playing
	m_ImgList.Add(AfxGetApp()->LoadIcon(IDI_ICON2));	//Empty

	m_lobby.SetImageList(&m_ImgList, LVSIL_SMALL);
	m_desk.SetImageList(&m_ImgList, LVSIL_SMALL);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常：OCX 属性页应返回 FALSE
}

void CPlayNetDlg::OnBnClickedJoin()
{
	// TODO: 在此添加控件通知处理程序代码
	int nItem = -1;
	nItem = m_desk.GetNextItem(nItem, LVNI_SELECTED);

	if(nItem < 0 || nItem >= MAXPAIR)	return;

	CString mesg;
	mesg.Format("J%d,%s,", nItem, PWND->userid);
	PWND->pSock->SendMesg(mesg, mesg.GetLength(), PWND->Serverpsa);
}

void CPlayNetDlg::OnBnClickedQuery()
{
	// TODO: 在此添加控件通知处理程序代码
}

void CPlayNetDlg::OnBnClickedRefresh()
{
	// TODO: 在此添加控件通知处理程序代码
    PWND->pSock->SendMesg("U", 1, PWND->Serverpsa);
}

void CPlayNetDlg::OnBnClickedQuit()
{
	// TODO: 在此添加控件通知处理程序代码
}

void CPlayNetDlg::OnBnClickedSendtalk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
//	AppendMesg(PWND->userid + ": " + m_talk);
//	if(m_talk[0] == '/') ... 
	CString mesg;
	mesg.Format("C%s: %s", PWND->userid, m_talk);
	PWND->pSock->SendMesg(mesg, mesg.GetLength(), PWND->Serverpsa);

	CEdit * pEdit = (CEdit *)GetDlgItem(IDC_TALK);
	pEdit->SetWindowText("");
	pEdit->SetFocus();
}

void CPlayNetDlg::AppendMesg(CString mesg)
{
	m_info += mesg;
	m_info += "\r\n";
	UpdateData(FALSE);

	CEdit * pEdit = (CEdit *)GetDlgItem(IDC_INFO);
	int lines = pEdit->GetLineCount();
	pEdit->LineScroll(lines);
}

