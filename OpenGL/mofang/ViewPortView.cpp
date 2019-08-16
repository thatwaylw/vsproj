// ViewPortView.cpp : implementation of the CViewPortView class
//

#include "stdafx.h"
#include "ViewPort.h"

#include "ViewPortDoc.h"
#include "ViewPortView.h"
#include "hlpdlg.h"

#include "gl\gl.h"
#include "gl\glu.h"
#include "gl\glaux.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

GLfloat rotstep = 10.0f;
#define TRANS glTranslatef(-2.0f,-1.5f,-7.0f)

short step[9999];
int curstep=0;
short rotdir;

short mofang[6][3][3]=
{
	{{0,0,0},{0,0,0},{0,0,0}},
	{{1,1,1},{1,1,1},{1,1,1}},
	{{2,2,2},{2,2,2},{2,2,2}},
	{{3,3,3},{3,3,3},{3,3,3}},
	{{4,4,4},{4,4,4},{4,4,4}},
	{{5,5,5},{5,5,5},{5,5,5}}
};

GLfloat Color[6][3]=
{
	{1.0f,0.0f,0.0f},
	{0.0f,1.0f,0.0f},
	{1.0f,1.0f,0.0f},
	{0.0f,0.0f,1.0f},
	{0.0f,1.0f,1.0f},
	{1.0f,0.0f,1.0f}
};

GLfloat rx=0.0f,ry=0.0f,rz=0.0f,angleX=0.0f,angleY=0.0f,angleZ=0.0f;

GLfloat rx0=0.0f,ry0=0.0f,rz0=0.0f,angleX0=0.0f,angleY0=0.0f,angleZ0=0.0f;
GLfloat rx1=0.0f,ry1=0.0f,rz1=0.0f,angleX1=0.0f,angleY1=0.0f,angleZ1=0.0f;
GLfloat rx2=0.0f,ry2=0.0f,rz2=0.0f,angleX2=0.0f,angleY2=0.0f,angleZ2=0.0f;

GLfloat cubesize = 0.5f,center=0.0f;
BOOL sht=FALSE,ctl=FALSE;
short qaz=0;

void rotM(int M,short dir)
{
	int i,j;
	short tmp[3][3];

	for(i=0;i<3;i++)
		for(j=0;j<3;j++)
			tmp[i][j] = mofang[M][i][j];

	if(dir == 1){
		for(i=0;i<3;i++){
			mofang[M][2][i]   =  tmp[2-i][2];
			mofang[M][2-i][2] =  tmp[0][2-i];
			mofang[M][0][2-i] =  tmp[i][0];
			mofang[M][i][0]   =  tmp[2][i];
		}
	}
	else if(dir ==-1){
		for(i=0;i<3;i++){
			mofang[M][i][0]   =  tmp[0][2-i];
			mofang[M][0][2-i] =  tmp[2-i][2];
			mofang[M][2-i][2] =  tmp[2][i];
			mofang[M][2][i]   =  tmp[i][0];
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
// CViewPortView

IMPLEMENT_DYNCREATE(CViewPortView, CView)

BEGIN_MESSAGE_MAP(CViewPortView, CView)
	//{{AFX_MSG_MAP(CViewPortView)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_SSZ_Q, OnSszQ)
	ON_COMMAND(ID_SSZ_H, OnSszH)
	ON_COMMAND(ID_SSZ_Z, OnSszZ)
	ON_COMMAND(ID_NSZ_H, OnNszH)
	ON_COMMAND(ID_NSZ_Q, OnNszQ)
	ON_COMMAND(ID_NSZ_Z, OnNszZ)
	ON_COMMAND(ID_SSZ_ALL, OnSszAll)
	ON_COMMAND(ID_NSZ_ALL, OnNszAll)
	ON_COMMAND(ID_SZ_LEFT, OnSzLeft)
	ON_COMMAND(ID_SZ_MID, OnSzMid)
	ON_COMMAND(ID_SZ_RIGHT, OnSzRight)
	ON_COMMAND(ID_SZ_ALL, OnSzAll)
	ON_COMMAND(ID_XZ_LEFT, OnXzLeft)
	ON_COMMAND(ID_XZ_MID, OnXzMid)
	ON_COMMAND(ID_XZ_RIGHT, OnXzRight)
	ON_COMMAND(ID_XZ_ALL, OnXzAll)
	ON_COMMAND(ID_ZZ_S, OnZzS)
	ON_COMMAND(ID_ZZ_Z, OnZzZ)
	ON_COMMAND(ID_ZZ_X, OnZzX)
	ON_COMMAND(ID_ZZ_ALL, OnZzAll)
	ON_COMMAND(ID_YZ_S, OnYzS)
	ON_COMMAND(ID_YZ_Z, OnYzZ)
	ON_COMMAND(ID_YZ_X, OnYzX)
	ON_COMMAND(ID_YZ_ALL, OnYzAll)
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
	ON_COMMAND(IDM_UNDO, OnUndo)
	ON_COMMAND(IDM_RESET, OnReset)
	ON_WM_TIMER()
	ON_COMMAND(IDM_SLOW, OnSlow)
	ON_UPDATE_COMMAND_UI(IDM_SLOW, OnUpdateSlow)
	ON_COMMAND(IDM_HLP, OnHlp)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CViewPortView construction/destruction

CViewPortView::CViewPortView()
{
	// TODO: add construction code here
	m_pDC = NULL;
}

CViewPortView::~CViewPortView()
{
}

BOOL CViewPortView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	cs.style |= WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
//	cs.style ^= WS_MAXIMIZEBOX;

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CViewPortView drawing

void CViewPortView::OnDraw(CDC* pDC)
{
	CViewPortDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	DrawScene();

	CClientDC dc(this);
	dc.TextOut(0,0,"Ä§·½--1.0");

}

/////////////////////////////////////////////////////////////////////////////
// CViewPortView printing

BOOL CViewPortView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CViewPortView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CViewPortView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CViewPortView diagnostics

#ifdef _DEBUG
void CViewPortView::AssertValid() const
{
	CView::AssertValid();
}

void CViewPortView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CViewPortDoc* CViewPortView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CViewPortDoc)));
	return (CViewPortDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CViewPortView message handlers

int CViewPortView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	Init();	
	return 0;
}

void CViewPortView::OnDestroy() 
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

void CViewPortView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	if(cy > 0)
	{
		glViewport(150,150,cx,cy);
//		glViewport(0,0,cx,cy);
		if((m_oldRect.right > cx) || (m_oldRect.bottom > cy))
			RedrawWindow();

		m_oldRect.right = cx;
		m_oldRect.bottom = cy;

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(45.0f,(GLdouble)cx/cy,1.0f,200);
		glMatrixMode(GL_MODELVIEW);
	}
	
}

BOOL CViewPortView::OnEraseBkgnd(CDC* pDC) 
{
	return TRUE;
}

void CViewPortView::Init()
{
	PIXELFORMATDESCRIPTOR pfd;
	int n;
	HGLRC hrc;
	GLfloat fMaxObjSize, fAspect;
	GLfloat fNearPlane, fFarPlane;

	m_pDC =  new CClientDC(this);

	ASSERT(m_pDC != NULL);

	if(!bSetupPixelFormat())
		return;

	n = ::GetPixelFormat(m_pDC->GetSafeHdc());
	::DescribePixelFormat(m_pDC->GetSafeHdc(),n,sizeof(pfd),&pfd);

	hrc = wglCreateContext(m_pDC->GetSafeHdc());
	wglMakeCurrent(m_pDC->GetSafeHdc(),hrc);

	GetClientRect(&m_oldRect);
//	glClearColor(0.0,0.0,0.0,0.0);
	glClearDepth(1.0f);
//	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);

	if(m_oldRect.bottom)
		fAspect = (GLfloat)m_oldRect.right/m_oldRect.bottom;
	else
		fAspect = 1.0f;
	fNearPlane = 1.0f;
	fFarPlane = 200;
	fMaxObjSize = 3.0f;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f,fAspect,fNearPlane,fFarPlane);
	glMatrixMode(GL_MODELVIEW);

	m_busy = FALSE;
	m_complete = FALSE;
	m_undo=FALSE;
	
	center=1.5f*cubesize;
}

BOOL CViewPortView::bSetupPixelFormat()
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

void CViewPortView::DrawScene()
{
	glClearColor(0.0f,0.0f,0.0f,1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();

//	glTranslatef(-2.5f,-2.0f,-2.0f);
//	glRotatef(angle,0.0f,1.0f,0.0f);

	glTranslatef(-2.0f,-1.5f,-7.0f);

	glRotatef(angleX,1.0f,0.0f,0.0f);
	glRotatef(angleY,0.0f,1.0f,0.0f);
	glRotatef(angleZ,0.0f,0.0f,1.0f);

	DrawM0(0,0);
	DrawM1(0,0);
	DrawM2(0,0);
	DrawM3(0,0);
	DrawM4(0,0);
	DrawM5(0,0);

	glPopMatrix();

	glFinish();
	SwapBuffers(wglGetCurrentDC());

	CClientDC dc(this);
	char c[20];
	sprintf(c,"Step:%d",curstep);
	dc.TextOut(0,0,c);
}

void CViewPortView::DrawM0(short dir,short pos)
{
	int i,j;

	if(dir == 0)
	for(i=0;i<3;i++)
		for(j=0;j<3;j++)
		{
			glBegin(GL_QUADS);
			glColor3fv(Color[mofang[0][i][j]]);

			glVertex3f(i*cubesize-center,    j*cubesize-center,    0.0f+center);
			glVertex3f((i+1)*cubesize-center,j*cubesize-center,    0.0f+center);
			glVertex3f((i+1)*cubesize-center,(j+1)*cubesize-center,0.0f+center);
			glVertex3f(i*cubesize-center,    (j+1)*cubesize-center,0.0f+center);

			glEnd();
		}
	else if(dir==1)
		for(i=0;i<3;i++)
		{
			glBegin(GL_QUADS);
			glColor3fv(Color[mofang[0][i][pos]]);

			glVertex3f(i*cubesize-center,    pos*cubesize-center,    0.0f+center);
			glVertex3f((i+1)*cubesize-center,pos*cubesize-center,    0.0f+center);
			glVertex3f((i+1)*cubesize-center,(pos+1)*cubesize-center,0.0f+center);
			glVertex3f(i*cubesize-center,    (pos+1)*cubesize-center,0.0f+center);

			glEnd();
		}
	else if(dir==2)
		for(j=0;j<3;j++)
		{
			glBegin(GL_QUADS);
			glColor3fv(Color[mofang[0][pos][j]]);

			glVertex3f(pos*cubesize-center,    j*cubesize-center,    0.0f+center);
			glVertex3f((pos+1)*cubesize-center,j*cubesize-center,    0.0f+center);
			glVertex3f((pos+1)*cubesize-center,(j+1)*cubesize-center,0.0f+center);
			glVertex3f(pos*cubesize-center,    (j+1)*cubesize-center,0.0f+center);

			glEnd();
		}
}

void CViewPortView::DrawM1(short dir,short pos)
{
	int i,j;
	if(dir ==0)
	for(i=0;i<3;i++)
		for(j=0;j<3;j++)
		{
			glBegin(GL_QUADS);
			glColor3fv(Color[mofang[1][i][j]]);

			glVertex3f(3*cubesize-center,j*cubesize-center,    -i*cubesize+center   );
			glVertex3f(3*cubesize-center,(j+1)*cubesize-center,-i*cubesize+center   );
			glVertex3f(3*cubesize-center,(j+1)*cubesize-center,-(i+1)*cubesize+center);
			glVertex3f(3*cubesize-center,j*cubesize-center,    -(i+1)*cubesize+center);

			glEnd();
		}
	else if(dir==1)
		for(i=0;i<3;i++)
		{
			glBegin(GL_QUADS);
			glColor3fv(Color[mofang[1][i][pos]]);

			glVertex3f(3*cubesize-center,pos*cubesize-center,    -i*cubesize+center   );
			glVertex3f(3*cubesize-center,(pos+1)*cubesize-center,-i*cubesize+center   );
			glVertex3f(3*cubesize-center,(pos+1)*cubesize-center,-(i+1)*cubesize+center);
			glVertex3f(3*cubesize-center,pos*cubesize-center,    -(i+1)*cubesize+center);

			glEnd();
		}
	else if(dir==2)
		for(j=0;j<3;j++)
		{
			glBegin(GL_QUADS);
			glColor3fv(Color[mofang[1][pos][j]]);

			glVertex3f(3*cubesize-center,j*cubesize-center,    -pos*cubesize+center   );
			glVertex3f(3*cubesize-center,(j+1)*cubesize-center,-pos*cubesize+center   );
			glVertex3f(3*cubesize-center,(j+1)*cubesize-center,-(pos+1)*cubesize+center);
			glVertex3f(3*cubesize-center,j*cubesize-center,    -(pos+1)*cubesize+center);

			glEnd();
		}

}

void CViewPortView::DrawM2(short dir,short pos)
{
	int i,j;
	if(dir == 0)
	for(i=0;i<3;i++)
		for(j=0;j<3;j++)
		{
			glBegin(GL_QUADS);
			glColor3fv(Color[mofang[2][i][j]]);

			glVertex3f(i*cubesize-center,    3*cubesize-center,-j*cubesize+center    );
			glVertex3f((i+1)*cubesize-center,3*cubesize-center,-j*cubesize+center    );
			glVertex3f((i+1)*cubesize-center,3*cubesize-center,-(j+1)*cubesize+center);
			glVertex3f(i*cubesize-center,    3*cubesize-center,-(j+1)*cubesize+center);

			glEnd();
		}
	else if(dir == 1)
		for(i=0;i<3;i++)
		{
			glBegin(GL_QUADS);
			glColor3fv(Color[mofang[2][i][pos]]);

			glVertex3f(i*cubesize-center,    3*cubesize-center,-pos*cubesize+center    );
			glVertex3f((i+1)*cubesize-center,3*cubesize-center,-pos*cubesize+center    );
			glVertex3f((i+1)*cubesize-center,3*cubesize-center,-(pos+1)*cubesize+center);
			glVertex3f(i*cubesize-center,    3*cubesize-center,-(pos+1)*cubesize+center);

			glEnd();
		}
	else if(dir == 2)
		for(j=0;j<3;j++)
		{
			glBegin(GL_QUADS);
			glColor3fv(Color[mofang[2][pos][j]]);

			glVertex3f(pos*cubesize-center,    3*cubesize-center,-j*cubesize+center    );
			glVertex3f((pos+1)*cubesize-center,3*cubesize-center,-j*cubesize+center    );
			glVertex3f((pos+1)*cubesize-center,3*cubesize-center,-(j+1)*cubesize+center);
			glVertex3f(pos*cubesize-center,    3*cubesize-center,-(j+1)*cubesize+center);

			glEnd();
		}
}

void CViewPortView::DrawM3(short dir,short pos)
{
	int i,j;
	if(dir ==0 )
	for(i=0;i<3;i++)
		for(j=0;j<3;j++)
		{
			glBegin(GL_QUADS);
			glColor3fv(Color[mofang[3][i][j]]);

			glVertex3f(i*cubesize-center,    j*cubesize-center,    -3*cubesize+center);
			glVertex3f((i+1)*cubesize-center,j*cubesize-center,    -3*cubesize+center);
			glVertex3f((i+1)*cubesize-center,(j+1)*cubesize-center,-3*cubesize+center);
			glVertex3f(i*cubesize-center,    (j+1)*cubesize-center,-3*cubesize+center);

			glEnd();
		}
	else if(dir == 1)
		for(i=0;i<3;i++)
		{
			glBegin(GL_QUADS);
			glColor3fv(Color[mofang[3][i][pos]]);

			glVertex3f(i*cubesize-center,    pos*cubesize-center,    -3*cubesize+center);
			glVertex3f((i+1)*cubesize-center,pos*cubesize-center,    -3*cubesize+center);
			glVertex3f((i+1)*cubesize-center,(pos+1)*cubesize-center,-3*cubesize+center);
			glVertex3f(i*cubesize-center,    (pos+1)*cubesize-center,-3*cubesize+center);

			glEnd();
		}
	else if(dir ==2)
		for(j=0;j<3;j++)
		{
			glBegin(GL_QUADS);
			glColor3fv(Color[mofang[3][pos][j]]);

			glVertex3f(pos*cubesize-center,    j*cubesize-center,    -3*cubesize+center);
			glVertex3f((pos+1)*cubesize-center,j*cubesize-center,    -3*cubesize+center);
			glVertex3f((pos+1)*cubesize-center,(j+1)*cubesize-center,-3*cubesize+center);
			glVertex3f(pos*cubesize-center,    (j+1)*cubesize-center,-3*cubesize+center);

			glEnd();
		}
}

void CViewPortView::DrawM4(short dir,short pos)
{
	int i,j;
	if(dir == 0)
	for(i=0;i<3;i++)
		for(j=0;j<3;j++)
		{
			glBegin(GL_QUADS);
			glColor3fv(Color[mofang[4][i][j]]);

			glVertex3f(0.0f-center,j*cubesize-center,    -i*cubesize+center   );
			glVertex3f(0.0f-center,(j+1)*cubesize-center,-i*cubesize+center   );
			glVertex3f(0.0f-center,(j+1)*cubesize-center,-(i+1)*cubesize+center);
			glVertex3f(0.0f-center,j*cubesize-center,    -(i+1)*cubesize+center);

			glEnd();
		}
	else if(dir ==1)
		for(i=0;i<3;i++)
		{
			glBegin(GL_QUADS);
			glColor3fv(Color[mofang[4][i][pos]]);

			glVertex3f(0.0f-center,pos*cubesize-center,    -i*cubesize+center   );
			glVertex3f(0.0f-center,(pos+1)*cubesize-center,-i*cubesize+center   );
			glVertex3f(0.0f-center,(pos+1)*cubesize-center,-(i+1)*cubesize+center);
			glVertex3f(0.0f-center,pos*cubesize-center,    -(i+1)*cubesize+center);

			glEnd();
		}
	else if(dir ==2)
		for(j=0;j<3;j++)
		{
			glBegin(GL_QUADS);
			glColor3fv(Color[mofang[4][pos][j]]);

			glVertex3f(0.0f-center,j*cubesize-center,    -pos*cubesize+center   );
			glVertex3f(0.0f-center,(j+1)*cubesize-center,-pos*cubesize+center   );
			glVertex3f(0.0f-center,(j+1)*cubesize-center,-(pos+1)*cubesize+center);
			glVertex3f(0.0f-center,j*cubesize-center,    -(pos+1)*cubesize+center);

			glEnd();
		}
}

void CViewPortView::DrawM5(short dir,short pos)
{
	int i,j;
	if(dir == 0)
	for(i=0;i<3;i++)
		for(j=0;j<3;j++)
		{
			glBegin(GL_QUADS);
			glColor3fv(Color[mofang[5][i][j]]);

			glVertex3f(i*cubesize-center,    0.0f-center,-j*cubesize+center    );
			glVertex3f((i+1)*cubesize-center,0.0f-center,-j*cubesize+center    );
			glVertex3f((i+1)*cubesize-center,0.0f-center,-(j+1)*cubesize+center);
			glVertex3f(i*cubesize-center,    0.0f-center,-(j+1)*cubesize+center);

			glEnd();
		}
	else if(dir == 1)
		for(i=0;i<3;i++)
		{
			glBegin(GL_QUADS);
			glColor3fv(Color[mofang[5][i][pos]]);

			glVertex3f(i*cubesize-center,    0.0f-center,-pos*cubesize+center    );
			glVertex3f((i+1)*cubesize-center,0.0f-center,-pos*cubesize+center    );
			glVertex3f((i+1)*cubesize-center,0.0f-center,-(pos+1)*cubesize+center);
			glVertex3f(i*cubesize-center,    0.0f-center,-(pos+1)*cubesize+center);

			glEnd();
		}
	else if(dir == 2)
		for(j=0;j<3;j++)
		{
			glBegin(GL_QUADS);
			glColor3fv(Color[mofang[5][pos][j]]);

			glVertex3f(pos*cubesize-center,    0.0f-center,-j*cubesize+center    );
			glVertex3f((pos+1)*cubesize-center,0.0f-center,-j*cubesize+center    );
			glVertex3f((pos+1)*cubesize-center,0.0f-center,-(j+1)*cubesize+center);
			glVertex3f(pos*cubesize-center,    0.0f-center,-(j+1)*cubesize+center);

			glEnd();
		}
}

void CViewPortView::DrawPM(short dir,short pos)
{
	if(dir == 0)		//xy
	{
		glBegin(GL_QUADS);
		glColor3f(0.5f,0.5f,0.5f);

		glVertex3f(0.0f-center,      0.0f-center,	   -pos*cubesize+center);
		glVertex3f(3*cubesize-center,0.0f-center,      -pos*cubesize+center);
		glVertex3f(3*cubesize-center,3*cubesize-center,-pos*cubesize+center);
		glVertex3f(0.0f-center,      3*cubesize-center,-pos*cubesize+center);

		glEnd();
	}
	else if(dir ==1)	//yz
	{
		glBegin(GL_QUADS);
		glColor3f(0.5f,0.5f,0.5f);

		glVertex3f(pos*cubesize-center,0.0f-center,      -0.0f+center      );
		glVertex3f(pos*cubesize-center,3*cubesize-center,-0.0f+center      );
		glVertex3f(pos*cubesize-center,3*cubesize-center,-3*cubesize+center);
		glVertex3f(pos*cubesize-center,0.0f-center,      -3*cubesize+center);

		glEnd();
	}
	else if(dir == 2)	//xz
	{
		glBegin(GL_QUADS);
		glColor3f(0.5f,0.5f,0.5f);

		glVertex3f(0.0f-center,      pos*cubesize-center,-0.0f+center      );
		glVertex3f(3*cubesize-center,pos*cubesize-center,-0.0f+center      );
		glVertex3f(3*cubesize-center,pos*cubesize-center,-3*cubesize+center);
		glVertex3f(0.0f-center,      pos*cubesize-center,-3*cubesize+center);

		glEnd();
	}
}

void CViewPortView::DrawAll(short dir)
{
	glClearColor(0.0f,0.0f,0.0f,1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if(dir ==0)
	{
	 	glPushMatrix();
		TRANS;
		glRotatef(angleZ0,0.0f,0.0f,1.0f);
		DrawM0(0,0);
		DrawM2(1,0);
		DrawM1(2,0);
		DrawM4(2,0);
		DrawM5(1,0);
		glPopMatrix();

		glPushMatrix();
		TRANS;
		glRotatef(angleZ1,0.0f,0.0f,1.0f);
		DrawPM(0,1);
		DrawM2(1,1);
		DrawM1(2,1);
		DrawM4(2,1);
		DrawM5(1,1);
		glPopMatrix();

		glPushMatrix();
		TRANS;
		glRotatef(angleZ2,0.0f,0.0f,1.0f);
		DrawPM(0,2);
		DrawM2(1,2);
		DrawM1(2,2);
		DrawM4(2,2);
		DrawM5(1,2);
		glPopMatrix();
	}
	else if(dir == 1)
	{
		glPushMatrix();
		TRANS;
		glRotatef(angleX0,1.0f,0.0f,0.0f);
		DrawPM(1,1);
		DrawM0(2,0);
		DrawM2(2,0);
		DrawM3(2,0);
		DrawM5(2,0);
		glPopMatrix();

		glPushMatrix();
		TRANS;
		glRotatef(angleX1,1.0f,0.0f,0.0f);
		DrawPM(1,2);
		DrawM0(2,1);
		DrawM2(2,1);
		DrawM3(2,1);
		DrawM5(2,1);
		glPopMatrix();

		glPushMatrix();
		TRANS;
		glRotatef(angleX2,1.0f,0.0f,0.0f);
		DrawM1(0,0);
		DrawM0(2,2);
		DrawM2(2,2);
		DrawM3(2,2);
		DrawM5(2,2);
		glPopMatrix();
	}
	else if(dir ==2)
	{
		glPushMatrix();
		TRANS;
		glRotatef(angleY0,0.0f,1.0f,0.0f);
		DrawPM(2,1);
		DrawM0(1,0);
		DrawM1(1,0);
		DrawM3(1,0);
		DrawM4(1,0);
		glPopMatrix();

		glPushMatrix();
		TRANS;
		glRotatef(angleY1,0.0f,1.0f,0.0f);
		DrawPM(2,2);
		DrawM0(1,1);
		DrawM1(1,1);
		DrawM3(1,1);
		DrawM4(1,1);
		glPopMatrix();

		glPushMatrix();
		TRANS;
		glRotatef(angleY2,0.0f,1.0f,0.0f);
		DrawM2(0,0);
		DrawM0(1,2);
		DrawM1(1,2);
		DrawM3(1,2);
		DrawM4(1,2);
		glPopMatrix();
	}

	glFinish();
	SwapBuffers(wglGetCurrentDC());
}

void CViewPortView::OnSszQ() 
{
	// TODO: Add your command handler code here
	if(m_busy) return;

	if(m_complete){
		short tmp[3];
		for(int i=0;i<3;i++){
			tmp[i] = mofang[1][0][i];
			mofang[1][0][i] = mofang[2][2-i][0];
			mofang[2][2-i][0] = mofang[4][0][2-i];
			mofang[4][0][2-i] = mofang[5][i][0];
			mofang[5][i][0] = tmp[i];
		}

		rotM(0,1);
		
		DrawScene();
		if(m_undo)
			m_undo=FALSE;
		else
			step[curstep++]=1;
		m_complete=FALSE;
	}
	else
	{
		SetTimer(2,15,NULL);
		rotdir=0;
		rz0=-rotstep;
		m_busy=TRUE;
	}
}

void CViewPortView::OnSszH() 
{
	// TODO: Add your command handler code here
	if(m_busy) return;

	if(m_complete){
		short tmp[3];
		for(int i=0;i<3;i++){
			tmp[i] = mofang[1][2][i];
			mofang[1][2][i] = mofang[2][2-i][2];
			mofang[2][2-i][2] = mofang[4][2][2-i];
			mofang[4][2][2-i] = mofang[5][i][2];
			mofang[5][i][2] = tmp[i];
		}

		rotM(3,1);
		
		DrawScene();
		if(m_undo)
			m_undo=FALSE;
		else
			step[curstep++]=3;
		m_complete=FALSE;
	}
	else
	{
		SetTimer(2,15,NULL);
		rotdir=0;
		rz2=-rotstep;
		m_busy=TRUE;
	}
}

void CViewPortView::OnSszZ() 
{
	// TODO: Add your command handler code here
	if(m_busy) return;

	if(m_complete){
		short tmp[3];
		for(int i=0;i<3;i++){
			tmp[i] = mofang[1][1][i];
			mofang[1][1][i] = mofang[2][2-i][1];
			mofang[2][2-i][1] = mofang[4][1][2-i];
			mofang[4][1][2-i] = mofang[5][i][1];
			mofang[5][i][1] = tmp[i];
		}
		DrawScene();
		if(m_undo)
			m_undo=FALSE;
		else
			step[curstep++]=2;
		m_complete=FALSE;
	}
	else
	{
		SetTimer(2,15,NULL);
		rotdir=0;
		rz1=-rotstep;
		m_busy=TRUE;
	}
}

void CViewPortView::OnNszQ() 
{
	// TODO: Add your command handler code here
	if(m_busy) return;

	if(m_complete){
		short tmp[3];
		for(int i=0;i<3;i++){
			tmp[i] = mofang[5][i][0];
			mofang[5][i][0] = mofang[4][0][2-i];
			mofang[4][0][2-i] = mofang[2][2-i][0];
			mofang[2][2-i][0] = mofang[1][0][i];
			mofang[1][0][i] = tmp[i];
		}

		rotM(0,-1);
		DrawScene();
		if(m_undo)
			m_undo=FALSE;
		else
			step[curstep++]=5;
		m_complete=FALSE;
	}
	else
	{
		SetTimer(2,15,NULL);
		rotdir=0;
		rz0=rotstep;
		m_busy=TRUE;
	}
}
void CViewPortView::OnNszH() 
{
	// TODO: Add your command handler code here
	if(m_busy) return;

	if(m_complete){
		short tmp[3];
		for(int i=0;i<3;i++){
			tmp[i] = mofang[5][i][2];
			mofang[5][i][2] = mofang[4][2][2-i];
			mofang[4][2][2-i] = mofang[2][2-i][2];
			mofang[2][2-i][2] = mofang[1][2][i];
			mofang[1][2][i] = tmp[i];
		}

		rotM(3,-1);
		DrawScene();
		if(m_undo)
			m_undo=FALSE;
		else
			step[curstep++]=7;
		m_complete=FALSE;
	}
	else
	{
		SetTimer(2,15,NULL);
		rotdir=0;
		rz2=rotstep;
		m_busy=TRUE;
	}
}

void CViewPortView::OnNszZ() 
{
	// TODO: Add your command handler code here
	if(m_busy) return;

	if(m_complete){
		short tmp[3];
		for(int i=0;i<3;i++){
			tmp[i] = mofang[5][i][1];
			mofang[5][i][1] = mofang[4][1][2-i];
			mofang[4][1][2-i] = mofang[2][2-i][1];
			mofang[2][2-i][1] = mofang[1][1][i];
			mofang[1][1][i] = tmp[i];
		}
		DrawScene();
		if(m_undo)
			m_undo=FALSE;
		else
			step[curstep++]=6;
		m_complete=FALSE;
	}
	else
	{
		SetTimer(2,15,NULL);
		rotdir=0;
		rz1=rotstep;
		m_busy=TRUE;
	}
}

void CViewPortView::OnSszAll() 
{
	// TODO: Add your command handler code here
	if(m_busy) return;

	if(m_complete){
		short tmp[3];
		int i,j;

		for(j=0;j<3;j++)
		for(i=0;i<3;i++){
			tmp[i] = mofang[1][j][i];
			mofang[1][j][i] = mofang[2][2-i][j];
			mofang[2][2-i][j] = mofang[4][j][2-i];
			mofang[4][j][2-i] = mofang[5][i][j];
			mofang[5][i][j] = tmp[i];
		}

		rotM(0,1);
		rotM(3,1);
		DrawScene();
		if(m_undo)
			m_undo=FALSE;
		else
			step[curstep++]=0;
		m_complete=FALSE;
	}
	else
	{
		SetTimer(1,15,NULL);
		rz=-rotstep;
		m_busy=TRUE;
	}
}

void CViewPortView::OnNszAll() 
{
	// TODO: Add your command handler code here
	if(m_busy) return;

	if(m_complete){
		short tmp[3];
		int i,j;

		for(j=0;j<3;j++)
		for(i=0;i<3;i++){
			tmp[i] = mofang[5][i][j];
			mofang[5][i][j] = mofang[4][j][2-i];
			mofang[4][j][2-i] = mofang[2][2-i][j];
			mofang[2][2-i][j] = mofang[1][j][i];
			mofang[1][j][i] = tmp[i];
		}

		rotM(0,-1);
		rotM(3,-1);
		DrawScene();
		if(m_undo)
			m_undo=FALSE;
		else
			step[curstep++]=4;
		m_complete=FALSE;
	}
	else
	{
	SetTimer(1,15,NULL);
	rz=rotstep;
	m_busy=TRUE;
	}
}
void CViewPortView::OnSzLeft() 
{
	// TODO: Add your command handler code here
	if(m_busy) return;

	if(m_complete){
		short tmp[3];
		for(int i=0;i<3;i++){
			tmp[i] = mofang[2][0][i];
			mofang[2][0][i] = mofang[0][0][i];
			mofang[0][0][i] = mofang[5][0][2-i];
			mofang[5][0][2-i] = mofang[3][0][2-i];
			mofang[3][0][2-i] = tmp[i];
		}
		
		rotM(4,1);
		DrawScene();
		if(m_undo)
			m_undo=FALSE;
		else
			step[curstep++]=9;
		m_complete=FALSE;
	}
	else
	{
		SetTimer(2,15,NULL);
		rotdir=1;
		rx0=-rotstep;
		m_busy=TRUE;
	}
}

void CViewPortView::OnSzMid() 
{
	// TODO: Add your command handler code here
	if(m_busy) return;

	if(m_complete){
		short tmp[3];
		for(int i=0;i<3;i++){
			tmp[i] = mofang[2][1][i];
			mofang[2][1][i] = mofang[0][1][i];
			mofang[0][1][i] = mofang[5][1][2-i];
			mofang[5][1][2-i] = mofang[3][1][2-i];
			mofang[3][1][2-i] = tmp[i];
		}
		DrawScene();
		if(m_undo)
			m_undo=FALSE;
		else
			step[curstep++]=10;
		m_complete=FALSE;
	}	
	else
	{
		SetTimer(2,15,NULL);
		rotdir=1;
		rx1=-rotstep;
		m_busy=TRUE;
	}
}

void CViewPortView::OnSzRight() 
{
	// TODO: Add your command handler code here
	if(m_busy) return;

	if(m_complete){
		short tmp[3];
		for(int i=0;i<3;i++){
			tmp[i] = mofang[2][2][i];
			mofang[2][2][i] = mofang[0][2][i];
			mofang[0][2][i] = mofang[5][2][2-i];
			mofang[5][2][2-i] = mofang[3][2][2-i];
			mofang[3][2][2-i] = tmp[i];
		}
		
		rotM(1,1);
		DrawScene();
		if(m_undo)
			m_undo=FALSE;
		else
			step[curstep++]=11;
		m_complete=FALSE;
	}
	else
	{
		SetTimer(2,15,NULL);
		rotdir=1;
		rx2=-rotstep;
		m_busy=TRUE;
	}
}

void CViewPortView::OnSzAll() 
{
	// TODO: Add your command handler code here
	if(m_busy) return;

	if(m_complete){
		short tmp[3];
		int i,j;

		for(j=0;j<3;j++)
		for(i=0;i<3;i++){
			tmp[i] = mofang[2][j][i];
			mofang[2][j][i] = mofang[0][j][i];
			mofang[0][j][i] = mofang[5][j][2-i];
			mofang[5][j][2-i] = mofang[3][j][2-i];
			mofang[3][j][2-i] = tmp[i];
		}
		
		rotM(1,1);
		rotM(4,1);
		DrawScene();
		if(m_undo)
			m_undo=FALSE;
		else
			step[curstep++]=8;
		m_complete=FALSE;
	}
	else
	{
		SetTimer(1,15,NULL);
		rx=-rotstep;
		m_busy=TRUE;
	}
}

void CViewPortView::OnXzLeft() 
{
	// TODO: Add your command handler code here
	if(m_busy) return;

	if(m_complete){
		short tmp[3];
		for(int i=0;i<3;i++){
			tmp[i] = mofang[3][0][2-i];
			mofang[3][0][2-i] = mofang[5][0][2-i];
			mofang[5][0][2-i] = mofang[0][0][i];
			mofang[0][0][i] = mofang[2][0][i];
			mofang[2][0][i] = tmp[i];
		}
		
		rotM(4,-1);
		DrawScene();
		if(m_undo)
			m_undo=FALSE;
		else
			step[curstep++]=13;
		m_complete=FALSE;
	}	
	else
	{
		SetTimer(2,15,NULL);
		rotdir=1;
		rx0=rotstep;
		m_busy=TRUE;
	}
}

void CViewPortView::OnXzMid() 
{
	// TODO: Add your command handler code here
	if(m_busy) return;

	if(m_complete){
		short tmp[3];
		for(int i=0;i<3;i++){
			tmp[i] = mofang[3][1][2-i];
			mofang[3][1][2-i] = mofang[5][1][2-i];
			mofang[5][1][2-i] = mofang[0][1][i];
			mofang[0][1][i] = mofang[2][1][i];
			mofang[2][1][i] = tmp[i];
		}
		
		DrawScene();
		if(m_undo)
			m_undo=FALSE;
		else
			step[curstep++]=14;
		m_complete=FALSE;
	}	
	else
	{
		SetTimer(2,15,NULL);
		rotdir=1;
		rx1=rotstep;
		m_busy=TRUE;
	}
}

void CViewPortView::OnXzRight() 
{
	// TODO: Add your command handler code here
	if(m_busy) return;

	if(m_complete){
		short tmp[3];
		for(int i=0;i<3;i++){
			tmp[i] = mofang[3][2][2-i];
			mofang[3][2][2-i] = mofang[5][2][2-i];
			mofang[5][2][2-i] = mofang[0][2][i];
			mofang[0][2][i] = mofang[2][2][i];
			mofang[2][2][i] = tmp[i];
		}
		
		rotM(1,-1);
		DrawScene();
		if(m_undo)
			m_undo=FALSE;
		else
			step[curstep++]=15;
		m_complete=FALSE;
	}	
	else
	{
		SetTimer(2,15,NULL);
		rotdir=1;
		rx2=rotstep;
		m_busy=TRUE;
	}
}

void CViewPortView::OnXzAll() 
{
	// TODO: Add your command handler code here

	if(m_busy) return;

	if(m_complete){
		short tmp[3];
		for(int j=0;j<3;j++)
		for(int i=0;i<3;i++){
			tmp[i] = mofang[3][j][2-i];
			mofang[3][j][2-i] = mofang[5][j][2-i];
			mofang[5][j][2-i] = mofang[0][j][i];
			mofang[0][j][i] = mofang[2][j][i];
			mofang[2][j][i] = tmp[i];
		}
		
		rotM(4,-1);
		rotM(1,-1);
		DrawScene();
		if(m_undo)
			m_undo=FALSE;
		else
			step[curstep++]=12;
		m_complete=FALSE;
	}
	else
	{
		SetTimer(1,15,NULL);
		rx=rotstep;
		m_busy=TRUE;
	}

}

void CViewPortView::OnZzS() 
{
	// TODO: Add your command handler code here
	if(m_busy) return;

	if(m_complete){
		short tmp[3];
		for(int i=0;i<3;i++){
			tmp[i] = mofang[0][i][2];
			mofang[0][i][2] = mofang[1][i][2];
			mofang[1][i][2] = mofang[3][2-i][2];
			mofang[3][2-i][2] = mofang[4][2-i][2];
			mofang[4][2-i][2] = tmp[i];
		}
		
		rotM(2,1);
		DrawScene();
		if(m_undo)
			m_undo=FALSE;
		else
			step[curstep++]=17;
		m_complete=FALSE;
	}	
	else
	{
		SetTimer(2,15,NULL);
		rotdir=2;
		ry2=-rotstep;
		m_busy=TRUE;
	}
}

void CViewPortView::OnZzZ() 
{
	// TODO: Add your command handler code here
	if(m_busy) return;

	if(m_complete){
		short tmp[3];
		for(int i=0;i<3;i++){
			tmp[i] = mofang[0][i][1];
			mofang[0][i][1] = mofang[1][i][1];
			mofang[1][i][1] = mofang[3][2-i][1];
			mofang[3][2-i][1] = mofang[4][2-i][1];
			mofang[4][2-i][1] = tmp[i];
		}
		
		DrawScene();
		if(m_undo)
			m_undo=FALSE;
		else
			step[curstep++]=18;
		m_complete=FALSE;
	}	
	else
	{
		SetTimer(2,15,NULL);
		rotdir=2;
		ry1=-rotstep;
		m_busy=TRUE;
	}
}

void CViewPortView::OnZzX() 
{
	// TODO: Add your command handler code here
	if(m_busy) return;

	if(m_complete){
		short tmp[3];
		for(int i=0;i<3;i++){
			tmp[i] = mofang[0][i][0];
			mofang[0][i][0] = mofang[1][i][0];
			mofang[1][i][0] = mofang[3][2-i][0];
			mofang[3][2-i][0] = mofang[4][2-i][0];
			mofang[4][2-i][0] = tmp[i];
		}
		
		rotM(5,1);
		DrawScene();
		if(m_undo)
			m_undo=FALSE;
		else
			step[curstep++]=19;
		m_complete=FALSE;
	}	
	else
	{
		SetTimer(2,15,NULL);
		rotdir=2;
		ry0=-rotstep;
		m_busy=TRUE;
	}
}

void CViewPortView::OnZzAll() 
{
	// TODO: Add your command handler code here
	if(m_busy) return;

	if(m_complete){
		short tmp[3];
		for(int j=0;j<3;j++)
		for(int i=0;i<3;i++){
			tmp[i] = mofang[0][i][j];
			mofang[0][i][j] = mofang[1][i][j];
			mofang[1][i][j] = mofang[3][2-i][j];
			mofang[3][2-i][j] = mofang[4][2-i][j];
			mofang[4][2-i][j] = tmp[i];
		}
		
		rotM(2,1);
		rotM(5,1);
		DrawScene();
		if(m_undo)
			m_undo=FALSE;
		else
			step[curstep++]=16;
		m_complete=FALSE;
	}	
	else
	{
		SetTimer(1,15,NULL);
		ry=-rotstep;
		m_busy=TRUE;
	}

}

void CViewPortView::OnYzS() 
{
	// TODO: Add your command handler code here
	if(m_busy) return;

	if(m_complete){
		short tmp[3];
		for(int i=0;i<3;i++){
			tmp[i] = mofang[4][2-i][2];
			mofang[4][2-i][2] = mofang[3][2-i][2];
			mofang[3][2-i][2] = mofang[1][i][2];
			mofang[1][i][2] = mofang[0][i][2];
			mofang[0][i][2] = tmp[i];
		}
		
		rotM(2,-1);
		DrawScene();
		if(m_undo)
			m_undo=FALSE;
		else
			step[curstep++]=21;
		m_complete=FALSE;
	}
	else
	{
		SetTimer(2,15,NULL);
		rotdir=2;
		ry2=rotstep;
		m_busy=TRUE;
	}
}

void CViewPortView::OnYzZ() 
{
	// TODO: Add your command handler code here
	if(m_busy) return;

	if(m_complete){
		short tmp[3];
		for(int i=0;i<3;i++){
			tmp[i] = mofang[4][2-i][1];
			mofang[4][2-i][1] = mofang[3][2-i][1];
			mofang[3][2-i][1] = mofang[1][i][1];
			mofang[1][i][1] = mofang[0][i][1];
			mofang[0][i][1] = tmp[i];
		}
		
		DrawScene();
		if(m_undo)
			m_undo=FALSE;
		else
			step[curstep++]=22;
		m_complete=FALSE;
	}	
	else
	{
		SetTimer(2,15,NULL);
		rotdir=2;
		ry1=rotstep;
		m_busy=TRUE;
	}
}

void CViewPortView::OnYzX() 
{
	// TODO: Add your command handler code here
	if(m_busy) return;

	if(m_complete){
		short tmp[3];
		for(int i=0;i<3;i++){
			tmp[i] = mofang[4][2-i][0];
			mofang[4][2-i][0] = mofang[3][2-i][0];
			mofang[3][2-i][0] = mofang[1][i][0];
			mofang[1][i][0] = mofang[0][i][0];
			mofang[0][i][0] = tmp[i];
		}
		
		rotM(5,-1);
		DrawScene();
		if(m_undo)
			m_undo=FALSE;
		else
			step[curstep++]=23;
		m_complete=FALSE;
	}	
	else
	{
		SetTimer(2,15,NULL);
		rotdir=2;
		ry0=rotstep;
		m_busy=TRUE;
	}
}

void CViewPortView::OnYzAll() 
{
	// TODO: Add your command handler code here
	if(m_busy) return;

	if(m_complete){
		short tmp[3];
		for(int j=0;j<3;j++)
		for(int i=0;i<3;i++){
			tmp[i] = mofang[4][2-i][j];
			mofang[4][2-i][j] = mofang[3][2-i][j];
			mofang[3][2-i][j] = mofang[1][i][j];
			mofang[1][i][j] = mofang[0][i][j];
			mofang[0][i][j] = tmp[i];
		}
		
		rotM(2,-1);
		rotM(5,-1);
		DrawScene();
		if(m_undo)
			m_undo=FALSE;
		else
			step[curstep++]=20;
		m_complete=FALSE;
	}
	else
	{
		SetTimer(1,15,NULL);
		ry=+rotstep;
		m_busy=TRUE;
	}
	
}

void CViewPortView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	switch(nChar){
	case 81:	qaz=1;break;
	case 65:	qaz=2;break;
	case 90:	qaz=3;break;
	case 38:	
		if(qaz==0)		OnSzAll();
		else if(qaz==1)	OnSzLeft();
		else if(qaz==2) OnSzMid();
		else if(qaz==3) OnSzRight();
		break;
	case 37:
		if(qaz==0)		OnZzAll();
		else if(qaz==1)	OnZzS();
		else if(qaz==2) OnZzZ();
		else if(qaz==3) OnZzX();
		break;
	case 39:
		if(qaz==0)		OnYzAll();
		else if(qaz==1)	OnYzS();
		else if(qaz==2) OnYzZ();
		else if(qaz==3) OnYzX();
		break;
	case 40:	
		if(qaz==0)		OnXzAll();
		else if(qaz==1)	OnXzLeft();
		else if(qaz==2) OnXzMid();
		else if(qaz==3) OnXzRight();
		break;
	case 46:	
		if(qaz==0)		OnNszAll();
		else if(qaz==1)	OnNszH();
		else if(qaz==2) OnNszZ();
		else if(qaz==3) OnNszQ();
		break;
	case 34:	
		if(qaz==0)		OnSszAll();
		else if(qaz==1)	OnSszH();
		else if(qaz==2) OnSszZ();
		else if(qaz==3) OnSszQ();
		break;
	}

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CViewPortView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	switch(nChar){
	case 81:	qaz=0;break;
	case 65:	qaz=0;break;
	case 90:	qaz=0;break;
	}	
	CView::OnKeyUp(nChar, nRepCnt, nFlags);
}

void CViewPortView::OnUndo() 
{
	// TODO: Add your command handler code here
	short laststep;

	if(curstep==0) return;
	
	laststep = step[--curstep];
	
	switch(laststep){
	case 0:		OnNszAll();	break;
	case 1:		OnNszQ();	break;
	case 2:		OnNszZ();	break;
	case 3:		OnNszH();	break;

	case 4:		OnSszAll();	break;
	case 5:		OnSszQ();	break;
	case 6:		OnSszZ();	break;
	case 7:		OnSszH();	break;

	case 8:		OnXzAll();	break;
	case 9:		OnXzLeft();	break;
	case 10:	OnXzMid();	break;
	case 11:	OnXzRight();break;

	case 12:	OnSzAll();	break;
	case 13:	OnSzLeft();	break;
	case 14:	OnSzMid();	break;
	case 15:	OnSzRight();break;

	case 16:	OnYzAll();	break;
	case 17:	OnYzS();	break;
	case 18:	OnYzZ();	break;
	case 19:	OnYzX();	break;

	case 20:	OnZzAll();	break;
	case 21:	OnZzS();	break;
	case 22:	OnZzZ();	break;
	case 23:	OnZzX();	break;
	}
	m_undo=TRUE;
}

void CViewPortView::OnReset() 
{
	// TODO: Add your command handler code here
	for(int i=0;i<6;i++)
		for(int j=0;j<3;j++)
			for(int k=0;k<3;k++)
				mofang[i][j][k]=i;

	DrawScene();
	curstep=0;
}

void CViewPortView::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
if(nIDEvent==1){

	angleX+=rx;
	angleY+=ry;
	angleZ+=rz;
	DrawScene();

	if(angleX>=90.0f){
		KillTimer(1);
		angleX=0.0f;
		rx=0.0f;
		m_busy=FALSE;
		m_complete = TRUE;
		OnXzAll();
	}
	else if(angleX<=-90.0f){
		KillTimer(1);
		angleX=0.0f;
		rx=0.0f;
		m_busy=FALSE;
		m_complete = TRUE;
		OnSzAll();
	}
	else if(angleY<=-90.0f){
		KillTimer(1);
		angleY=0.0f;
		ry=0.0f;
		m_busy=FALSE;
		m_complete = TRUE;
		OnZzAll();
	}
	else if(angleY>=90.0f){
		KillTimer(1);
		angleY=0.0f;
		ry=0.0f;
		m_busy=FALSE;
		m_complete = TRUE;
		OnYzAll();
	}
	else if(angleZ>=90.0f){
		KillTimer(1);
		angleZ=0.0f;
		rz=0.0f;
		m_busy=FALSE;
		m_complete = TRUE;
		OnNszAll();
	}
	else if(angleZ<=-90.0f){
		KillTimer(1);
		angleZ=0.0f;
		rz=0.0f;
		m_busy=FALSE;
		m_complete = TRUE;
		OnSszAll();
	}
}
else if(nIDEvent == 2){

	angleX0+=rx0;
	angleY0+=ry0;
	angleZ0+=rz0;

	angleX1+=rx1;
	angleY1+=ry1;
	angleZ1+=rz1;

	angleX2+=rx2;
	angleY2+=ry2;
	angleZ2+=rz2;

	DrawAll(rotdir);

	if(angleZ0>=90.0f){
		KillTimer(2);
		angleZ0=0.0f;
		rz0=0.0f;
		m_busy=FALSE;
		m_complete = TRUE;
		OnNszQ();
	}
	else if(angleZ0<=-90.0f){
		KillTimer(2);
		angleZ0=0.0f;
		rz0=0.0f;
		m_busy=FALSE;
		m_complete = TRUE;
		OnSszQ();
	}
	else if(angleZ1>=90.0f){
		KillTimer(2);
		angleZ1=0.0f;
		rz1=0.0f;
		m_busy=FALSE;
		m_complete = TRUE;
		OnNszZ();
	}
	else if(angleZ1<=-90.0f){
		KillTimer(2);
		angleZ1=0.0f;
		rz1=0.0f;
		m_busy=FALSE;
		m_complete = TRUE;
		OnSszZ();
	}
	else if(angleZ2>=90.0f){
		KillTimer(2);
		angleZ2=0.0f;
		rz2=0.0f;
		m_busy=FALSE;
		m_complete = TRUE;
		OnNszH();
	}
	else if(angleZ2<=-90.0f){
		KillTimer(2);
		angleZ2=0.0f;
		rz2=0.0f;
		m_busy=FALSE;
		m_complete = TRUE;
		OnSszH();
	}

	else if(angleX0<=-90.0f){
		KillTimer(2);
		angleX0=0.0f;
		rx0=0.0f;
		m_busy=FALSE;
		m_complete = TRUE;
		OnSzLeft();
	}
	else if(angleX0>=90.0f){
		KillTimer(2);
		angleX0=0.0f;
		rx0=0.0f;
		m_busy=FALSE;
		m_complete = TRUE;
		OnXzLeft();
	}
	else if(angleX1<=-90.0f){
		KillTimer(2);
		angleX1=0.0f;
		rx1=0.0f;
		m_busy=FALSE;
		m_complete = TRUE;
		OnSzMid();
	}
	else if(angleX1>=90.0f){
		KillTimer(2);
		angleX1=0.0f;
		rx1=0.0f;
		m_busy=FALSE;
		m_complete = TRUE;
		OnXzMid();
	}
	else if(angleX2<=-90.0f){
		KillTimer(2);
		angleX2=0.0f;
		rx2=0.0f;
		m_busy=FALSE;
		m_complete = TRUE;
		OnSzRight();
	}
	else if(angleX2>=90.0f){
		KillTimer(2);
		angleX2=0.0f;
		rx2=0.0f;
		m_busy=FALSE;
		m_complete = TRUE;
		OnXzRight();
	}

	else if(angleY2<=-90.0f){
		KillTimer(2);
		angleY2=0.0f;
		ry2=0.0f;
		m_busy=FALSE;
		m_complete = TRUE;
		OnZzS();
	}
	else if(angleY2>=90.0f){
		KillTimer(2);
		angleY2=0.0f;
		ry2=0.0f;
		m_busy=FALSE;
		m_complete = TRUE;
		OnYzS();
	}
	else if(angleY1<=-90.0f){
		KillTimer(2);
		angleY1=0.0f;
		ry1=0.0f;
		m_busy=FALSE;
		m_complete = TRUE;
		OnZzZ();
	}
	else if(angleY1>=90.0f){
		KillTimer(2);
		angleY1=0.0f;
		ry1=0.0f;
		m_busy=FALSE;
		m_complete = TRUE;
		OnYzZ();
	}
	else if(angleY0<=-90.0f){
		KillTimer(2);
		angleY0=0.0f;
		ry0=0.0f;
		m_busy=FALSE;
		m_complete = TRUE;
		OnZzX();
	}
	else if(angleY0>=90.0f){
		KillTimer(2);
		angleY0=0.0f;
		ry0=0.0f;
		m_busy=FALSE;
		m_complete = TRUE;
		OnYzX();
	}
}
	CView::OnTimer(nIDEvent);
}

void CViewPortView::OnSlow() 
{
	// TODO: Add your command handler code here
	if(rotstep == 30.0f)
		rotstep = 10.0f;
	else if(rotstep == 10.0f)
		rotstep = 30.f;
}

void CViewPortView::OnUpdateSlow(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if(rotstep == 30.0f)
		pCmdUI->SetCheck(1);
	else if(rotstep == 10.0f)
		pCmdUI->SetCheck(0);
}


void CViewPortView::OnHlp() 
{
	// TODO: Add your command handler code here
	CHlpDlg d;
	d.DoModal();
}
