
// ConfigToolsDlg.h : header file
//

#pragma once
#include <string>
#include <vector>
#include <map>
#include "afxcmn.h"
#include "afxwin.h"
#include "SearchInfoDlg.h"

typedef struct _T_APP_COMMON_INFO
{
	std::string strAppChName;
	std::string strAppEnName;
	std::string strUserTblName;
	unsigned int nAcType;
	std::string  strAcType;
}T_APP_COMMON_INFO;


// CConfigToolsDlg dialog
class CConfigToolsDlg : public CDialogEx
{
// Construction
public:
	CConfigToolsDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_CONFIGTOOLS_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual BOOL PreTranslateMessage(MSG* pMsg);

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBnClickedButtonSaveConfig();
	afx_msg void OnBnClickedButtonAddtbl();
	DECLARE_MESSAGE_MAP()
private:

	CListCtrl m_listSearch;
	std::map<std::string, std::string> mapPersonalInfo;
	std::vector<std::string> m_vecTblFiled;
	std::vector<std::string> m_vecTblName;
	BOOL GenerateSqlConfig(const T_APP_COMMON_INFO &commonInfo);
	BOOL SavePersonalMapInfo();
	std::string GetEditTextValue(int nID);
	BOOL GetAPPCommonInfo(T_APP_COMMON_INFO &tCommInfo);
	std::vector<std::string> GetMsgTable(const std::string &strIn) const;
	std::vector<std::string> StrExplode(const std::string &strIn, char seperator) const;

	VOID InitSearchListCtrl();
	BOOL SaveSqlConfig(const std::string &strConfigSql);
};
