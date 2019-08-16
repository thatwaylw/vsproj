// rcubeView.cpp : implementation of the CRcubeView class
//

#include "stdafx.h"
#include "rcube.h"

#include "rcubeDoc.h"
#include "rcubeView.h"

#include "gl\gl.h"
#include "gl\glu.h"

unsigned char threeto8[8]={
	0 , 0111>>1 , 0222>>1 , 0333>>1 , 0444>>1 , 0555>>1 , 0666>>1 , 0377
};
unsigned char twoto8[4]={
	0 , 0x55 , 0xaa , 0xff
};

unsigned char oneto8[2]={
	0 , 255
};
static int defaultOverride[13]={
	0 , 3 , 24 , 27 , 64 , 67 , 88 , 173 , 181 , 236 , 247 , 164 , 91
};

static PALETTEENTRY defaultPalEntry[20]={
	{0,   0,   0,   0},
	{0x80,0   ,0,   0},
	{0,   0x80,0,   0},
	{0x80,0x80,0,   0},
	{0,   0,   0x80,0},
	{0x80,0   ,0x80,0},
	{0,   0x80,0x80,0},
	{0x80,0x80,0x80,0},

	{192, 220, 192, 0},
	{166, 202, 240, 0},
	{255, 251, 240, 0},
	{160, 160, 164, 0},

	{0x80,0x80,0x80,0},
	{0xff,0   ,0,   0},
	{0,   0xff,0,   0},
	{0xff,0xff,0,   0},
	{0,   0,   0xff,0},
	{0xff,0   ,0xff,0},
	{0,   0xff,0xff,0},
	{0xff,0xff,0xff,0}
};

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRcubeView

IMPLEMENT_DYNCREATE(CRcubeView, CView)

BEGIN_MESSAGE_MAP(CRcubeView, CView)
	//{{AFX_MSG_MAP(CRcubeView)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_TIMER()
	ON_COMMAND(IDM_PLAY, OnPlay)
	ON_UPDATE_COMMAND_UI(IDM_PLAY, OnUpdatePlay)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRcubeView construction/destruction

CRcubeView::CRcubeView()
{
	// TODO: add construction code here
	m_pDC = NULL;
	m_pOldPalette = NULL;
	m_play = FALSE;
}

CRcubeView::~CRcubeView()
{
}

BOOL CRcubeView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	cs.style |= WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CRcubeView drawing

void CRcubeView::OnDraw(CDC* pDC)
{
	CRcubeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	DrawScene();
}

/////////////////////////////////////////////////////////////////////////////
// CRcubeView printing

BOOL CRcubeView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CRcubeView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CRcubeView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CRcubeView diagnostics

#ifdef _DEBUG
void CRcubeView::AssertValid() const
{
	CView::AssertValid();
}

void CRcubeView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CRcubeDoc* CRcubeView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CRcubeDoc)));
	return (CRcubeDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CRcubeView message handlers

int CRcubeView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	Init();
	
	return 0;
}

void CRcubeView::OnDestroy() 
{
	HGLRC hrc;
	KillTimer(1);

	hrc = ::wglGetCurrentContext();

	::wglMakeCurrent(NULL,NULL);

	if(hrc)
		::wglDeleteContext(hrc);

	if(m_pOldPalette)
		m_pDC->SelectPalette(m_pOldPalette,FALSE);

	if(m_pDC)
		delete m_pDC;
		
	CView::OnDestroy();
}

void CRcubeView::OnSize(UINT nType, int cx, int cy) 
{

	CView::OnSize(nType, cx, cy);
	
	if(cy > 0)
	{
		glViewport(150,120,cx,cy);
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

BOOL CRcubeView::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	
//	return CView::OnEraseBkgnd(pDC);
	return TRUE;
}

void CRcubeView::OnTimer(UINT nIDEvent) 
{
	DrawScene();
	
	CView::OnTimer(nIDEvent);

	MSG msg;
	while(::PeekMessage(&msg,m_hWnd,WM_TIMER,WM_TIMER,PM_REMOVE));
}

void CRcubeView::Init()
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

	CreateRGBPalette();

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
	fNearPlane = 3.0f;
	fFarPlane = 7.0f;
	fMaxObjSize = 3.0f;
	m_fRadius = fNearPlane + fMaxObjSize / 2.0f;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f,fAspect,fNearPlane,fFarPlane);
	glMatrixMode(GL_MODELVIEW);
}

BOOL CRcubeView::bSetupPixelFormat()
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

unsigned char CRcubeView::ComponentFromIndex(int i,UINT nbits,UINT shift)
{
	unsigned char val;
	val = (unsigned char) (i >> shift);
	switch(nbits)
	{
	case 1:
		val &= 0x1;
		return oneto8[val];
	case 2:
		val &= 0x3;
		return twoto8[val];
	case 3:
		val &= 0x7;
		return threeto8[val];
	default:
		return 0;
	}
}

void CRcubeView::CreateRGBPalette()
{
	PIXELFORMATDESCRIPTOR pfd;
	LOGPALETTE * pPal;
	int n,i;

	n = ::GetPixelFormat(m_pDC->GetSafeHdc());
	::DescribePixelFormat(m_pDC->GetSafeHdc(),n,sizeof(pfd),&pfd);

	if(pfd.dwFlags & PFD_NEED_PALETTE)
	{
		n = 1 << pfd.cColorBits;
		pPal = (PLOGPALETTE) new char[sizeof(LOGPALETTE) + 
					n * sizeof(PALETTEENTRY)];

		ASSERT(pPal != NULL);

		pPal->palVersion = 0x300;
		pPal->palNumEntries = n;

		for(i=0;i<n;i++)
		{
			pPal->palPalEntry[i].peRed = 
				ComponentFromIndex(i,pfd.cRedBits,pfd.cRedShift);
			pPal->palPalEntry[i].peGreen = 
				ComponentFromIndex(i,pfd.cGreenBits,pfd.cGreenShift);
			pPal->palPalEntry[i].peBlue = 
				ComponentFromIndex(i,pfd.cBlueBits,pfd.cBlueShift);
			pPal->palPalEntry[i].peFlags = 0;
		}

		if((pfd.cColorBits == 8) &&
			(pfd.cRedBits == 3) && (pfd.cRedShift == 0) &&
			(pfd.cGreenBits == 3) && (pfd.cGreenShift == 3) &&
			(pfd.cBlueBits == 2) && (pfd.cBlueShift == 6))
		{
			for(i=1;i<=12;i++)
				pPal->palPalEntry[defaultOverride[i]]=defaultPalEntry[i];
		}
		
		m_cPalette.CreatePalette(pPal);
		delete pPal;

		m_pOldPalette = m_pDC->SelectPalette(&m_cPalette,FALSE);
		m_pDC->RealizePalette();
	}
}

void CRcubeView::OnPlay()
{
	// TODO: Add your command handler code here
	m_play = !m_play;
	if(m_play)
		SetTimer(1,15,NULL);
	else
		KillTimer(1);
}

void CRcubeView::OnUpdatePlay(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_play);
}

void CRcubeView::DrawScene()
{
	static BOOL bBusy = FALSE;
	static GLfloat wAngleY = -20.0f;
	static GLfloat wAngleX = 1.0f;
	static GLfloat wAngleZ = 5.0f;

	if(bBusy)
		return;
	bBusy = TRUE;

	glClearColor(0.0f,0.0f,0.0f,1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();

	glTranslatef(-.8f,-.8f,-m_fRadius);

//For Animation
	glRotatef(wAngleX,1.0f,0.0f,0.0f);
	glRotatef(wAngleY,0.0f,1.0f,0.0f);
	glRotatef(wAngleZ,0.0f,0.0f,1.0f);

	wAngleX += 0.2f;
	wAngleY += 0.4f;
	wAngleZ += 0.6f;
//
	glBegin(GL_QUAD_STRIP);
	glColor3f(1.0f,0.0f,1.0f);
	glVertex3f(-0.5f,0.5f,0.5f);

	glColor3f(1.0f,0.0f,0.0f);
	glVertex3f(-0.5f,-0.5f,0.5f);
	glColor3f(1.0f,1.0f,1.0f);
	glVertex3f(0.5f,0.5f,0.5f);

	glColor3f(1.0f,1.0f,0.0f);
	glVertex3f(0.5f,-0.5f,0.5f);
	glColor3f(0.0f,1.0f,1.0f);
	glVertex3f(0.5f,0.5f,-0.5f);

	glColor3f(0.0f,1.0f,0.0f);
	glVertex3f(0.5f,-0.5f,-0.5f);

	glColor3f(0.0f,0.0f,1.0f);
	glVertex3f(-0.5f,0.5f,-0.5f);

	glColor3f(0.0f,0.0f,0.0f);
	glVertex3f(-0.5f,-0.5f,-0.5f);

	glColor3f(1.0f,0.0f,1.0f);
	glVertex3f(-0.5f,0.5f,0.5f);

	glColor3f(1.0f,0.0f,0.0f);
	glVertex3f(-0.5f,-0.5f,0.5f);

	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1.0f,0.0f,1.0f);
	glVertex3f(-0.5f,0.5f,0.5f);

	glColor3f(1.0f,1.0f,1.0f);
	glVertex3f(0.5f,0.5f,0.5f);

	glColor3f(0.0f,1.0f,1.0f);
	glVertex3f(0.5f,0.5f,-0.5f);

	glColor3f(0.0f,0.0f,1.0f);
	glVertex3f(-0.5f,0.5f,-0.5f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1.0f,0.0f,0.0f);
	glVertex3f(-0.5f,-0.5f,0.5f);

	glColor3f(1.0f,1.0f,0.0f);
	glVertex3f(0.5f,-0.5f,0.5f);

	glColor3f(0.0f,1.0f,0.0f);
	glVertex3f(0.5f,-0.5f,-0.5f);

	glColor3f(0.0f,0.0f,0.0f);
	glVertex3f(-0.5f,-0.5f,-0.5f);
	glEnd();

	glPopMatrix();

	glFinish();
	SwapBuffers(wglGetCurrentDC());

	bBusy = FALSE;
}
