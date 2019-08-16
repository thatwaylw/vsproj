// FapDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ViewPort.h"
#include "FapDlg.h"

#include "ViewPortView.h"
#include "DoFap.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

int faptab[6][12] = {
	{18,  3, 15, 14,  6, 53,  7, 54, 12, 59, 13, 60},
	{ 4, 51,  8, 55,  9, 56,  5, 52, 10, 57, 11, 58},
	{17, 16, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28},
	{29, 30, 31, 32, 33, 34, 35, 36, 37, 38,  0,  0},
	{39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50},
	{61, 62, 63, 64, 65, 66, 67, 68,  0,  0,  0,  0}
};
char fapname[6][12][20] = {
	{"FAP18:DprsChin",  "FAP3: Open Jaw",  "FAP15:ShiftJaw", "Fap14:ThrustJaw","FAP6: InnLipLft", "Fap53:OutLipLft", "Fap7: InnLipRgt", "Fap54:OutLipRgt", "FAP12:CLLipInn",  "FAP59:CLLipOut",  "FAP13:CRLipInn",  "FAP60:CRLipOut" },
	{"FAP4: UprLipBtm", "FAP51:UprLipTop", "FAP8: ULLipBtm", "FAP55:ULLipTop", "FAP9: URLipBtm",  "FAP56:URLipTop",  "FAP5: LowLipTop", "FAP52:LowLipBtm", "FAP10:LLLipTop",  "FAP57:LLLipBtm",  "FAP11:LRLipTop",  "FAP58:LRLipBtm" },
	{"FAP17:PushULip",  "FAP16:PushLLip",  "FAP19:TopLftEye","FAP20:TopRgtEye","FAP21:BtmLftEye", "FAP22:BtmRgtEye", "FAP23:YawLftEye", "FAP24:YawRgtEye", "FAP25:PthLftEye", "FAP26:PthRgtEye", "FAP27:ThrLftEye", "FAP28:ThrRgtEye"},
	{"FAP29:DltLftPpl", "FAP30:DltRgtPpl", "FAP31:LftInnEbw","FAP32:RgtInnEbw","FAP33:LftMidEbw", "FAP34:RgtMidEbw", "FAP35:LftOutEbw", "FAP36:RgtOutEbw", "FAP37:SqzLftEbw", "FAP38:SqzRgtEbw", "?", "?"},
	{"FAP39:PufLftChk", "FAP40:PufRgtChk", "FAP41:LifLftChk","FAP42:LifRgtChk","FAP43:ShfTgnTip", "FAP44:RseTgnTip", "FAP45:ThtTgnTip", "FAP46:RaiseTgn",  "FAP47:RollTgn",   "FAP48:HeadPitch", "FAP49:HeadRoll",  "FAP50:HeadYaw"},
	{"FAP61:StrLftNos", "FAP62:StrRgtNos", "FAP63:RaiseNose","FAP64:BendNose", "FAP65:RseLftEar", "FAP66:RseRgtEar", "FAP67:PulLftEar", "FAP68:PulRgtEar", "?", "?", "?", "?"}
};
/////////////////////////////////////////////////////////////////////////////
// CFapDlg dialog


CFapDlg::CFapDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFapDlg::IDD, pParent)
{
	m_pParent=pParent;				//For Modalless
	m_nID=CFapDlg::IDD;				//For Modalless
	nTab = 0;
	bDSet = FALSE;
	//{{AFX_DATA_INIT(CFapDlg)
	m_v1 = faps[faptab[nTab][0]];
	m_v2 = faps[faptab[nTab][1]];
	m_v3 = faps[faptab[nTab][2]];
	m_v4 = faps[faptab[nTab][3]];
	m_v5 = faps[faptab[nTab][4]];
	m_v6 = faps[faptab[nTab][5]];
	m_v7 = faps[faptab[nTab][6]];
	m_v8 = faps[faptab[nTab][7]];
	m_v9 = faps[faptab[nTab][8]];
	m_v10 =faps[faptab[nTab][9]];
	m_v11 =faps[faptab[nTab][10]];
	m_v12 =faps[faptab[nTab][11]];
	m_l1 = _T(fapname[nTab][0]);
	m_l2 = _T(fapname[nTab][1]);
	m_l3 = _T(fapname[nTab][2]);
	m_l4 = _T(fapname[nTab][3]);
	m_l5 = _T(fapname[nTab][4]);
	m_l6 = _T(fapname[nTab][5]);
	m_l7 = _T(fapname[nTab][6]);
	m_l8 = _T(fapname[nTab][7]);
	m_l9 = _T(fapname[nTab][8]);
	m_l10 =_T(fapname[nTab][9]);
	m_l11 =_T(fapname[nTab][10]);
	m_l12 =_T(fapname[nTab][11]);
	//}}AFX_DATA_INIT
}


void CFapDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFapDlg)
	DDX_Control(pDX, IDC_FAPSLD9, m_f9);
	DDX_Control(pDX, IDC_FAPSLD2, m_f2);
	DDX_Control(pDX, IDC_FAPSLD12, m_f12);
	DDX_Control(pDX, IDC_FAPSLD11, m_f11);
	DDX_Control(pDX, IDC_FAPSLD10, m_f10);
	DDX_Control(pDX, IDC_FAPSLD1, m_f1);
	DDX_Control(pDX, IDC_FAPSLD8, m_f8);
	DDX_Control(pDX, IDC_FAPSLD7, m_f7);
	DDX_Control(pDX, IDC_FAPSLD6, m_f6);
	DDX_Control(pDX, IDC_FAPSLD5, m_f5);
	DDX_Control(pDX, IDC_FAPSLD4, m_f4);
	DDX_Control(pDX, IDC_FAPSLD3, m_f3);
	DDX_Control(pDX, IDC_TAB1, m_tab);
	DDX_Text(pDX, IDC_FAPVALUE3, m_v3);
	DDX_Text(pDX, IDC_FAPVALUE4, m_v4);
	DDX_Text(pDX, IDC_FAPVALUE5, m_v5);
	DDX_Text(pDX, IDC_FAPVALUE6, m_v6);
	DDX_Text(pDX, IDC_FAPVALUE7, m_v7);
	DDX_Text(pDX, IDC_FAPVALUE8, m_v8);
	DDX_Text(pDX, IDC_FAPVALUE1, m_v1);
	DDX_Text(pDX, IDC_FAPVALUE11, m_v11);
	DDX_Text(pDX, IDC_FAPVALUE12, m_v12);
	DDX_Text(pDX, IDC_FAPVALUE10, m_v10);
	DDX_Text(pDX, IDC_FAPVALUE2, m_v2);
	DDX_Text(pDX, IDC_FAPVALUE9, m_v9);
	DDX_Text(pDX, IDC_L1, m_l1);
	DDX_Text(pDX, IDC_L2, m_l2);
	DDX_Text(pDX, IDC_L3, m_l3);
	DDX_Text(pDX, IDC_L4, m_l4);
	DDX_Text(pDX, IDC_L5, m_l5);
	DDX_Text(pDX, IDC_L6, m_l6);
	DDX_Text(pDX, IDC_L7, m_l7);
	DDX_Text(pDX, IDC_L8, m_l8);
	DDX_Text(pDX, IDC_L9, m_l9);
	DDX_Text(pDX, IDC_L10, m_l10);
	DDX_Text(pDX, IDC_L11, m_l11);
	DDX_Text(pDX, IDC_L12, m_l12);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFapDlg, CDialog)
	//{{AFX_MSG_MAP(CFapDlg)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, OnSelchangeTab1)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_FAPSLD3, OnCustomdrawFapsld3)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_FAPSLD4, OnCustomdrawFapsld4)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_FAPSLD5, OnCustomdrawFapsld5)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_FAPSLD6, OnCustomdrawFapsld6)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_FAPSLD7, OnCustomdrawFapsld7)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_FAPSLD8, OnCustomdrawFapsld8)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_FAPSLD1, OnCustomdrawFapsld1)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_FAPSLD2, OnCustomdrawFapsld2)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_FAPSLD9, OnCustomdrawFapsld9)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_FAPSLD10, OnCustomdrawFapsld10)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_FAPSLD11, OnCustomdrawFapsld11)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_FAPSLD12, OnCustomdrawFapsld12)
	ON_BN_CLICKED(IDC_CLEAR, OnClear)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFapDlg message handlers

void CFapDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	((CViewPortView *)m_pParent)->m_pFapDlg = NULL;
	DestroyWindow();
	
//	CDialog::OnCancel();
}

BOOL CFapDlg::Create()
{
	return(CDialog::Create(m_nID,m_pParent));
}

void CFapDlg::PostNcDestroy() 
{
	// TODO: Add your specialized code here and/or call the base class
	delete this;	
	//	CDialog::PostNcDestroy();
}

BOOL CFapDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	TC_ITEM TabCtrlItem;
	TabCtrlItem.mask = TCIF_TEXT;
	TabCtrlItem.pszText = "×ì²¿";
	m_tab.InsertItem( 0, &TabCtrlItem );
	TabCtrlItem.pszText = "×ì´½";
	m_tab.InsertItem( 1, &TabCtrlItem );
	TabCtrlItem.pszText = "ÑÛ²¿";
	m_tab.InsertItem( 2, &TabCtrlItem );
	TabCtrlItem.pszText = "Ã¼Ã«";
	m_tab.InsertItem( 3, &TabCtrlItem );
	TabCtrlItem.pszText = "Á³²¿";
	m_tab.InsertItem( 4, &TabCtrlItem );
	TabCtrlItem.pszText = "¶ú±Ç";
	m_tab.InsertItem( 5, &TabCtrlItem );
	
	bDSet = TRUE;
	m_f1.SetRange(-1023, 1023, TRUE);	m_f1.SetPos((int)(faps[faptab[nTab][0]]));
	m_f2.SetRange(-1023, 1023, TRUE);	m_f2.SetPos((int)(faps[faptab[nTab][1]]));
	m_f3.SetRange(-1023, 1023, TRUE);	m_f3.SetPos((int)(faps[faptab[nTab][2]]));
	m_f4.SetRange(-1023, 1023, TRUE);	m_f4.SetPos((int)(faps[faptab[nTab][3]]));
	m_f5.SetRange(-1023, 1023, TRUE);	m_f5.SetPos((int)(faps[faptab[nTab][4]]));
	m_f6.SetRange(-1023, 1023, TRUE);	m_f6.SetPos((int)(faps[faptab[nTab][5]]));
	m_f7.SetRange(-1023, 1023, TRUE);	m_f7.SetPos((int)(faps[faptab[nTab][6]]));
	m_f8.SetRange(-1023, 1023, TRUE);	m_f8.SetPos((int)(faps[faptab[nTab][7]]));
	m_f9.SetRange(-1023, 1023, TRUE);	m_f9.SetPos((int)(faps[faptab[nTab][8]]));
	m_f10.SetRange(-1023, 1023, TRUE);	m_f10.SetPos((int)(faps[faptab[nTab][9]]));
	m_f11.SetRange(-1023, 1023, TRUE);	m_f11.SetPos((int)(faps[faptab[nTab][10]]));
	m_f12.SetRange(-1023, 1023, TRUE);	m_f12.SetPos((int)(faps[faptab[nTab][11]]));
	bDSet = FALSE;
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CFapDlg::RefreshDlg()
{
	bDSet = TRUE;
	m_f1.SetPos((int)(faps[faptab[nTab][0]]));
	m_f2.SetPos((int)(faps[faptab[nTab][1]]));
	m_f3.SetPos((int)(faps[faptab[nTab][2]]));
	m_f4.SetPos((int)(faps[faptab[nTab][3]]));
	m_f5.SetPos((int)(faps[faptab[nTab][4]]));
	m_f6.SetPos((int)(faps[faptab[nTab][5]]));
	m_f7.SetPos((int)(faps[faptab[nTab][6]]));
	m_f8.SetPos((int)(faps[faptab[nTab][7]]));
	m_f9.SetPos((int)(faps[faptab[nTab][8]]));
	m_f10.SetPos((int)(faps[faptab[nTab][9]]));
	m_f11.SetPos((int)(faps[faptab[nTab][10]]));
	m_f12.SetPos((int)(faps[faptab[nTab][11]]));
	bDSet = FALSE;
	
	m_v1 = faps[faptab[nTab][0]];
	m_v2 = faps[faptab[nTab][1]];
	m_v3 = faps[faptab[nTab][2]];
	m_v4 = faps[faptab[nTab][3]];
	m_v5 = faps[faptab[nTab][4]];
	m_v6 = faps[faptab[nTab][5]];
	m_v7 = faps[faptab[nTab][6]];
	m_v8 = faps[faptab[nTab][7]];
	m_v9 = faps[faptab[nTab][8]];
	m_v10 =faps[faptab[nTab][9]];
	m_v11 =faps[faptab[nTab][10]];
	m_v12 =faps[faptab[nTab][11]];
	
	m_l1 = _T(fapname[nTab][0]);
	m_l2 = _T(fapname[nTab][1]);
	m_l3 = _T(fapname[nTab][2]);
	m_l4 = _T(fapname[nTab][3]);
	m_l5 = _T(fapname[nTab][4]);
	m_l6 = _T(fapname[nTab][5]);
	m_l7 = _T(fapname[nTab][6]);
	m_l8 = _T(fapname[nTab][7]);
	m_l9 = _T(fapname[nTab][8]);
	m_l10 =_T(fapname[nTab][9]);
	m_l11 =_T(fapname[nTab][10]);
	m_l12 =_T(fapname[nTab][11]);
	UpdateData(FALSE);
}

void CFapDlg::OnSelchangeTab1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	nTab =  m_tab.GetCurSel();
	RefreshDlg();

	*pResult = 0;
}

void CFapDlg::RefreshDraw()
{
	((CViewPortView *)m_pParent)->ResetFaceModel();
	DoFaps();
	((CViewPortView *)m_pParent)->ReDrawScene();	
}

void CFapDlg::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);
	bDSet = TRUE;
	if(m_v1 != faps[faptab[nTab][0]])
	{
		faps[faptab[nTab][0]] = m_v1;
		m_f1.SetPos((int)(m_v1));
	}
	else if(m_v2 != faps[faptab[nTab][1]])
	{
		faps[faptab[nTab][1]] = m_v2;
		m_f2.SetPos((int)(m_v2));
	}
	else if(m_v3 != faps[faptab[nTab][2]])
	{
		faps[faptab[nTab][2]] = m_v3;
		m_f3.SetPos((int)(m_v3));
	}
	else if(m_v4 != faps[faptab[nTab][3]])
	{
		faps[faptab[nTab][3]] = m_v4;
		m_f4.SetPos((int)(m_v4));
	}
	else if(m_v5 != faps[faptab[nTab][4]])
	{
		faps[faptab[nTab][4]] = m_v5;
		m_f5.SetPos((int)(m_v5));
	}
	else if(m_v6 != faps[faptab[nTab][5]])
	{
		faps[faptab[nTab][5]] = m_v6;
		m_f6.SetPos((int)(m_v6));
	}
	else if(m_v7 != faps[faptab[nTab][6]])
	{
		faps[faptab[nTab][6]] = m_v7;
		m_f7.SetPos((int)(m_v7));
	}
	else if(m_v8 != faps[faptab[nTab][7]])
	{
		faps[faptab[nTab][7]] = m_v8;
		m_f8.SetPos((int)(m_v8));
	}
	else if(m_v9 != faps[faptab[nTab][8]])
	{
		faps[faptab[nTab][8]] = m_v9;
		m_f9.SetPos((int)(m_v9));
	}
	else if(m_v10 != faps[faptab[nTab][9]])
	{
		faps[faptab[nTab][9]] = m_v10;
		m_f10.SetPos((int)(m_v10));
	}
	else if(m_v11 != faps[faptab[nTab][10]])
	{
		faps[faptab[nTab][10]] = m_v11;
		m_f11.SetPos((int)(m_v11));
	}
	else if(m_v12 != faps[faptab[nTab][11]])
	{
		faps[faptab[nTab][11]] = m_v12;
		m_f12.SetPos((int)(m_v12));
	}
	bDSet = FALSE;
	
	RefreshDraw();	
	
	CEdit * pe = (CEdit *)GetFocus();
	pe->SetSel(0, 6);
	//	CDialog::OnOK();
}

void CFapDlg::OnCustomdrawFapsld1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	if(!bDSet)
	{
		faps[faptab[nTab][0]] = (float)(m_f1.GetPos());
		m_v1 = faps[faptab[nTab][0]];
		UpdateData(FALSE);
		
		RefreshDraw();	
	}	
	*pResult = 0;
}

void CFapDlg::OnCustomdrawFapsld2(NMHDR* pNMHDR, LRESULT* pResult) 
{
	if(!bDSet)
	{
		faps[faptab[nTab][1]] = (float)(m_f2.GetPos());
		m_v2 = faps[faptab[nTab][1]];
		UpdateData(FALSE);
		
		RefreshDraw();	
	}	
	*pResult = 0;
}

void CFapDlg::OnCustomdrawFapsld3(NMHDR* pNMHDR, LRESULT* pResult) 
{
	if(!bDSet)
	{
		faps[faptab[nTab][2]] = (float)(m_f3.GetPos());
		m_v3 = faps[faptab[nTab][2]];
		UpdateData(FALSE);

		RefreshDraw();	
	}	
	*pResult = 0;
}

void CFapDlg::OnCustomdrawFapsld4(NMHDR* pNMHDR, LRESULT* pResult) 
{
	if(!bDSet)
	{
		faps[faptab[nTab][3]] = (float)(m_f4.GetPos());
		m_v4 = faps[faptab[nTab][3]];
		UpdateData(FALSE);
		
		RefreshDraw();	
	}	
	*pResult = 0;
}

void CFapDlg::OnCustomdrawFapsld5(NMHDR* pNMHDR, LRESULT* pResult) 
{
	if(!bDSet)
	{
		faps[faptab[nTab][4]] = (float)(m_f5.GetPos());
		m_v5 = faps[faptab[nTab][4]];
		UpdateData(FALSE);
		
		RefreshDraw();	
	}	
	*pResult = 0;
}

void CFapDlg::OnCustomdrawFapsld6(NMHDR* pNMHDR, LRESULT* pResult) 
{
	if(!bDSet)
	{
		faps[faptab[nTab][5]] = (float)(m_f6.GetPos());
		m_v6 = faps[faptab[nTab][5]];
		UpdateData(FALSE);
		
		RefreshDraw();	
	}	
	*pResult = 0;
}

void CFapDlg::OnCustomdrawFapsld7(NMHDR* pNMHDR, LRESULT* pResult) 
{
	if(!bDSet)
	{
		faps[faptab[nTab][6]] = (float)(m_f7.GetPos());
		m_v7 = faps[faptab[nTab][6]];
		UpdateData(FALSE);
		
		RefreshDraw();	
	}
	*pResult = 0;
}

void CFapDlg::OnCustomdrawFapsld8(NMHDR* pNMHDR, LRESULT* pResult) 
{
	if(!bDSet)
	{
		faps[faptab[nTab][7]] = (float)(m_f8.GetPos());
		m_v8 = faps[faptab[nTab][7]];
		UpdateData(FALSE);
		
		RefreshDraw();	
	}	
	*pResult = 0;
}

void CFapDlg::OnCustomdrawFapsld9(NMHDR* pNMHDR, LRESULT* pResult) 
{
	if(!bDSet)
	{
		faps[faptab[nTab][8]] = (float)(m_f9.GetPos());
		m_v9 = faps[faptab[nTab][8]];
		UpdateData(FALSE);
		
		RefreshDraw();	
	}	
	*pResult = 0;
}

void CFapDlg::OnCustomdrawFapsld10(NMHDR* pNMHDR, LRESULT* pResult) 
{
	if(!bDSet)
	{
		faps[faptab[nTab][9]] = (float)(m_f10.GetPos());
		m_v10 = faps[faptab[nTab][9]];
		UpdateData(FALSE);
		
		RefreshDraw();	
	}	
	*pResult = 0;
}

void CFapDlg::OnCustomdrawFapsld11(NMHDR* pNMHDR, LRESULT* pResult) 
{
	if(!bDSet)
	{
		faps[faptab[nTab][10]] = (float)(m_f11.GetPos());
		m_v11 = faps[faptab[nTab][10]];
		UpdateData(FALSE);
		
		RefreshDraw();	
	}	
	*pResult = 0;
}

void CFapDlg::OnCustomdrawFapsld12(NMHDR* pNMHDR, LRESULT* pResult) 
{
	if(!bDSet)
	{
		faps[faptab[nTab][11]] = (float)(m_f12.GetPos());
		m_v12 = faps[faptab[nTab][11]];
		UpdateData(FALSE);
		
		RefreshDraw();	
	}	
	*pResult = 0;
}

void CFapDlg::OnClear() 
{
	// TODO: Add your control notification handler code here
	bDSet = TRUE;
	m_f1.SetPos(0);		m_v1 = 0.0f;	faps[faptab[nTab][0]] = 0.0f;
	m_f2.SetPos(0);		m_v2 = 0.0f;	faps[faptab[nTab][1]] = 0.0f;
	m_f3.SetPos(0);		m_v3 = 0.0f;	faps[faptab[nTab][2]] = 0.0f;
	m_f4.SetPos(0);		m_v4 = 0.0f;	faps[faptab[nTab][3]] = 0.0f;
	m_f5.SetPos(0);		m_v5 = 0.0f;	faps[faptab[nTab][4]] = 0.0f;
	m_f6.SetPos(0);		m_v6 = 0.0f;	faps[faptab[nTab][5]] = 0.0f;
	m_f7.SetPos(0);		m_v7 = 0.0f;	faps[faptab[nTab][6]] = 0.0f;
	m_f8.SetPos(0);		m_v8 = 0.0f;	faps[faptab[nTab][7]] = 0.0f;
	m_f9.SetPos(0);		m_v9 = 0.0f;	faps[faptab[nTab][8]] = 0.0f;
	m_f10.SetPos(0);	m_v10 = 0.0f;	faps[faptab[nTab][9]] = 0.0f;
	m_f11.SetPos(0);	m_v11 = 0.0f;	faps[faptab[nTab][10]] = 0.0f;
	m_f12.SetPos(0);	m_v12 = 0.0f;	faps[faptab[nTab][11]] = 0.0f;
	bDSet = FALSE;
	
	UpdateData(FALSE);
	RefreshDraw();
}

