
// ChildFrm.h : CChildFrame Ŭ������ �������̽�
//

#pragma once

class CChildFrame : public CMDIChildWndEx
{
	DECLARE_DYNCREATE(CChildFrame)
public:
	CChildFrame();

// Ư���Դϴ�.
public:

// �۾��Դϴ�.
public:
	CSplitterWnd m_wndSplitter1;
	CSplitterWnd m_wndSplitter2;

// �������Դϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// �����Դϴ�.
public:
	virtual ~CChildFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
public:
	afx_msg void OnStartCapture();
	void ListClick(int item);
	unsigned char arrPacket[100];
};
