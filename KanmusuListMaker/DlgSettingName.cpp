// DlgSettingName.cpp : �����t�@�C��
//

#include "stdafx.h"
#include "KanmusuListMaker.h"
#include "DlgSettingName.h"
#include "afxdialogex.h"


// CDlgSettingName �_�C�A���O

IMPLEMENT_DYNAMIC(CDlgSettingName, CDialogEx)

CDlgSettingName::CDlgSettingName(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_NAME, pParent)
{

}

CDlgSettingName::~CDlgSettingName()
{
}

void CDlgSettingName::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_SETTINGNAME, m_CtrlName);
}


BEGIN_MESSAGE_MAP(CDlgSettingName, CDialogEx)
END_MESSAGE_MAP()


// CDlgSettingName ���b�Z�[�W �n���h���[


void CDlgSettingName::OnOK()
{
	m_CtrlName.GetWindowText(m_name);

	CDialogEx::OnOK();
}
