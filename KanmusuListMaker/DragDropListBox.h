#pragma once


// CDragDropListBox

class CDragDropListBox : public CListBox
{
	DECLARE_DYNAMIC(CDragDropListBox)

public:
	CDragDropListBox();
	virtual ~CDragDropListBox();

protected:
	DECLARE_MESSAGE_MAP()
private:
	bool m_Dragging;
	bool m_Captured;
	int m_ScrollDir;	// if zero, scroll up. if 1, scroll down.
	bool m_Scrolling;
	int m_TargetIndex;	// index of the dragged item; value is updated when it is dragged
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
private:
	void SwapItem(int newIndex);
};


