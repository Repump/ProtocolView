// TopView.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ProtocolView.h"
#include "TopView.h"
#include "ChildFrm.h"

// CTopView

IMPLEMENT_DYNCREATE(CTopView, CListView)

CTopView::CTopView()
{

}

CTopView::~CTopView()
{
}

BEGIN_MESSAGE_MAP(CTopView, CListView)
	ON_NOTIFY_REFLECT(LVN_ITEMCHANGED, &CTopView::OnLvnItemchanged)
END_MESSAGE_MAP()


// CTopView 진단입니다.

#ifdef _DEBUG
void CTopView::AssertValid() const
{
	CListView::AssertValid();
}

#ifndef _WIN32_WCE
void CTopView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}
#endif
#endif //_DEBUG


// CTopView 메시지 처리기입니다.


void CTopView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	CListCtrl &m_ListIPPacketInfo = GetListCtrl();
	//ListCtrl init
	m_ListIPPacketInfo.InsertColumn(0, _T("Num") , LVCFMT_CENTER, 40);
	m_ListIPPacketInfo.InsertColumn(1, _T("Length"), LVCFMT_CENTER, 50);
	m_ListIPPacketInfo.InsertColumn(2, _T("수신 MAC 주소"), LVCFMT_CENTER, 130);
	m_ListIPPacketInfo.InsertColumn(3, _T("발신 MAC 주소"), LVCFMT_CENTER, 130);
	m_ListIPPacketInfo.InsertColumn(4, _T("근원지 IP 주소"), LVCFMT_CENTER, 100);
	m_ListIPPacketInfo.InsertColumn(5, _T("목적지 IP 주소"), LVCFMT_CENTER, 100);
	m_ListIPPacketInfo.InsertColumn(6, _T("네트워크 계층"), LVCFMT_CENTER, 100);
	m_ListIPPacketInfo.InsertColumn(7, _T("트랜스포트 계층"), LVCFMT_CENTER, 100);
	m_ListIPPacketInfo.InsertColumn(8, _T("응용 계층"), LVCFMT_CENTER, 100);
	m_ListIPPacketInfo.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

}


BOOL CTopView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	cs.style &= ~LVS_TYPEMASK;
	cs.style |= LVS_REPORT;
	cs.style |= LVS_SHOWSELALWAYS;
	return CListView::PreCreateWindow(cs);
}


void CTopView::OnLvnItemchanged(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	int ListSeletedNum;
	ListSeletedNum = pNMListView->iItem;

	// TODO: Add your control notification handler code here
 	CChildFrame* child = (CChildFrame *)this->GetParentFrame();
	
	child->ListClick(ListSeletedNum);
	
	*pResult = 0;
}
