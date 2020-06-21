#pragma once
#include "afxwin.h"


// CDlgSettingName ダイアログ

class CDlgSettingName : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgSettingName)

public:
	CDlgSettingName(CWnd* pParent = NULL);   // 標準コンストラクター
	virtual ~CDlgSettingName();

// ダイアログ データ
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_NAME };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
	CString m_name;
private:
	CEdit m_CtrlName;
	virtual void OnOK();
};
