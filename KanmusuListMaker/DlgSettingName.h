#pragma once
#include "afxwin.h"


// CDlgSettingName �_�C�A���O

class CDlgSettingName : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgSettingName)

public:
	CDlgSettingName(CWnd* pParent = NULL);   // �W���R���X�g���N�^�[
	virtual ~CDlgSettingName();

// �_�C�A���O �f�[�^
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_NAME };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g

	DECLARE_MESSAGE_MAP()
public:
	CString m_name;
private:
	CEdit m_CtrlName;
	virtual void OnOK();
};
