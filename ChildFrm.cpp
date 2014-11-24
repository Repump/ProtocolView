
// ChildFrm.cpp : CChildFrame 클래스의 구현
//

#include "stdafx.h"
#include "ProtocolView.h"
#include "TopView.h"
#include "LeftView.h"
#include "RightView.h"

#include "SelectAdaptorDlg.h"

#include "ChildFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CChildFrame

IMPLEMENT_DYNCREATE(CChildFrame, CMDIChildWndEx)

	BEGIN_MESSAGE_MAP(CChildFrame, CMDIChildWndEx)
		ON_COMMAND(ID_START_CAPTURE, &CChildFrame::OnStartCapture)
	END_MESSAGE_MAP()

	// CChildFrame 생성/소멸

	CChildFrame::CChildFrame()
	{
		// TODO: 여기에 멤버 초기화 코드를 추가합니다.
	}

	CChildFrame::~CChildFrame()
	{
	}


	BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs)
	{
		// TODO: CREATESTRUCT cs를 수정하여 여기에서 Window 클래스 또는 스타일을 수정합니다.
		if( !CMDIChildWndEx::PreCreateWindow(cs) )
			return FALSE;

		return TRUE;
	}

	// CChildFrame 진단

#ifdef _DEBUG
	void CChildFrame::AssertValid() const
	{
		CMDIChildWndEx::AssertValid();
	}

	void CChildFrame::Dump(CDumpContext& dc) const
	{
		CMDIChildWndEx::Dump(dc);
	}
#endif //_DEBUG

	// CChildFrame 메시지 처리기


	BOOL CChildFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
	{
		// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
		//첫 분할 윈도우 생성
		if(!m_wndSplitter1.CreateStatic(this, 2, 1))
		{
			TRACE0("스플리터 생성 실패\n");
			return FALSE;
		}
		//두번째 분할 윈도우 생성
		if(!m_wndSplitter2.CreateStatic(&m_wndSplitter1, 1, 2, WS_CHILD | WS_VISIBLE | WS_BORDER, m_wndSplitter1.IdFromRowCol(1, 0)))
		{
			TRACE0("스플리터 생성 실패\n");
			return FALSE;
		}
		//분할된 윈도우에 넣을 뷰 생성
		m_wndSplitter1.CreateView(0, 0, RUNTIME_CLASS(CTopView), CSize(800, 200), pContext);
		m_wndSplitter2.CreateView(0, 0, RUNTIME_CLASS(CLeftView), CSize(300, 800), pContext);
		m_wndSplitter2.CreateView(0, 1, RUNTIME_CLASS(CRightView), CSize(500, 800), pContext);

		return TRUE;
	}


	void CChildFrame::OnStartCapture()
	{
		// TODO: 여기에 명령 처리기 코드를 추가합니다.
		CTopView * topview = (CTopView *)m_wndSplitter1.GetPane(0,0);
		CListCtrl &m_LIST_PacketInfo = topview->GetListCtrl();

		//Ncap lib.(Dialog based class lib.) 객체 생성.
		CSelectAdaptorDlg * pDlg = new CSelectAdaptorDlg;
		if(pDlg->DoModal() != IDOK)
		{
			delete pDlg;
			return;
		}

		//선택된 네트워크 어댑터를 사용할 수 있도록 초기화.
		if(pDlg->OpenAdaptor(0))
		{
			::AfxMessageBox(_T("Adaptor open 실패"));

			pDlg->CloseAdaptor();
			delete pDlg;

			return;
		}
#define MaxBufferLen	2048
		UpdateData(TRUE);
		for (int i=0; i<20; i++)
		{
			int len;
			unsigned char arrTemp[MaxBufferLen];
			memset(arrTemp, 0, MaxBufferLen);

			// Packet 하나 획득
			if ((len=pDlg->Ncap(arrTemp, MaxBufferLen)) < 0) {
				i--;
				continue;
			}

			// 0. Num
			CString strNum;
			strNum.Format(_T("%3d"), i+1);
			m_LIST_PacketInfo.InsertItem(LVIF_TEXT, i,
				strNum, 0, 0, 0, 0);

			// 1. Length
			CString strLen;
			strLen.Format(_T("%d"), len);
			m_LIST_PacketInfo.SetItem(i, 1, LVIF_TEXT, 
				strLen, 0, 0, 0, 0);

			// 2. 수신 MAC 주소
			CString strDestMac;
			strDestMac.Format(
				_T("%02X %02X %02X - %02X %02X %02X"),
				arrTemp[0], arrTemp[1], arrTemp[2],
				arrTemp[3], arrTemp[4], arrTemp[5]);
			m_LIST_PacketInfo.SetItem(i, 2, LVIF_TEXT,
				strDestMac, 0, 0, 0, 0);

			// 3. 발신 MAC 주소
			CString strSrcMac;
			strSrcMac.Format(
				_T("%02X %02X %02X - %02X %02X %02X"),
				arrTemp[6], arrTemp[7], arrTemp[8],
				arrTemp[9], arrTemp[10], arrTemp[11]);
			m_LIST_PacketInfo.SetItem(i, 3, LVIF_TEXT,
				strSrcMac, 0, 0, 0, 0);

			// 4. 근원지 IP 주소
			CString strSrcIP;
			strSrcIP.Format(_T("%d.%d.%d.%d"),
				arrTemp[26], arrTemp[27], arrTemp[28], arrTemp[29]);
			m_LIST_PacketInfo.SetItem(i, 4, LVIF_TEXT,
				strSrcIP, 0, 0, 0, 0);

			// 5. 목적지 IP 주소
			CString strDestIP;
			strDestIP.Format(_T("%d.%d.%d.%d"),
				arrTemp[30], arrTemp[31], arrTemp[32], arrTemp[33]);
			m_LIST_PacketInfo.SetItem(i, 5, LVIF_TEXT,
				strDestIP, 0, 0, 0, 0);

			// 6. 네트워크 계층
			CString strType;
			bool isIP = false;
			unsigned int iTypeORLength = 
				pDlg->Twobytes_to_number(arrTemp[12], arrTemp[13]);
			if (iTypeORLength == 0x0800) {
				strType.Format(_T("IP"));
				isIP = true;
			} else if (iTypeORLength == 0x0806) {
				strType.Format(_T("ARP"));
			} else if (iTypeORLength <= 0x1500) {
				strType.Format(_T("IEEE 802.3"));
			} else {
				strType.Format(_T("ETC"));
			}
			m_LIST_PacketInfo.SetItem(i, 6, LVIF_TEXT,
				strType, 0, 0, 0, 0);

			// 7. 트랜스포트 계층
			CString strTransType;
			if(isIP) {
				unsigned int iTransType = arrTemp[23];
				if (iTransType == 0x06) {
					strTransType.Format(_T("TCP"));
				} else if (iTransType == 0x11) { 
					strTransType.Format(_T("UDP"));
				} else if (iTransType == 0x01) { 
					strTransType.Format(_T("IMCP"));
				}
			}
			m_LIST_PacketInfo.SetItem(i, 7, LVIF_TEXT,
				strTransType, 0, 0, 0, 0);

			// 8. 응용 계층

			//m_EDIT_iCountOutput = i+1;
			UpdateData(FALSE);

			m_LIST_PacketInfo.EnsureVisible(i, 0); // 마지막이 보이게
		}

		pDlg->CloseAdaptor();
	}


	void CChildFrame::ListClick(int item)
	{
		int ListSeletedNum = item;

		// TODO: Add your control notification handler code here
		CTopView * topview = (CTopView *)this->m_wndSplitter1.GetPane(0,0);
		CListCtrl &m_ListIPPacketInfo = topview->GetListCtrl();

		CLeftView * leftview = (CLeftView *)this->m_wndSplitter2.GetPane(0,0);
		CTreeCtrl &m_Tree_info = leftview->GetTreeCtrl();

		CRightView * rightview = (CRightView *)this->m_wndSplitter2.GetPane(0,1);
		CEdit &m_edit_info = rightview->GetEditCtrl();

		m_Tree_info.DeleteAllItems();// 모든 항목 삭제 
		m_Tree_info.InsertItem(_T("TCP/IP Packet Analyze"), 0, 0);
		m_Tree_info.InsertItem(_T("Ethernet 802.3"), 0, 0);

		CString str = _T("0000 00 01 02 03 04");
		m_edit_info.SetWindowTextW(str);
	}
