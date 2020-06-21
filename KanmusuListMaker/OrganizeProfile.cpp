// OrganizeProfile.cpp : 実装ファイル
//

#include "stdafx.h"
#include "KanmusuListMaker.h"
#include "OrganizeProfile.h"
#include "afxdialogex.h"


// COrganizePreset ダイアログ

IMPLEMENT_DYNAMIC(COrganizePreset, CDialogEx)

COrganizePreset::COrganizePreset(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_ORGANIZE_PROFILE, pParent)
{

}

COrganizePreset::~COrganizePreset()
{
}

void COrganizePreset::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_PROFILES, m_CtrlListProf);
	DDX_Control(pDX, IDC_BUTTON_PROFILE_TOTOP, m_CtrlButtonTop);
	DDX_Control(pDX, IDC_BUTTON_PROFILE_UP, m_CtrlButtonUp);
	DDX_Control(pDX, IDC_BUTTON_PROFILE_DOWN, m_CtrlButtonDown);
	DDX_Control(pDX, IDC_BUTTON_PROFILE_TOBOTTOM, m_CtrlButtonBottom);
}


BEGIN_MESSAGE_MAP(COrganizePreset, CDialogEx)
	ON_WM_GETMINMAXINFO()
	ON_BN_CLICKED(IDC_BUTTON_PROFILE_TOTOP, &COrganizePreset::OnBnClickedButtonProfileTotop)
	ON_BN_CLICKED(IDC_BUTTON_PROFILE_UP, &COrganizePreset::OnBnClickedButtonProfileUp)
	ON_BN_CLICKED(IDC_BUTTON_PROFILE_DOWN, &COrganizePreset::OnBnClickedButtonProfileDown)
	ON_BN_CLICKED(IDC_BUTTON_PROFILE_TOBOTTOM, &COrganizePreset::OnBnClickedButtonProfileTobottom)
	ON_BN_CLICKED(IDC_BUTTON_PROFILE_DELETE, &COrganizePreset::OnBnClickedButtonProfileDelete)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// COrganizePreset メッセージ ハンドラー


BOOL COrganizePreset::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	GetWindowRect(&m_DialogMinimumSize);

	int i;
	for (i = 0; i < (int)m_Data.size(); i++) {
		m_CtrlListProf.AddString(m_Data[i]->name);
		m_CtrlListProf.SetItemDataPtr(i, m_Data[i]);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 例外 : OCX プロパティ ページは必ず FALSE を返します。
}


void COrganizePreset::OnDestroy()
{
	CDialogEx::OnDestroy();

	// write back organized profiles into m_Data
	int i;
	for (i = 0; i < m_CtrlListProf.GetCount(); i++) {
		m_Data[i] = static_cast<SPreset *>(m_CtrlListProf.GetItemDataPtr(i));
	}
	for (; i < (int)m_Data.size(); i++) {
		m_Data[i] = NULL;
	}
}


void COrganizePreset::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	lpMMI->ptMinTrackSize = CPoint(m_DialogMinimumSize.Width(), m_DialogMinimumSize.Height());

	CDialogEx::OnGetMinMaxInfo(lpMMI);
}


void COrganizePreset::OnBnClickedButtonProfileTotop()
{
	int sel = m_CtrlListProf.GetCurSel();
	if (sel == LB_ERR)
		return;
	SPreset* pProf = static_cast<SPreset*>(m_CtrlListProf.GetItemDataPtr(sel));
	m_CtrlListProf.DeleteString(sel);
	m_CtrlListProf.InsertString(0, pProf->name);
	m_CtrlListProf.SetItemDataPtr(0, pProf);
	m_CtrlListProf.SetCurSel(0);
}


void COrganizePreset::OnBnClickedButtonProfileUp()
{
	int sel = m_CtrlListProf.GetCurSel();
	if (sel == LB_ERR)
		return;
	if (sel == 0)
		return;
	SPreset* pProf = static_cast<SPreset*>(m_CtrlListProf.GetItemDataPtr(sel));
	m_CtrlListProf.DeleteString(sel);
	m_CtrlListProf.InsertString(sel-1, pProf->name);
	m_CtrlListProf.SetItemDataPtr(sel-1, pProf);
	m_CtrlListProf.SetCurSel(sel-1);
}


void COrganizePreset::OnBnClickedButtonProfileDown()
{
	int sel = m_CtrlListProf.GetCurSel();
	if (sel == LB_ERR)
		return;
	if (sel == m_CtrlListProf.GetCount() - 1)
		return;
	SPreset* pProf = static_cast<SPreset*>(m_CtrlListProf.GetItemDataPtr(sel));
	m_CtrlListProf.DeleteString(sel);
	m_CtrlListProf.InsertString(sel+1, pProf->name);
	m_CtrlListProf.SetItemDataPtr(sel+1, pProf);
	m_CtrlListProf.SetCurSel(sel+1);
}


void COrganizePreset::OnBnClickedButtonProfileTobottom()
{
	int sel = m_CtrlListProf.GetCurSel();
	if (sel == LB_ERR)
		return;
	if (sel == m_CtrlListProf.GetCount() - 1)
		return;
	SPreset* pProf = static_cast<SPreset*>(m_CtrlListProf.GetItemDataPtr(sel));
	m_CtrlListProf.DeleteString(sel);
	m_CtrlListProf.InsertString(m_CtrlListProf.GetCount(), pProf->name);
	m_CtrlListProf.SetItemDataPtr(m_CtrlListProf.GetCount()-1, pProf);
	m_CtrlListProf.SetCurSel(m_CtrlListProf.GetCount() - 1);
}


void COrganizePreset::OnBnClickedButtonProfileDelete()
{
	int sel = m_CtrlListProf.GetCurSel();
	if (sel == LB_ERR)
		return;
	SPreset* pProf = static_cast<SPreset*>(m_CtrlListProf.GetItemDataPtr(sel));
	m_CtrlListProf.DeleteString(sel);
	delete pProf;
}


