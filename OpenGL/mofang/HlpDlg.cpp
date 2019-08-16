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
	m_edit = "以魔方正对着你的方向为准\r\n\r\n\r\n";

	m_edit+= "左右方向键表示：左旋、右旋90度\r\n";
	m_edit+= "－－按住Q、A、Z键分别表示只上片、中片、下片进行左右旋转\r\n";
	m_edit+= "－－不按则表示整个魔方进行左右旋转\r\n\r\n";

	m_edit+= "上下方向键表示：上旋、下旋90度\r\n";
	m_edit+= "－－按住Q、A、Z键分别表示只左片、中片、右片进行左右旋转\r\n";
	m_edit+= "－－不按则表示整个魔方进行上下旋转\r\n\r\n";

	m_edit+= "Del、PageDown键表示：顺时针旋、逆时针旋90度\r\n";
	m_edit+= "－－按住Q、A、Z键分别表示只后片、中片、前片进行左右旋转\r\n";
	m_edit+= "－－不按则表示整个魔方进行顺时针、逆时针旋转\r\n";

	UpdateData(FALSE);
	
}
