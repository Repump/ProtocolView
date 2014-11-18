
// ProtocolViewView.cpp : CProtocolViewView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "ProtocolView.h"
#endif

#include "ProtocolViewDoc.h"
#include "ProtocolViewView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CProtocolViewView

IMPLEMENT_DYNCREATE(CProtocolViewView, CView)

BEGIN_MESSAGE_MAP(CProtocolViewView, CView)
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CProtocolViewView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CProtocolViewView ����/�Ҹ�

CProtocolViewView::CProtocolViewView()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

}

CProtocolViewView::~CProtocolViewView()
{
}

BOOL CProtocolViewView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CProtocolViewView �׸���

void CProtocolViewView::OnDraw(CDC* /*pDC*/)
{
	CProtocolViewDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
}


// CProtocolViewView �μ�


void CProtocolViewView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CProtocolViewView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CProtocolViewView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CProtocolViewView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}

void CProtocolViewView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CProtocolViewView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CProtocolViewView ����

#ifdef _DEBUG
void CProtocolViewView::AssertValid() const
{
	CView::AssertValid();
}

void CProtocolViewView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CProtocolViewDoc* CProtocolViewView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CProtocolViewDoc)));
	return (CProtocolViewDoc*)m_pDocument;
}
#endif //_DEBUG


// CProtocolViewView �޽��� ó����
