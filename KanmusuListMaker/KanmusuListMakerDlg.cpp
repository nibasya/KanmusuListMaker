
// KanmusuListMakerDlg.cpp : �����t�@�C��
//

#include "stdafx.h"
#include "KanmusuListMaker.h"
#include "KanmusuListMakerDlg.h"
#include "afxdialogex.h"
#include "DlgSettingName.h"
#include <algorithm>
#include "OrganizeProfile.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace std;

CString GetLastErrorString()
{
	LPTSTR buff;
	CString ret;

	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&buff, 0, NULL);
	ret = buff;
	LocalFree(buff);
	return ret;
}

// �A�v���P�[�V�����̃o�[�W�������Ɏg���� CAboutDlg �_�C�A���O

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �_�C�A���O �f�[�^
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g

// ����
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


// CKanmusuListMakerDlg �_�C�A���O




CKanmusuListMakerDlg::CKanmusuListMakerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CKanmusuListMakerDlg::IDD, pParent)
	, m_LimitDir(0)
	, m_DefImgRect(0,0,0,0), m_SelectedSetting(-1), m_EnableUpdatePreview(true)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CKanmusuListMakerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_LEFT, m_CtrlEditLeft);
	DDX_Control(pDX, IDC_EDIT_TOP, m_CtrlEditTop);
	DDX_Control(pDX, IDC_EDIT_RIGHT, m_CtrlEditRight);
	DDX_Control(pDX, IDC_EDIT_BOTTOM, m_CtrlEditBottom);
	DDX_Control(pDX, IDC_EDIT_LINENUM, m_CtrlEditLineNum);
	DDX_Control(pDX, IDC_STATIC_IMAGE, m_CtrlImgPreview);
	DDX_Radio(pDX, IDC_RADIO_HEIGHT, m_LimitDir);
	DDX_Radio(pDX, IDC_RADIO_TOP_TO_BOTTOM, m_PriorityDir);
	DDX_Control(pDX, IDC_BUTTON_SAVE, m_CtrlButtonSave);
	DDX_Control(pDX, IDC_EDIT_HEADER_Y1, m_CtrlEditHeaderY1);
	DDX_Control(pDX, IDC_EDIT_HEADER_Y2, m_CtrlEditHeaderY2);
	DDX_Control(pDX, IDC_CHECK_HEADER, m_CtrlCheckHeader);
	DDX_Control(pDX, IDC_COMBO_SETTING, m_CtrlComboSetting);
	DDX_Control(pDX, IDC_EDIT_COLOR_R, m_CtrlEditColorR);
	DDX_Control(pDX, IDC_EDIT_COLOR_G, m_CtrlEditColorG);
	DDX_Control(pDX, IDC_EDIT_COLOR_B, m_CtrlEditColorB);
}

BEGIN_MESSAGE_MAP(CKanmusuListMakerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CKanmusuListMakerDlg::OnBnClickedButtonAdd)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, &CKanmusuListMakerDlg::OnBnClickedButtonClear)
	ON_WM_DROPFILES()
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CKanmusuListMakerDlg::OnBnClickedButtonSave)
	ON_EN_CHANGE(IDC_EDIT_HEADER_Y1, &CKanmusuListMakerDlg::Preview)
	ON_EN_CHANGE(IDC_EDIT_HEADER_Y2, &CKanmusuListMakerDlg::Preview)
	ON_EN_CHANGE(IDC_EDIT_LEFT, &CKanmusuListMakerDlg::Preview)
	ON_EN_CHANGE(IDC_EDIT_TOP, &CKanmusuListMakerDlg::Preview)
	ON_EN_CHANGE(IDC_EDIT_RIGHT, &CKanmusuListMakerDlg::Preview)
	ON_EN_CHANGE(IDC_EDIT_BOTTOM, &CKanmusuListMakerDlg::Preview)
	ON_EN_CHANGE(IDC_EDIT_LINENUM, &CKanmusuListMakerDlg::Preview)
	ON_EN_CHANGE(IDC_EDIT_COLOR_R, &CKanmusuListMakerDlg::Preview)
	ON_EN_CHANGE(IDC_EDIT_COLOR_G, &CKanmusuListMakerDlg::Preview)
	ON_EN_CHANGE(IDC_EDIT_COLOR_B, &CKanmusuListMakerDlg::Preview)
	ON_BN_CLICKED(IDC_RADIO_HEIGHT, &CKanmusuListMakerDlg::Preview)
	ON_BN_CLICKED(IDC_RADIO_WIDTH, &CKanmusuListMakerDlg::Preview)
	ON_BN_CLICKED(IDC_RADIO_LEFT_TO_RIGHT, &CKanmusuListMakerDlg::Preview)
	ON_BN_CLICKED(IDC_RADIO_TOP_TO_BOTTOM, &CKanmusuListMakerDlg::Preview)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_CHECK_HEADER, &CKanmusuListMakerDlg::OnBnClickedCheckHeader)
	ON_WM_GETMINMAXINFO()
	ON_CBN_SELCHANGE(IDC_COMBO_SETTING, &CKanmusuListMakerDlg::OnCbnSelchangeComboSetting)
	ON_BN_CLICKED(IDC_BUTTON_ADDSETTING, &CKanmusuListMakerDlg::OnBnClickedButtonAddSetting)
	ON_BN_CLICKED(IDC_BUTTON_SAVESETTING, &CKanmusuListMakerDlg::OnBnClickedButtonSavesetting)
	ON_BN_CLICKED(IDC_BUTTON_COPY, &CKanmusuListMakerDlg::OnBnClickedButtonCopy)
	ON_BN_CLICKED(IDC_BUTTON_PRESET_ORGANIZE, &CKanmusuListMakerDlg::OnBnClickedButtonPresetOrganize)
END_MESSAGE_MAP()


// CKanmusuListMakerDlg ���b�Z�[�W �n���h���[

BOOL CKanmusuListMakerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// "�o�[�W�������..." ���j���[���V�X�e�� ���j���[�ɒǉ����܂��B

	// IDM_ABOUTBOX �́A�V�X�e�� �R�}���h�͈͓̔��ɂȂ���΂Ȃ�܂���B
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

	// ���̃_�C�A���O�̃A�C�R����ݒ肵�܂��B�A�v���P�[�V�����̃��C�� �E�B���h�E���_�C�A���O�łȂ��ꍇ�A
	//  Framework �́A���̐ݒ�������I�ɍs���܂��B
	SetIcon(m_hIcon, TRUE);			// �傫���A�C�R���̐ݒ�
	SetIcon(m_hIcon, FALSE);		// �������A�C�R���̐ݒ�

	// �������������ɒǉ����܂��B
	m_hAccKey =::LoadAccelerators(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_ACCELERATOR));

	if (AfxGetApp()->GetProfileInt("common", "initialized", 0) == 0)
		CreateInitialData();
	if (InitSettingCombo() > 0) {
		CString defaultPreset = AfxGetApp()->GetProfileString("common", "default selection", "");
		int sel;
		if (defaultPreset == "") {
			sel = 0;
		}
		else {
			sel = m_CtrlComboSetting.FindString(0, defaultPreset);
			if (sel == CB_ERR) {
				sel = 0;
			}
			else {
				CString selTxt;
				m_CtrlComboSetting.GetLBText(sel, selTxt);
				if (selTxt != defaultPreset) {
					sel = 0;
				}
			}
		}
		m_CtrlComboSetting.SetCurSel(sel);
		m_SelectedSetting = sel;
	}

	OnCbnSelchangeComboSetting();

	GetWindowRect(&m_DefParentRect);
	m_CtrlImgPreview.GetClientRect(&m_DefImgRect);
	{
		int x, y, width, height;
		x = AfxGetApp()->GetProfileInt("common", "window pos x", m_DefParentRect.left);
		y = AfxGetApp()->GetProfileInt("common", "window pos y", m_DefParentRect.top);
		width = AfxGetApp()->GetProfileInt("common", "window width", m_DefParentRect.Width());
		height = AfxGetApp()->GetProfileInt("common", "window height", m_DefParentRect.Height());
		SetWindowPos(NULL, x, y, width, height, 0);
	}

	m_FileOpenTypeFilter.Format("Image Files|*.png;*.jpg;*.jpeg;*.bmp;*.gif|JPEG Files(jpg)|*.jpg;*.jpeg|PNG Files(png)|*.png|BMP Files(bmp)|*.bmp|GIF Files(gif)|*.gif||");
	m_FileSaveTypeFilter.Format("Image Files|*.png;*.jpg;*.jpeg;*.bmp;*.gif|JPEG Files(jpg)|*.jpg;*.jpeg|PNG Files(png)|*.png|BMP Files(bmp)|*.bmp|GIF Files(gif)|*.gif||");

	return TRUE;  // �t�H�[�J�X���R���g���[���ɐݒ肵���ꍇ�������ATRUE ��Ԃ��܂��B
}


void CKanmusuListMakerDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	OnBnClickedButtonClear();
	int sel;
	CString buff;
	sel=m_CtrlComboSetting.GetCurSel();
	if(sel!=LB_ERR){
		m_CtrlComboSetting.GetLBText(sel, buff);
		AfxGetApp()->WriteProfileString("common", "default selection", buff);
	}
	CRect rect;
	GetWindowRect(&rect);
	if (0 == AfxGetApp()->WriteProfileInt("common", "window pos x", rect.left))
		{MessageBox(GetLastErrorString()); return; }
	if (0 == AfxGetApp()->WriteProfileInt("common", "window pos y", rect.top))
		{MessageBox(GetLastErrorString()); return; }
	if (0 == AfxGetApp()->WriteProfileInt("common", "window width", rect.Width()))
		{MessageBox(GetLastErrorString()); return; }
	if (0 == AfxGetApp()->WriteProfileInt("common", "window height", rect.Height()))
		{MessageBox(GetLastErrorString()); return; }
}


void CKanmusuListMakerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// �_�C�A���O�ɍŏ����{�^����ǉ�����ꍇ�A�A�C�R����`�悷�邽�߂�
//  ���̃R�[�h���K�v�ł��B�h�L�������g/�r���[ ���f�����g�� MFC �A�v���P�[�V�����̏ꍇ�A
//  ����́AFramework �ɂ���Ď����I�ɐݒ肳��܂��B

void CKanmusuListMakerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �`��̃f�o�C�X �R���e�L�X�g

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// �N���C�A���g�̎l�p�`�̈���̒���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �A�C�R���̕`��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ���[�U�[���ŏ��������E�B���h�E���h���b�O���Ă���Ƃ��ɕ\������J�[�\�����擾���邽�߂ɁA
//  �V�X�e�������̊֐����Ăяo���܂��B
HCURSOR CKanmusuListMakerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CKanmusuListMakerDlg::OnBnClickedButtonAdd()
{
	const int NAMEBUFFERLENGTH=128*10240;
	
	CString iniPath=AfxGetApp()->GetProfileString("common", "Path LastLoadedPath");

	CFileDialog fd(TRUE, "image", NULL, 0, m_FileOpenTypeFilter);
	fd.m_ofn.lpstrInitialDir=iniPath;
	fd.m_ofn.Flags|=OFN_ALLOWMULTISELECT;
	if(fd.DoModal() != IDOK)
		return;

	// ���X�g�ɒǉ��B�g���q�̃`�F�b�N���͎��ۂɊJ���Ƃ��Ɋm�F�B
	TCHAR *p=fd.m_ofn.lpstrFile;
	TCHAR path[MAX_PATH];
	
	_tcscpy_s(path, MAX_PATH, p);
	CString buff;
	vector< CString > fileList;
	p+=_tcslen(p)+1;
	if(_tcslen(p)!=0){
		while(*p!=_T('\0')){
			buff.Format("%s\\%s", path, p);
			fileList.push_back(buff);
			p+=_tcslen(p)+1;
		}
	} else {
		fileList.push_back(path);
		PathRemoveFileSpec(path);
	}

	LoadImage(&fileList);

	AfxGetApp()->WriteProfileString("common", "Path LastLoadedPath", path);
	Preview();
}


void CKanmusuListMakerDlg::OnDropFiles(HDROP hDropInfo)
{
	// ���X�g�ɒǉ��B�g���q�̃`�F�b�N���͎��ۂɊJ���Ƃ��Ɋm�F�B
	UINT filenum=DragQueryFile(hDropInfo, -1, NULL, 0);	// �t�@�C�������擾
	UINT i;
	int pathlength=0;
	int reqiredPathLength;
	TCHAR *pathbuff=NULL;
	vector< CString > fileList;

	for(i=0;i<filenum;i++){
		// �K�v�ȃ������e�ʊm�F
		reqiredPathLength=DragQueryFile(hDropInfo, i, NULL, 0);
		if(reqiredPathLength>pathlength){
			pathlength=reqiredPathLength;
			delete pathbuff;
			pathbuff=new TCHAR[pathlength+1];
		}
		// �t�@�C�������p�X���Ǝ擾
		DragQueryFile(hDropInfo, i, pathbuff, pathlength+1);
		fileList.push_back(pathbuff);
	}

	LoadImage(&fileList);
	delete pathbuff;
	Preview();

	CDialogEx::OnDropFiles(hDropInfo);
}


void CKanmusuListMakerDlg::OnBnClickedButtonClear()
{
	m_CtrlImgPreview.ClearList();
	m_CtrlImgPreview.UpdatePreview();
}


void CKanmusuListMakerDlg::Preview()
{
	CRect canvasRect;
	CRect listRect;
	CString buff;
	int limit;
	CRect headerRect(0,0,0,0);
	HDC canvasDC=NULL;

	if (m_CtrlImgPreview.m_ImageList.size() == 0)
		return;
	if (!m_EnableUpdatePreview)
		return;

	// �����W
	UpdateData();
	m_CtrlEditLeft.GetWindowText(buff);
	listRect.left = GetCtrlValue(&m_CtrlEditLeft);
	listRect.top = GetCtrlValue(&m_CtrlEditTop);
	listRect.right = GetCtrlValue(&m_CtrlEditRight);
	listRect.bottom = GetCtrlValue(&m_CtrlEditBottom);
	limit = GetCtrlValue(&m_CtrlEditLineNum);
	if (limit == 0)
		limit = CCurrentImage::EError::EE_OUT_OF_RANGE;
	
	if(m_CtrlCheckHeader.GetCheck()==BST_CHECKED){
		headerRect.right=listRect.right;
		headerRect.left=listRect.left;
		headerRect.top = GetCtrlValue(&m_CtrlEditHeaderY1);
		headerRect.bottom = GetCtrlValue(&m_CtrlEditHeaderY2);
	}

	// �f�[�^�̓]��
	m_CtrlImgPreview.m_DrawHeader = (m_CtrlCheckHeader.GetCheck() == BST_CHECKED);
	m_CtrlImgPreview.m_HeaderRect.top = headerRect.top;
	m_CtrlImgPreview.m_HeaderRect.bottom = headerRect.bottom;
	m_CtrlImgPreview.m_HeaderRect.left = headerRect.left;
	m_CtrlImgPreview.m_HeaderRect.right = headerRect.right;
	m_CtrlImgPreview.m_TrimRect.top = listRect.top;
	m_CtrlImgPreview.m_TrimRect.bottom = listRect.bottom;
	m_CtrlImgPreview.m_TrimRect.left = listRect.left;
	m_CtrlImgPreview.m_TrimRect.right = listRect.right;
	m_CtrlImgPreview.m_Priority = (m_PriorityDir == 0) ? CCurrentImage::EPriority::EP_HEIGHT : CCurrentImage::EPriority::EP_WIDTH;
	m_CtrlImgPreview.m_Limit = limit;
	m_CtrlImgPreview.m_LimitDir = (m_LimitDir == 0) ? CCurrentImage::ELimit::EL_WIDTH : CCurrentImage::ELimit::EL_HEIGHT;
	m_CtrlImgPreview.m_ColorR = GetCtrlValue(&m_CtrlEditColorR);
	m_CtrlImgPreview.m_ColorG = GetCtrlValue(&m_CtrlEditColorG);
	m_CtrlImgPreview.m_ColorB = GetCtrlValue(&m_CtrlEditColorB);
	m_CtrlImgPreview.UpdatePreview();
	m_CtrlImgPreview.Invalidate();
}


void CKanmusuListMakerDlg::OnBnClickedButtonSave()
{
	if(!m_CtrlImgPreview.m_ImageAvailable){
		MessageBox("�ۑ��ł����Ԃł͂���܂���");
		return;
	}

	CString iniPath=AfxGetApp()->GetProfileString("common", "Path LastSavedPath");

	CFileDialog fd(FALSE, "image", NULL, 0, m_FileSaveTypeFilter);
	fd.m_ofn.lpstrInitialDir=iniPath;
	if(fd.DoModal() != IDOK)
		return;

	iniPath=fd.GetPathName();
	char *buff=new char[iniPath.GetLength()+1];
	strcpy_s(buff, iniPath.GetLength()+1, iniPath);
	PathRemoveFileSpec(buff);
	AfxGetApp()->WriteProfileString("common", "Path LastSavedPath", buff);

	CString file=fd.GetPathName();

	if(m_CtrlImgPreview.m_Image.Save(file)!=S_OK){
		MessageBox("�t�@�C���̕ۑ��Ɏ��s���܂���:%s", file);
		return;
	}

	MessageBox("�ۑ����܂���");
}


void CKanmusuListMakerDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: �����Ƀ��b�Z�[�W �n���h���[ �R�[�h��ǉ����܂��B
	if(m_DefParentRect.right==0)
		return;
}


void CKanmusuListMakerDlg::OnBnClickedCheckHeader()
{
	if(m_CtrlCheckHeader.GetCheck()==BST_CHECKED){
		m_CtrlEditHeaderY1.EnableWindow(TRUE);
		m_CtrlEditHeaderY2.EnableWindow(TRUE);
	} else {
		m_CtrlEditHeaderY1.EnableWindow(FALSE);
		m_CtrlEditHeaderY2.EnableWindow(FALSE);
	}
	Preview();
}


void CKanmusuListMakerDlg::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	// TODO: �����Ƀ��b�Z�[�W �n���h���[ �R�[�h��ǉ����邩�A����̏������Ăяo���܂��B
	lpMMI->ptMinTrackSize=CPoint(m_DefParentRect.Width(), m_DefParentRect.Height());

	CDialogEx::OnGetMinMaxInfo(lpMMI);
}

void CKanmusuListMakerDlg::CreateInitialData()
{
	CWinApp* p=AfxGetApp();
	
	p->WriteProfileString("0", "Profile name", "�͑��ꗗ�쐬");
	p->WriteProfileString("0", "Image Cutting Left", "356");
	p->WriteProfileString("0", "Image Cutting Top", "154");
	p->WriteProfileString("0", "Image Cutting Right", "800");
	p->WriteProfileString("0", "Image Cutting Bottom", "433");
	p->WriteProfileInt("0", "Image layout direction", 0);
	p->WriteProfileInt("0", "Output Mode", 0);
	p->WriteProfileString("0", "Output Line Num", "1");
	p->WriteProfileInt("0", "BackGroundColor R", 238);
	p->WriteProfileInt("0", "BackGroundColor G", 231);
	p->WriteProfileInt("0", "BackGroundColor B", 218);
	p->WriteProfileInt("0", "Header Enable", 1);
	p->WriteProfileString("0", "Header Y1", "95");
	p->WriteProfileString("0", "Header Y2", "128");

	p->WriteProfileString("1", "Profile name", "�����ꗗ�쐬");
	p->WriteProfileString("1", "Image Cutting Left", "200");
	p->WriteProfileString("1", "Image Cutting Top", "130");
	p->WriteProfileString("1", "Image Cutting Right", "569");
	p->WriteProfileString("1", "Image Cutting Bottom", "430");
	p->WriteProfileInt("1", "Image layout direction", 0);
	p->WriteProfileInt("1", "Output Mode", 0);
	p->WriteProfileString("1", "Output Line Num", "1");
	p->WriteProfileInt("1", "BackGroundColor R", 238);
	p->WriteProfileInt("1", "BackGroundColor G", 231);
	p->WriteProfileInt("1", "BackGroundColor B", 218);
	p->WriteProfileInt("1", "Header Enable", 1);
	p->WriteProfileString("1", "Header Y1", "100");
	p->WriteProfileString("1", "Header Y2", "129");

	p->WriteProfileString("common", "default selection", "�͑��ꗗ�쐬");
	p->WriteProfileInt("common", "initialized", 1);
}

// Reads preset number [sel] from .ini file and set values to [pPreset]
void CKanmusuListMakerDlg::LoadPreset(int sel, SPreset * pPreset)
{
	CString section;
	section.Format("%d", sel);

	pPreset->name = AfxGetApp()->GetProfileString(section, "Profile name", "���O������܂���");
	pPreset->imgTrim.left = AfxGetApp()->GetProfileInt(section, "Image Cutting Left", 356);
	pPreset->imgTrim.top = AfxGetApp()->GetProfileInt(section, "Image Cutting Top", 154);
	pPreset->imgTrim.right = AfxGetApp()->GetProfileInt(section, "Image Cutting Right", 800);
	pPreset->imgTrim.bottom = AfxGetApp()->GetProfileInt(section, "Image Cutting Bottom", 433);
	pPreset->priorityDir = AfxGetApp()->GetProfileInt(section, "Image layout direction", 0);
	pPreset->limitDir = AfxGetApp()->GetProfileInt(section, "Output Mode", 0);
	pPreset->lineNum= AfxGetApp()->GetProfileInt(section, "Output Line Num", 1);

	pPreset->colorR = AfxGetApp()->GetProfileInt(section, "BackGroundColor R", 238);
	pPreset->colorG = AfxGetApp()->GetProfileInt(section, "BackGroundColor G", 231);
	pPreset->colorB = AfxGetApp()->GetProfileInt(section, "BackGroundColor B", 218);

	pPreset->enableHeader = AfxGetApp()->GetProfileInt(section, "Header Enable", 1)== 0 ? false : true;
	pPreset->headerY1 = AfxGetApp()->GetProfileInt(section, "Header Y1", 95);
	pPreset->headerY2 = AfxGetApp()->GetProfileInt(section, "Header Y2", 128);
}

void CKanmusuListMakerDlg::OnCbnSelchangeComboSetting()
{
	int sel;
	m_EnableUpdatePreview = false;
	sel=m_CtrlComboSetting.GetCurSel();
	if(sel==CB_ERR)
		sel=0;

	SPreset prof;
	LoadPreset(sel, &prof);
	m_SelectedSetting=sel;

	m_CtrlEditLeft.SetWindowText(IntToStr(prof.imgTrim.left));
	m_CtrlEditTop.SetWindowText(IntToStr(prof.imgTrim.top));
	m_CtrlEditRight.SetWindowText(IntToStr(prof.imgTrim.right));
	m_CtrlEditBottom.SetWindowText(IntToStr(prof.imgTrim.bottom));
	m_PriorityDir = prof.priorityDir;
	m_LimitDir = prof.limitDir;
	m_CtrlEditLineNum.SetWindowText(IntToStr(prof.lineNum));
	m_CtrlEditColorR.SetWindowText(IntToStr(prof.colorR));
	m_CtrlEditColorG.SetWindowText(IntToStr(prof.colorG));
	m_CtrlEditColorB.SetWindowText(IntToStr(prof.colorB));
	UpdateData(FALSE);

	if(prof.enableHeader){
		m_CtrlCheckHeader.SetCheck(BST_CHECKED);
	} else {
		m_CtrlCheckHeader.SetCheck(BST_UNCHECKED);
	}
	m_CtrlEditHeaderY1.SetWindowText(IntToStr(prof.headerY1));
	m_CtrlEditHeaderY2.SetWindowText(IntToStr(prof.headerY2));
	OnBnClickedCheckHeader();
	m_EnableUpdatePreview = true;
	Preview();
}


// converts int number to CString text
CString CKanmusuListMakerDlg::IntToStr(int i)
{
	CString str;
	str.Format("%d", i);
	return str;
}


void CKanmusuListMakerDlg::OnBnClickedButtonAddSetting()
{
	CString buff;
	CDlgSettingName dlgName;

	if (dlgName.DoModal() != IDOK) {
		return;
	}
	buff=dlgName.m_name;
	if (buff.GetLength() < 1) {
		MessageBox("���O���Z�����܂�");
		return;
	}
	int index=m_CtrlComboSetting.AddString(buff);
	m_CtrlComboSetting.SetCurSel(index);
	m_SelectedSetting = index;
	OnCbnSelchangeComboSetting();
	OnBnClickedButtonSavesetting();
}


int CKanmusuListMakerDlg::InitSettingCombo()
{
	const int MAXBUFF = 4096;
	char buff[MAXBUFF];
	char name[MAXBUFF];
	int ret;
	int count = 0;

	ret = GetPrivateProfileSectionNames(buff, MAXBUFF, AfxGetApp()->m_pszProfileName);
	if (ret == MAXBUFF - 2) {
		MessageBox("�ݒ萔���������܂��B���炵�Ă��������B");
		exit(-1);
	}
	char* p = buff;
	char* pChk;
	bool flag;
	while(*p!='\0'){
		pChk = p;
		flag = true;
		while (*pChk != '\0') {
			if (flag && !isdigit(static_cast<int>(*pChk))) {
				flag = false;
			}
			pChk++;
		}
		if (flag) {
			ret=GetPrivateProfileString(p, "Profile name", "Empty", name, MAXBUFF, AfxGetApp()->m_pszProfileName);
			if (ret >= MAXBUFF - 1) {
				MessageBox("The name of the setting is too long");
				return 0;
			}
			m_CtrlComboSetting.AddString(name);
			count++;
		}
		p = pChk + 1;
	}

	return count;
}


void CKanmusuListMakerDlg::SavePreset(int index, SPreset *pPreset)
{
	CString section;
	section.Format("%d", index);

	if (index < 0)
		return;

	UpdateData(TRUE);
	CString buff;
	if (0 == AfxGetApp()->WriteProfileString(section, "Profile name", pPreset->name))
		{MessageBox(GetLastErrorString()); return;}
	if (0 == AfxGetApp()->WriteProfileInt(section, "Image Cutting Left", pPreset->imgTrim.left))
		{MessageBox(GetLastErrorString()); return; }
	if (0 == AfxGetApp()->WriteProfileInt(section, "Image Cutting Top", pPreset->imgTrim.top))
		{MessageBox(GetLastErrorString()); return; }
	if (0 == AfxGetApp()->WriteProfileInt(section, "Image Cutting Right", pPreset->imgTrim.right))
		{MessageBox(GetLastErrorString()); return; }
	if (0 == AfxGetApp()->WriteProfileInt(section, "Image Cutting Bottom", pPreset->imgTrim.bottom))
		{MessageBox(GetLastErrorString()); return; }

	if (0 == AfxGetApp()->WriteProfileInt(section, "Image layout direction", pPreset->priorityDir))
		{MessageBox(GetLastErrorString()); return; }
	if (0 == AfxGetApp()->WriteProfileInt(section, "Output mode", pPreset->limitDir))
		{MessageBox(GetLastErrorString()); return; }
	if (0 == AfxGetApp()->WriteProfileInt(section, "Output Line Num", pPreset->lineNum))
		{MessageBox(GetLastErrorString()); return; }

	if (0 == AfxGetApp()->WriteProfileInt(section, "BackGroundColor R", pPreset->colorR))
		{MessageBox(GetLastErrorString()); return; }
	if (0 == AfxGetApp()->WriteProfileInt(section, "BackGroundColor G", pPreset->colorG))
		{MessageBox(GetLastErrorString()); return; }
	if (0 == AfxGetApp()->WriteProfileInt(section, "BackGroundColor B", pPreset->colorB))
		{MessageBox(GetLastErrorString()); return; }

	if (0 == AfxGetApp()->WriteProfileInt(section, "Header Enable", pPreset->enableHeader))
		{MessageBox(GetLastErrorString()); return; }
	if (0 == AfxGetApp()->WriteProfileInt(section, "Header Y1", pPreset->headerY1))
		{MessageBox(GetLastErrorString()); return; }
	if (0 == AfxGetApp()->WriteProfileInt(section, "Header Y2", pPreset->headerY2))
		{MessageBox(GetLastErrorString()); return; }
}


void CKanmusuListMakerDlg::OnBnClickedButtonSavesetting()
{
	int index = m_SelectedSetting;

	CString section;
	section.Format("%d", index);

	if (index < 0)
		return;
	if (m_CtrlComboSetting.GetCount() <= index) {
		OnBnClickedButtonAddSetting();
		return;
	}

	UpdateData(TRUE);
	CString buff;
	SPreset prof;
	m_CtrlComboSetting.GetWindowText(buff);
	prof.name = buff;
	m_CtrlEditLeft.GetWindowText(buff);
	prof.imgTrim.left = buff.GetLength() != 0 ? atoi(buff) : 0;
	m_CtrlEditTop.GetWindowText(buff);
	prof.imgTrim.top = buff.GetLength() != 0 ? atoi(buff) : 0;
	m_CtrlEditRight.GetWindowText(buff);
	prof.imgTrim.right = buff.GetLength() != 0 ? atoi(buff) : 0;
	m_CtrlEditBottom.GetWindowText(buff);
	prof.imgTrim.bottom = buff.GetLength() != 0 ? atoi(buff) : 0;

	prof.priorityDir = m_PriorityDir;
	prof.limitDir = m_LimitDir;

	m_CtrlEditLineNum.GetWindowText(buff);
	prof.lineNum = buff.GetLength() != 0 ? atoi(buff) : 1;

	m_CtrlEditColorR.GetWindowText(buff);
	prof.colorR = buff.GetLength() != 0 ? atoi(buff) : 0;
	m_CtrlEditColorG.GetWindowText(buff);
	prof.colorG = buff.GetLength() != 0 ? atoi(buff) : 0;
	m_CtrlEditColorB.GetWindowText(buff);
	prof.colorB = buff.GetLength() != 0 ? atoi(buff) : 0;

	if (m_CtrlCheckHeader.GetCheck() == BST_CHECKED) {
		prof.enableHeader = 1;
	}
	else {
		prof.enableHeader = 0;
	}
	m_CtrlEditHeaderY1.GetWindowText(buff);
	prof.headerY1 = buff.GetLength() != 0 ? atoi(buff) : 0;
	m_CtrlEditHeaderY2.GetWindowText(buff);
	prof.headerY2 = buff.GetLength() != 0 ? atoi(buff) : 0;

	SavePreset(index, &prof);
	m_CtrlComboSetting.DeleteString(index);
	m_CtrlComboSetting.InsertString(index, prof.name);
	m_CtrlComboSetting.SetCurSel(index);
}


bool CKanmusuListMakerDlg::LoadImage(std::vector< CString> * fileList)
{
	CImage *img;
	unsigned int i;
	HRESULT res;
	bool fail = false, invalid_size = false;

	sort(fileList->begin(), fileList->end());
	for (i = 0; i<fileList->size(); i++) {
		// �t�@�C����ǂݍ���
		img = new CImage;
		res = img->Load((*fileList)[i]);
		if (res != S_OK) {
			fail = true;
			delete img;
			continue;
		}
		if (!m_CtrlImgPreview.AddImage(img)) {
			invalid_size = true;
			delete img;
		}
	}
	if (fail)
		MessageBox("�ǂݍ��߂Ȃ��t�@�C��������܂���");
	if (invalid_size)
		MessageBox("���ƃT�C�Y�̈قȂ�t�@�C��������܂����B�X�L�b�v���܂��B");

	if(fail || invalid_size)
		return false;
	return true;
}


int CKanmusuListMakerDlg::GetCtrlValue(CWnd* pCtrl)
{
	CString buff;
	int i;
	pCtrl->GetWindowText(buff);
	if (strlen(buff) == 0)
		return CCurrentImage::EError::EE_EMPTY;
	i = atoi(buff);
	if (i < 0)
		return CCurrentImage::EError::EE_MINUS;
	else
		return i;
}


void CKanmusuListMakerDlg::OnBnClickedButtonCopy()
{
	if (!m_CtrlImgPreview.m_ImageAvailable) {
		MessageBox("�R�s�[�ł����Ԃł͂���܂���");
		return;
	}

	CImage* pImg = &m_CtrlImgPreview.m_Image;
	DIBSECTION ds;
	if (GetObject(*pImg, sizeof(DIBSECTION), &ds) == NULL) {
		MessageBox("�r�b�g�}�b�v���̎擾�Ɏ��s(GetObject���s)");
		return;
	}

	long int bmpSize = ds.dsBmih.biWidth*abs(ds.dsBmih.biHeight)*ds.dsBmih.biBitCount / 8;
	HGLOBAL hmBI = GlobalAlloc(GMEM_MOVEABLE, sizeof(BITMAPINFO)+bmpSize);
	if (hmBI == NULL) {
		MessageBox("������������܂���(GlobalAlloc���s)");
		return;
	}
	BITMAPINFO *pBI = (BITMAPINFO*) GlobalLock(hmBI);
	if (pBI == NULL) {
		MessageBox("�R�s�y�p�������̃��b�N�Ɏ��s(GlobalLock���s)");
		GlobalFree(hmBI);
		return;
	}
	pBI->bmiHeader = ds.dsBmih;
	BYTE *pBmpDest = (BYTE*)(pBI + 1);
	BYTE *pBmpSrc = (BYTE*)ds.dsBm.bmBits;
	for (int i = 0; i < bmpSize; i++) {
		pBmpDest[i] = pBmpSrc[i];
	}
	GlobalUnlock(hmBI);

	if (!OpenClipboard()) {
		MessageBox("�N���b�v�{�[�h���J���܂���ł���");
		GlobalFree(hmBI);
		return;
	}
	if (!EmptyClipboard()) {
		MessageBox("�N���b�v�{�[�h���N���A�ł��܂���ł���");
		CloseClipboard();
		GlobalFree(hmBI);
		return;
	}

	if (SetClipboardData(CF_DIB, hmBI) == NULL) {
		MessageBox("�N���b�v�{�[�h�ւ̉摜�\��t���Ɏ��s���܂���");
		CloseClipboard();
		return;
	}
	if (!CloseClipboard()) {
		MessageBox("�N���b�v�{�[�h�����̂Ɏ��s���܂���");
	}
}


BOOL CKanmusuListMakerDlg::PreTranslateMessage(MSG* pMsg)
{
	if (m_hAccKey!=NULL) {
		if (::TranslateAccelerator(this->m_hWnd, m_hAccKey, pMsg))
			return true;
	}
	
	return CDialogEx::PreTranslateMessage(pMsg);
}


void CKanmusuListMakerDlg::OnBnClickedButtonPresetOrganize()
{
	COrganizePreset org;

	int i;
	CString str;
	SPreset *pProf;

	for (i = 0; i < m_CtrlComboSetting.GetCount(); i++) {
		pProf = new SPreset;
		LoadPreset(i, pProf);
		org.m_Data.push_back(pProf);
	}

	INT_PTR ret;
	ret = org.DoModal();

	ASSERT(ret != -1);
	ASSERT(ret != IDABORT);

	if (ret == IDOK) {
		CString name;
		// backup name of the current selected preset name
		if (m_CtrlComboSetting.GetCurSel() == CB_ERR)
			name = "empty";	// set dummy data if nothing is selected
		else
			m_CtrlComboSetting.GetLBText(m_CtrlComboSetting.GetCurSel(), name);

		while(m_CtrlComboSetting.GetCount()>0) {
			m_CtrlComboSetting.DeleteString(0);
		}

		std::vector<SPreset> presetList;
		SPreset preset;
		// save presets
		for (i = 0; i < (int)org.m_Data.size(); i++) {
			if (org.m_Data[i] != NULL) {
				SavePreset(i, org.m_Data[i]);
				m_CtrlComboSetting.InsertString(i, org.m_Data[i]->name);
			}
			else {
				// Delete section
				ret = AfxGetApp()->WriteProfileString(IntToStr(i), NULL, NULL);
				if (ret == 0) {
					MessageBox(GetLastErrorString());
				}
			}
		}

		i = 0;
		int j = -1;
		CString str;
		while (j < (i = m_CtrlComboSetting.FindStringExact(i, name))) {
			// find item name which completely matches to the selected preset name
			i = m_CtrlComboSetting.FindStringExact(i, name);
			if (i == CB_ERR) {
				if (m_CtrlComboSetting.GetCount() == 0) {
					m_CtrlComboSetting.SetWindowText("");
					break;
				}
				m_CtrlComboSetting.SetCurSel(0);
				break;
			}
			m_CtrlComboSetting.GetLBText(i, str);
			if (str == name) {
				m_CtrlComboSetting.SetCurSel(i);
				break;
			}
			j = i;
		}
		if (m_CtrlComboSetting.GetCurSel() == CB_ERR) {
			if (m_CtrlComboSetting.GetCount() == 0) {
				m_CtrlComboSetting.SetWindowText("");
			}
			else {
				m_CtrlComboSetting.SetCurSel(0);
			}
		}
	}

	for (i = 0; i < (int)org.m_Data.size(); i++) {
		if (org.m_Data[i] != NULL) {
			delete org.m_Data[i];
		}
	}
}

