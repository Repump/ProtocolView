#pragma once


// CTopView 뷰입니다.

class CTopView : public CListView
{
	DECLARE_DYNCREATE(CTopView)

protected:
	CTopView();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CTopView();

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	afx_msg void OnLvnItemchanged(NMHDR *pNMHDR, LRESULT *pResult);
};


