// TestRotDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TestRot.h"
#include "TestRotDlg.h"

#include "math.h"
#define Pi	3.14159

#include "gl\gl.h"
#include "gl\glu.h"
#include "gl\glaux.h"

#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glaux.lib")

#define TableLength		100.0f
#define TableWidth		 65.0f
#define TableDepth		500.0f
#define BallRadius		  33.5f
#define BallSep			20

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CTestRotDlg �Ի���



CTestRotDlg::CTestRotDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTestRotDlg::IDD, pParent)
	, m_info(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestRotDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER1, m_s1);
	DDX_Control(pDX, IDC_SLIDER2, m_s2);
	DDX_Text(pDX, IDC_INFO, m_info);
}

BEGIN_MESSAGE_MAP(CTestRotDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER1, OnNMCustomdrawSlider1)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER2, OnNMCustomdrawSlider2)
END_MESSAGE_MAP()


// CTestRotDlg ��Ϣ�������

BOOL CTestRotDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��\������...\���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO���ڴ���Ӷ���ĳ�ʼ������
	m_s1.SetRange(-180, 180, TRUE);
	m_s2.SetRange(-180, 180, TRUE);
//	m_s1.SetPos(0);
//	m_s2.SetPos(0);

	XRot = 0.0f;
	YRot = 0.0f;
	ZRot = 0.0f;
	xr = 0.0f;
	yr = 0.0f;
	Init();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30.0f, 1.0f, 1.0f, 1000.0f);
	glMatrixMode(GL_MODELVIEW);
	
	return TRUE;  // ���������˿ؼ��Ľ��㣬���򷵻� TRUE
}

void CTestRotDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CTestRotDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ��������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}

	DrawScene();
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù����ʾ��
HCURSOR CTestRotDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

BOOL CTestRotDlg::bSetupPixelFormat()
{
	static PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),
			1,
			PFD_DRAW_TO_WINDOW |
			PFD_SUPPORT_OPENGL |
			PFD_DOUBLEBUFFER,
			PFD_TYPE_RGBA,
			24,
			0,0,0,0,0,
			0,
			0,
			0,
			0,0,0,0,
			32,
			0,
			0,
			PFD_MAIN_PLANE,
			0,
			0,0,0
	};
	int pixelformat;
	
	if((pixelformat = ChoosePixelFormat(m_pDC->GetSafeHdc(),&pfd)) == 0)
	{
		MessageBox("ChoosePixelFormat failed");
		return FALSE;
	}
	
	if(SetPixelFormat(m_pDC->GetSafeHdc(),pixelformat,&pfd) == FALSE)
	{
		MessageBox("SetPixelFormat failed");
		return FALSE;
	}
	return TRUE;
}

void CTestRotDlg::Init(void)
{
	PIXELFORMATDESCRIPTOR pfd;
	int n;
	HGLRC hrc;

	m_pDC =  GetDlgItem(IDC_PIC)->GetDC();

	ASSERT(m_pDC != NULL);

	if(!bSetupPixelFormat())
		return;

	n = ::GetPixelFormat(m_pDC->GetSafeHdc());
	::DescribePixelFormat(m_pDC->GetSafeHdc(),n,sizeof(pfd),&pfd);

	hrc = wglCreateContext(m_pDC->GetSafeHdc());
	wglMakeCurrent(m_pDC->GetSafeHdc(),hrc);

//	GetClientRect(&m_oldRect);

	glEnable(GL_DEPTH_TEST);	// Hidden surface removal
	glFrontFace(GL_CCW);		// Counter clock-wise polygons face out
	glEnable(GL_CULL_FACE);		// Do not calculate inside of jet

//	glEnable(GL_LIGHTING);
//	glEnable(GL_LIGHT0);

	glClearColor(0.0f,0.0f,0.3f,0.0f);

//	TexBits = LoadDIBitmap("pot.bmp", &TexInfo);
}

void CTestRotDlg::DrawScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();

//	glTranslatef(0.0,0.0,-70.0);
//	glRotatef(45.0,1.0,0.0,0.0);

	glTranslatef(0.0f, 0.0f, -TableDepth);
	glRotatef(XRot, 1.0f, 0.0f, 0.0f);
	glRotatef(YRot, 0.0f, 1.0f, 0.0f);
	glRotatef(ZRot, 0.0f, 0.0f, 1.0f);
//	glTranslatef(XTrs, YTrs, 0.0f);

	glColor3f(0.0f, 0.5f, 0.0f);
	glBegin(GL_QUADS);
		glVertex3f(-TableLength, -TableWidth, 0.0f);
		glVertex3f( TableLength, -TableWidth, 0.0f);
		glVertex3f( TableLength,  TableWidth, 0.0f);
		glVertex3f(-TableLength,  TableWidth, 0.0f);
	glEnd();

	glTranslatef(0.0f, 0.0f, BallRadius);
	DrawBall();

	glPopMatrix();

	SwapBuffers(wglGetCurrentDC());
}

void CTestRotDlg::DrawBall()
{
	int i, j;
	float f1, f2, f3, f4, g1, g2, g3, g4;
	float theta = Pi/BallSep;

	glRotatef(yr, 0.0f, 1.0f, 0.0f);
	glRotatef(xr, 1.0f, 0.0f, 0.0f);

	for(i=0; i<BallSep; i++)
	{
		if(i<BallSep/2)	glColor3f(1.0f, 0.0f, 0.0f);
		else			glColor3f(1.0f, 1.0f, 1.0f);
		if(i == 0)
		{		f1 = 0.0f;		f2 = BallRadius;		}
		else
		{		f1 = g1;		f2 = g2;				}
		g1 = BallRadius*sin((i+1)*theta);
		g2 = BallRadius*cos((i+1)*theta);

		for(j=0; j<BallSep; j++)
		{
//			glColor3f((float)(i)/BallSep, (float)(j)/BallSep, 1.0f);
			glBegin(GL_QUADS);

				if(j == 0)
				{		f3 = 0.0f;		f4 = 1.0f;				}
				else
				{		f3 = g3;		f4 = g4;				}
				g3 = sin(2*(j+1)*theta);
				g4 = cos(2*(j+1)*theta);

				glVertex3f(	f1*f4, f1*f3, f2);
				glVertex3f( g1*f4, g1*f3, g2);
				glVertex3f( g1*g4, g1*g3, g2);
				glVertex3f( f1*g4, f1*g3, f2);

			glEnd();

		}
	}
}

BOOL bm = FALSE;
int px;
int py;

void CTestRotDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	bm = TRUE;
	px = point.x;
	py = point.y;

	CDialog::OnLButtonDown(nFlags, point);
}

void CTestRotDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	bm = FALSE;

	CDialog::OnLButtonUp(nFlags, point);
}

void CTestRotDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if(bm)
	{
		ZRot += point.x - px;
		XRot += point.y - py;
		px = point.x;
		py = point.y;
		DrawScene();
	}

	CDialog::OnMouseMove(nFlags, point);
}

void CTestRotDlg::OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	xr = m_s1.GetPos();
	m_info.Format("xr=%f,   yr=%f", xr, yr);
	UpdateData(FALSE);
	DrawScene();
	*pResult = 0;
}

void CTestRotDlg::OnNMCustomdrawSlider2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	yr = m_s2.GetPos();
	m_info.Format("xr=%f,   yr=%f", xr, yr);
	UpdateData(FALSE);
	DrawScene();
	*pResult = 0;
}
