// CurrentImage.cpp : 実装ファイル
//

#include "stdafx.h"
//#include "KanmusuListMakerDlg.h"
#include "CurrentImage.h"

// CCurrentImage

IMPLEMENT_DYNAMIC(CCurrentImage, CStatic)

CCurrentImage::CCurrentImage()
	:m_Rect(0,0,0,0), m_ColorR(255),m_ColorG(255), m_ColorB(255),m_StartTrack(false),
	m_ImageAvailable(false), m_SelectWindowRect(0,0,0,0), m_Captured(false), m_Dragging(false)
{
	VERIFY(m_PopupMenu.CreatePopupMenu());
	MENUITEMINFO mii = { sizeof(MENUITEMINFO), MIIM_FTYPE | MIIM_ID | MIIM_STRING, MFT_STRING, MFS_UNHILITE, 0, 0, 0, 0, NULL, NULL, 0, 0 };

	char *buff;

	buff = "削除";
	mii.wID = 1;
	mii.dwTypeData = buff;
	mii.cch = strlen(buff);
	VERIFY(m_PopupMenu.InsertMenuItem(0, &mii));
}

CCurrentImage::~CCurrentImage()
{
	ClearList();
}


BEGIN_MESSAGE_MAP(CCurrentImage, CStatic)
	ON_WM_RBUTTONUP()
	ON_WM_MOUSEHOVER()
	ON_WM_MOUSELEAVE()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()



// CCurrentImage メッセージ ハンドラー




void CCurrentImage::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	if(m_Rect.right==0)
		return;

	CDC dc;
	dc.CreateCompatibleDC(CDC::FromHandle(lpDrawItemStruct->hDC));
	CBitmap bmp;
	VERIFY(bmp.CreateCompatibleBitmap(CDC::FromHandle(lpDrawItemStruct->hDC), lpDrawItemStruct->rcItem.right, lpDrawItemStruct->rcItem.bottom)!=0);
	CBitmap* pOldBmp = dc.SelectObject(&bmp);
	ASSERT(pOldBmp != NULL);
	
	// 背景塗りつぶし
	CBrush myBrush(RGB(212, 208, 200));
	CPen myPen;
	myPen.CreatePen(PS_SOLID, 0, RGB(212, 208, 200));
	CBrush* pOldBrush = dc.SelectObject(&myBrush);
	CPen* pOldPen = dc.SelectObject(&myPen);
	dc.Rectangle(&lpDrawItemStruct->rcItem);
	dc.SelectObject(pOldBrush);
	dc.SelectObject(pOldPen);
	if(!m_Image.IsNull())
		DrawItem(&dc);

	CDC diDC;
	diDC.Attach(lpDrawItemStruct->hDC);

	diDC.BitBlt(0, 0, lpDrawItemStruct->rcItem.right, lpDrawItemStruct->rcItem.bottom, &dc, 0, 0, SRCCOPY);

	diDC.Detach();
	dc.SelectObject(pOldBmp);
}

void CCurrentImage::DrawItem(CDC* pDC)
{
	static CRect oldSelectWindowRect;

	// プレビューサイズ計算
	CRect ctrlRect;
	GetClientRect(&ctrlRect);
	CRect dstRect = ctrlRect;
	if (dstRect.right<(m_Rect.right*dstRect.bottom) / m_Rect.bottom) {
		dstRect.right = dstRect.right;
		dstRect.bottom = (m_Rect.bottom*dstRect.right) / m_Rect.right;
	}
	else {
		dstRect.right = (m_Rect.right*dstRect.bottom) / m_Rect.bottom;
		dstRect.bottom = dstRect.bottom;
	}
	CPoint d = ctrlRect.CenterPoint() - dstRect.CenterPoint();
	dstRect.MoveToXY(d);
	
	// プレビュー作成
	pDC->SetStretchBltMode(HALFTONE);
	SetBrushOrgEx(pDC->m_hDC, 0, 0, NULL);
	m_Image.StretchBlt(pDC->m_hDC, dstRect, m_Rect, SRCCOPY);
	m_DestRect = dstRect;

	if (m_ShowSelectWindow && m_SelectWindowRect.Width() != 0 && m_SelectWindowRect.Height() != 0) {
		// 赤枠作成
		CImage waku;
		waku.Create(m_SelectWindowRect.Width(), m_SelectWindowRect.Height(), 32);
		CDC wakuDC;
		wakuDC.Attach(waku.GetDC());

		CPen pen, *pOldpen;
		const int lineWidth = 5;
		pen.CreatePen(PS_SOLID, lineWidth, RGB(255, 0, 0));
		pOldpen = (CPen*)(wakuDC.SelectObject(&pen));
		wakuDC.BitBlt(0,0,m_SelectWindowRect.Width(),m_SelectWindowRect.Height(), pDC, m_SelectWindowRect.left, m_SelectWindowRect.top, SRCCOPY);
		wakuDC.MoveTo(lineWidth / 2, lineWidth / 2);
		wakuDC.LineTo(m_SelectWindowRect.Width() - lineWidth / 2, lineWidth / 2);
		wakuDC.LineTo(m_SelectWindowRect.Width() - lineWidth / 2, m_SelectWindowRect.Height() - lineWidth / 2);
		wakuDC.LineTo(lineWidth / 2, m_SelectWindowRect.Height() - lineWidth / 2);
		wakuDC.LineTo(lineWidth / 2, lineWidth / 2);
		BLENDFUNCTION bf = { AC_SRC_OVER, 0, 180, 0 };
		pDC->AlphaBlend(m_SelectWindowRect.left, m_SelectWindowRect.top, m_SelectWindowRect.Width(), m_SelectWindowRect.Height(), &wakuDC, 0, 0, m_SelectWindowRect.Width(), m_SelectWindowRect.Height(), bf);

		wakuDC.SelectObject(pOldpen);
		wakuDC.Detach();
		waku.ReleaseDC();
	}
	oldSelectWindowRect = m_SelectWindowRect;

	// drag中の半透明イメージを表示
	if (m_Dragging) {
		CRect rect = m_DragRect;
		CDC dragDC;
		dragDC.Attach(m_ImageList[m_DragTargetIndex]->GetDC());
		rect.OffsetRect(m_CurrentMousePoint - m_DragStartPoint);
		_RPTN(_CRT_WARN, "dx=%d dy=%d rectx=%d recty=%d\n", (m_CurrentMousePoint - m_DragStartPoint).cx, (m_CurrentMousePoint - m_DragStartPoint).cy, rect.left, rect.top);
		BLENDFUNCTION bf = { AC_SRC_OVER, 0, 225, 0 };
		pDC->AlphaBlend(rect.left, rect.top, rect.Width(), rect.Height(), &dragDC, m_TrimRect.left, m_TrimRect.top, m_TrimRect.Width(), m_TrimRect.Height(), bf);
		dragDC.Detach();
		m_ImageList[m_DragTargetIndex]->ReleaseDC();
	}
}


void CCurrentImage::OnRButtonUp(UINT nFlags, CPoint point)
{
	if (!m_ImageAvailable)
		return;

	int ret;
	CPoint sp = point;
	ClientToScreen(&sp);
	CPoint p = CalcSelectWindowPoint(point);
	int index = CalcIndexFromPoint(point);
	if (p.x >= 0 && p.x < m_Width && p.y >= 0 && p.y < m_Height && index<(int)m_ImageList.size()) {
		if (GetSystemMetrics(SM_MENUDROPALIGNMENT)) {
			ret = TrackPopupMenu(m_PopupMenu, TPM_RIGHTALIGN | TPM_RETURNCMD, sp.x, sp.y, 0, m_hWnd, NULL);
		}
		else {
			ret = TrackPopupMenu(m_PopupMenu, TPM_LEFTALIGN | TPM_RETURNCMD, sp.x, sp.y, 0, m_hWnd, NULL);
		}
		if (ret == 1) {
			delete m_ImageList[index];
			m_ImageList.erase(m_ImageList.begin() + index);
			UpdatePreview();
		}
	}
	CStatic::OnRButtonUp(nFlags, point);
}

bool CCurrentImage::AddImage(CImage *image)
{
	// if there are no image, then initialize
	if (m_ImageList.size() == 0) {
		m_RepresentiveImageRect.bottom = image->GetHeight();
		m_RepresentiveImageRect.right = image->GetWidth();
	}

	if (m_RepresentiveImageRect.Width() == image->GetWidth() && m_RepresentiveImageRect.Height() == image->GetHeight()) {
		m_ImageList.push_back(image);
		return true;
	}
	else {
		return false;
	}
}


void CCurrentImage::UpdatePreview()
{
	HDC canvasDC = NULL;
	std::vector< CString > errmsg;

	// Check image
	if (m_ImageList.size() == 0) {
		RedrawWindow();
		return;
//		errmsg.push_back("");
//		errmsg.push_back("画像ファイルをここにドラッグ\n");
	}
	if (m_TrimRect.left == EE_EMPTY) {
		errmsg.push_back("画像切り出し位置エラー\n　X1に数値を入力してください");
	}
	if (m_TrimRect.left == EE_MINUS) {
		errmsg.push_back("画像切り出し位置エラー\n　X1は0または正の数値にしてください");
	}
	if (m_TrimRect.top == EE_EMPTY) {
		errmsg.push_back("画像切り出し位置エラー\n　Y1に数値を入力してください");
	}
	if (m_TrimRect.top == EE_MINUS) {
		errmsg.push_back("画像切り出し位置エラー\n　Y1は0または正の数値にしてください");
	}
	if (m_TrimRect.right == EE_EMPTY) {
		errmsg.push_back("画像切り出し位置エラー\n　X2に数値を入力してください");
	}
	if (m_TrimRect.right == EE_MINUS) {
		errmsg.push_back("画像切り出し位置エラー\n　X2は0または正の数値にしてください");
	}
	if (m_TrimRect.bottom == EE_EMPTY) {
		errmsg.push_back("画像切り出し位置エラー\n　Y2に数値を入力してください");
	}
	if (m_TrimRect.bottom == EE_MINUS) {
		errmsg.push_back("画像切り出し位置エラー\n　Y2は0または正の数値にしてください");
	}
	if (m_HeaderRect.top == EE_EMPTY) {
		errmsg.push_back("ヘッダ切り出し位置エラー\n　Y1に数値を入力してください");
	}
	if (m_HeaderRect.top == EE_MINUS) {
		errmsg.push_back("ヘッダ切り出し位置エラー\n　Y1は0または正の数値にしてください");
	}
	if (m_HeaderRect.bottom == EE_EMPTY) {
		errmsg.push_back("ヘッダ切り出し位置エラー\n　Y2に数値を入力してください");
	}
	if (m_HeaderRect.bottom == EE_MINUS) {
		errmsg.push_back("ヘッダ切り出し位置エラー\n　Y2は0または正の数値にしてください");
	}
	if (m_Limit == EE_EMPTY) {
		errmsg.push_back("サイズ制限エラー\n　行/列数に数値を入力してください");
	}
	if (m_Limit == EE_MINUS || m_Limit == EE_OUT_OF_RANGE) {
		errmsg.push_back("サイズ制限エラー\n　行/列数に1以上の数値を入れてください");
	}
	if (m_TrimRect.bottom <= m_TrimRect.top) {
		errmsg.push_back("画像切り出し位置エラー\n　Y2はY1より大きくしてください\n");
	}
	if (m_RepresentiveImageRect.bottom < m_TrimRect.bottom) {
		errmsg.push_back("画像切り出し位置エラー\n　Y2が画像からはみ出しています\n");
	}
	if (m_TrimRect.right <= m_TrimRect.left) {
		errmsg.push_back("画像切り出し位置エラー\n　X2はX2より大きくしてください\n");
	}
	if (m_RepresentiveImageRect.right < m_TrimRect.right) {
		errmsg.push_back("画像切り出し位置エラー\n　X2が画像からはみ出しています\n");
	}
	if (m_HeaderRect.bottom <= m_HeaderRect.top && m_DrawHeader) {
		errmsg.push_back("ヘッダ切り出し位置エラー\n　Y2はY1より大きくしてください\n");
	}
	if (m_RepresentiveImageRect.bottom < m_HeaderRect.bottom && m_DrawHeader) {
		errmsg.push_back("ヘッダ切り出し位置エラー\n　Y2が画像からはみ出しています\n");
	}
	if(errmsg.size()){
		m_ImageAvailable = false;
		DrawErrorMessage(&errmsg);
		RedrawWindow();
		return;
	}

	int limit = m_Limit;
	if (limit > (int)m_ImageList.size())
		limit = m_ImageList.size();
	// 縦横の演算
	switch (m_LimitDir) {
	case ELimit::EL_WIDTH:
		m_Width = limit;
		m_Height = (m_ImageList.size() + limit - 1) / limit;
		break;
	case ELimit::EL_HEIGHT:
		m_Height = limit;
		m_Width = (m_ImageList.size() + limit - 1) / limit;
		break;
	default:
		MessageBox("ありえない数値がラジオボタンに設定されました");
		return;
	}
	switch (m_Priority) {
	case EPriority::EP_HEIGHT:
		if (((int)m_ImageList.size()+m_Height-1) / m_Height < m_Width)
			m_Width = m_ImageList.size() / m_Height;
		break;
	case EPriority::EP_WIDTH:
		if (((int)m_ImageList.size()+m_Height-1) / m_Width < m_Height)
			m_Height = m_ImageList.size() / m_Height;
		break;
	}
	// キャンバスの生成
	if (!m_Image.IsNull()) {
		m_Image.Destroy();
	}
	m_Rect.right = m_Width*m_TrimRect.Width();
	m_Rect.bottom = m_Height*m_TrimRect.Height() + m_HeaderRect.Height();
	m_Image.Create(m_Rect.Width(), m_Rect.Height(), 32);
	canvasDC = m_Image.GetDC();
	{
		CDC::FromHandle(canvasDC)->FillSolidRect(&m_Rect, RGB(m_ColorR, m_ColorG, m_ColorB));
	}
	
	int i;
	// ヘッダの生成
	if (m_DrawHeader) {
		for (i = 0; i < m_Width; i++) {
			m_ImageList[0]->BitBlt(canvasDC, i*m_HeaderRect.Width(), 0, m_HeaderRect.Width(), m_HeaderRect.Height(), m_HeaderRect.left, m_HeaderRect.top);
		}
	}

	// 画像の生成
	for (i = 0; i < (int)m_ImageList.size(); i++) {
		switch (m_Priority) {
		case EPriority::EP_HEIGHT:
			m_ImageList[i]->BitBlt(canvasDC, (i / m_Height)*m_TrimRect.Width(), (i%m_Height)*m_TrimRect.Height() + m_HeaderRect.Height(), m_TrimRect.Width(), m_TrimRect.Height(), m_TrimRect.left, m_TrimRect.top);
			break;
		case EPriority::EP_WIDTH:
			m_ImageList[i]->BitBlt(canvasDC, (i % m_Width)*m_TrimRect.Width(), (i / m_Width)*m_TrimRect.Height() + m_HeaderRect.Height(), m_TrimRect.Width(), m_TrimRect.Height(), m_TrimRect.left, m_TrimRect.top);
			break;
		default:
			throw "unknown case set in 画像の生成:m_ImageLayoutDir";
		}
	}
	m_Image.ReleaseDC();

	// プレビュー
	RedrawWindow();
	m_ImageAvailable = true;
}


void CCurrentImage::ClearList()
{
	unsigned int i;
	for (i = 0; i < m_ImageList.size(); i++)
		delete m_ImageList[i];
	m_ImageList.clear();

	if (!m_Image.IsNull()) {
		m_Image.Destroy();
	}
}


void CCurrentImage::DrawErrorMessage(std::vector< CString > * msg)
{
	CRect rect;
	GetWindowRect(&rect);
	HDC hCanvasDC;
	unsigned int i;
	int height;

	// キャンバスの生成
	if (!m_Image.IsNull()) {
		m_Image.Destroy();
	}
	m_Rect.right = rect.Width();
	m_Rect.bottom = rect.Height();
	m_Image.Create(m_Rect.Width(), m_Rect.Height(), 32);
	hCanvasDC = m_Image.GetDC();
	{
		CDC canvasDC;
		canvasDC.Attach(hCanvasDC);
		canvasDC.FillSolidRect(&m_Rect, RGB(212, 208, 200));
		canvasDC.SetBkMode(TRANSPARENT);
		CFont font, *pOldFont;
		font.CreatePointFont(90, "MS UI Gothic");
		pOldFont = canvasDC.SelectObject(&font);
		rect = m_Rect;
		for (i = 0; i < msg->size(); i++) {
			height = canvasDC.DrawText((*msg)[i], &rect, 0);
			rect.top += height;
		}
		canvasDC.SelectObject(pOldFont);
		canvasDC.Detach();
	}
	m_Image.ReleaseDC();
}


void CCurrentImage::OnMouseHover(UINT nFlags, CPoint point)
{
	// TODO: ここにメッセージ ハンドラー コードを追加するか、既定の処理を呼び出します。

	CStatic::OnMouseHover(nFlags, point);
}


void CCurrentImage::OnMouseLeave()
{
	m_StartTrack = false;
	m_SelectWindowRect = CRect(0, 0, 0, 0);

	CStatic::OnMouseLeave();
}


void CCurrentImage::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (m_ImageAvailable) {
		int target = CalcIndexFromPoint(point);
		_RPTN(_CRT_WARN, "index:%d\n", target);
		if (target >= 0 && target < (int)m_ImageList.size()) {
			m_Dragging = true;
			m_DragStartPoint = point;
			m_DragTargetIndex = CalcIndexFromPoint(point);
			m_DragRect = CalcSelectWindowRect(point);
		}
	}

	CStatic::OnLButtonDown(nFlags, point);
}


void CCurrentImage::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (m_Dragging) {
		m_Dragging = false;
		ReleaseCapture();
		m_Captured = false;
		int target = CalcIndexFromPoint(point);
		if (target >= 0 && target < (int)m_ImageList.size()) {
			CImage* tmp = m_ImageList[target];
			m_ImageList[target] = m_ImageList[m_DragTargetIndex];
			m_ImageList[m_DragTargetIndex] = tmp;
			UpdatePreview();
		}
	}

	CStatic::OnLButtonUp(nFlags, point);
}


void CCurrentImage::OnMouseMove(UINT nFlags, CPoint point)
{
	static CRect oldSelectWindowRect;
	m_CurrentMousePoint = point;

	if (m_ImageAvailable) {
		CRect rect = CalcSelectWindowRect(point);
		if (!m_StartTrack) {
			TRACKMOUSEEVENT tk;
			tk.cbSize = sizeof(TRACKMOUSEEVENT);
			tk.dwFlags = TME_HOVER | TME_LEAVE;
			tk.dwHoverTime = HOVER_DEFAULT;
			tk.hwndTrack = this->m_hWnd;
			if (TrackMouseEvent(&tk)) {
				m_StartTrack = true;
			}
		}
		CPoint pt = CalcSelectWindowPoint(point);
		int index = CalcIndexFromPoint(point);
		if (!m_Dragging) {
			m_SelectWindowRect = rect;
		}
		if (pt.x>=0 && pt.x<m_Width && pt.y>=0 && pt.y<m_Height && index<(int)m_ImageList.size()) {
			m_ShowSelectWindow = true;
		}
		else {
			m_ShowSelectWindow = false;
		}

		if (oldSelectWindowRect != m_SelectWindowRect) {
			Invalidate();
			oldSelectWindowRect = m_SelectWindowRect;
		}

		if (m_Dragging) {
			if (!m_Captured) {
				SetCapture();
				m_Captured = true;
			}
			Invalidate();
		}
	}

	CStatic::OnMouseMove(nFlags, point);
}


CRect CCurrentImage::CalcSelectWindowRect(CPoint & point)
{
	ASSERT(m_ImageAvailable);

	int iWidth, iHeight;	// size of each image in actual control
	int oy=m_DestRect.top;	// origin of the image
	double zy = static_cast<double>(m_DestRect.Height()) / m_Rect.Height();
	int hy = static_cast<int>(m_HeaderRect.Height()*zy);

	iWidth = m_DestRect.Width() / m_Width;
	if (m_DrawHeader) {
		iHeight = (m_DestRect.Height() - hy) / m_Height;
		oy += hy;
	}
	else {
		iHeight = m_DestRect.Height() / m_Height;
	}
	CRect ret;
	CPoint pt = CalcSelectWindowPoint(point);
	ret.left = m_DestRect.left + pt.x*iWidth;
	ret.right = m_DestRect.left + (pt.x + 1)*iWidth;
	ret.top = oy + pt.y*iHeight;
	ret.bottom = oy + (pt.y+1)*iHeight;
	return ret;
}

CPoint CCurrentImage::CalcSelectWindowPoint(CPoint & point)
{
	ASSERT(m_ImageAvailable);

	int iWidth, iHeight;	// size of each image in actual control
	int oy = m_DestRect.top;	// origin of the image
	double zy = static_cast<double>(m_DestRect.Height()) / m_Rect.Height();
	int hy = static_cast<int>(m_HeaderRect.Height()*zy);

	iWidth = m_DestRect.Width() / m_Width;
	if (m_DrawHeader) {
		iHeight = (m_DestRect.Height() - hy) / m_Height;
		oy += hy;
	}
	else {
		iHeight = m_DestRect.Height() / m_Height;
	}
	CPoint ret;
	ret.x = (point.x - m_DestRect.left) / iWidth;
	ret.y = (point.y - oy) / iHeight;
	if ((point.x - m_DestRect.left) < 0)
		ret.x--;
	if ((point.y - oy) < 0)
		ret.y--;
	return ret;
}

// returns -1 or value equal or larger than m_ImageList.size()
int CCurrentImage::CalcIndexFromPoint(CPoint& point)
{
	ASSERT(m_ImageAvailable);

	CPoint p = CalcSelectWindowPoint(point);
	switch (m_Priority) {
	case EP_WIDTH:
		if (p.x < 0 || p.x >= m_Width)
			return -1;
		return p.y*m_Width + p.x;
		break;
	case EP_HEIGHT:
		if (p.y < 0 || p.y >= m_Height)
			return -1;
		return p.x*m_Height + p.y;
		break;
	default:
		throw "Invalid m_Priority given in CalcIndexFromPoint";
	}
}



