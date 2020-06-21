#pragma once
#include "afxwin.h"
#include "KanmusuListMakerDlg.h"
#include "DragDropListBox.h"
#include <vector>

// COrganizePreset �_�C�A���O

class COrganizePreset : public CDialogEx
{
	DECLARE_DYNAMIC(COrganizePreset)

public:
	COrganizePreset(CWnd* pParent = NULL);   // �W���R���X�g���N�^�[
	virtual ~COrganizePreset();

// �_�C�A���O �f�[�^
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_ORGANIZE_PROFILE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);

	// IDC_LIST_PROFILES�i���X�g�R���g���[��)�̃R���g���[���ϐ�
	CDragDropListBox m_CtrlListProf;
	// IDC_BUTTON_PROFILE_TOTOP�̃R���g���[���ϐ�
	CButton m_CtrlButtonTop;
	// IDC_BUTTON_PROFILE_UP�̃R���g���[���ϐ�
	CButton m_CtrlButtonUp;
	// IDC_BUTTON_PROFILE_BOTTOM�̃R���g���[���ϐ�
	CButton m_CtrlButtonDown;
	// IDC_BUTTON_PROFILE_TOBOTTOM�̃R���g���[���ϐ�
	CButton m_CtrlButtonBottom;
	// �_�C�A���O�̍ŏ��T�C�Y
	CRect m_DialogMinimumSize;
	// �ݒ�f�[�^�ւ̃|�C���^�z��(���NULL)(��ɂȂ����f�[�^�͖{�N���X��delete����)
	std::vector<SPreset*> m_Data;
	afx_msg void OnBnClickedButtonProfileTotop();
	afx_msg void OnBnClickedButtonProfileUp();
	afx_msg void OnBnClickedButtonProfileDown();
	afx_msg void OnBnClickedButtonProfileTobottom();
	afx_msg void OnBnClickedButtonProfileDelete();
	afx_msg void OnDestroy();
};
