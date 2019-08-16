// ViewPortDoc.h : interface of the CViewPortDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_VIEWPORTDOC_H__E4FB22F3_82A7_11D4_B7B3_5254AB1984FC__INCLUDED_)
#define AFX_VIEWPORTDOC_H__E4FB22F3_82A7_11D4_B7B3_5254AB1984FC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CViewPortDoc : public CDocument
{
protected: // create from serialization only
	CViewPortDoc();
	DECLARE_DYNCREATE(CViewPortDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CViewPortDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CViewPortDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CViewPortDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIEWPORTDOC_H__E4FB22F3_82A7_11D4_B7B3_5254AB1984FC__INCLUDED_)
