#pragma once


// CSearchInfoDlg dialog
#include <vector>

class CSearchInfoDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSearchInfoDlg)

public:
	CSearchInfoDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSearchInfoDlg();

// Dialog Data
	enum { IDD = IDD_SEARCH_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonAddTable();
	CString m_strTblName;
	CString m_strTblFiled;
	std::vector<CString> tblNameVec;
	std::vector<CString> tblFiledVec;

};
