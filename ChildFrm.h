
// ChildFrm.h : CChildFrame 클래스의 인터페이스
//

#pragma once

class CChildFrame : public CMDIChildWndEx
{
	DECLARE_DYNCREATE(CChildFrame)
public:
	CChildFrame();

// 특성입니다.
public:

// 작업입니다.
public:
	CSplitterWnd m_wndSplitter1;
	CSplitterWnd m_wndSplitter2;

// 재정의입니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 구현입니다.
public:
	virtual ~CChildFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
public:
	afx_msg void OnStartCapture();
	void ListClick(int item);
	unsigned char arrPacket[100];
};
