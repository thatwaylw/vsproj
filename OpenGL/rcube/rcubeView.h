// rcubeView.h : interface of the CRcubeView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_RCUBEVIEW_H__5753988D_8347_11D4_B7B3_5254AB1984FC__INCLUDED_)
#define AFX_RCUBEVIEW_H__5753988D_8347_11D4_B7B3_5254AB1984FC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CRcubeView : public CView
{
protected: // create from serialization only
	CRcubeView();
	DECLARE_DYNCREATE(CRcubeView)

// Attributes
public:
	CRcubeDoc* GetDocument();
	CPalette m_cPalette;
	CPalette * m_pOldPalette;
	CRect m_oldRect;
	float m_fRadius;
	BOOL m_play;
	CClientDC * m_pDC;

// Operations
public:
	void Init();
	void CreateRGBPalette(void);
	BOOL bSetupPixelFormat(void);
	unsigned char ComponentFromIndex(int i,UINT nbits,UINT shift);
	void DrawScene(void);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRcubeView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CRcubeView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CRcubeView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnPlay();
	afx_msg void OnUpdatePlay(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in rcubeView.cpp
inline CRcubeDoc* CRcubeView::GetDocument()
   { return (CRcubeDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RCUBEVIEW_H__5753988D_8347_11D4_B7B3_5254AB1984FC__INCLUDED_)
