// HlpDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ViewPort.h"
#include "HlpDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHlpDlg dialog


CHlpDlg::CHlpDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CHlpDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CHlpDlg)
	m_edit = _T("");
	//}}AFX_DATA_INIT
}


void CHlpDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHlpDlg)
	DDX_Text(pDX, IDC_EDIT1, m_edit);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CHlpDlg, CDialog)
	//{{AFX_MSG_MAP(CHlpDlg)
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHlpDlg message handlers

void CHlpDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	
	// TODO: Add your message handler code here
	m_edit = "��ħ����������ķ���Ϊ׼\r\n\r\n\r\n";

	m_edit+= "���ҷ������ʾ������������90��\r\n";
	m_edit+= "������סQ��A��Z���ֱ��ʾֻ��Ƭ����Ƭ����Ƭ����������ת\r\n";
	m_edit+= "�����������ʾ����ħ������������ת\r\n\r\n";

	m_edit+= "���·������ʾ������������90��\r\n";
	m_edit+= "������סQ��A��Z���ֱ��ʾֻ��Ƭ����Ƭ����Ƭ����������ת\r\n";
	m_edit+= "�����������ʾ����ħ������������ת\r\n\r\n";

	m_edit+= "Del��PageDown����ʾ��˳ʱ��������ʱ����90��\r\n";
	m_edit+= "������סQ��A��Z���ֱ��ʾֻ��Ƭ����Ƭ��ǰƬ����������ת\r\n";
	m_edit+= "�����������ʾ����ħ������˳ʱ�롢��ʱ����ת\r\n";

	UpdateData(FALSE);
	
}
