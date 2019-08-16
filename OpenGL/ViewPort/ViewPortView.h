// ViewPortView.h : interface of the CViewPortView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_VIEWPORTVIEW_H__E4FB22F5_82A7_11D4_B7B3_5254AB1984FC__INCLUDED_)
#define AFX_VIEWPORTVIEW_H__E4FB22F5_82A7_11D4_B7B3_5254AB1984FC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CViewPortView : public CView
{
protected: // create from serialization only
	CViewPortView();
	DECLARE_DYNCREATE(CViewPortView)

// Attributes
public:
	CRect m_oldRect;
	CClientDC * m_pDC;

	CViewPortDoc* GetDocument();

// Operations
public:

	void Init();
	BOOL bSetupPixelFormat(void);
	void DrawScene(void);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CViewPortView)
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
	virtual ~CViewPortView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CViewPortView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ViewPortView.cpp
inline CViewPortDoc* CViewPortView::GetDocument()
   { return (CViewPortDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIEWPORTVIEW_H__E4FB22F5_82A7_11D4_B7B3_5254AB1984FC__INCLUDED_)
