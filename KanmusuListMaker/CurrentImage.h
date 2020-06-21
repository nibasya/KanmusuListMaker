#pragma once

#include <vector>

// CCurrentImage

class CCurrentImage : public CStatic
{
	DECLARE_DYNAMIC(CCurrentImage)

public:
	CCurrentImage();
	virtual ~CCurrentImage();

protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseHover(UINT nFlags, CPoint point);
	afx_msg void OnMouseLeave();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);

	void UpdatePreview();
	bool AddImage(CImage *image);
	void ClearList();
	void DrawErrorMessage(std::vector< CString > * msg);
	CRect CalcSelectWindowRect(CPoint & point);
	CPoint CalcSelectWindowPoint(CPoint & point);
	int CalcIndexFromPoint(CPoint& point);

	std::vector< CImage * > m_ImageList;	// List of CImage to be shown
	CImage m_Image;	// an image of original size
	bool m_ImageAvailable;
	CRect m_Rect;	// represents original image size
	CRect m_DestRect;	// represents drawn image size which is fit to the control
	int m_ColorR;	// R of background color
	int m_ColorG;	// R of background color
	int m_ColorB;	// R of background color
	bool m_DrawHeader;	// If true, Header image is shown
	CRect m_HeaderRect;	// Header trimming region
	CRect m_TrimRect;	// Image trimming region for each image
	int m_Width;	// how many images are set in column direction
	int m_Height;	// how many images are set in row direction
	CRect m_RepresentiveImageRect;	// representive size of single image in m_ImageList
	enum EPriority {EP_WIDTH, EP_HEIGHT} m_Priority;
	enum ELimit {EL_WIDTH, EL_HEIGHT} m_LimitDir;
	int m_Limit;	// maximum number of images to drow in horizontal or vertical line

	enum EError {EE_EMPTY=-1, EE_MINUS=-2, EE_OUT_OF_RANGE=-3};
	bool m_StartTrack;
	CMenu m_PopupMenu;	// Popup menu object which is shown on right click
	CRect m_SelectWindowRect;
	bool m_ShowSelectWindow;	// when true, the rect indicator is shown
	void DrawItem(CDC* pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
private:
	bool m_Dragging;
	bool m_Captured;
	int m_DragTargetIndex;	// index of the dragged item; value is updated when it is dragged
	CPoint m_DragStartPoint;	// CPoint of the LButtonDown. used for drawing transperent image.
	CPoint m_CurrentMousePoint;	// CPoint of the mouse.
	CRect m_DragRect;	// The rect representing drag image
};


