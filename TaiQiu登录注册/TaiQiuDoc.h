// TaiQiuDoc.h :  CTaiQiuDoc ��Ľӿ�
//


#pragma once

class CTaiQiuDoc : public CDocument
{
protected: // �������л�����
	CTaiQiuDoc();
	DECLARE_DYNCREATE(CTaiQiuDoc)

// ����
public:

// ����
public:

// ��д
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// ʵ��
public:
	virtual ~CTaiQiuDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};


