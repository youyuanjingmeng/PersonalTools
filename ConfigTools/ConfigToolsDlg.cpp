
// ConfigToolsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ConfigTools.h"
#include "ConfigToolsDlg.h"
#include "afxdialogex.h"
#include <algorithm>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About
const unsigned int g_nCredible = 5;        //可信度
const std::string g_strRetrieveType = "1"; //挖掘类型
const std::string g_strSrcAccount = "strSrcAccount";

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CConfigToolsDlg dialog



CConfigToolsDlg::CConfigToolsDlg(CWnd* pParent /*=NULL*/)
: CDialogEx(CConfigToolsDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CConfigToolsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CConfigToolsDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_SAVE_CONFIG, &CConfigToolsDlg::OnBnClickedButtonSaveConfig)
END_MESSAGE_MAP()


// CConfigToolsDlg message handlers

BOOL CConfigToolsDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CConfigToolsDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CConfigToolsDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CConfigToolsDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

BOOL CConfigToolsDlg::SaveSqlConfig(const T_APP_COMMON_INFO &commonInfo)
{
	//MFCONFIG.db 
	//TBL_CF_MARK_TABLE_REF_CONFIG
	std::string strSqlConfig("-- MFCONFIG.db\r\n");
	strSqlConfig.append("-- TBL_CF_MARK_TABLE_REF_CONFIG\r\n");
	strSqlConfig.append("insert into [main].[TBL_CF_MARK_TABLE_REF_CONFIG] values('");
	std::string strAppEnName = commonInfo.strAppEnName;
	
	transform(strAppEnName.begin(), strAppEnName.end(), strAppEnName.begin(), ::toupper);
	std::string strTblName("TBL_PR_");
	strTblName += strAppEnName;

	strSqlConfig += strTblName + "', '" + commonInfo.strAppChName + "', '" + commonInfo.strAppEnName + "', '" + commonInfo.strUserTblName + "', '', 0);\r\n";

	//--BrowserConfig\RetrieveConfig.db
	//-- TBL_CR_PERSONAL_INFO
	strSqlConfig.append("-- BrowserConfig\\RetrieveConfig.db\r\n");
	strSqlConfig.append("-- TBL_CR_PERSONAL_INFO\r\n");
	for (auto mapIter = mapPersonalInfo.begin(); mapIter != mapPersonalInfo.end(); mapIter++)
	{
		strSqlConfig.append("insert into [main].[TBL_CR_PERSONAL_INFO] values('");
		strSqlConfig += commonInfo.strAppChName + "', '" + commonInfo.strAppEnName + "', '" + mapIter->first + "', " + std::to_string(g_nCredible) + ", '";
		strSqlConfig += commonInfo.strUserTblName + "', '" + mapIter->second + "', " + std::to_string(commonInfo.nAcType) + ", '" + commonInfo.strAcType + "');";
		strSqlConfig += "\r\n";
	}

	//-- TBL_CR_STATICS_INFO
	strSqlConfig.append("-- TBL_CR_STATICS_INFO\r\n");
	std::string strUid = GetEditTextValue(IDC_EDIT_UID);
	std::string strNickName = GetEditTextValue(IDC_EDIT_NICKNAME);
	std::vector<std::string> vecTblName = GetMsgTable(GetEditTextValue(IDC_RICHEDIT_MSGTBL));
	for (size_t i = 0; i < vecTblName.size(); i++)
	{
		strSqlConfig.append("insert into [main].[TBL_CR_STATICS_INFO] values('");
		strSqlConfig += commonInfo.strAppChName + "', '" + commonInfo.strAppEnName + "', '" + commonInfo.strUserTblName + "', '";
		strSqlConfig += strUid + "', '" + commonInfo.strUserTblName + "', '" + strNickName + "', '" + vecTblName[i] + "', '";
		strSqlConfig += g_strSrcAccount + "', " + std::to_string(g_nCredible) + ", " + std::to_string(commonInfo.nAcType) + ", '" + commonInfo.strAcType + "');";
		strSqlConfig += "\r\n";
	}

	//-- TBL_RC_FULL_TEXT_SEARCH_INFO
	strSqlConfig.append("-- TBL_RC_FULL_TEXT_SEARCH_INFO\r\n");
	return TRUE;
}

BOOL CConfigToolsDlg::SavePersonalMapInfo()
{
	BOOL bChecked = FALSE;

	if (BST_CHECKED == ((CButton*)GetDlgItem(IDC_CHECK_PORTRAIT))->GetCheck())
	{
		mapPersonalInfo.insert(std::make_pair("PORTRAIT", "strAvatar"));
		bChecked = TRUE;
	}

	if (BST_CHECKED == ((CButton*)GetDlgItem(IDC_CHECK_PHONE))->GetCheck())
	{
		mapPersonalInfo.insert(std::make_pair("PHONE", "strPhoneNum"));
		bChecked = TRUE;
	}

	if (BST_CHECKED == ((CButton*)GetDlgItem(IDC_CHECK_IDCARD))->GetCheck())
	{
		mapPersonalInfo.insert(std::make_pair("ID", "strIdentifyCard"));
		bChecked = TRUE;
	}

	if (BST_CHECKED == ((CButton*)GetDlgItem(IDC_CHECK_NAME))->GetCheck())
	{
		mapPersonalInfo.insert(std::make_pair("NAME", "strRealName"));
		bChecked = TRUE;
	}

	if (BST_CHECKED == ((CButton*)GetDlgItem(IDC_CHECK_ADDRESS))->GetCheck())
	{
		mapPersonalInfo.insert(std::make_pair("ADDRESS", "strAddress"));
		bChecked = TRUE;
	}

	if (BST_CHECKED == ((CButton*)GetDlgItem(IDC_CHECK_BANKCARD))->GetCheck())
	{
		mapPersonalInfo.insert(std::make_pair("CARD", "strBankCard"));
		bChecked = TRUE;
	}
	return bChecked;
}

std::vector<std::string> CConfigToolsDlg::GetMsgTable(const std::string &strIn) const
{
	//多个消息表，用“,”隔开
	std::vector<std::string> vecRet;
	vecRet = StrExplode(strIn, ',');

	return vecRet;
}

std::vector<std::string> CConfigToolsDlg::StrExplode(const std::string &strIn, char seperator) const
{
	std::vector<std::string> vecRet = { "" };
	for (char c : strIn) 
	{
		if (c == seperator) 
		{
			vecRet.emplace_back();
		}
		else 
		{
			vecRet.back() += c;
		}
	}
	return vecRet;
}

std::string CConfigToolsDlg::GetEditTextValue(int nID)
{
	CString strValue;
	std::string strRet;
	GetDlgItemText(nID, strValue);
	if (!strValue.IsEmpty())
	{
		strRet = CT2A(strValue.GetBuffer());
		strValue.ReleaseBuffer();
	}
	return strRet;
}

BOOL CConfigToolsDlg::GetAPPCommonInfo(T_APP_COMMON_INFO &tCommInfo)
{
	BOOL bRet = FALSE;
	std::string strEnName = GetEditTextValue(IDC_EDIT_APPNAME_EN);
	std::string strChName = GetEditTextValue(IDC_EDIT_APPNAME_CH);
	std::string strTblName = GetEditTextValue(IDC_EDIT_USERTBL);
	std::string strAcType = GetEditTextValue(IDC_EDIT_AC_ETYPE);
	std::string strAcValue = GetEditTextValue(IDC_EDIT_ACVALUE);
	if (strEnName.empty() || strChName.empty() || strTblName.empty() || strAcType.empty() || strAcValue.empty())
	{
		MessageBox(L"填写应用配置必要的项目");
	}
	else
	{
		tCommInfo.strAppChName = GetEditTextValue(IDC_EDIT_APPNAME_CH);
		tCommInfo.strAppEnName = GetEditTextValue(IDC_EDIT_APPNAME_EN);
		tCommInfo.strUserTblName = GetEditTextValue(IDC_EDIT_USERTBL);
		tCommInfo.nAcType = std::stoi(GetEditTextValue(IDC_EDIT_ACVALUE));
		tCommInfo.strAcType = GetEditTextValue(IDC_EDIT_AC_ETYPE);
		bRet = TRUE;
	}
	

	return bRet;
}

void CConfigToolsDlg::OnBnClickedButtonSaveConfig()
{
	// TODO: Add your control notification handler code here
	//std::vector<std::string> strRet = GetMsgTable("TBL_TEST,TBL_TEST222,TBL_TEST333");
	T_APP_COMMON_INFO tCommInfo;
	if (!GetAPPCommonInfo(tCommInfo))
	{
		return;
	}

	BOOL bCheckd = SavePersonalMapInfo();
	if (!bCheckd)
	{
		MessageBox(L"支持的人物属性没有任何勾选");
	}
	SaveSqlConfig(tCommInfo);
}



BOOL CConfigToolsDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	
		// 修改回车键的操作反应  
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
	{
		return  TRUE;
	}
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE)
	{
		return  TRUE;
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}
