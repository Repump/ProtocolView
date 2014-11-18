// TopView.cpp : ���� �����Դϴ�.
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


// CTopView �����Դϴ�.

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


// CTopView �޽��� ó�����Դϴ�.


void CTopView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();

	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	CListCtrl &m_ListIPPacketInfo = GetListCtrl();
	//ListCtrl init
	m_ListIPPacketInfo.InsertColumn(0, _T("Num") , LVCFMT_CENTER, 40);
	m_ListIPPacketInfo.InsertColumn(1, _T("Length"), LVCFMT_CENTER, 50);
	m_ListIPPacketInfo.InsertColumn(2, _T("���� MAC �ּ�"), LVCFMT_CENTER, 130);
	m_ListIPPacketInfo.InsertColumn(3, _T("�߽� MAC �ּ�"), LVCFMT_CENTER, 130);
	m_ListIPPacketInfo.InsertColumn(4, _T("�ٿ��� IP �ּ�"), LVCFMT_CENTER, 100);
	m_ListIPPacketInfo.InsertColumn(5, _T("������ IP �ּ�"), LVCFMT_CENTER, 100);
	m_ListIPPacketInfo.InsertColumn(6, _T("��Ʈ��ũ ����"), LVCFMT_CENTER, 100);
	m_ListIPPacketInfo.InsertColumn(7, _T("Ʈ������Ʈ ����"), LVCFMT_CENTER, 100);
	m_ListIPPacketInfo.InsertColumn(8, _T("���� ����"), LVCFMT_CENTER, 100);
	m_ListIPPacketInfo.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

}


BOOL CTopView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	cs.style &= ~LVS_TYPEMASK;
	cs.style |= LVS_REPORT;
	cs.style |= LVS_SHOWSELALWAYS;
	return CListView::PreCreateWindow(cs);
}


void CTopView::OnLvnItemchanged(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	int ListSeletedNum;
	ListSeletedNum = pNMListView->iItem;

	// TODO: Add your control notification handler code here
 	CChildFrame* child = (CChildFrame *)this->GetParentFrame();
	
	child->ListClick(ListSeletedNum);
	
	*pResult = 0;
}
