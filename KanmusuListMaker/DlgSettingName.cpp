// DlgSettingName.cpp : 実装ファイル
//

#include "stdafx.h"
#include "KanmusuListMaker.h"
#include "DlgSettingName.h"
#include "afxdialogex.h"


// CDlgSettingName ダイアログ

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


// CDlgSettingName メッセージ ハンドラー


void CDlgSettingName::OnOK()
{
	m_CtrlName.GetWindowText(m_name);

	CDialogEx::OnOK();
}
