// rcubeDoc.h : interface of the CRcubeDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_RCUBEDOC_H__5753988B_8347_11D4_B7B3_5254AB1984FC__INCLUDED_)
#define AFX_RCUBEDOC_H__5753988B_8347_11D4_B7B3_5254AB1984FC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CRcubeDoc : public CDocument
{
protected: // create from serialization only
	CRcubeDoc();
	DECLARE_DYNCREATE(CRcubeDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRcubeDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CRcubeDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CRcubeDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RCUBEDOC_H__5753988B_8347_11D4_B7B3_5254AB1984FC__INCLUDED_)
