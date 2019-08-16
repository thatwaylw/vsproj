// TaiQiuView.cpp : CTaiQiuView 类的实现
//

#include "stdafx.h"
#include "TaiQiu.h"

#include "TaiQiuDoc.h"
#include "TaiQiuView.h"

#include "math.h"
#define Pi	3.14159
#define PP	0.017453

#include "gl\gl.h"
#include "gl\glu.h"
#include "gl\glaux.h"

#include "mmsystem.h"

//#include "bitmap.c"
#include "GlText.CPP"

#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glaux.lib")

#pragma comment(lib, "winmm.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define LineMode		FALSE
#define HitAction		TRUE
#define SoundOn			TRUE
#define HintsOn			TRUE

#define TableLength		100.0f
#define TableWidth		 65.0f
#define TableDepth		300.0f
#define BallRadius		  3.5f
#define BallSep				20
#define CHR				  2.5f
#define MHR				  2.0f

#define DETTIME 40
#define SUBDETTIME 25
float MAXPOWER = 4.0f*DETTIME;				// 240.0f
float MINDV  = 0.02f*DETTIME/SUBDETTIME;	// 0.8f/25
float ADDV = MAXPOWER/25;					// 10.0f

float power = 0.0f;
float hitx, hity, hitangle;
float mdd, mxpos, mypos;

BOOL rmd = FALSE;
CPoint rp;
BOOL whiteballok;

char hzHints[200];
float hzRed, hzGreen, hzBlue;
int hint_cnt;

#define MAX_CHAT 5
char chat[MAX_CHAT][100];						// 最多显示5行
int chat_ttl[MAX_CHAT] = {0, 0, 0, 0, 0};		// 生存期，最多5秒
int sum_ttl = 0;								// ttl总和，用于判断是否还有字在
BOOL bInputing = FALSE;
char in_chat[100];

//#define ptSize 1.0f
// CTaiQiuView

IMPLEMENT_DYNCREATE(CTaiQiuView, CView)

BEGIN_MESSAGE_MAP(CTaiQiuView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
	ON_WM_SIZE()
	ON_WM_CREATE()
	ON_WM_KEYDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_TIMER()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_DESTROY()
	ON_WM_CHAR()
END_MESSAGE_MAP()

// CTaiQiuView 构造/销毁
void ResetAngle(TBall * pb)
{
	pb->Mat[0][0] = 1.0f;	pb->Mat[0][1] = 0.0f;	pb->Mat[0][2] = 0.0f;
	pb->Mat[1][0] = 0.0f;	pb->Mat[1][1] = 1.0f;	pb->Mat[1][2] = 0.0f;
	pb->Mat[2][0] = 0.0f;	pb->Mat[2][1] = 0.0f;	pb->Mat[2][2] = 1.0f;
}
void ResetBall(TBall * pb)
{
	pb->xpos = 0.0f;
	pb->ypos = 0.0f;
	pb->dir = 0.0f;
	pb->speed = 0.0f;
	pb->bUP = TRUE;
}

CTaiQiuView::CTaiQiuView()
{
	// TODO: 在此处添加构造代码
	XRot = -60.0f;
	YRot = 0.0f;
	ZRot = -20.0f;

	bPlaying = FALSE;
	bNewGame = FALSE;

	srand( (unsigned)time( NULL ) );
}

CTaiQiuView::~CTaiQiuView()
{
}

BOOL CTaiQiuView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改 CREATESTRUCT cs 来修改窗口类或
	// 样式

	return CView::PreCreateWindow(cs);
}

// CTaiQiuView 绘制

void CTaiQiuView::OnDraw(CDC* /*pDC*/)
{
	CTaiQiuDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: 在此处为本机数据添加绘制代码
	DrawScene();
}


// CTaiQiuView 打印

BOOL CTaiQiuView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CTaiQiuView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 打印前添加额外的初始化
}

void CTaiQiuView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 打印后添加清除过程
}


// CTaiQiuView 诊断

#ifdef _DEBUG
void CTaiQiuView::AssertValid() const
{
	CView::AssertValid();
}

void CTaiQiuView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTaiQiuDoc* CTaiQiuView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTaiQiuDoc)));
	return (CTaiQiuDoc*)m_pDocument;
}
#endif //_DEBUG

void MxM(float a[3][3], float b[3][3], float r[3][3])
{
	int i, j, k;
	float sum;

	for(i=0; i<3; i++)
	{
		for(j=0; j<3; j++)
		{
			sum = 0.0f;
			for(k=0; k<3; k++)
			{
				sum += a[i][k]*b[k][j];
			}
			r[i][j] = sum;
		}
	}
}

void MxV(float m[3][3], float v[3], float r[3])
{
	int i, j;
	float sum;

	for(i=0; i<3; i++)
	{
		sum = 0.0f;
		for(j=0; j<3; j++)
		{
			sum += m[i][j]*v[j];
		}
		r[i] = sum;
	}
}

// CTaiQiuView 消息处理程序

BOOL CTaiQiuView::bSetupPixelFormat()
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

void CTaiQiuView::Init(void)
{
	PIXELFORMATDESCRIPTOR pfd;
	int n;
	HGLRC hrc;

	m_pDC =  new CClientDC(this);

	ASSERT(m_pDC != NULL);

	if(!bSetupPixelFormat())
		return;

	n = ::GetPixelFormat(m_pDC->GetSafeHdc());
	::DescribePixelFormat(m_pDC->GetSafeHdc(),n,sizeof(pfd),&pfd);

	hrc = wglCreateContext(m_pDC->GetSafeHdc());
	wglMakeCurrent(m_pDC->GetSafeHdc(),hrc);

	GetClientRect(&m_oldRect);

	glEnable(GL_DEPTH_TEST);	// Hidden surface removal
	glFrontFace(GL_CCW);		// Counter clock-wise polygons face out
	glDisable(GL_CULL_FACE);	// Do not calculate inside of jet
//	glEnable(GL_LINE_SMOOTH);
	glLineWidth(1.0f);
//	glPointSize(ptSize);

//	glEnable(GL_LIGHTING);
//	glEnable(GL_LIGHT0);

	glClearColor(0.0f,0.0f,0.3f,0.0f);

//	PreShowHZ(HZs, "开始游戏！白球落袋，犯规！黑球落袋，罚！中了！！");
//	LoadHZLib("HZK16");
	LoadTextLib("");

//	TexBits = LoadDIBitmap("pot.bmp", &TexInfo);
}

void CTaiQiuView::NewGame()
{	
	bAllStop = TRUE;

//	ShowHints("开始游戏！");
	bPlaying = FALSE;
	bNewGame = TRUE;

	for(int i=0; i<BALLNUM; i++)
	{
		ResetAngle(&Balls[i]);
		RollBall(i, Pi/2*rand()/RAND_MAX, Pi*rand()/RAND_MAX);
		ResetBall(&Balls[i]);
	}
	Balls[0].xpos = -TableLength/2;
//	Balls[1].xpos =  TableLength/2;
	hitx =  -TableLength/2;
	hity = 0.0f;

	int orig_seq[14];		// 自然序列
	int ball_seq[14];		// 球的乱序序列
	int j, k, n;

	for(i=0; i<14; i++)		orig_seq[i] = i;

	for(i=0; i<14; i++)
	{
		k = (int)((14.0-i)*rand()/RAND_MAX);
		n = orig_seq[k]+1;
		if(n >= 8)	n ++;
		ball_seq[i] = n;
		for(j=k+1; j<14-i; j++)		orig_seq[j-1] = orig_seq[j];
	}

	k = 0;
	for(i=1; i<=5; i++)
	for(j=1; j<=i; j++)
	{
		if(k<=3)			n = ball_seq[k];
		else if(k == 4)		n = 8;
		else				n = ball_seq[k-1];
	//	Balls[n].xpos = 1.75f*BallRadius*(i-1+0.01f*rand()/RAND_MAX) + TableLength/3;
	//	Balls[n].ypos = 2.02f*BallRadius*(j-1+0.02f*rand()/RAND_MAX) - 1.01f*BallRadius*(i-1+0.02f*rand()/RAND_MAX);
		Balls[n].xpos = 1.9f*BallRadius*(i-1) + TableLength/3 + (0.01f*rand()/RAND_MAX-0.005f)*BallRadius;
		Balls[n].ypos = 2.2f*BallRadius*(j-1) - 1.1f*BallRadius*(i-1) + (0.01f*rand()/RAND_MAX-0.005f)*BallRadius;
		k ++;
	}
}

void CTaiQiuView::RollBall(int ballNum, float alfa, float beta)
{
/*	float x;
	Balls[ballNum].yr = 180/Pi*atan(tan(beta)*cos(alfa));
	Balls[ballNum].xr = -180/Pi*asin(sin(beta)*sin(alfa));

	if(beta > Pi/2+Pi/20)
	{
		Balls[ballNum].yr = 180.0f + Balls[ballNum].yr;
	}
	
	CString sss;
	sss.Format("xr = %f,    yr = %f\n", Balls[ballNum].xr, Balls[ballNum].yr);
	OutputDebugString(sss);
//	x = atan(tan(PP*Balls[ballNum].xr)/cos(PP*Balls[ballNum].yr));
//	x -= atan(tan(beta)*sin(alfa));
//	Balls[ballNum].yr += 180/Pi*atan(tan(beta)*cos(alfa));
//	Balls[ballNum].xr = 180/Pi*atan(tan(x)*sin(PP*Balls[ballNum].yr));

	Balls[ballNum].xpos = beta*BallRadius*cos(alfa);
	Balls[ballNum].ypos = beta*BallRadius*sin(alfa);
*/
	float m[3][3];
	m[0][0] =  cos(alfa)*cos(alfa)*cos(beta)+sin(alfa)*sin(alfa);
	m[0][1] =  sin(alfa)*cos(alfa)*cos(beta)-sin(alfa)*cos(alfa);
	m[0][2] =  cos(alfa)*sin(beta);
	m[1][0] =  sin(alfa)*cos(alfa)*cos(beta)-sin(alfa)*cos(alfa);
	m[1][1] =  sin(alfa)*sin(alfa)*cos(beta)+cos(alfa)*cos(alfa);
	m[1][2] =  sin(alfa)*sin(beta);
	m[2][0] = -cos(alfa)*sin(beta);
	m[2][1] = -sin(alfa)*sin(beta);
	m[2][2] =  cos(beta);

	float r[3][3];
	MxM(m, Balls[ballNum].Mat, r);
	memcpy(Balls[ballNum].Mat, r, sizeof(float)*3*3);

	Balls[ballNum].xpos += beta*BallRadius*cos(alfa);
	Balls[ballNum].ypos += beta*BallRadius*sin(alfa);

}

float ball_clr[14][3] = {
	{ 1.0, 0.0, 0.0 },	// 1
	{ 0.0, 1.0, 0.0 },	// 2
	{ 0.0, 0.0, 1.0 },	// 3
	{ 0.0, 0.8, 0.8 },	// 4
	{ 0.8, 0.8, 0.0 },	// 5
	{ 0.8, 0.0, 0.8 },	// 6
	{ 0.3, 0.0, 0.5 },	// 7
	{ 1.0, 0.0, 0.0 },	// 1+
	{ 0.0, 1.0, 0.0 },	// 2+
	{ 0.0, 0.0, 1.0 },	// 3+
	{ 0.0, 1.0, 1.0 },	// 4+
	{ 1.0, 1.0, 0.0 },	// 5+
	{ 1.0, 0.0, 1.0 },	// 6+
	{ 0.6, 0.0, 1.0 }	// 7+
};

void CTaiQiuView::DrawBall(int ballNum)
{
	int i, j;
	float f1, f2, f3, f4, g1, g2, g3, g4;
	float theta = Pi/BallSep;
	float v[3];
	float r[3];

//	if(!Balls[ballNum].bUP)		// 在 DrawStat 中调用 （高度和缩放）
//	{
//		Balls[ballNum].xpos = 2*ballNum*TableLength/BALLNUM - TableLength;	// ...
//		Balls[ballNum].ypos = -TableWidth-3*BallRadius;	//...
//	}

	glPushMatrix();
	glTranslatef(Balls[ballNum].xpos, Balls[ballNum].ypos, 0.0f);
//	glRotatef(Balls[ballNum].yr, 0.0f, 1.0f, 0.0f);
//	glRotatef(Balls[ballNum].xr, 1.0f, 0.0f, 0.0f);

	for(i=0; i<BallSep; i++)
	{
		if(i == 0)
		{		f1 = 0.0f;		f2 = BallRadius;		}
		else
		{		f1 = g1;		f2 = g2;				}
		g1 = BallRadius*sin((i+1)*theta);
		g2 = BallRadius*cos((i+1)*theta);

		for(j=0; j<BallSep; j++)
		{
			if(ballNum == 0)
			{
				if(j == 0 || j == BallSep/2)	glColor3f(0.0f, 0.0f, 0.0f);
				else
				{
					if(Balls[0].bUP || whiteballok)
						glColor3f(1.0f, 1.0f, 1.0f);
					else
						glColor3f(0.5f, 0.5f, 0.5f);
				}
			}
			else if(ballNum < 8)
			{
				if((i*2/BallSep + j*4/BallSep) % 2)	glColor3f(1.0f, 1.0f, 1.0f);
				else								glColor3fv(ball_clr[ballNum-1]);
			}
			else if(ballNum > 8)
			{
				if(i>5 && i<=15)	glColor3fv(ball_clr[ballNum-9]);
				else				glColor3f(1.0f, 1.0f, 1.0f);
			}
			else
			{
				if(j == 0 || j == BallSep/2)	glColor3f(1.0f, 1.0f, 1.0f);
				else							glColor3f(0.0f, 0.0f, 0.0f);
			}

			if(j == 0)
			{		f3 = 0.0f;		f4 = 1.0f;				}
			else
			{		f3 = g3;		f4 = g4;				}
			g3 = sin(2*(j+1)*theta);
			g4 = cos(2*(j+1)*theta);

			glBegin(GL_QUADS);

				v[0] = f1*f4; v[1] = f1*f3; v[2] = f2;
				MxV(Balls[ballNum].Mat, v, r);		glVertex3fv(r);
				v[0] = g1*f4; v[1] = g1*f3; v[2] = g2;
				MxV(Balls[ballNum].Mat, v, r);		glVertex3fv(r);
				v[0] = g1*g4; v[1] = g1*g3; v[2] = g2;
				MxV(Balls[ballNum].Mat, v, r);		glVertex3fv(r);
				v[0] = f1*g4; v[1] = f1*g3; v[2] = f2;
				MxV(Balls[ballNum].Mat, v, r);		glVertex3fv(r);
//				glVertex3f(	f1*f4, f1*f3, f2);
//				glVertex3f( g1*f4, g1*f3, g2);
//				glVertex3f( g1*g4, g1*g3, g2);
//				glVertex3f( f1*g4, f1*g3, f2);
			glEnd();
		}
	}
	glPopMatrix();
}

void CTaiQiuView::DrawPartTable(void)
{
	int i;
	float CholeR, MholeR;
	CholeR = BallRadius * 2.0f; //CHR;
	MholeR = BallRadius * 2.0f; //MHR;
    
	glColor3f(0.0f, 0.5f, 0.0f);
	glBegin(GL_QUADS);										// Draw the Center Table
		glVertex3f(0.0f,		0.0f,				0.0f);
		glVertex3f(TableLength, 0.0f,				0.0f);
		glVertex3f(TableLength,	TableWidth-CholeR,	0.0f);
		glVertex3f(0.0f,		TableWidth-CholeR,	0.0f);
	glEnd();
	glBegin(GL_QUADS);										// 上面的一小块
		glVertex3f(TableLength-CholeR,	TableWidth-CholeR,	0.0f);
		glVertex3f(MholeR,				TableWidth-CholeR,	0.0f);
		glVertex3f(MholeR,				TableWidth,			0.0f);
		glVertex3f(TableLength-CholeR,	TableWidth,			0.0f);
	glEnd();
	glBegin(GL_QUADS);										// 左上（中洞）的一点点
		glVertex3f(0.0f,	TableWidth-CholeR,		0.0f);
		glVertex3f(0.0f,	TableWidth-MholeR/2,	0.0f);
		glVertex3f(MholeR,	TableWidth-MholeR/2,	0.0f);
		glVertex3f(MholeR,	TableWidth-CholeR,		0.0f);
	glEnd();
	glBegin(GL_TRIANGLE_FAN);								// 中洞处的弧线，做了Y向2倍压缩
		glVertex3f(MholeR,	TableWidth-MholeR/2,	0.0f);
//		glVertex3f(0.0f,	TableWidth-MholeR/2,	0.0f);
//		glVertex3f(sin(Pi/2/BallSep)*MholeR,	TableWidth-cos(Pi/2/BallSep)*MholeR/2,	0.0f);
		for(i=0; i<=BallSep; i++)
			glVertex3f(sin(i*Pi/2/BallSep)*MholeR,	TableWidth-cos(i*Pi/2/BallSep)*MholeR/2,	0.0f);
	glEnd();
	glBegin(GL_TRIANGLE_FAN);								// 角洞处的弧线
		glVertex3f(TableLength-CholeR,	TableWidth-CholeR,	0.0f);
//		glVertex3f(TableLength,			TableWidth-CholeR,	0.0f);
//		glVertex3f(TableLength-sin(Pi/2/BallSep)*CholeR,	TableWidth-cos(Pi/2/BallSep)*CholeR,	0.0f);
		for(i=0; i<=BallSep; i++)
			glVertex3f(TableLength-sin(i*Pi/2/BallSep)*CholeR,	TableWidth-cos(i*Pi/2/BallSep)*CholeR,	0.0f);
	glEnd();

	glColor3f(0.1f, 0.3f, 0.1f);
	glBegin(GL_QUADS);										// 右壁竖起来的部分
		glVertex3f(TableLength,	TableWidth-CholeR,	0.0f);
		glVertex3f(TableLength,	TableWidth-CholeR,	BallRadius);
		glVertex3f(TableLength,	0.0f,				BallRadius);
		glVertex3f(TableLength,	0.0f,				0.0f);
	glEnd();
	glBegin(GL_QUADS);										// 右壁高出的一条
		glVertex3f(TableLength,			TableWidth-CholeR,	BallRadius);
		glVertex3f(TableLength,			0.0f,				BallRadius);
		glVertex3f(TableLength+CholeR,	0.0f,				BallRadius);
		glVertex3f(TableLength+CholeR,	TableWidth-CholeR,	BallRadius);
	glEnd();

	glBegin(GL_QUADS);										// 上壁竖起来的部分
		glVertex3f(MholeR,				TableWidth,		0.0f);
		glVertex3f(MholeR,				TableWidth,		BallRadius);
		glVertex3f(TableLength-CholeR,	TableWidth,		BallRadius);
		glVertex3f(TableLength-CholeR,	TableWidth,		0.0f);
	glEnd();
	glBegin(GL_QUADS);										// 上壁高出的一条
		glVertex3f(TableLength-CholeR,	TableWidth,			BallRadius);
		glVertex3f(MholeR,				TableWidth,			BallRadius);
		glVertex3f(MholeR,				TableWidth+CholeR,	BallRadius);
		glVertex3f(TableLength-CholeR,	TableWidth+CholeR,	BallRadius);
	glEnd();
	glBegin(GL_TRIANGLE_FAN);								// 上洞高出处的弧线
		glVertex3f(CholeR,	TableWidth+CholeR,	BallRadius);
		for(i=0; i<=BallSep; i++)
			glVertex3f(sin(i*Pi/2/BallSep)*CholeR,	TableWidth+cos(i*Pi/2/BallSep)*CholeR,	BallRadius);
	glEnd();
	glBegin(GL_TRIANGLE_FAN);								// 右洞高出处的弧线（左上角）
		glVertex3f(TableLength-CholeR,	TableWidth+CholeR,	BallRadius);
		for(i=0; i<=BallSep; i++)
			glVertex3f(TableLength-sin(i*Pi/2/BallSep)*CholeR,	TableWidth+cos(i*Pi/2/BallSep)*CholeR,	BallRadius);
	glEnd();
	glBegin(GL_TRIANGLE_FAN);								// 右洞高出处的弧线（最右上角）
		glVertex3f(TableLength+CholeR,	TableWidth+CholeR,	BallRadius);
		for(i=0; i<=BallSep; i++)
			glVertex3f(TableLength+sin(i*Pi/2/BallSep)*CholeR,	TableWidth+cos(i*Pi/2/BallSep)*CholeR,	BallRadius);
	glEnd();
	glBegin(GL_TRIANGLE_FAN);								// 右洞高出处的弧线（右下角）
		glVertex3f(TableLength+CholeR,	TableWidth-CholeR,	BallRadius);
		for(i=0; i<=BallSep; i++)
			glVertex3f(TableLength+sin(i*Pi/2/BallSep)*CholeR,	TableWidth-cos(i*Pi/2/BallSep)*CholeR,	BallRadius);
	glEnd();

	glColor3f(0.05f, 0.2f, 0.05f);
	glBegin(GL_QUADS);										// 上壁镶边
		glVertex3f(0.0f,					TableWidth+CholeR*1.2f,	BallRadius);
		glVertex3f(0.0f,					TableWidth+CholeR,		BallRadius);
		glVertex3f(TableLength+CholeR*1.2f,	TableWidth+CholeR,		BallRadius);
		glVertex3f(TableLength+CholeR*1.2f,	TableWidth+CholeR*1.2f,	BallRadius);
	glEnd();
	glBegin(GL_QUADS);										// 上壁外帮
		glVertex3f(0.0f,					TableWidth+CholeR*1.2f,-BallRadius);
		glVertex3f(0.0f,					TableWidth+CholeR*1.2f, BallRadius);
		glVertex3f(TableLength+CholeR*1.2f,	TableWidth+CholeR*1.2f, BallRadius);
		glVertex3f(TableLength+CholeR*1.2f,	TableWidth+CholeR*1.2f,-BallRadius);
	glEnd();
	glBegin(GL_QUADS);										// 右壁镶边
		glVertex3f(TableLength+CholeR,		TableWidth+CholeR,	BallRadius);
		glVertex3f(TableLength+CholeR,		0.0f,				BallRadius);
		glVertex3f(TableLength+CholeR*1.2f,	0.0f,				BallRadius);
		glVertex3f(TableLength+CholeR*1.2f,	TableWidth+CholeR,	BallRadius);
	glEnd();
	glBegin(GL_QUADS);										// 右壁镶边
		glVertex3f(TableLength+CholeR*1.2f,	TableWidth+CholeR*1.2f,	 BallRadius);
		glVertex3f(TableLength+CholeR*1.2f,	0.0f,					 BallRadius);
		glVertex3f(TableLength+CholeR*1.2f,	0.0f,					-BallRadius);
		glVertex3f(TableLength+CholeR*1.2f,	TableWidth+CholeR*1.2f,	-BallRadius);
	glEnd();

}

void CTaiQiuView::DrawTable(void)
{
	DrawPartTable();
	glPushMatrix();
	glScalef(-1.0f, 1.0f, 1.0f);
	DrawPartTable();
	glPopMatrix();
	glPushMatrix();
	glRotatef(180.0f, 0.0f, 0.0f, 1.0f);
	DrawPartTable();
	glPushMatrix();
	glScalef(-1.0f, 1.0f, 1.0f);
	DrawPartTable();
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 1.3f);	// 画指示线
	glColor3f(0.1f, 0.3f, 0.1f);
	glBegin(GL_LINES);
		glVertex3f(-TableLength/2, TableWidth, 0.0f);
		glVertex3f(-TableLength/2,-TableWidth, 0.0f);
	glEnd();
	DrawArc(BallRadius/2, 0, Pi*2, -TableLength/2, 0.0f);
	
	hzSize = 0.8f;
	hzXpos = -TableLength/3;
	hzYpos = -8*hzSize;
	glColor3f(0.02f, 0.45f, 0.02f);
	ShowText("Victor 制造 :)");

	glPopMatrix();
}

void CTaiQiuView::DrawScene()
{
	int i;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();
//	glTranslatef(0.0f, 0.0f, -100.0f);
	glTranslatef(0.0f, 0.0f, -(TableDepth-BallRadius)/3);
	glScalef(1.0f/3, 1.0f/3, 1.0f/3);

	if(bInputing)
	{
		hzSize = 0.36f;
		hzYpos = -TableWidth/1.2;
		glColor3f(0.0f, 1.0f, 1.0f);

		hzXpos = -TableLength;
		ShowASCII(": ");

		hzXpos = -TableLength+5.76f;	// hzSize*8*strlen(": ");
		ShowText(in_chat);
	}

	if(sum_ttl)
	{
		hzSize = 0.32f;
		hzXpos = -TableLength - 10.0f;
		hzYpos = TableWidth + 5.0f;
		glColor3f(1.0f, 1.0f, 0.0f);

		for(i=0; i<MAX_CHAT; i++)
		{
			if(chat_ttl[i])
			{
				ShowText(chat[i]);
				hzYpos -= 5.12f;	// hzSize*16;
			}
		}
	}

	if(HintsOn)
	{
		if(hzHints[0])
		{
			hzSize = 1.0f*(hint_cnt/40.0f) + 0.2f;
			hzYpos = -hzSize*20 + (40-hint_cnt)*2.0f;
			hzXpos = -hzSize*4*strlen(hzHints);

			hzRed -= 0.02f;
			hzGreen -= 0.01f;
			hzBlue += 0.02f;

			glColor3f(hzRed, hzGreen, hzBlue);
	//		ShowHZ(HZs, hzFrom, hzTo);
			ShowHZ(hzHints);
		}
		if(!bPlaying && bNewGame)
		{
			hzSize = 0.8f;
			hzYpos = TableWidth/2;
			hzXpos = -TableLength/2;

			glColor3f(1.0f, 1.0f, 1.0f);
			ShowHZ("点击鼠标左键开始");
		}
	}

	DrawStat();
	glPopMatrix();

	if(!bAllStop || rmd || !bPlaying || !LineMode)
	{
		glPushMatrix();
		glTranslatef(0.0f, 0.0f, -TableDepth);
		
		if(rmd || !bAllStop || !bPlaying)
		{
			glRotatef(XRot, 1.0f, 0.0f, 0.0f);
			glRotatef(YRot, 0.0f, 1.0f, 0.0f);
			glRotatef(ZRot, 0.0f, 0.0f, 1.0f);
		}

		DrawTable();

		glTranslatef(0.0f, 0.0f, BallRadius);
	//	auxSolidSphere(BallRadius);
		for(i=0; i<BALLNUM; i++)
		{
			if(Balls[i].bUP)
				DrawBall(i);
		}

		if(Balls[0].bUP)
		{
			DrawHit();
		}
		else
		{
			if(!haveCrossing(0))
			{
				whiteballok = TRUE;
			}
			else
			{
				whiteballok = FALSE;
			}
			DrawBall(0);
		}
		glPopMatrix();
	}
	
	SwapBuffers(wglGetCurrentDC());
}

void CTaiQiuView::AddChat(char * str)
{
	int i;
	
	if(str[0] == '\0')	return;

	for(i=0; i<MAX_CHAT; i++)
	{
		if(chat_ttl[i] == 0)
		{
			strcpy(chat[i], str);
			chat_ttl[i] = 8;		// 8秒的生存时间（显示时间）
			
			if(sum_ttl == 0)	
				SetTimer(5, 1000, NULL);

			sum_ttl += 8;

			PlayEffect(4);

			return;
		}
	}
}

void CTaiQiuView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	int i;
	
	if(bInputing)
	{
		i = strlen(in_chat);

		if(nChar == VK_BACK)
		{
			in_chat[i-1] = '\0';
		}
		else if(nChar != VK_RETURN)
		{
			in_chat[i++] = nChar;
			in_chat[i] = '\0';
		}
		
		DrawScene();
	}

	CView::OnChar(nChar, nRepCnt, nFlags);
}

void CTaiQiuView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{

	switch(nChar)
	{
/*	case VK_LEFT:		ZRot += 3.0f;	break;
	case VK_RIGHT:		ZRot -= 3.0f;	break;
	case VK_UP:			XRot += 3.0f;	break;
	case VK_DOWN:		XRot -= 3.0f;	break;
	case VK_DELETE:		YRot += 3.0f;	break;
	case VK_END:		YRot -= 3.0f;	break;	
	case 'Q':			RollBall(0, Pi/4, Pi/10);		break;
	case 'A':			RollBall(0, Pi/4, -Pi/10);		break;
*/
	case VK_SPACE:
		if(bInputing)	break;
		if(XRot == 0.0f && YRot == 0.0f && ZRot == 0.0f)
		{
			XRot = -60.0f;
			YRot = 0.0f;
			ZRot = -20.0f;
		}
		else
		{
			XRot = 0.0f;
			YRot = 0.0f;
			ZRot = 0.0f;
		}
		break;
	case 'R':
		if(bInputing)	break;
		NewGame();		
		break;
	case VK_RETURN:
		if(!bInputing)
		{
			bInputing = TRUE;
			in_chat[0] = '\0';
		}
		else
		{
			bInputing = FALSE;
			AddChat(in_chat);
		}
		break;
	case VK_ESCAPE:
		if(bInputing)
		{
			bInputing = FALSE;
		}
	}
	DrawScene();

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CTaiQiuView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	if(cy > 0)
	{
		glViewport(0,0,cx,cy);
		if((m_oldRect.right > cx) || (m_oldRect.bottom > cy))
			RedrawWindow();

		m_oldRect.right = cx;
		m_oldRect.bottom = cy;
		
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
//		gluPerspective(90.0f,(GLdouble)cx/cy,1.0f,200);
		gluPerspective(30.0f, (GLdouble)cx/cy, 1.0f, 1000.0f);
		
		glMatrixMode(GL_MODELVIEW);
	}

	DrawScene();

}

int CTaiQiuView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	Init();

	NewGame();

	Eff_t = ::GetTickCount();
//	ShowCursor(FALSE);
	return 0;
}

void CTaiQiuView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	SetCursor(NULL);
	rmd = TRUE;
	rp = point;
	if(bAllStop)	DrawScene();
	power = 0.0f;
	KillTimer(2);
	
	CView::OnRButtonDown(nFlags, point);
}

void CTaiQiuView::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	SetCursor(NULL);
	rmd = FALSE;
	if(bAllStop)	DrawScene();
	CView::OnRButtonUp(nFlags, point);
}
/*
BOOL CTaiQiuView::bAllStop()
{
	for(int i=0; i<BALLNUM; i++)
	{
		if(Balls[i].speed > 0.0f)	return FALSE;
	}
	return TRUE;
}*/

float sqr(float x)
{
	return(x*x);
}

float GetAngle(float dx, float dy)
{
	float angle;
	if(dx == 0.0f)
	{
		if(dy >= 0.0f)	return 90.0f;
		else			return 270.0f;
	}
	else
	{
		angle = atan((double)(dy)/dx)/PP;
		if(dx < 0)	angle += 180.0f;
	}
	return angle;
}

void CTaiQiuView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	SetCursor(NULL);
	int dx, dy;
//	float dr;

	if(rmd)
	{
		XRot += point.y - rp.y;
		ZRot += point.x - rp.x;
		rp = point;
		
		if(bAllStop && !(HintsOn && hzHints[0]))
			DrawScene();

		goto quit_MouseMove;
	}

	if(bAllStop && bPlaying)
	{
		dx =  point.x - m_oldRect.right/2;
		dy = -point.y + m_oldRect.bottom/2;
		if(!Balls[0].bUP)
		{
			Balls[0].xpos = dx*159.0f/m_oldRect.Height();
			Balls[0].ypos = dy*159.0f/m_oldRect.Height();
		}
		dx -= Balls[0].xpos*m_oldRect.Height()/159.0f;
		dy -= Balls[0].ypos*m_oldRect.Height()/159.0f;
		if(dx == 0 && dy == 0)	dy = 1;
		mdd = sqrt(dx*dx+dy*dy); 
//		dr = mdd/BallRadius/1.2;
		hitangle = GetAngle((float)dx, (float)dy);
		hitx = Balls[0].xpos;
		hity = Balls[0].ypos;

		if(!(HintsOn && hzHints[0]))
			DrawScene();
	}

quit_MouseMove:
	CView::OnMouseMove(nFlags, point);
}

void CTaiQiuView::DrawArc(float r, float s, float a, float x, float y)
{
	glBegin(GL_LINE_STRIP);
//	glVertex3f(x+r*cos(s), y+r*sin(s), 0.0f);
	for(int i=0; i<=BallSep; i++)
	{
		glVertex3f(x+r*cos(s+i*a/BallSep), y+r*sin(s+i*a/BallSep), 0.0f);
	}
	glEnd();
}

void CTaiQiuView::DrawStat(void)
{
	if(rmd || !bAllStop || !bPlaying)			return;
    
	if(Balls[0].bUP)
	{
		glColor3f(0.0f, 0.5f, 0.5f);							// 力量虚线框
		glBegin(GL_LINE_LOOP);
			glVertex3f(-110.0f, -75.0f, 0.0f);
			glVertex3f(-104.0f, -51.0f, 0.0f);
			glVertex3f(-116.0f, -51.0f, 0.0f);
		glEnd();
		glColor3f(0.0f, 1.0f, 1.0f);
		glBegin(GL_TRIANGLES);									// 力量
			glVertex3f(-110.0f, -75.0f, 0.0f);
			glVertex3f(-110.0f+power*6/MAXPOWER, -75.0f+power*24/MAXPOWER, 0.0f);
			glVertex3f(-110.0f-power*6/MAXPOWER, -75.0f+power*24/MAXPOWER, 0.0f);
		glEnd();
	}
    if(LineMode)
	{
		glBegin(GL_LINE_LOOP);									// 球台
	//	glColor3f(0.0f, 1.0f, 0.0f);
	//	glBegin(GL_QUADS);
			glVertex3f(-TableLength, -TableWidth, 0.0f);
			glVertex3f( TableLength, -TableWidth, 0.0f);
			glVertex3f( TableLength,  TableWidth, 0.0f);
			glVertex3f(-TableLength,  TableWidth, 0.0f);
		glEnd();
	//	glColor3f(0.0f, 0.0f, 0.0f);
		DrawArc(BallRadius*CHR,	0.0f, -Pi/2, -TableLength,  TableWidth);	// 6个洞
		DrawArc(BallRadius*CHR,	0.0f,  Pi/2, -TableLength, -TableWidth);
		DrawArc(BallRadius*CHR,	Pi/2,  Pi/2,  TableLength, -TableWidth);
		DrawArc(BallRadius*CHR,	Pi,    Pi/2,  TableLength,  TableWidth);
		DrawArc(BallRadius*MHR,	0.0f, -Pi,    0.0f,			TableWidth);
		DrawArc(BallRadius*MHR,	0.0f,  Pi,    0.0f,		   -TableWidth);
	}
	
	for(int i=1; i<BALLNUM; i++)										// 色球
	{
		if(!Balls[i].bUP)
		{
			DrawBall(i);
			continue;
		}

		for(int j=0; j<2; j++)
		{
			if(!LineMode)	j ++;
			glPushMatrix();
			if(j == 0)
				glTranslatef(Balls[i].xpos, Balls[i].ypos, 0.0f);
			else
				glTranslatef(i*2*TableLength/BALLNUM - TableLength, 
							 -TableWidth-3*BallRadius, 0.0f);

			if(i<8)
				glColor3fv(ball_clr[i+6]);
			else if(i>8)
				glColor3fv(ball_clr[i-2]);
			else
				glColor3f(0.5f, 0.5f, 0.5f);
			DrawArc(BallRadius,   0.0f, 2*Pi,    0.0f, 0.0f);
			if(i<8)
			{
				glBegin(GL_LINES);
					glVertex3f(0.0f, -BallRadius, 0.0f);
					glVertex3f(0.0f,  BallRadius, 0.0f);
					glVertex3f(-BallRadius, 0.0f, 0.0f);
					glVertex3f( BallRadius, 0.0f, 0.0f);
				glEnd();
			}
			else if(i>8)
			{
				glBegin(GL_LINES);
					glVertex3f(-BallRadius/1.414f, -BallRadius/2, 0.0f);
					glVertex3f( BallRadius/1.414f, -BallRadius/2, 0.0f);
					glVertex3f(-BallRadius/1.414f,  BallRadius/2, 0.0f);
					glVertex3f( BallRadius/1.414f,  BallRadius/2, 0.0f);
				glEnd();
			}
			glPopMatrix();
		}
	}

	if(!Balls[0].bUP)		return;

	glTranslatef(Balls[0].xpos, Balls[0].ypos, 0.0f);					// 白球
	if(LineMode)
	{
		glColor3f(1.0f, 1.0f, 1.0f);
		DrawArc(BallRadius,   0.0f, 2*Pi,    0.0f, 0.0f);
	}
	glRotatef(hitangle, 0.0f, 0.0f, 1.0f);
	glColor3f(1.0f, 1.0f, 1.0f);										// 瞄准线
	glBegin(GL_LINES);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(mdd*159.0f/m_oldRect.Height(), 0.0f, 0.0f);
		glVertex3f(mdd*159.0f/m_oldRect.Height()+BallRadius,		0.0f,				0.0f);
		glVertex3f(mdd*159.0f/m_oldRect.Height()-BallRadius/1.414f, BallRadius/1.414f,	0.0f);
		glVertex3f(mdd*159.0f/m_oldRect.Height()+BallRadius,		0.0f,				0.0f);
		glVertex3f(mdd*159.0f/m_oldRect.Height()-BallRadius/1.414f,-BallRadius/1.414f,	0.0f);
	glEnd();
	DrawArc(BallRadius,   0.0f, 2*Pi, mdd*159.0f/m_oldRect.Height(), 0.0f);		// 瞄准球
}

#define HitLen	78.0f
#define HitSR	0.6f
#define HitBR	1.2f
BOOL bHitting = FALSE;					// 开启了击球动作才需要此段代码
float HitSpeed;							// 开启了击球动作才需要此段代码

void CTaiQiuView::DrawHit()
{
	float a, b, aa, bb;

	if(!bAllStop && !bHitting)	// return;
		glTranslatef(0.0f, 0.0f, 2*BallRadius);
/*
	glPushMatrix();
	glTranslatef(Balls[0].xpos, Balls[0].ypos, 0.0f);
	glRotatef(hitangle, 0.0f, 0.0f, 1.0f);
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_LINES);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(mdd*0.3f, 0.0f, 0.0f);
	glEnd();
	glPopMatrix();
*/
	glTranslatef(hitx, hity, 0.0f);
	glRotatef(hitangle, 0.0f, 0.0f, 1.0f);
	glTranslatef(-power/30-BallRadius*1.2f, 0.0f, 0.0f);

	glColor3f(159/255.0f, 91/255.0f, 0.0f);
	for(int i=0; i<BallSep; i++)
	{
		if(i == 0)
		{
			a = 0.0f;
			b = 1.0f;
		}
		else
		{
			a = aa;
			b = bb;
		}
		aa = sin(Pi*2*(i+1)/BallSep);
		bb = cos(Pi*2*(i+1)/BallSep);
		glBegin(GL_TRIANGLES);
			glVertex3f(0.0f, 0.0f, 0.0f);
			glVertex3f(0.0f, HitSR*a, HitSR*b);
			glVertex3f(0.0f, HitSR*aa, HitSR*bb);
		glEnd();
		glBegin(GL_QUADS);
			glVertex3f(0.0f, HitSR*aa, HitSR*bb);
			glVertex3f(0.0f, HitSR*a, HitSR*b);
			glVertex3f(-HitLen, HitBR*a, HitBR*b+BallRadius);
			glVertex3f(-HitLen, HitBR*aa, HitBR*bb+BallRadius);
		glEnd();
		glBegin(GL_TRIANGLES);
			glVertex3f(-HitLen, 0.0f, BallRadius);
			glVertex3f(-HitLen, HitBR*a, HitBR*b+BallRadius);
			glVertex3f(-HitLen, HitBR*aa, HitBR*bb+BallRadius);
		glEnd();

	}
/*	glBegin(GL_QUADS);
		glVertex3f(0.0f, 0.5f, 0.0f);
		glVertex3f(-60.0f, 1.0f, 0.0f);
		glVertex3f(-60.0f, -1.0f, 0.0f);
		glVertex3f(0.0f, -0.5f, 0.0f);
	glEnd();
*/
}

void CTaiQiuView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	SetCursor(NULL);

	if(!bPlaying && bNewGame)
	{
		bPlaying = TRUE;
		bNewGame = FALSE;
		ShowHints("开始游戏！");
	}
	else
	{
		if(Balls[0].bUP)
			SetTimer(2, 40, NULL);

		else if(!haveCrossing(0))
		{
			Balls[0].bUP = TRUE;
			DrawScene();
		}
	}

	CView::OnLButtonDown(nFlags, point);
}

float BBdis[BALLNUM][BALLNUM];		// 球与球之间的距离
float BWdis[BALLNUM][4];			// 球与壁之间的距离

void CTaiQiuView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	SetCursor(NULL);

	if(Balls[0].bUP && power > 0.0f)
	{
		Balls[0].dir = hitangle;
	/*	hitx = -TableLength;
		hity = TableWidth;
		hitangle = 180.0f;
	*/
	//	speed = mdd/1.5f;
		KillTimer(2);
		Balls[0].speed = power;
		bAllStop = FALSE;
		
		for(int i=0; i<BALLNUM; i++)
		{
			if(!Balls[i].bUP)			continue;

			for(int j=0; j<4; j++)
			{
				if(j==0)		BWdis[i][j] = Balls[i].xpos - (-TableLength);
				else if(j==1)	BWdis[i][j] = (TableLength) - Balls[i].xpos;
				else if(j==2)	BWdis[i][j] = Balls[i].ypos - (-TableWidth);
				else			BWdis[i][j] = (TableWidth)  - Balls[i].ypos;
			}
			
			for(int j=i+1; j<BALLNUM; j++)
			{
				if(!Balls[j].bUP)			continue;
				BBdis[i][j] = sqr(Balls[i].xpos-Balls[j].xpos) + sqr(Balls[i].ypos-Balls[j].ypos);
			}
		}

		if(!HitAction)
		{
			power = 0.0f;						// 在击球动作结束之后再重置
			PlayEffect(0);
			SetTimer(1, DETTIME, NULL);			// 开始滚动
		}
		else									// 开启了击球动作才需要此段代码
		{
			SetTimer(3, 40, NULL);				// 击球动作
			bHitting = TRUE;
			HitSpeed = (power + 0.2*BallRadius)/5;
		}
	}
	CView::OnLButtonUp(nFlags, point);
}

BOOL CTaiQiuView::haveCrossing(int i)	// 此球是否与其他球，壁，洞有交叉，仅仅左1/4桌面有效
{
	int j;
	float dr, A, B, R;

	for(j=0; j<2; j++)				// 入袋
	{
		if(j == 0)
		{	A = -TableLength;	B = TableWidth;	R = CHR*BallRadius;	} // 左上
		else if(j == 1)
		{	A = -TableLength;	B =-TableWidth;	R = CHR*BallRadius;	} // 左下
/*		else if(j == 2)
		{	A = 0.0f;			B = TableWidth;	R = MHR*BallRadius;} // 中上
		else if(j == 3)
		{	A = 0.0f;			B =-TableWidth;	R = MHR*BallRadius;} // 中下
		else if(j == 4)
		{	A = TableLength;	B = TableWidth;	R = CHR*BallRadius;	} // 右上
		else
		{	A = TableLength;	B =-TableWidth;	R = CHR*BallRadius;	} // 右上
*/
		dr = sqr(Balls[i].xpos-A) + sqr(Balls[i].ypos-B);
		if(dr < sqr(R))
			return TRUE;
	}
	for(j=0; j<4; j++)
	{							// 撞击4壁
		if(j==0)		dr = Balls[i].xpos - (-TableLength);
		else if(j==1)	dr = (-TableLength/2+BallRadius+0.5f) - Balls[i].xpos;	//*** 仅仅左1/4桌面有效
		else if(j==2)	dr = Balls[i].ypos - (-TableWidth);
		else			dr = (TableWidth)  - Balls[i].ypos;

		if(dr < BallRadius)
			return TRUE;
	}
	for(j=0; j<BALLNUM; j++)	// 相互撞击
	{
		if(i==j || !Balls[j].bUP)			continue;

		dr = sqr(Balls[i].xpos-Balls[j].xpos) + sqr(Balls[i].ypos-Balls[j].ypos);

		if(dr < 4*sqr(BallRadius))
			return TRUE;
	}
	return FALSE;
}

void CTaiQiuView::DoGodJob()	// 以小角度（最大240/25度）模拟撞击，可不考虑先后撞击顺序
{
	int i, j;
	float dr, A, B, R, b, c, d;
	float vix, viy, vjx, vjy;
	BOOL bCrossing;

	for(i=0; i<BALLNUM; i++)
	{
		if(Balls[i].bUP)
			RollBall(i, PP*Balls[i].dir, PP*Balls[i].speed/25);
	}

	bAllStop = TRUE;

	for(i=0; i<BALLNUM; i++)
	{
		if(!Balls[i].bUP)			continue;

		bCrossing = FALSE;
		for(j=0; j<6; j++)				// 入袋
		{
			if(j == 0)
			{	A = -TableLength;	B = TableWidth;	R = CHR*BallRadius;	} // 左上
			else if(j == 1)
			{	A = -TableLength;	B =-TableWidth;	R = CHR*BallRadius;	} // 左下
			else if(j == 2)
			{	A = 0.0f;			B = TableWidth;	R = MHR*BallRadius;} // 中上
			else if(j == 3)
			{	A = 0.0f;			B =-TableWidth;	R = MHR*BallRadius;} // 中下
			else if(j == 4)
			{	A = TableLength;	B = TableWidth;	R = CHR*BallRadius;	} // 右上
			else
			{	A = TableLength;	B =-TableWidth;	R = CHR*BallRadius;	} // 右上

			dr = sqr(Balls[i].xpos-A) + sqr(Balls[i].ypos-B);
			if(dr < sqr(R))// && Balls[i].speed>0.0f)				// 进了！！
			{
				if(i != 0 && i != 8)
					ShowHints("中了！！");

				Balls[i].bUP = FALSE;
				Balls[i].xpos = 2*i*TableLength/BALLNUM - TableLength;	// ...
				Balls[i].ypos = -TableWidth-3*BallRadius;	//...

				PlayEffect(3);

				break;
			}
		}
		if(!Balls[i].bUP)			continue;

		for(j=0; j<4; j++)
		{							// 撞击4壁
			if(j==0)		dr = Balls[i].xpos - (-TableLength);
			else if(j==1)	dr = (TableLength) - Balls[i].xpos;
			else if(j==2)	dr = Balls[i].ypos - (-TableWidth);
			else			dr = (TableWidth)  - Balls[i].ypos;

			if(dr <= BallRadius)
			{
				if(dr < BWdis[i][j] && BWdis[i][j] > BallRadius)
				{
					if(j < 2)
						Balls[i].dir = 180.0f - Balls[i].dir;
					else
						Balls[i].dir = - Balls[i].dir;

					Balls[i].speed *= 0.95f;

					PlayEffect(2);
				}
				bCrossing = TRUE;
			}
			BWdis[i][j] = dr;
		}

		for(j=i+1; j<BALLNUM; j++)	// 相互撞击
		{
			if(!Balls[j].bUP)			continue;

			dr = sqr(Balls[i].xpos-Balls[j].xpos) + sqr(Balls[i].ypos-Balls[j].ypos);
			d = 4*sqr(BallRadius);
			if(dr <= d)
			{
				if(dr < BBdis[i][j] && BBdis[i][j] > d)
				{
					A = Balls[i].xpos - Balls[j].xpos;
					B = Balls[i].ypos - Balls[j].ypos;
					A /= 2*BallRadius;					// cos(fai)
					B /= 2*BallRadius;					// sin(fai)

					vix = Balls[i].speed*cos(PP*Balls[i].dir);
					viy = Balls[i].speed*sin(PP*Balls[i].dir);
					vjx = Balls[j].speed*cos(PP*Balls[j].dir);
					vjy = Balls[j].speed*sin(PP*Balls[j].dir);

					b = vix*A + viy*B - vjx*A - vjy*B;
					c = 0.025*(sqr(Balls[i].speed)+sqr(Balls[j].speed));
					d = b*b-4*c;
					if(d < 0.0)		R = -b/2;
					else			R = (sqrt(d)-b)/2;

					vix += R*A;
					viy += R*B;
					vjx -= R*A;
					vjy -= R*B;

					Balls[i].speed = sqrt(vix*vix+viy*viy);
					Balls[j].speed = sqrt(vjx*vjx+vjy*vjy);
					Balls[i].dir = GetAngle(vix, viy);
					Balls[j].dir = GetAngle(vjx, vjy);

					PlayEffect(1);
				}
				bCrossing = TRUE;
			}
			BBdis[i][j] = dr;
		}

		dr = Balls[i].speed*0.0005f;
		if(dr < MINDV)	dr = MINDV;
		Balls[i].speed -= dr;

		if(Balls[i].speed <= 0.0f)
		{
			if(bCrossing)
			{
				Balls[i].speed += 1.5f*dr;
				bAllStop = FALSE;
			}
//			for(j=0; j<4; j++)
//				while(BWdis[i][j]) < BallRadius){...} 沿着老方向运动使之与壁再无碰撞
//			for(j=0; j<BALLNUM, j!=i, j is Up; j++)
//				while(BWdis[i][j]) < BallRadius){...} 沿着老方向运动使之与球再无碰撞
//		但是不好，因为其他的球也许还在运动，阻塞在这里不爽，除非在AllStop为所有球判断
			else
			{
				Balls[i].speed = 0.0f;
			}
		}
		else
		{
			bAllStop = FALSE;
		}
	}
}

void CTaiQiuView::OnTimer(UINT nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(nIDEvent == 1)
	{
		for(int i=0; i<SUBDETTIME ;i++)
			DoGodJob();

		if(bAllStop)
		{
			KillTimer(1);
			
			BOOL bAllOver = TRUE;
			
			for(i=1; i<BALLNUM; i++)
				if(Balls[i].bUP)
					bAllOver = FALSE;

			if(!Balls[0].bUP)
				ShowHints("白球落袋，犯规！");

			if(bAllOver)
			{
				NewGame();
			}
			else if(!Balls[8].bUP)	// 黑球落袋，罚回去
			{
				ShowHints("黑球落袋，罚！");

				while(haveCrossing(8))
				{
					Balls[8].xpos = -TableLength + TableLength/2*rand()/RAND_MAX;
					Balls[8].ypos = -TableWidth  + TableWidth*2*rand()/RAND_MAX;
				}
				Balls[8].speed = 0.0f;
				Balls[8].bUP = TRUE;
			}
		}
				
		DrawScene();

	}
	else if(nIDEvent == 2)
	{
		power += ADDV;
		if(power >= MAXPOWER)
		{
			power = MAXPOWER;
			KillTimer(2);
		}

		DrawScene();
	}
	else if(nIDEvent == 3)					// 开启了击球动作才需要此段代码
	{
		power -= HitSpeed;
		DrawScene();
		
		if(power <= -0.2*BallRadius)
		{
			bHitting = FALSE;
			KillTimer(3);

			power = 0.0f;
			PlayEffect(0);
			SetTimer(1, DETTIME, NULL);
		}
	}
	else if(nIDEvent == 4)
	{
		hint_cnt -- ;

		if(hint_cnt <= 0)
		{
			KillTimer(4);
			hzHints[0] = '\0';
		}
		
		DrawScene();

	}
	else if(nIDEvent == 5)
	{
		for(int i=0; i<MAX_CHAT; i++)
		{
			if(chat_ttl[i] > 0)
			{
				chat_ttl[i] --;
				sum_ttl --;
			}
		}
		if(sum_ttl == 0)
			KillTimer(5);

		for(i=0; i<MAX_CHAT; i++)	// 找到第一个不是零的，前移之
		{
			if(chat_ttl[i] > 0)		break;
		}
		if(i == 0)					return;		// 都还在，不要移动了
		for(int j=i; j<MAX_CHAT; j++)
		{
			strcpy(chat[j-i], chat[j]);
			chat_ttl[j-i] = chat_ttl[j];
			chat_ttl[j] = 0;
		}
	}

	CView::OnTimer(nIDEvent);
}

void CTaiQiuView::ShowHints(char * hints)
{
	if(!HintsOn)	return;

	strcpy(hzHints, hints);

	hzSize = 1.2f; 
	hzXpos = -hzSize*4*strlen(hints);
	hzYpos = -hzSize*20;

	hzRed = 1.0f;
	hzGreen = 1.0f;
	hzBlue = 0.0f;

//	DrawScene();

	hint_cnt = 40;
	SetTimer(4, 40, NULL);
}

void CTaiQiuView::PlayEffect(int idx)
{
	if(!SoundOn)
		return;

	DWORD tt = ::GetTickCount();
	if(idx!=3 && tt < Eff_t)	// 前次的播放还没有结束，落袋声音优先播放
		return;
	if(idx == 0)
	{
		PlaySound("Hit.wav", NULL, SND_ASYNC | SND_FILENAME);
		Eff_t = tt+270;
	}
	else if(idx == 1)
	{
		PlaySound("bb.wav", NULL, SND_ASYNC | SND_FILENAME);
		Eff_t = tt+80;
	}
	else if(idx == 2)
	{
		PlaySound("bw.wav", NULL, SND_ASYNC | SND_FILENAME);
		Eff_t = tt+80;
	}
	else if(idx == 3)
	{
		PlaySound("drop.wav", NULL, SND_ASYNC | SND_FILENAME);
		Eff_t = tt+1610;
	}
	else if(idx == 4)
	{
		PlaySound("note.wav", NULL, SND_ASYNC | SND_FILENAME);
		Eff_t = tt+240;
	}
}

void CTaiQiuView::OnDestroy()
{
	HGLRC hrc;
	hrc = ::wglGetCurrentContext();

	::wglMakeCurrent(NULL,NULL);

	if(hrc)
		::wglDeleteContext(hrc);

	if(m_pDC)
		delete m_pDC;

	CView::OnDestroy();
}
