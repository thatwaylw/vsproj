// ViewPortView.cpp : implementation of the CViewPortView class
//

#include "stdafx.h"
#include "ViewPort.h"

#include "ViewPortDoc.h"
#include "ViewPortView.h"

#include "gl\gl.h"
#include "gl\glu.h"
#include "gl\glaux.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CViewPortView

IMPLEMENT_DYNCREATE(CViewPortView, CView)

BEGIN_MESSAGE_MAP(CViewPortView, CView)
	//{{AFX_MSG_MAP(CViewPortView)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CViewPortView construction/destruction

BYTE HZs[64*100];		// 最多100个汉字
void PreShowHZ(BYTE * pb, char * str)
{
	int i, j, n;
	unsigned long idx;
	unsigned char qm, wm;
	FILE * fp;

	fp = fopen("E:\\Victor\\HZ\\hzk16", "rb");
	if(fp == NULL)	return;

	n = 0;
	while(str[n] != '\0')
	{
		qm = str[n++];
		wm = str[n++];
		idx = 94*(qm-161) + wm-161;

		fseek(fp, 32*(long)idx, SEEK_SET);
		j = 60;
		for(i=0; i<16; i++)
		{
			pb[j++] = fgetc(fp);
			pb[j++] = fgetc(fp);
			pb[j++] = 0;
			pb[j] = 0;
			j -= 7;
		}
		pb += 64;
	}

	fclose(fp);
}

void ShowHZ(BYTE * hzk, int s, int e)
{
	int i;
	for(i=s; i<=e; i++)
	{
		glBitmap(16, 16, 0.0, 0.0, 17.0, 0.0, &hzk[i*64]);
	}
	glBitmap(0, 0, 0.0, 0.0, -17.0*(e-s+1), 0.0, NULL);
}

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
	cs.style |= WS_CLIPSIBLINGS | WS_CLIPCHILDREN ;

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

BOOL CViewPortView::OnEraseBkgnd(CDC* pDC) 
{
	return TRUE;
}

void CViewPortView::Init()
{
	PIXELFORMATDESCRIPTOR pfd;
	int n;
	HGLRC hrc;
//	GLfloat fMaxObjSize, fAspect;
//	GLfloat fNearPlane, fFarPlane;

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
	glEnable(GL_CULL_FACE);		// Do not calculate inside of jet

	glClearColor(0.0f,0.3f,0.1f,1.0f);

	PreShowHZ(HZs, "钟庆是个沙比！");
}

void CViewPortView::OnSize(UINT nType, int cx, int cy) 
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

GLfloat XRot = 0.0f, YRot = 0.0f;
GLfloat XTrs = 0.0f, YTrs = 0.0f;

void CViewPortView::DrawScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();

	glTranslatef(0.0,0.0,-70.0);
//	glRotatef(45.0,1.0,0.0,0.0);
	glColor3f(1.0,0.0,0.0);

	glRotatef(XRot, 1.0f, 0.0f, 0.0f);
	glRotatef(YRot, 0.0f, 1.0f, 0.0f);
	glTranslatef(XTrs, YTrs, 0.0f);

	auxWireTeapot(10.0);

	glPopMatrix();

//	glColor3f(1.0, 0.0, 1.0);
//	glRasterPos2i(0, 0);
	ShowHZ(HZs, 0, 6);

	SwapBuffers(wglGetCurrentDC());
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

int MDn = 0;
CPoint pr_p;

void CViewPortView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	MDn = 1;
	pr_p = point;
	CView::OnLButtonDown(nFlags, point);
}

void CViewPortView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	MDn = 0;
	CView::OnLButtonUp(nFlags, point);
}

void CViewPortView::OnMouseMove(UINT nFlags, CPoint point) 
{
	if(MDn == 1)
	{
		YRot += (point.x - pr_p.x)/3.0f;
		XRot += (point.y - pr_p.y)/3.0f;
		if(XRot > 360.0f)		XRot = 0.0f;
		if(XRot < -0.0f)		XRot = 360.0f;
		if(YRot > 360.0f)		YRot = 0.0f;
		if(YRot < -0.0f)		YRot = 355.0f;
	}
	else if(MDn == 2)
	{
		XTrs += (point.x - pr_p.x)/20.0f;
		YTrs -= (point.y - pr_p.y)/20.0f;
	}
	pr_p = point;
	DrawScene();
	CView::OnMouseMove(nFlags, point);
}

void CViewPortView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	MDn = 2;
	pr_p = point;
	CView::OnRButtonDown(nFlags, point);
}

void CViewPortView::OnRButtonUp(UINT nFlags, CPoint point) 
{
	MDn = 0;
	CView::OnRButtonUp(nFlags, point);
}
