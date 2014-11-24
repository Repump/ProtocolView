
// ChildFrm.cpp : CChildFrame Ŭ������ ����
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

	// CChildFrame ����/�Ҹ�

	CChildFrame::CChildFrame()
	{
		// TODO: ���⿡ ��� �ʱ�ȭ �ڵ带 �߰��մϴ�.
	}

	CChildFrame::~CChildFrame()
	{
	}


	BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs)
	{
		// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡�� Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.
		if( !CMDIChildWndEx::PreCreateWindow(cs) )
			return FALSE;

		return TRUE;
	}

	// CChildFrame ����

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

	// CChildFrame �޽��� ó����


	BOOL CChildFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
	{
		// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
		//ù ���� ������ ����
		if(!m_wndSplitter1.CreateStatic(this, 2, 1))
		{
			TRACE0("���ø��� ���� ����\n");
			return FALSE;
		}
		//�ι�° ���� ������ ����
		if(!m_wndSplitter2.CreateStatic(&m_wndSplitter1, 1, 2, WS_CHILD | WS_VISIBLE | WS_BORDER, m_wndSplitter1.IdFromRowCol(1, 0)))
		{
			TRACE0("���ø��� ���� ����\n");
			return FALSE;
		}
		//���ҵ� �����쿡 ���� �� ����
		m_wndSplitter1.CreateView(0, 0, RUNTIME_CLASS(CTopView), CSize(800, 200), pContext);
		m_wndSplitter2.CreateView(0, 0, RUNTIME_CLASS(CLeftView), CSize(300, 800), pContext);
		m_wndSplitter2.CreateView(0, 1, RUNTIME_CLASS(CRightView), CSize(500, 800), pContext);

		return TRUE;
	}


	void CChildFrame::OnStartCapture()
	{
		// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
		CTopView * topview = (CTopView *)m_wndSplitter1.GetPane(0,0);
		CListCtrl &m_LIST_PacketInfo = topview->GetListCtrl();

		//Ncap lib.(Dialog based class lib.) ��ü ����.
		CSelectAdaptorDlg * pDlg = new CSelectAdaptorDlg;
		if(pDlg->DoModal() != IDOK)
		{
			delete pDlg;
			return;
		}

		//���õ� ��Ʈ��ũ ����͸� ����� �� �ֵ��� �ʱ�ȭ.
		if(pDlg->OpenAdaptor(0))
		{
			::AfxMessageBox(_T("Adaptor open ����"));

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

			// Packet �ϳ� ȹ��
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

			// 2. ���� MAC �ּ�
			CString strDestMac;
			strDestMac.Format(
				_T("%02X %02X %02X - %02X %02X %02X"),
				arrTemp[0], arrTemp[1], arrTemp[2],
				arrTemp[3], arrTemp[4], arrTemp[5]);
			m_LIST_PacketInfo.SetItem(i, 2, LVIF_TEXT,
				strDestMac, 0, 0, 0, 0);

			// 3. �߽� MAC �ּ�
			CString strSrcMac;
			strSrcMac.Format(
				_T("%02X %02X %02X - %02X %02X %02X"),
				arrTemp[6], arrTemp[7], arrTemp[8],
				arrTemp[9], arrTemp[10], arrTemp[11]);
			m_LIST_PacketInfo.SetItem(i, 3, LVIF_TEXT,
				strSrcMac, 0, 0, 0, 0);

			// 4. �ٿ��� IP �ּ�
			CString strSrcIP;
			strSrcIP.Format(_T("%d.%d.%d.%d"),
				arrTemp[26], arrTemp[27], arrTemp[28], arrTemp[29]);
			m_LIST_PacketInfo.SetItem(i, 4, LVIF_TEXT,
				strSrcIP, 0, 0, 0, 0);

			// 5. ������ IP �ּ�
			CString strDestIP;
			strDestIP.Format(_T("%d.%d.%d.%d"),
				arrTemp[30], arrTemp[31], arrTemp[32], arrTemp[33]);
			m_LIST_PacketInfo.SetItem(i, 5, LVIF_TEXT,
				strDestIP, 0, 0, 0, 0);

			// 6. ��Ʈ��ũ ����
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

			// 7. Ʈ������Ʈ ����
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

			// 8. ���� ����

			//m_EDIT_iCountOutput = i+1;
			UpdateData(FALSE);

			m_LIST_PacketInfo.EnsureVisible(i, 0); // �������� ���̰�
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

		m_Tree_info.DeleteAllItems();// ��� �׸� ���� 
		m_Tree_info.InsertItem(_T("TCP/IP Packet Analyze"), 0, 0);
		m_Tree_info.InsertItem(_T("Ethernet 802.3"), 0, 0);

		CString str = _T("0000 00 01 02 03 04");
		m_edit_info.SetWindowTextW(str);
	}
