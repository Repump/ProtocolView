// RightView.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ProtocolView.h"
#include "RightView.h"


// CRightView

IMPLEMENT_DYNCREATE(CRightView, CEditView)

CRightView::CRightView()
{

}

CRightView::~CRightView()
{
}

BEGIN_MESSAGE_MAP(CRightView, CEditView)
END_MESSAGE_MAP()


// CRightView 진단입니다.

#ifdef _DEBUG
void CRightView::AssertValid() const
{
	CEditView::AssertValid();
}

#ifndef _WIN32_WCE
void CRightView::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}
#endif
#endif //_DEBUG


// CRightView 메시지 처리기입니다.
