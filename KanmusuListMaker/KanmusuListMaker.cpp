
// KanmusuListMaker.cpp : �A�v���P�[�V�����̃N���X������`���܂��B
//

#include "stdafx.h"
#include "KanmusuListMaker.h"
#include "KanmusuListMakerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CKanmusuListMakerApp

BEGIN_MESSAGE_MAP(CKanmusuListMakerApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CKanmusuListMakerApp �R���X�g���N�V����

CKanmusuListMakerApp::CKanmusuListMakerApp()
{
	// �ċN���}�l�[�W���[���T�|�[�g���܂�
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: ���̈ʒu�ɍ\�z�p�R�[�h��ǉ����Ă��������B
	// ������ InitInstance ���̏d�v�ȏ��������������ׂċL�q���Ă��������B
}


// �B��� CKanmusuListMakerApp �I�u�W�F�N�g�ł��B

CKanmusuListMakerApp theApp;


// CKanmusuListMakerApp ������

BOOL CKanmusuListMakerApp::InitInstance()
{
	// �A�v���P�[�V���� �}�j�t�F�X�g�� visual �X�^�C����L���ɂ��邽�߂ɁA
	// ComCtl32.dll Version 6 �ȍ~�̎g�p���w�肷��ꍇ�́A
	// Windows XP �� InitCommonControlsEx() ���K�v�ł��B�����Ȃ���΁A�E�B���h�E�쐬�͂��ׂĎ��s���܂��B
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// �A�v���P�[�V�����Ŏg�p���邷�ׂẴR���� �R���g���[�� �N���X���܂߂�ɂ́A
	// �����ݒ肵�܂��B
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	// �_�C�A���O�ɃV�F�� �c���[ �r���[�܂��̓V�F�� ���X�g �r���[ �R���g���[����
	// �܂܂�Ă���ꍇ�ɃV�F�� �}�l�[�W���[���쐬���܂��B
	CShellManager *pShellManager = new CShellManager;

	// �W��������
	// �����̋@�\���g�킸�ɍŏI�I�Ȏ��s�\�t�@�C����
	// �T�C�Y���k���������ꍇ�́A�ȉ�����s�v�ȏ�����
	// ���[�`�����폜���Ă��������B
	// �ݒ肪�i�[����Ă��郌�W�X�g�� �L�[��ύX���܂��B
	// TODO: ��Ж��܂��͑g�D���Ȃǂ̓K�؂ȕ������
	// ���̕������ύX���Ă��������B
	// SetRegistryKey(_T("�A�v���P�[�V���� �E�B�U�[�h�Ő������ꂽ���[�J�� �A�v���P�[�V����"));
	// ���W�X�g���͌����Ȃ̂Ŏg��Ȃ�
	TCHAR path[_MAX_PATH+1];
	GetModuleFileName(NULL, path, _MAX_PATH);
	PathRenameExtension(path, TEXT(".ini"));
	free((void*)m_pszProfileName);
	m_pszProfileName=_tcsdup(path);

	CKanmusuListMakerDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: �_�C�A���O�� <OK> �ŏ����ꂽ���̃R�[�h��
		//  �L�q���Ă��������B
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �_�C�A���O�� <�L�����Z��> �ŏ����ꂽ���̃R�[�h��
		//  �L�q���Ă��������B
	}

	// ��ō쐬���ꂽ�V�F�� �}�l�[�W���[���폜���܂��B
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// �_�C�A���O�͕����܂����B�A�v���P�[�V�����̃��b�Z�[�W �|���v���J�n���Ȃ���
	//  �A�v���P�[�V�������I�����邽�߂� FALSE ��Ԃ��Ă��������B
	return FALSE;
}
