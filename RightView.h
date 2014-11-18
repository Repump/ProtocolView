#pragma once


// CRightView 뷰입니다.

class CRightView : public CEditView
{
	DECLARE_DYNCREATE(CRightView)

protected:
	CRightView();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CRightView();

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
};


