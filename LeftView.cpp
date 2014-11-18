// LeftView.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ProtocolView.h"
#include "LeftView.h"


// CLeftView

IMPLEMENT_DYNCREATE(CLeftView, CTreeView)

CLeftView::CLeftView()
{

}

CLeftView::~CLeftView()
{
}

BEGIN_MESSAGE_MAP(CLeftView, CTreeView)
END_MESSAGE_MAP()


// CLeftView 진단입니다.

#ifdef _DEBUG
void CLeftView::AssertValid() const
{
	CTreeView::AssertValid();
}

#ifndef _WIN32_WCE
void CLeftView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}
#endif
#endif //_DEBUG


// CLeftView 메시지 처리기입니다.
