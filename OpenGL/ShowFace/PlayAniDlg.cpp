// PlayAniDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ViewPort.h"
#include "PlayAniDlg.h"

#include "MMSystem.h"
#pragma comment(lib, "winmm.lib")

#include "ViewPortView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPlayAniDlg dialog
void TestforTrash(FILE *fp);
int GetInt(FILE *fp);

CPlayAniDlg::CPlayAniDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPlayAniDlg::IDD, pParent)
{
	m_pParent=pParent;				//For Modalless
	m_nID=CPlayAniDlg::IDD;			//For Modalless
	
	bDSet = FALSE;
	bPlay = FALSE;
	FileName.Empty();
	bIntpl = FALSE;
	fp_swp = NULL;
	sec_top = 0;	sec_btm = 0;
	frm_len = 0;	min_len = 0;
	intpl_fac = 1.0f;

	//{{AFX_DATA_INIT(CPlayAniDlg)
	m_totalfrm = _T("");
	m_curfrm = 0;
	m_playinfo = _T("");
	m_fdet = 1.0f;
	//}}AFX_DATA_INIT
}


void CPlayAniDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPlayAniDlg)
	DDX_Control(pDX, IDC_SLIDER1, m_sfrm);
	DDX_Text(pDX, IDC_TOTALFRM, m_totalfrm);
	DDX_Text(pDX, IDC_CUR_FRM, m_curfrm);
	DDX_Text(pDX, IDC_PLAYINFO, m_playinfo);
	DDX_Text(pDX, IDC_PLAY_SPEED, m_fdet);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPlayAniDlg, CDialog)
	//{{AFX_MSG_MAP(CPlayAniDlg)
	ON_BN_CLICKED(IDC_BTNPLAY, OnBtnplay)
	ON_BN_CLICKED(IDC_BTNPAUSE, OnBtnpause)
	ON_BN_CLICKED(IDC_BTNSTOP, OnBtnstop)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER1, OnCustomdrawSlider1)
	ON_BN_CLICKED(IDC_GOTO, OnGoto)
	ON_BN_CLICKED(IDC_PREV_FRM, OnPrevFrm)
	ON_BN_CLICKED(IDC_NEXT_FRM, OnNextFrm)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPlayAniDlg message handlers

void CPlayAniDlg::OnOK() 
{
	// TODO: Add extra validation here
	
//	CDialog::OnOK();
}

void CPlayAniDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	if(bPlay)		return;

	if(fp_swp)
	{
		fclose(fp_swp);
		system("del ANI_TMP");
	}
	au = 5e-4f;
	((CViewPortView *)m_pParent)->m_pPlayAniDlg = NULL;
	DestroyWindow();
	
//	CDialog::OnCancel();
}


BOOL CPlayAniDlg::Create()
{
	return(CDialog::Create(m_nID,m_pParent));
}


void CPlayAniDlg::PostNcDestroy() 
{
	// TODO: Add your specialized code here and/or call the base class
	delete this;	
//	CDialog::PostNcDestroy();
}


BOOL CPlayAniDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	VERIFY(m_BtnPlay.AutoLoad(IDC_BTNPLAY, this));
	VERIFY(m_BtnPause.AutoLoad(IDC_BTNPAUSE, this));
	VERIFY(m_BtnStop.AutoLoad(IDC_BTNSTOP, this));

	ReadAniFile();
	m_sfrm.SetRange(0, total_frm-1, FALSE);
	m_totalfrm.Format("%d", total_frm);
	m_playinfo.Format("%.2d:%.2d:%.3d\tPlay %d Frames, Skip %d Frames, ¡« %.3f fps", 0, 0, 0, 0, 0, 0);

	idx = 0;
	cur_Frm = 0;
	play_t = 0;
	skip_frm = 0;
	play_frm = 0;
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPlayAniDlg::OnBtnplay() 
{
	// TODO: Add your control notification handler code here
	if(bPlay)		return;
	
	bPlay = TRUE;
	m_BtnPlay.SetState(TRUE);
	m_BtnPause.SetState(FALSE);
	UpdateData(TRUE);
	if(!((m_fdet >= 0.01f && m_fdet <= 100.0f) || (m_fdet <= -0.01f && m_fdet >= -100.0f)))		return;
	CEdit * pe = (CEdit *)GetDlgItem(IDC_PLAY_SPEED);
	pe->SetReadOnly(TRUE);
	if(WavFile[0] != '\0')
	{
		SetTimer(3, 30, NULL);
	}
	PlayAniFile();
	pe->SetReadOnly(FALSE);
}

void CPlayAniDlg::OnBtnpause() 
{
	// TODO: Add your control notification handler code here
	if(cur_Frm == 0)	return;
	if(!bPlay)			return;

	bPlay = !bPlay;
	m_BtnPlay.SetState(bPlay);
	m_BtnPause.SetState(!bPlay);
//	if(bPlay)
//		PlayAniFile();
}

void CPlayAniDlg::OnBtnstop() 
{
	// TODO: Add your control notification handler code here
	bPlay = FALSE;
	intpl_fac = 1.0f;
	
	bDSet = TRUE;	m_sfrm.SetPos(0);	bDSet = FALSE;
	cur_Frm = 0;		TestSection();
	m_curfrm = 0;
	UpdateData(FALSE);
	PlayFrame();

	m_BtnPlay.SetState(FALSE);
	m_BtnPause.SetState(FALSE);
	
	play_t = 0;
	play_frm = 0;
	skip_frm = 0;
}

void CPlayAniDlg::OnCustomdrawSlider1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	if(!bDSet)
	{
		cur_Frm = m_sfrm.GetPos();		TestSection();
		m_curfrm = cur_Frm;
		UpdateData(FALSE);
		PlayFrame();
	}

//	CString dbg;
//	dbg.Format("Slider Draw at frame %d\n", cur_Frm);
//	OutputDebugString(dbg);
	
	*pResult = 0;
}

void CPlayAniDlg::OnPrevFrm() 
{
	int step;
	UpdateData(TRUE);
	if(m_fdet > 0.0f)
	{	step = (int)(0.5+m_fdet);	if(step == 0)	step = 1;	}
	else
	{	step = (int)(-0.5+m_fdet);	if(step == 0)	step = -1;	}
	cur_Frm -= step;		TestSection();

	bDSet = TRUE;	m_sfrm.SetPos(cur_Frm);	bDSet = FALSE;
	m_curfrm = cur_Frm;
	UpdateData(FALSE);
	PlayFrame();
	
}
void CPlayAniDlg::OnNextFrm() 
{
	int step;
	UpdateData(TRUE);
	if(m_fdet > 0.0f)
	{	step = (int)(0.5+m_fdet);	if(step == 0)	step = 1;	}
	else
	{	step = (int)(-0.5+m_fdet);	if(step == 0)	step = -1;	}
	cur_Frm += step;		TestSection();

	bDSet = TRUE;	m_sfrm.SetPos(cur_Frm);	bDSet = FALSE;
	m_curfrm = cur_Frm;
	UpdateData(FALSE);
	PlayFrame();
}

void CPlayAniDlg::OnGoto() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	cur_Frm = m_curfrm;		TestSection();
	bDSet = TRUE;	m_sfrm.SetPos(cur_Frm);	bDSet = FALSE;
	PlayFrame();
}

void CPlayAniDlg::ReadFrame(pAniParam pa, FILE * fp)
{
	int i;

	TestforTrash(fp);
	
	for(i=0; i<NO_FAPS; i++)
		pa->anifaps[i] = GetInt(fp);
	
	pa->anitime = GetInt(fp);		// for the frame duration time
	if(frm_len)
		pa->anitime = frm_len;		// 40 ms for each frame
	
	if(pa->anifaps[0])				// need explain visems
	{
		pa->aniv1 = GetInt(fp);
		pa->aniv2 = GetInt(fp);
		pa->anivb = GetInt(fp);
		GetInt(fp);
	}
	if(pa->anifaps[1])				// need explain expressions
	{
		pa->anie1 =  GetInt(fp);
		pa->aniev1 = GetInt(fp);
		pa->anie2 =  GetInt(fp);
		pa->aniev2 = GetInt(fp);
		GetInt(fp);
		GetInt(fp);
	}
	
	for(i=2; i<NO_FAPS; i++)
	{
		if(pa->anifaps[i])
			pa->anifaps[i] = GetInt(fp);
	}
	
	fgets(trash,BUFFER_SIZE,fp);
	
}	

void CPlayAniDlg::ReadAniFile()
{
	FILE * fp;
	float version, fps;
	int f;
	AniParam tmpfrm;

	strcpy(WavFile, FileName);
	f = strlen(WavFile);
	WavFile[f-3] = 'w';	WavFile[f-2] = 'a';	WavFile[f-1] = 'v';
	fp = fopen(WavFile, "rb");
	if(fp == NULL)
	{
		WavFile[0] = '\0';
	}
	else
	{
		fclose(fp);
	}
	
	fp = fopen(FileName, "r");

	if(fp == NULL)
	{
		AfxMessageBox("Read Ani File Error!");
		return;
	}
	
	TestforTrash(fp);
	fscanf(fp, "%f %s %f %d", &version, trash, &fps, &total_frm);
	
	sprintf(trash, "ÈËÁ³Ä£ÐÍ - %s (ver %.1f)", FileName, version);
	SetWindowText(trash);

	if(version == 2.1f){		au = 1e-5f;		bIntpl = TRUE;	}
	else			   {		au = 5e-4f;		bIntpl = FALSE;	}

	if(fps > 0.0)
	{
		frm_len = (int)(1000/fps);
		if(version == 2.5)//	have min fps check to smooth
			min_len = 30;
		else
			min_len = 0;
	}
	else
	{
		frm_len = 0;
		min_len = -(int)(1000/fps);
	}

	sec_btm = total_frm;
	if(total_frm > MAX_FRMS)	sec_btm = MAX_FRMS;

	for(f=0; f<sec_btm; f++)
	{
		ReadFrame(&anip[f], fp);
	}
	memcpy(&top_anip, &anip[0], sizeof(AniParam));
	memcpy(&btm_anip, &anip[sec_btm-1], sizeof(AniParam));

	if(total_frm > MAX_FRMS)	//	Create a Swap Binary File to Quick Access
	{
		fp_swp = fopen("ANI_TMP", "wb");
		if(fp_swp == NULL)
		{
			AfxMessageBox("File too Big, Create Swap File Error!");
			goto end_raf;
		}
		fwrite(anip, sizeof(AniParam), MAX_FRMS, fp_swp);

		ReadFrame(&tmpfrm, fp);
		fwrite(&tmpfrm, sizeof(AniParam), 1, fp_swp);
		memcpy(&btm_anip, &tmpfrm, sizeof(AniParam));
		for(f=MAX_FRMS+1; f<total_frm; f++)
		{
			ReadFrame(&tmpfrm, fp);
			fwrite(&tmpfrm, sizeof(AniParam), 1, fp_swp);
		}
		fclose(fp_swp);
		fp_swp = fopen("ANI_TMP", "rb");
		sec_top = 0;
		if(fp_swp == NULL)
		{
			AfxMessageBox("File too Big, Read Swap File Error!");
			goto end_raf;
		}
	}
	
end_raf:
	fclose(fp);
}

int CPlayAniDlg::SwapTmp(int top)
{
	int left, ret;

	if(top == 0)	return sec_btm;

	left = total_frm - sec_top;
	if(left > MAX_FRMS)		left = MAX_FRMS;

	if(top < 0 && sec_top > 0)
	{
		fseek(fp_swp, (sec_top-1)*sizeof(AniParam), SEEK_SET);
		fread(&top_anip, sizeof(AniParam), 1, fp_swp);
	}
	fseek(fp_swp, sec_top*sizeof(AniParam), SEEK_SET);
	fread(anip, sizeof(AniParam), left, fp_swp);
	ret = sec_top + left;
	
	if(top > 0)
	{
		if(ret < total_frm)
			fread(&btm_anip, sizeof(AniParam), 1, fp_swp);
		else
			memcpy(&btm_anip, &anip[MAX_FRMS-1], sizeof(AniParam));
	}
	if(top < 0 && sec_top == 0)
		memcpy(&top_anip, &anip[0], sizeof(AniParam));

	return (ret);
}

void CPlayAniDlg::TestSection()
{
	if(fp_swp == NULL)
	{
		idx = cur_Frm;
		return;
	}
	if(cur_Frm >= total_frm || cur_Frm < 0)
	{
		idx = 0;
		return;
	}
	if(cur_Frm < sec_top )
	{
		sec_top -= MAX_FRMS;
		memcpy(&btm_anip, &anip[0], sizeof(AniParam));
		sec_btm = SwapTmp(-1);
	}
	else if(cur_Frm >= sec_btm )
	{
		sec_top += MAX_FRMS;
		memcpy(&top_anip, &anip[MAX_FRMS-1], sizeof(AniParam));
		sec_btm = SwapTmp(1);
	}
	idx = cur_Frm - sec_top;
}

void CPlayAniDlg::InsertFrm()
{
	int counter;
	float faps_tmp[NO_FAPS+1];

	for(counter=3;counter<=NO_FAPS;counter++)
		faps_tmp[counter] = intpl_fac * faps[counter];
	
	if(m_fdet > 0.0f)
	{
		if(idx >= sec_btm-1)
			ParseFrm(&btm_anip);
		else
			ParseFrm(&anip[idx+1]);
	}
	else
	{
		if(idx < 1)
			ParseFrm(&top_anip);
		else
			ParseFrm(&anip[idx-1]);
	}

	for(counter=3;counter<=NO_FAPS;counter++)
		faps[counter] = faps_tmp[counter] + (1.0f-intpl_fac)*faps[counter];
	
}

void CPlayAniDlg::ParseFrm(pAniParam p)
{
	if(p->anifaps[0])
	{
		viseme1 = p->aniv1;
		viseme2 = p->aniv2;
		vis_blend = p->anivb;
	}
	if(p->anifaps[1])
	{
		expres1 = p->anie1;
		exp_val1 = p->aniev1;
		expres2 = p->anie2;
		exp_val2 = p->aniev2;
	}
	for(int i=0; i<NO_FAPS; i++)
		faps[i+1] = (float)(p->anifaps[i]);
	
	ParseExpVis();
}

void CPlayAniDlg::PlayFrame()
{
	((CViewPortView *)m_pParent)->ResetFaceModel();
	ResetFaps();

//	CString dbg;
//	dbg.Format("frame %d, fac: %f\n", idx, intpl_fac);
//	OutputDebugString(dbg);

	ParseFrm(&anip[idx]);

	if(min_len && intpl_fac != 1.0f)
	{
		InsertFrm();
	}
//	DoExpression();
//	DoVisem();
	if(bIntpl)		FAP_Interpolation();
	
	if(((CViewPortView *)m_pParent)->m_pFapDlg)
		((CViewPortView *)m_pParent)->m_pFapDlg->RefreshDlg();
	
	DoFaps();
	((CViewPortView *)m_pParent)->ReDrawScene();	
}

void CPlayAniDlg::PlayAniFile()
{
	long begin_t, cur_t, ani_t, tt;
	long pre_frm;
	MSG message;
	int minute, second;
	int play_dir;
	float fps, play_step;

	pre_frm = cur_Frm;
	if(m_fdet > 0.0f)
	{
		play_dir = 1;
		play_step = m_fdet;
	}
	else
	{
		play_dir = -1;
		play_step = -m_fdet;
	}

	begin_t = ::GetTickCount();
	ani_t = 0;

	while(cur_Frm < total_frm && cur_Frm >= 0)
	{
		if(::PeekMessage(&message,NULL,0,0,PM_REMOVE))
		{
			::TranslateMessage(&message);
			::DispatchMessage(&message);
		}
		
		if(!bPlay)		break;

		cur_t = ::GetTickCount() - begin_t;
		
		tt = ani_t - cur_t;
		if(tt > 0)
		{
			if(min_len > 0 && tt >= min_len)
			{
				cur_Frm = pre_frm;		TestSection();
				intpl_fac = 1.0f*tt/(anip[idx].anitime/play_step);
				goto play_it;
			}
			if(tt > 1)				//	if time is too short, no sleep, wait in while(){loop}
				Sleep(tt - 1);
			continue;
		}

		ani_t += (int)(anip[idx].anitime/play_step);
		while(cur_t >= ani_t)
		{
			pre_frm = cur_Frm;
			cur_Frm += play_dir;		TestSection();
			if(cur_Frm >= total_frm || cur_Frm < 0)	goto end_play;
			ani_t += (int)(anip[idx].anitime/play_step);
			skip_frm ++;
		}
		intpl_fac = 1.0f*(ani_t-cur_t)/(anip[idx].anitime/play_step);

play_it:
		play_frm ++;
		tt = play_t + ani_t;
		fps = play_frm*1000.0f / tt;
		minute = tt / 60000;
		tt -= minute*60000;
		second = tt / 1000;
		tt -= second*1000;
		m_playinfo.Format("%.2d:%.2d:%.3d\tPlay %d Frames, Skip %d Frames, ¡« %.3f fps", minute, second, tt, play_frm, skip_frm, fps);
		
		if(cur_Frm != pre_frm)
		{
			bDSet = TRUE;	m_sfrm.SetPos(cur_Frm);	bDSet = FALSE;
			m_curfrm = cur_Frm;
			pre_frm = cur_Frm;
		}
		UpdateData(FALSE);
		
		PlayFrame();
		
		cur_Frm += play_dir;		TestSection();
	}
end_play:
	
	intpl_fac = 1.0f;
	
	if(cur_Frm > 0)
		play_t += ani_t;

	if(bPlay)	OnBtnstop();
}

void CPlayAniDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	if(nIDEvent == 3)
	{
		KillTimer(3);
		PlaySound((LPCTSTR)WavFile, NULL, SND_FILENAME | SND_ASYNC);
	}
	CDialog::OnTimer(nIDEvent);
}
