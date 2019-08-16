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
		gluPerspective(90.0f,(GLdouble)cx/cy,1.0f,200);
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
//	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);
	glClearDepth(1.0f);
	
	if(m_oldRect.bottom)
		fAspect = (GLfloat)m_oldRect.right/m_oldRect.bottom;
	else
		fAspect = 1.0f;
	fNearPlane = 1.0f;
	fFarPlane = 200;
	fMaxObjSize = 3.0f;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90.0f,fAspect,fNearPlane,fFarPlane);
	glMatrixMode(GL_MODELVIEW);
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
	glPushMatrix();
	glClearColor(0.0f,0.0f,0.0f,1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glViewport(0,0,400,400);
	glLoadIdentity();

	gluPerspective(90.0,1.0,1.0,200);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glPushMatrix();

	glTranslatef(0.0,0.0,-70.0);
	glRotatef(45.0,1.0,0.0,0.0);
	glColor3f(1.0,0.0,0.0);

	auxWireTeapot(40.0);

	glPopMatrix();

	glPopMatrix();
	glPushMatrix();
	glViewport(100,100,400,400);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(90.0,1.0,1.0,200);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glPushMatrix();

	glTranslatef(0.0,0.0,-50);
	glRotatef(45.0,1.0,0.0,0.0);
	glColor3f(0.0,1.0,0.0);

	auxWireSphere(20.0);

	glPopMatrix();
	glPopMatrix();
	glFinish();
	SwapBuffers(wglGetCurrentDC());
}