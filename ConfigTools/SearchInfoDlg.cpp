// SearchInfoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ConfigTools.h"
#include "SearchInfoDlg.h"
#include "afxdialogex.h"
#include <algorithm>

// CSearchInfoDlg dialog

IMPLEMENT_DYNAMIC(CSearchInfoDlg, CDialogEx)

CSearchInfoDlg::CSearchInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSearchInfoDlg::IDD, pParent)
	, m_strTblName(_T(""))
	, m_strTblFiled(_T(""))
{

}

CSearchInfoDlg::~CSearchInfoDlg()
{
}

void CSearchInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_TBLNAME, m_strTblName);
	DDX_Text(pDX, IDC_EDIT_TBLFIELD, m_strTblFiled);
}


BEGIN_MESSAGE_MAP(CSearchInfoDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_ADD_TABLE, &CSearchInfoDlg::OnBnClickedButtonAddTable)
END_MESSAGE_MAP()


// CSearchInfoDlg message handlers


void CSearchInfoDlg::OnBnClickedButtonAddTable()
{
	// TODO: Add your control notification handler code here
	GetDlgItemText(IDC_EDIT_TBLFIELD, m_strTblFiled);
	GetDlgItemText(IDC_EDIT_TBLNAME, m_strTblName);
	if (m_strTblFiled.IsEmpty() || m_strTblName.IsEmpty())
	{
		GotoDlgCtrl(GetDlgItem(IDC_EDIT_TBLNAME));
		MessageBox(L"����������Ϣ");
		return;
	}
	auto iterFiled = std::find(tblFiledVec.cbegin(), tblFiledVec.cend(), m_strTblFiled);
	if (iterFiled != tblFiledVec.cend())
	{
		GotoDlgCtrl(GetDlgItem(IDC_EDIT_TBLFIELD));
		MessageBox(L"�����ظ������Ҫ�ھ�����ݱ��ֶ�");
		return;
	}

	auto iterName = std::find(tblNameVec.cbegin(), tblNameVec.cend(), m_strTblName);
	if (iterName != tblNameVec.cend())
	{
		GotoDlgCtrl(GetDlgItem(IDC_EDIT_TBLNAME));
		MessageBox(L"�����ظ������Ҫ�ھ�����ݱ�����");
		return;
	}

	tblNameVec.push_back(m_strTblName);
	tblFiledVec.push_back(m_strTblFiled);
	int nRet = ::MessageBox(NULL, L"��ӳɹ����Ƿ������ӣ�", L"���ݷ���", MB_YESNO);
	if (nRet == IDYES)
	{
		SetDlgItemText(IDC_EDIT_TBLFIELD, L"");
		SetDlgItemText(IDC_EDIT_TBLNAME, L"");
		GotoDlgCtrl(GetDlgItem(IDC_EDIT_TBLNAME));
	}
	else
	{
		this->PostMessage(WM_CLOSE);
	}
}
