// ViewPortView.cpp : implementation of the CViewPortView class
//

#include "stdafx.h"
#include "ViewPort.h"

#include "ViewPortDoc.h"
#include "ViewPortView.h"


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


//---------------------------------------------------------------------------------

GLubyte *                          /* O - Bitmap data */
CViewPortView::LoadDIBitmap(const char *filename, /* I - File to load */
             BITMAPINFO **info)    /* O - Bitmap information */
    {
    FILE             *fp;          /* Open file pointer */
    GLubyte          *bits;        /* Bitmap pixel bits */
    int              bitsize;      /* Size of bitmap */
    int              infosize;     /* Size of header information */
    BITMAPFILEHEADER header;       /* File header */


    /* Try opening the file; use "rb" mode to read this *binary* file. */
    if ((fp = fopen(filename, "rb")) == NULL)
        return (NULL);

    /* Read the file header and any following bitmap information... */
    if (fread(&header, sizeof(BITMAPFILEHEADER), 1, fp) < 1)
        {
        /* Couldn't read the file header - return NULL... */
	fclose(fp);
        return (NULL);
        }

    if (header.bfType != 'MB')	/* Check for BM reversed... */
        {
        /* Not a bitmap file - return NULL... */
        fclose(fp);
        return (NULL);
        }

    infosize = header.bfOffBits - sizeof(BITMAPFILEHEADER);
    if ((*info = (BITMAPINFO *)malloc(infosize)) == NULL)
        {
        /* Couldn't allocate memory for bitmap info - return NULL... */
        fclose(fp);
        return (NULL);
        }

    if (fread(*info, 1, infosize, fp) < infosize)
        {
        /* Couldn't read the bitmap header - return NULL... */
        free(*info);
        fclose(fp);
        return (NULL);
        }

    /* Now that we have all the header info read in, allocate memory for *
     * the bitmap and read *it* in...                                    */
    if ((bitsize = (*info)->bmiHeader.biSizeImage) == 0)
        bitsize = ((*info)->bmiHeader.biWidth *
                   (*info)->bmiHeader.biBitCount + 7) / 8 *
  	           abs((*info)->bmiHeader.biHeight);

    if ((bits = (GLubyte *)malloc(bitsize)) == NULL)
        {
        /* Couldn't allocate memory - return NULL! */
        free(*info);
        fclose(fp);
        return (NULL);
        }

    if (fread(bits, 1, bitsize, fp) < bitsize)
        {
        /* Couldn't read bitmap - free memory and return NULL! */
        free(*info);
        free(bits);
        fclose(fp);
        return (NULL);
        }

    /* OK, everything went fine - return the allocated bitmap... */
    fclose(fp);
    return (bits);
    }

int                                /* O - 0 = success, -1 = failure */
CViewPortView::SaveDIBitmap(const char *filename, /* I - File to load */
             BITMAPINFO *info,     /* I - Bitmap information */
	     GLubyte    *bits)     /* I - Bitmap data */
    {
    FILE             *fp;          /* Open file pointer */
    int              size,         /* Size of file */
                     infosize,     /* Size of bitmap info */
                     bitsize;      /* Size of bitmap pixels */
    BITMAPFILEHEADER header;       /* File header */


    /* Try opening the file; use "wb" mode to write this *binary* file. */
    if ((fp = fopen(filename, "wb")) == NULL)
        return (-1);

    /* Figure out the bitmap size */
    if (info->bmiHeader.biSizeImage == 0)
	bitsize = (info->bmiHeader.biWidth *
        	   info->bmiHeader.biBitCount + 7) / 8 *
		  abs(info->bmiHeader.biHeight);
    else
	bitsize = info->bmiHeader.biSizeImage;

    /* Figure out the header size */
    infosize = sizeof(BITMAPINFOHEADER);
    switch (info->bmiHeader.biCompression)
	{
	case BI_BITFIELDS :
            infosize += 12; /* Add 3 RGB doubleword masks */
            if (info->bmiHeader.biClrUsed == 0)
	      break;
	case BI_RGB :
            if (info->bmiHeader.biBitCount > 8 &&
        	info->bmiHeader.biClrUsed == 0)
	      break;
	case BI_RLE8 :
	case BI_RLE4 :
            if (info->bmiHeader.biClrUsed == 0)
              infosize += (1 << info->bmiHeader.biBitCount) * 4;
	    else
              infosize += info->bmiHeader.biClrUsed * 4;
	    break;
	}

    size = sizeof(BITMAPFILEHEADER) + infosize + bitsize;

    /* Write the file header, bitmap information, and bitmap pixel data... */
    header.bfType      = 'MB'; /* Non-portable... sigh */
    header.bfSize      = size;
    header.bfReserved1 = 0;
    header.bfReserved2 = 0;
    header.bfOffBits   = sizeof(BITMAPFILEHEADER) + infosize;

    if (fwrite(&header, 1, sizeof(BITMAPFILEHEADER), fp) < sizeof(BITMAPFILEHEADER))
        {
        /* Couldn't write the file header - return... */
        fclose(fp);
        return (-1);
        }

    if (fwrite(info, 1, infosize, fp) < infosize)
        {
        /* Couldn't write the bitmap header - return... */
        fclose(fp);
        return (-1);
        }

    if (fwrite(bits, 1, bitsize, fp) < bitsize)
        {
        /* Couldn't write the bitmap - return... */
        fclose(fp);
        return (-1);
        }

    /* OK, everything went fine - return... */
    fclose(fp);
    return (0);
    }

GLuint                           /* O - Texture object or 0 on error */
CViewPortView::TextureLoad(char      *filename, /* I - Bitmap file to load */
            GLboolean alpha,     /* I - Generate alpha for bitmap */
            GLenum    minfilter, /* I - Minification filter */
	    GLenum    magfilter, /* I - Magnification filter */
	    GLenum    wrap)      /* I - Repeat or clamp */
    {
    int         i;               /* Looping var */
    BITMAPINFO	*info;           /* Bitmap information */
    GLubyte	*bits;           /* Bitmap RGB pixels */
    GLubyte     *ptr;            /* Pointer into bit buffer */
    GLubyte	*rgba;           /* RGBA pixel buffer */
    GLubyte	*rgbaptr;        /* Pointer into RGBA buffer */
    GLubyte     temp;            /* Swapping variable */
    GLenum      type;            /* Texture type */
    GLuint      texture;         /* Texture object */

    /* Try loading the bitmap file... */
    bits = LoadDIBitmap(filename, &info);
    if (bits == (GLubyte *)0)
        return (0);

#ifdef WIN32 /* This already done by non-WIN32 LoadDIBitmap */
    for (i = info->bmiHeader.biWidth * info->bmiHeader.biHeight, ptr = bits;
         i > 0;
	 i --, ptr += 3)
        {
	/* Swap red and blue */
	temp   = ptr[0];
	ptr[0] = ptr[2];
	ptr[2] = temp;
	}
#endif /* WIN32 */

    /* Figure out the type of texture... */
    if (info->bmiHeader.biHeight == 1)
        type = GL_TEXTURE_1D;
    else
        type = GL_TEXTURE_2D;

    /* Create and bind a texture object */
    glGenTextures(1, &texture);
    glBindTexture(type, texture);

    /* Set texture parameters */
    glTexParameteri(type, GL_TEXTURE_MAG_FILTER, magfilter);
    glTexParameteri(type, GL_TEXTURE_MIN_FILTER, minfilter);
    glTexParameteri(type, GL_TEXTURE_WRAP_S, wrap);
    glTexParameteri(type, GL_TEXTURE_WRAP_T, wrap);
    glTexEnvi(type, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    if (alpha)
        {
	/* Create and use an RGBA image... */
        rgba = (GLubyte *)malloc(info->bmiHeader.biWidth * info->bmiHeader.biHeight * 4);

        for (i = info->bmiHeader.biWidth * info->bmiHeader.biHeight,
	         rgbaptr = rgba, ptr = bits;
             i > 0;
	     i --, rgbaptr += 4, ptr += 3)
	    {
            rgbaptr[0] = ptr[0];
            rgbaptr[1] = ptr[1];
            rgbaptr[2] = ptr[2];
            rgbaptr[3] = (ptr[0] + ptr[1] + ptr[2]) / 3;
	    }

        /*
         * Set texture image; if the minification filter uses mip-mapping
         * then use gluBuild2D/1DMipmaps() to load the texture...
         */

        if (minfilter == GL_LINEAR || minfilter == GL_NEAREST)
            glTexImage2D(type, 0, 4, info->bmiHeader.biWidth,
                         info->bmiHeader.biHeight, 0, GL_RGBA,
                         GL_UNSIGNED_BYTE, rgba);
        else if (type == GL_TEXTURE_1D)
            gluBuild1DMipmaps(type, 4, info->bmiHeader.biWidth,
                              GL_RGBA, GL_UNSIGNED_BYTE, rgba);
        else  
            gluBuild2DMipmaps(type, 3, info->bmiHeader.biWidth,
                              info->bmiHeader.biHeight, GL_RGBA,
                              GL_UNSIGNED_BYTE, rgba);
        /* Free the RGBA buffer */
	free(rgba);
	}
    else
        {
        /*
         * Set texture image; if the minification filter uses mip-mapping
         * then use gluBuild2D/1DMipmaps() to load the texture...
         */

        if (minfilter == GL_LINEAR || minfilter == GL_NEAREST)
            glTexImage2D(type, 0, 3, info->bmiHeader.biWidth,
                         info->bmiHeader.biHeight, 0, GL_RGB,
                         GL_UNSIGNED_BYTE, bits);
        else if (type == GL_TEXTURE_1D)
            gluBuild1DMipmaps(type, 3, info->bmiHeader.biWidth,
                              GL_RGB, GL_UNSIGNED_BYTE, bits);
        else  
            gluBuild2DMipmaps(type, 3, info->bmiHeader.biWidth,
                              info->bmiHeader.biHeight, GL_RGB,
                              GL_UNSIGNED_BYTE, bits);
        }

    /* Free the bitmap and return... */
    free(info);
    free(bits);

    return (texture);
    }

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
	
//    TexBits = LoadDIBitmap("pot.bmp", &TexInfo);
	LandTexture = TextureLoad("pot.bmp", GL_FALSE, GL_LINEAR,
		GL_LINEAR, GL_CLAMP);
}

void CViewPortView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
    Width  = cx;
    Height = cy;
	
    /* Reset the viewport... */
    glViewport(0, 0, cx, cy);
	
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
//    glOrtho(0.0, (GLfloat)cx, 0.0, (GLfloat)cy, -1.0, 1.0);
	gluPerspective(30.0, (float)cx / (float)cy, 0.1, 1000.0);
	
    glMatrixMode(GL_MODELVIEW);

	DrawScene();	
}

GLfloat XRot = 0.0f, YRot = 0.0f;
GLfloat XTrs = 0.0f, YTrs = 0.0f;

#define TERRAIN_SIZE    400.0 /* Size of terrain database */

void CViewPortView::DrawScene()
{
    glClearColor(0.75, 0.75, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
    glPushMatrix();
	
	glTranslatef(0.0, 0.0, -0.5 * TERRAIN_SIZE);
	glRotatef(XRot, 1.0f, 0.0f, 0.0f);
	glRotatef(YRot, 0.0f, 1.0f, 0.0f);
	glTranslatef(XTrs, YTrs, 0.0);
	
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	
    glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, LandTexture);
	
	//	glColor3f(0.3, 0.8, 0.2);
	
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(-0.5 * 60, -0.5 * 60, 0.0);
    glTexCoord2f(1.0, 0.0);
    glVertex3f( 0.5 * 60, -0.5 * 60,  0.0);
    glTexCoord2f(1.0, 1.0);
    glVertex3f( 0.5 * 60, 0.5 * 60,  0.0);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(-0.05 * 60, 0.05 * 60,  0.0);
    glEnd();
	
    glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	
	SwapBuffers(wglGetCurrentDC());
//	glFlush();
}

BOOL CViewPortView::bSetupPixelFormat()
{
	static PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),
			1,
			PFD_DRAW_TO_WINDOW |
			PFD_SUPPORT_OPENGL |
//			PFD_DRAW_TO_BITMAP |
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
		DrawScene();
	}
	else if(MDn == 2)
	{
		XTrs += (point.x - pr_p.x)/20.0f;
		YTrs -= (point.y - pr_p.y)/20.0f;
		DrawScene();
	}
	pr_p = point;
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

