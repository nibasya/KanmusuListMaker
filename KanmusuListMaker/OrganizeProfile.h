#pragma once
#include "afxwin.h"
#include "KanmusuListMakerDlg.h"
#include "DragDropListBox.h"
#include <vector>

// COrganizePreset ダイアログ

class COrganizePreset : public CDialogEx
{
	DECLARE_DYNAMIC(COrganizePreset)

public:
	COrganizePreset(CWnd* pParent = NULL);   // 標準コンストラクター
	virtual ~COrganizePreset();

// ダイアログ データ
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_ORGANIZE_PROFILE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);

	// IDC_LIST_PROFILES（リストコントロール)のコントロール変数
	CDragDropListBox m_CtrlListProf;
	// IDC_BUTTON_PROFILE_TOTOPのコントロール変数
	CButton m_CtrlButtonTop;
	// IDC_BUTTON_PROFILE_UPのコントロール変数
	CButton m_CtrlButtonUp;
	// IDC_BUTTON_PROFILE_BOTTOMのコントロール変数
	CButton m_CtrlButtonDown;
	// IDC_BUTTON_PROFILE_TOBOTTOMのコントロール変数
	CButton m_CtrlButtonBottom;
	// ダイアログの最小サイズ
	CRect m_DialogMinimumSize;
	// 設定データへのポインタ配列(空はNULL)(空になったデータは本クラスがdeleteする)
	std::vector<SPreset*> m_Data;
	afx_msg void OnBnClickedButtonProfileTotop();
	afx_msg void OnBnClickedButtonProfileUp();
	afx_msg void OnBnClickedButtonProfileDown();
	afx_msg void OnBnClickedButtonProfileTobottom();
	afx_msg void OnBnClickedButtonProfileDelete();
	afx_msg void OnDestroy();
};
