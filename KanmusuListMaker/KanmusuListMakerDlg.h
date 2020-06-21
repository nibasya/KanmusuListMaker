
// KanmusuListMakerDlg.h : ヘッダー ファイル
//

#pragma once
#include "afxwin.h"
#include "CurrentImage.h"
#include <vector>

struct SPreset {
	CString name;
	CRect imgTrim;
	int priorityDir;
	int limitDir;
	int lineNum;
	bool enableHeader;
	int headerY1;
	int headerY2;
	int colorR;
	int colorG;
	int colorB;
};

// CKanmusuListMakerDlg ダイアログ
class CKanmusuListMakerDlg : public CDialogEx
{
// コンストラクション
public:
	CKanmusuListMakerDlg(CWnd* pParent = NULL);	// 標準コンストラクター

// ダイアログ データ
	enum { IDD = IDD_KANMUSULISTMAKER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV サポート


// 実装
protected:
	HICON m_hIcon;

	// 生成された、メッセージ割り当て関数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	// Event handlers
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedButtonClear();
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnBnClickedButtonSave();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedCheckHeader();
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	afx_msg void OnCbnSelchangeComboSetting();
	afx_msg void OnBnClickedButtonAddSetting();
	afx_msg void OnBnClickedButtonSavesetting();

	// Control variables
	CEdit m_CtrlEditLeft;
	CEdit m_CtrlEditTop;
	CEdit m_CtrlEditRight;
	CEdit m_CtrlEditBottom;
	CEdit m_CtrlEditLineNum;
	CCurrentImage m_CtrlImgPreview;
	CButton m_CtrlButtonSave;
	CEdit m_CtrlEditHeaderY1;
	CEdit m_CtrlEditHeaderY2;
	CButton m_CtrlCheckHeader;
	CComboBox m_CtrlComboSetting;

	// Member functions
	void CreateInitialData();
	int InitSettingCombo();
	void SavePreset(int index, SPreset *pPreset);
	void Preview();
	bool LoadImage(std::vector< CString> * fileList);
	int GetCtrlValue(CWnd* pCtrl);

	// Member variables
	int m_LimitDir;
	int m_PriorityDir;
	CString m_FileOpenTypeFilter;
	CString m_FileSaveTypeFilter;
	CRect m_DefParentRect;
	CRect m_DefImgRect;
	int m_SelectedSetting;
	bool m_EnableUpdatePreview;
	HACCEL m_hAccKey;
	afx_msg void OnBnClickedButtonCopy();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedButtonPresetOrganize();
	// Reads preset number [sel] from .ini file and set values to [pProf]
	void LoadPreset(int sel, SPreset * pPreset);
	CString IntToStr(int i);
	CEdit m_CtrlEditColorR;
	CEdit m_CtrlEditColorG;
	CEdit m_CtrlEditColorB;
};

CString GetLastErrorString();
