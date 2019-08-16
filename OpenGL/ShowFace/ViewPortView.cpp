// ViewPortView.cpp : implementation of the CViewPortView class
//

#include "stdafx.h"
#include "ViewPort.h"

#include "ViewPortDoc.h"
#include "ViewPortView.h"
#include "math.h"

#include "gl\gl.h"
#include "gl\glu.h"
#include "gl\glaux.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// Global Variables  -----
#include "DoFap.h"

GLfloat	xRot = 0.0f;
GLfloat	yRot = 0.0f;
GLfloat	zRot = 0.0f;

GLfloat	xTrs = 0.0f;
GLfloat	yTrs = 0.0f;
GLfloat	zTrs = 0.0f;

BOOL	bMdn = FALSE;
int		pr_Mx, pr_My;
BOOL	bGrid = FALSE;
BOOL	bTex =  TRUE;
BOOL	bRott = TRUE;

GLfloat InitLight[5][4] = { { 0.15f, 0.15f, 0.15f, 1.0f },			//ambient
							{ 0.7f , 0.7f , 0.7f , 1.0f },			//diffuse			
							{ 0.7f , 0.7f , 0.7f , 1.0f },			//specular
							{ 0.35f, 0.35f, 0.35f, 1.0f }  };		//lmodel_amb
GLfloat scale_factor, defscale;

GLfloat ModelShininess[NO_COLOURS] = {	100.0f, 64.0f, 100.0f, 60.0f, 90.0f, 60.0f, 60.0f, 
										128.0f, 70.0f, 100.0f, 0.0f};

GLfloat ModelColours[3*NO_COLOURS][4] = {
	{0.5f,0.3f,0.0f,1.0f},	{0.2f,0.2f,0.2f,1.0f},	{0.5f,0.5f,0.5f,1.0f}, //hair,eyebrows
	{0.7f,0.2f,0.4f,1.0f},	{1.0f,0.5f,0.4f,1.0f},	{1.0f,0.7f,0.7f,1.0f}, //tongue
	{1.0f,0.9f,0.8f,1.0f},	{1.0f,0.7f,0.6f,1.0f},	{0.5f,0.5f,0.5f,1.0f}, //skin
	{0.8f,0.2f,0.3f,1.0f},	{1.0f,0.5f,0.4f,1.0f},	{1.0f,0.7f,0.7f,1.0f}, //mouth
	{0.4f,0.4f,0.8f,1.0f},	{0.4f,0.4f,0.8f,1.0f},	{0.7f,0.7f,0.9f,1.0f}, //fringe
	{0.0f,0.0f,0.0f,1.0f},	{0.0f,0.0f,0.0f,1.0f},	{0.5f,0.5f,0.5f,1.0f}, //pupil 
	{0.5f,0.7f,0.4f,1.0f},	{0.4f,0.4f,0.8f,1.0f},	{0.5f,0.5f,0.8f,1.0f}, //iris
	{0.8f,0.8f,0.8f,1.0f},	{1.0f,1.0f,0.9f,1.0f},	{1.0f,1.0f,1.0f,1.0f}, //eyewhite
	{0.8f,0.8f,0.8f,1.0f},	{0.9f,0.9f,0.9f,1.0f},	{0.8f,0.8f,0.8f,1.0f}, //teeth
	{0.8f,0.8f,0.8f,1.0f},	{0.8f,0.8f,0.8f,1.0f},	{0.8f,0.8f,0.8f,1.0f}, //neutral
	{0.0f,0.0f,0.0f,1.0f},	{0.0f,0.0f,0.0f,1.0f},	{0.0f,0.0f,0.0f,1.0f}, //black
};

BOOL	ShowSeps[NO_FACE_REGIONS] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};

float  points_orig[NO_POINTS][3]; 
float  pts[NO_POINTS][3]; 
int    vertx[NO_VERTX][4];
float  norms[NO_POINTS][3];

int		Region_num[NO_FACE_REGIONS];
//------------------------

/////////////////////////////////////////////////////////////////////////////
// CViewPortView

IMPLEMENT_DYNCREATE(CViewPortView, CView)

BEGIN_MESSAGE_MAP(CViewPortView, CView)
	//{{AFX_MSG_MAP(CViewPortView)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_KEYDOWN()
	ON_COMMAND(ID_MGRID, OnMgrid)
	ON_UPDATE_COMMAND_UI(ID_MGRID, OnUpdateMgrid)
	ON_COMMAND(ID_MTEXTURE, OnMtexture)
	ON_UPDATE_COMMAND_UI(ID_MTEXTURE, OnUpdateMtexture)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_MROTT, OnMrott)
	ON_UPDATE_COMMAND_UI(ID_MROTT, OnUpdateMrott)
	ON_COMMAND(ID_MORIG, OnMorig)
	ON_COMMAND(ID_MSEP, OnMsep)
	ON_COMMAND(ID_MFAP, OnMfap)
	ON_COMMAND(ID_MEXP, OnMexp)
	ON_COMMAND(ID_MVIS, OnMvis)
	ON_COMMAND(ID_ANI_FILE_OPEN, OnAniFileOpen)
	ON_COMMAND(ID_PLAY_ANI, OnPlayAni)
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

	m_pSepDlg = NULL;
	m_pFapDlg = NULL;
	m_pExpDlg = NULL;
	m_pVisDlg = NULL;
	m_pPlayAniDlg = NULL;
	
	AniFileName.Empty();
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

void NormalizeVector(float *vec)
{
	float s;
	int   i;
	
	s = (float)(sqrt(sqr(vec[0]) + sqr(vec[1]) + sqr(vec[2]) ) );
	
	for(i=0;i<3;i++)
		vec[i]/=s;
}

void ObtainNormal(float *vector1, float *vector2, float *vector3, float *norm)
{
	norm[X] = vector1[Y]*(vector2[Z] - vector3[Z]) + vector2[Y]*(vector3[Z] - vector1[Z])
		+ vector3[Y]*(vector1[Z] - vector2[Z]);
	
	norm[Y] = vector1[X]*(vector3[Z] - vector2[Z]) + vector2[X]*(vector1[Z] - vector3[Z])
		+ vector3[X]*(vector2[Z] - vector1[Z]);
	
	norm[Z] = vector1[X]*(vector2[Y] - vector3[Y]) + vector2[X]*(vector3[Y] - vector1[Y])
		+ vector3[X]*(vector1[Y] - vector2[Y]);
	
	NormalizeVector(norm);
}

void ObtainVertsNormals()
{
	int   counter,i,j;
	float normal[3];
	
	for(counter=0; counter<NO_VERTX; counter++)
	{
		ObtainNormal(pts[vertx[counter][0]],pts[vertx[counter][1]],pts[vertx[counter][2]],normal);
		
		for(i=0;i<3;i++)
			for(j=0;j<3;j++) 
				norms[vertx[counter][i]][j] += normal[j];
	}
	
}

void CViewPortView::ResetFaceModel()
{
	memcpy(pts, points_orig, NO_POINTS*3*sizeof(float));
//	ObtainVertsNormals();
}

void CViewPortView::GetModelSize()
{
	float max_val,min_val,size;
	int   counter,pos;
	
	max_val=0;
	min_val=0;
	
	for(counter=0; counter< NO_POINTS ; counter++) 
	{
		for(pos=X; pos<=Z; pos++) 
		{
			if(points_orig[counter][pos]<min_val)		min_val = points_orig[counter][pos];
			else if(points_orig[counter][pos]>max_val)	max_val = points_orig[counter][pos];
		}
	}	
	
	size = max_val - min_val;
	
	scale_factor = (GLfloat)( SIZE_FACTOR/size );
	defscale = scale_factor;
}

void CViewPortView::Init()
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
	glClearDepth( 1.0 );
	
	glFrontFace(GL_CCW);		// Counter clock-wise polygons face out
	glEnable(GL_CULL_FACE);		// Do not calculate inside of jet
	glCullFace(GL_BACK);
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	
	glEnable(GL_LIGHTING);
	glLightfv(GL_LIGHT1, GL_AMBIENT, InitLight[0]);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, InitLight[1]);
	glLightfv(GL_LIGHT1, GL_SPECULAR, InitLight[2]);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, InitLight[3]);
	
	glEnable(GL_LIGHT1);
	glClearColor(0.0f, 0.15f, 0.25f, 1.0f);	//background
	
	LoadFaceModel();
	GetModelSize();
	ResetFaceModel();
	ObtainVertsNormals();
	GetFapUnits();
	ReadExpTable();
	ReadVisTable();
}

void CViewPortView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	if(cy > 0)
	{
		glViewport(0,0,cx,cy);
//		if((m_oldRect.right > cx) || (m_oldRect.bottom > cy))
//			RedrawWindow();
		
		m_oldRect.right = cx;
		m_oldRect.bottom = cy;
		
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		if (cx <= cy) 
			glOrtho (-ORTHO_FACTOR, ORTHO_FACTOR, -ORTHO_FACTOR*cy/cx, ORTHO_FACTOR*cy/cx, -NEARFAR, NEARFAR);
		else 
			glOrtho (-ORTHO_FACTOR*cx/cy, ORTHO_FACTOR*cx/cy, -ORTHO_FACTOR, ORTHO_FACTOR, -NEARFAR, NEARFAR);
		
//		gluPerspective(30.0f, (GLdouble)cx/cy, 1.0f, 1000.0f);

		glMatrixMode(GL_MODELVIEW);
//		glLoadIdentity();
	}
	RedrawWindow();
//	DrawScene();
}

void CViewPortView::DrawFace()
{
	int i,j;
	
	glEnable(GL_NORMALIZE);
	
	if(!bTex)
	{
		glMaterialfv( GL_FRONT, GL_AMBIENT,   ModelColours[3*9]);
		glMaterialfv( GL_FRONT, GL_DIFFUSE,   ModelColours[3*9+1]);
		glMaterialfv( GL_FRONT, GL_SPECULAR,  ModelColours[3*9+2]);
		glMaterialf ( GL_FRONT, GL_SHININESS, ModelShininess[9]);
	}

	for(i=0 ; i<NO_VERTX; i++)
	{
		if(!ShowSeps[GetSep(i)])	continue;
		
		if( (vertx[i][3]!=vertx[i-1][3]) || (i==0) ) 
		{
			if(bTex)
			{
				glMaterialfv( GL_FRONT, GL_AMBIENT,   ModelColours[3*vertx[i][3]]);
				glMaterialfv( GL_FRONT, GL_DIFFUSE,   ModelColours[3*vertx[i][3]+1]);
				glMaterialfv( GL_FRONT, GL_SPECULAR,  ModelColours[3*vertx[i][3]+2]);
				glMaterialf ( GL_FRONT, GL_SHININESS, ModelShininess[vertx[i][3]]);
			}
		}
		
		glBegin(GL_POLYGON);
		for(j=0;j<3;j++)
		{
			glNormal3fv(norms[vertx[i][j]]);
			glVertex3fv(pts[vertx[i][j]]);
		}
		glEnd();
		
	}
}

void CViewPortView::DrawScene()
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	glPushMatrix();
	
	glRotatef(xRot, 1.0f, 0.0f, 0.0f);
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);
	glRotatef(zRot, 0.0f, 0.0f, 1.0f);

	glTranslatef(0.0f, 0.35f, 0.0f);
	glTranslatef(xTrs, yTrs, zTrs);
/*---
	glEnable(GL_NORMALIZE);
	glBegin(GL_POLYGON);
	glVertex3f( 1.0, 1.0, 0.0);
	glVertex3f(-1.0, 1.0, 0.0);
	glVertex3f(  0.0, -1.0, 1.0);
	glEnd();
	auxWireTeapot(0.5);
//---*/
//*---
	glScalef(scale_factor,scale_factor,scale_factor);
	
	DrawFace();
	
	glPopMatrix();
//---*/	
	SwapBuffers(wglGetCurrentDC());
}

void CViewPortView::ReDrawScene()
{
	ObtainVertsNormals();
	DrawScene();
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

void KillLine(FILE *fp)
{ 
	int c;
	
	while((c = getc(fp)) != EOF && c != '\n')
		continue;
}

void TestforTrash(FILE *fp)
{
	while(ungetc(getc(fp),fp) == '#')
		KillLine(fp);
}

void CViewPortView::LoadFaceModel()
{
	FILE * fp;
	int i, j, point_num, color, c, total;
	char trash[BUFFER_SIZE];
	
	fp = fopen("ISTfacepoints", "r");
	if(fp == NULL)
	{
		AfxMessageBox("Open Points File error!");
		return;
	}
	
	fscanf(fp, "%d", &point_num);

	for(i=0; i<point_num; i++)
	{
		fscanf(fp, "%f", &points_orig[i][0]);
		fscanf(fp, "%f", &points_orig[i][1]);
		fscanf(fp, "%f", &points_orig[i][2]);
		fgets(trash, BUFFER_SIZE, fp);
	}
	fclose(fp);
	
	fp = fopen("ISTfacevertx", "r");
	if(fp == NULL)
	{
		AfxMessageBox("Open Vertex File error!");
		return;
	}
	
	total = 0;
	for(j=0; j<NO_FACE_REGIONS; j++)
	{
		TestforTrash(fp);

		fscanf(fp,"%d %d ",&color, &point_num);
		
		for(i=0; i<point_num; i++)
		{
			fscanf(fp,"%d",&vertx[total][0]);
			while(c = getc(fp),isspace(c) || ispunct(c));
			ungetc(c,fp);
			
			fscanf(fp,"%d",&vertx[total][1]);
			while(c = getc(fp),isspace(c) || ispunct(c));
			ungetc(c,fp);
			
			fscanf(fp,"%d",&vertx[total][2]);
			fgets(trash,BUFFER_SIZE,fp);
			vertx[total][3] = color;

			total ++;
		}
		Region_num[j] = total;
	}
	fclose(fp);
	
}

int CViewPortView::GetSep(int i)
{
	int j;
	for(j=0; j<NO_FACE_REGIONS; j++)
	{
		if(i<Region_num[j])
			return j;
	}
	return 0;
}

void CViewPortView::OnMgrid() 
{
	// TODO: Add your command handler code here
	bGrid = !bGrid;
	
	if(bGrid)
	{
		glDisable(GL_CULL_FACE);
		glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	}
	else
	{
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	}
	
	DrawScene();
}

void CViewPortView::OnUpdateMgrid(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(bGrid);
}

void CViewPortView::OnMtexture() 
{
	// TODO: Add your command handler code here
	bTex = !bTex;
	DrawScene();
}

void CViewPortView::OnUpdateMtexture(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(bTex);
	
}


void CViewPortView::OnMrott() 
{
	// TODO: Add your command handler code here
	bRott = !bRott;
}

void CViewPortView::OnUpdateMrott(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(bRott);
	
}

void CViewPortView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	bMdn = TRUE;
	pr_Mx = point.x;
	pr_My = point.y;
	CView::OnLButtonDown(nFlags, point);
}

void CViewPortView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	bMdn = FALSE;
	CView::OnLButtonUp(nFlags, point);
}

void CViewPortView::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if(bMdn)
	{
		if(bRott)
		{
			yRot += (point.x - pr_Mx)/3.0f;
			xRot += (point.y - pr_My)/3.0f;

			if(xRot > 360.0f)		xRot = 0.0f;
			if(xRot < -0.0f)		xRot = 360.0f;
			if(yRot > 360.0f)		yRot = 0.0f;
			if(yRot < -0.0f)		yRot = 355.0f;
		}
		else
		{
			xTrs += (point.x - pr_Mx)/100.0f;
			yTrs -= (point.y - pr_My)/100.0f;
		}
		pr_Mx = point.x;
		pr_My = point.y;

		DrawScene();
	}
	CView::OnMouseMove(nFlags, point);
}

void CViewPortView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	if(bRott)
	{
		switch(nChar)
		{
		case VK_LEFT:		yRot -= 2.0f;	break;
		case VK_RIGHT:		yRot += 2.0f;	break;
		case VK_UP:			xRot -= 2.0f;	break;
		case VK_DOWN:		xRot += 2.0f;	break;
		case VK_DELETE:		zRot += 2.0f;	break;
		case 34:			zRot -= 2.0f;	break;
		}
		if(xRot > 360.0f)		xRot = 0.0f;
		if(xRot < -0.0f)		xRot = 360.0f;
		if(yRot > 360.0f)		yRot = 0.0f;
		if(yRot < -0.0f)		yRot = 355.0f;
		if(zRot > 360.0f)		zRot = 0.0f;
		if(zRot < -0.0f)		zRot = 355.0f;
	}
	else
	{
		switch(nChar)
		{
		case VK_LEFT:		xTrs -= 0.1f;	break;
		case VK_RIGHT:		xTrs += 0.1f;	break;
		case VK_UP:			yTrs += 0.1f;	break;
		case VK_DOWN:		yTrs -= 0.1f;	break;
		case VK_DELETE:		zTrs -= 0.1f;	break;
		case 34:			zTrs += 0.1f;	break;
		}
	}
	
	if(nChar == VK_HOME)		scale_factor *= ZOOM_IN;
	else if(nChar == VK_END)	scale_factor *= ZOOM_OUT;
	DrawScene();
	
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CViewPortView::OnMorig() 
{
	// TODO: Add your command handler code here
	xTrs = 0.0f;	yTrs = 0.0f;	zTrs = 0.0f;
	xRot = 0.0f;	yRot = 0.0f;	zRot = 0.0f;
	scale_factor = defscale;

	DrawScene();
	
}

void CViewPortView::OnMsep() 
{
	// TODO: Add your command handler code here
//	CRect r;
	if(m_pSepDlg == NULL)				//Only Can Open one Window
	{
		m_pSepDlg = new CSepDlg(this);
		
		if(m_pSepDlg ->Create()==TRUE)
		{
			m_pSepDlg ->ShowWindow(SW_SHOW);
//			m_pSepDlg ->GetWindowRect(&r);
//			m_pSepDlg ->MoveWindow(m_oldRect.Width()*3/4, m_oldRect.Height(), r.Width(), r.Height());
		}
	}
	else
		m_pSepDlg ->SetActiveWindow();		//Only Can Open one Window
	
}

void CViewPortView::OnMfap() 
{
	// TODO: Add your command handler code here
	CRect r;
	if(m_pFapDlg == NULL)				//Only Can Open one Window
	{
		m_pFapDlg = new CFapDlg(this);
		
		if(m_pFapDlg ->Create()==TRUE)
		{
			m_pFapDlg ->ShowWindow(SW_SHOW);
			m_pFapDlg ->GetWindowRect(&r);
			m_pFapDlg ->MoveWindow(m_oldRect.Width()*3/4, 0, r.Width(), r.Height());
		}
	}
	else
		m_pFapDlg ->SetActiveWindow();		//Only Can Open one Window
}


void CViewPortView::OnMexp() 
{
	// TODO: Add your command handler code here
	CRect r;
	if(m_pExpDlg == NULL)				//Only Can Open one Window
	{
		m_pExpDlg = new CExpDlg(this);
		
		if(m_pExpDlg ->Create()==TRUE)
		{
			m_pExpDlg ->ShowWindow(SW_SHOW);
			m_pExpDlg ->GetWindowRect(&r);
			m_pExpDlg ->MoveWindow(m_oldRect.Width()*3/4, m_oldRect.Height(), r.Width(), r.Height());
		}
	}
	else
		m_pExpDlg ->SetActiveWindow();		//Only Can Open one Window
}

void CViewPortView::OnMvis() 
{
	// TODO: Add your command handler code here
	CRect r;
	if(m_pVisDlg == NULL)				//Only Can Open one Window
	{
		m_pVisDlg = new CVisDlg(this);
		
		if(m_pVisDlg ->Create()==TRUE)
		{
			m_pVisDlg ->ShowWindow(SW_SHOW);
			m_pVisDlg ->GetWindowRect(&r);
			m_pVisDlg ->MoveWindow(m_oldRect.Width()*3/4, m_oldRect.Height(), r.Width(), r.Height());
		}
	}
	else
		m_pVisDlg ->SetActiveWindow();		//Only Can Open one Window
}

void CViewPortView::OnAniFileOpen() 
{
	// TODO: Add your command handler code here
	CFileDialog fd(TRUE);
	fd.m_ofn.lpstrFilter= "ANI Files(*.ani)\0*.ani\0FAP Files(*.fap)\0*.fap\0All Files(*.*)\0*.*\0\0";

	if(fd.DoModal() == IDOK)
	{
		AniFileName = fd.GetFileName();
//		AfxGetApp()->m_pMainWnd->SetWindowText("ÈËÁ³Ä£ÐÍ - " + AniFileName);
//		CMenu menu;
//		menu.LoadMenu(IDR_MAINFRAME);
//		menu.EnableMenuItem(ID_PLAY_ANI, MF_GRAYED);
	}
}

void CViewPortView::OnPlayAni()
{
	if(AniFileName.IsEmpty())
		OnAniFileOpen();

	CRect r;
	if(m_pPlayAniDlg == NULL)				//Only Can Open one Window
	{
		m_pPlayAniDlg = new CPlayAniDlg(this);
		m_pPlayAniDlg ->FileName = AniFileName;
		
		if(m_pPlayAniDlg ->Create()==TRUE)
		{
			m_pPlayAniDlg ->ShowWindow(SW_SHOW);
			m_pPlayAniDlg ->GetWindowRect(&r);
			m_pPlayAniDlg ->MoveWindow(m_oldRect.Width()/4, m_oldRect.Height()+200, r.Width(), r.Height());
		}
	}
	else
		m_pPlayAniDlg ->SetActiveWindow();		//Only Can Open one Window
}
