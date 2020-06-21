// DragDropListBox.cpp : 実装ファイル
//

#include "stdafx.h"
//#include "KanmusuListMaker.h"
#include "DragDropListBox.h"

const int TIMER_SCROLL = 4231;

// CDragDropListBox

IMPLEMENT_DYNAMIC(CDragDropListBox, CListBox)

CDragDropListBox::CDragDropListBox()
	:m_Dragging(false), m_Captured(false), m_Scrolling(false)
{

}

CDragDropListBox::~CDragDropListBox()
{
}


BEGIN_MESSAGE_MAP(CDragDropListBox, CListBox)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_TIMER()
END_MESSAGE_MAP()



// CDragDropListBox メッセージ ハンドラー




void CDragDropListBox::OnLButtonDown(UINT nFlags, CPoint point)
{
	BOOL outside;
	int index;

	m_Dragging = false;
	m_Captured = false;

	index = ItemFromPoint(point, outside);
	if (!outside && index != LB_ERR) {
		m_Dragging = true;
		m_TargetIndex = index;
	}

	CListBox::OnLButtonDown(nFlags, point);
}


void CDragDropListBox::OnMouseMove(UINT nFlags, CPoint point)
{
	BOOL outside;
	int index;

	if (m_Dragging && !m_Captured) {
		SetCapture();
		m_Captured = true;
		index = ItemFromPoint(point, outside);
	}
	
	if (m_Dragging) {
		// スクロール制御
		index = ItemFromPoint(point, outside);
		if (!outside && m_Scrolling) { // スクロール停止
			VERIFY(KillTimer(TIMER_SCROLL)!=0);
			m_Scrolling = false;
		}

		if (outside) {
			if (!m_Scrolling) {
				CRect rect;
				GetClientRect(&rect);
				if (point.y < 0) {
					m_ScrollDir = 0;
					VERIFY(SetTimer(TIMER_SCROLL, 200, NULL)!=0);
					m_Scrolling = true;
				}
				if (point.y > rect.bottom) {
					m_ScrollDir = 1;
					VERIFY(SetTimer(TIMER_SCROLL, 200, NULL)!=0);
					m_Scrolling = true;
				}
			}
		}

		// ドラッグ処理
		if (!outside && index != m_TargetIndex) {
			SwapItem(index);
		}
	}

	CListBox::OnMouseMove(nFlags, point);
}


void CDragDropListBox::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (m_Captured) {
		ReleaseCapture();
	}
	if (m_Scrolling) {
		VERIFY(KillTimer(TIMER_SCROLL)!=0);
		m_Scrolling = false;
	}

	m_Captured = false;
	m_Dragging = false;

	CListBox::OnLButtonUp(nFlags, point);
}




void CDragDropListBox::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent != TIMER_SCROLL)
		return;

	int top=GetTopIndex();
	
	if (m_ScrollDir == 0 && top>0 && m_TargetIndex != 0){
		SwapItem(m_TargetIndex - 1);
		SetTopIndex(top - 1);
	}
	if (m_ScrollDir == 1) {
		CRect itemRect;
		CRect clientRect;
		VERIFY(GetItemRect(GetCount() - 1, &itemRect)!=LB_ERR);
		GetClientRect(&clientRect);

		int index = m_TargetIndex + 1;
		if (index < GetCount()) {
			SwapItem(index);
		}

		if (itemRect.bottom > clientRect.bottom) {
			SetTopIndex(top + 1);
		}
	}

	CListBox::OnTimer(nIDEvent);
}


 void CDragDropListBox::SwapItem(int newIndex)
{
	DWORD data;
	CString str;
	int top;

	SetRedraw(FALSE);
	top = GetTopIndex();

	int index=m_TargetIndex;
	
	if (newIndex > m_TargetIndex) {
		index++;
	}
	if (newIndex < m_TargetIndex) {
		index--;
	}
	GetText(index, str);
	data = GetItemData(index);
	ASSERT(data != LB_ERR);
	VERIFY(DeleteString(index) != LB_ERR);
	VERIFY(InsertString(m_TargetIndex, str) >= 0);
	VERIFY(SetItemData(m_TargetIndex, data) != LB_ERR);
	m_TargetIndex = index;
	SetTopIndex(top);
	SetRedraw(TRUE);
 }
