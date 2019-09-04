#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_29__   TYPE_7__ ;
typedef  struct TYPE_28__   TYPE_6__ ;
typedef  struct TYPE_27__   TYPE_5__ ;
typedef  struct TYPE_26__   TYPE_4__ ;
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;

/* Type definitions */
typedef  size_t UINT ;
struct TYPE_29__ {int /*<<< orphan*/  clr3dFace; } ;
struct TYPE_28__ {size_t bmWidth; size_t bmHeight; } ;
struct TYPE_23__ {scalar_t__ right; scalar_t__ left; size_t top; size_t bottom; } ;
struct TYPE_27__ {size_t itemID; int /*<<< orphan*/  CtlID; int /*<<< orphan*/  itemData; TYPE_1__ rcItem; void* hDC; int /*<<< orphan*/  hwndItem; int /*<<< orphan*/  itemState; int /*<<< orphan*/  itemAction; int /*<<< orphan*/  CtlType; } ;
struct TYPE_26__ {scalar_t__ nNotifyFormat; int iMargin; int /*<<< orphan*/  hwndSelf; int /*<<< orphan*/  himl; scalar_t__ nHeight; int /*<<< orphan*/  hwndNotify; TYPE_3__* items; } ;
struct TYPE_25__ {int fmt; TYPE_1__ rect; scalar_t__ pszText; int /*<<< orphan*/  iImage; scalar_t__ hbm; scalar_t__ bDown; int /*<<< orphan*/  lParam; } ;
struct TYPE_24__ {int dwDrawStage; size_t dwItemSpec; int /*<<< orphan*/  lItemlParam; int /*<<< orphan*/  uItemState; TYPE_1__ rc; void* hdc; } ;
typedef  TYPE_1__ RECT ;
typedef  int /*<<< orphan*/  NMHDR ;
typedef  TYPE_2__ NMCUSTOMDRAW ;
typedef  int LRESULT ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  size_t INT ;
typedef  scalar_t__ HTHEME ;
typedef  scalar_t__ HRGN ;
typedef  TYPE_3__ HEADER_ITEM ;
typedef  TYPE_4__ HEADER_INFO ;
typedef  void* HDC ;
typedef  TYPE_5__ DRAWITEMSTRUCT ;
typedef  scalar_t__ BOOL ;
typedef  TYPE_6__ BITMAP ;

/* Variables and functions */
 int /*<<< orphan*/  BitBlt (void*,size_t,size_t,size_t,size_t,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int CDDS_ITEM ; 
 int CDDS_PREPAINT ; 
 int /*<<< orphan*/  CDIS_SELECTED ; 
 int CDRF_NOTIFYITEMDRAW ; 
 int CDRF_SKIPDEFAULT ; 
 int /*<<< orphan*/  CLR_DEFAULT ; 
 int /*<<< orphan*/  COLOR_BTNTEXT ; 
 int /*<<< orphan*/  COLOR_GRAYTEXT ; 
 int /*<<< orphan*/  COLOR_HIGHLIGHT ; 
 void* CreateCompatibleDC (void*) ; 
 scalar_t__ CreateRectRgn (size_t,size_t,size_t,size_t) ; 
 int DT_CALCRECT ; 
 int DT_END_ELLIPSIS ; 
 int DT_LEFT ; 
 int DT_SINGLELINE ; 
 int DT_VCENTER ; 
 int /*<<< orphan*/  DeleteDC (void*) ; 
 int /*<<< orphan*/  DeleteObject (scalar_t__) ; 
 int /*<<< orphan*/  DrawTextW (void*,scalar_t__,int,TYPE_1__*,int) ; 
 int /*<<< orphan*/  DrawThemeText (scalar_t__,void*,int /*<<< orphan*/ ,int,scalar_t__,int,int,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  FillRgn (void*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GWLP_ID ; 
 void* GetDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetObjectW (scalar_t__,int,TYPE_6__*) ; 
 int /*<<< orphan*/  GetSysColorBrush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetThemeTextExtent (scalar_t__,void*,int /*<<< orphan*/ ,int,scalar_t__,int,int,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  GetWindowLongPtrW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ GetWindowTheme (int /*<<< orphan*/ ) ; 
 int HDF_BITMAP ; 
 int HDF_BITMAP_ON_RIGHT ; 
 int HDF_CENTER ; 
 int HDF_IMAGE ; 
 int HDF_JUSTIFYMASK ; 
 int HDF_LEFT ; 
 int HDF_OWNERDRAW ; 
 int HDF_RIGHT ; 
 int HDF_SORTDOWN ; 
 int HDF_SORTUP ; 
 int HDF_STRING ; 
 int HDI_IMAGE ; 
 int HDI_TEXT ; 
 int /*<<< orphan*/  HEADER_DrawItemFrame (TYPE_4__*,void*,TYPE_1__*,TYPE_3__*) ; 
 int /*<<< orphan*/  HEADER_FillItemFrame (TYPE_4__*,void*,TYPE_1__*,TYPE_3__*,scalar_t__) ; 
 int /*<<< orphan*/  HEADER_FreeCallbackItems (TYPE_3__*) ; 
 int /*<<< orphan*/  HEADER_PrepareCallbackItems (TYPE_4__*,size_t,int) ; 
 int HEADER_SendNotify (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int HIS_HOT ; 
 int HIS_NORMAL ; 
 int HIS_PRESSED ; 
 int /*<<< orphan*/  HP_HEADERITEM ; 
 int /*<<< orphan*/  ImageList_DrawEx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,size_t,size_t,size_t,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ImageList_GetIconSize (int /*<<< orphan*/ ,size_t*,size_t*) ; 
 size_t MulDiv (scalar_t__,int,int) ; 
 scalar_t__ NFR_UNICODE ; 
 int /*<<< orphan*/  NM_CUSTOMDRAW ; 
 int /*<<< orphan*/  ODA_DRAWENTIRE ; 
 int /*<<< orphan*/  ODS_SELECTED ; 
 int /*<<< orphan*/  ODT_HEADER ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  SRCCOPY ; 
 int /*<<< orphan*/  SelectClipRgn (void*,scalar_t__) ; 
 int /*<<< orphan*/  SelectObject (void*,scalar_t__) ; 
 scalar_t__ SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetBkColor (void*,int /*<<< orphan*/ ) ; 
 size_t SetBkMode (void*,size_t) ; 
 int /*<<< orphan*/  SetRectEmpty (TYPE_1__*) ; 
 int /*<<< orphan*/  SetTextColor (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,size_t,scalar_t__,int) ; 
 size_t TRANSPARENT ; 
 scalar_t__ VERT_BORDER ; 
 int /*<<< orphan*/  WM_DRAWITEM ; 
 TYPE_7__ comctl32_color ; 
 scalar_t__ create_sort_arrow (size_t,size_t,size_t,int) ; 

__attribute__((used)) static INT
HEADER_DrawItem (HEADER_INFO *infoPtr, HDC hdc, INT iItem, BOOL bHotTrack, LRESULT lCDFlags)
{
    HEADER_ITEM *phdi = &infoPtr->items[iItem];
    RECT r;
    INT  oldBkMode;
    HTHEME theme = GetWindowTheme (infoPtr->hwndSelf);
    NMCUSTOMDRAW nmcd;
    int state = 0;

    TRACE("DrawItem(iItem %d bHotTrack %d unicode flag %d)\n", iItem, bHotTrack, (infoPtr->nNotifyFormat == NFR_UNICODE));

    r = phdi->rect;
    if (r.right - r.left == 0)
	return phdi->rect.right;

    if (theme)
        state = (phdi->bDown) ? HIS_PRESSED : (bHotTrack ? HIS_HOT : HIS_NORMAL);

    /* Set the colors before sending NM_CUSTOMDRAW so that it can change them */
    SetTextColor(hdc, (bHotTrack && !theme) ? COLOR_HIGHLIGHT : COLOR_BTNTEXT);
    SetBkColor(hdc, comctl32_color.clr3dFace);

    if (lCDFlags & CDRF_NOTIFYITEMDRAW && !(phdi->fmt & HDF_OWNERDRAW))
    {
        LRESULT lCDItemFlags;

        nmcd.dwDrawStage  = CDDS_PREPAINT | CDDS_ITEM;
        nmcd.hdc          = hdc;
        nmcd.dwItemSpec   = iItem;
        nmcd.rc           = r;
        nmcd.uItemState   = phdi->bDown ? CDIS_SELECTED : 0;
        nmcd.lItemlParam  = phdi->lParam;

        lCDItemFlags = HEADER_SendNotify(infoPtr, NM_CUSTOMDRAW, (NMHDR *)&nmcd);
        if (lCDItemFlags & CDRF_SKIPDEFAULT)
            return phdi->rect.right;
    }

    /* Fill background, owner could draw over it. */
    HEADER_FillItemFrame(infoPtr, hdc, &r, phdi, bHotTrack);

    if (phdi->fmt & HDF_OWNERDRAW)
    {
	DRAWITEMSTRUCT dis;
        BOOL ret;

	dis.CtlType    = ODT_HEADER;
	dis.CtlID      = GetWindowLongPtrW (infoPtr->hwndSelf, GWLP_ID);
	dis.itemID     = iItem;
	dis.itemAction = ODA_DRAWENTIRE;
	dis.itemState  = phdi->bDown ? ODS_SELECTED : 0;
	dis.hwndItem   = infoPtr->hwndSelf;
	dis.hDC        = hdc;
	dis.rcItem     = phdi->rect;
	dis.itemData   = phdi->lParam;
        oldBkMode = SetBkMode(hdc, TRANSPARENT);
        ret = SendMessageW (infoPtr->hwndNotify, WM_DRAWITEM, dis.CtlID, (LPARAM)&dis);
        if (oldBkMode != TRANSPARENT)
            SetBkMode(hdc, oldBkMode);

        if (!ret)
            HEADER_FillItemFrame(infoPtr, hdc, &r, phdi, bHotTrack);

        /* Edges are always drawn if we don't have attached theme. */
        HEADER_DrawItemFrame(infoPtr, hdc, &r, phdi);
        /* If application processed WM_DRAWITEM we should skip label painting,
           edges are drawn no matter what. */
        if (ret) return phdi->rect.right;
    }
    else
        HEADER_DrawItemFrame(infoPtr, hdc, &r, phdi);

    if (phdi->bDown) {
        r.left += 2;
        r.top  += 2;
    }

    /* Now text and image */
    {
	INT rw, rh; /* width and height of r */
        INT *x = NULL; /* x and ... */
        UINT *w = NULL; /* ...  width of the pic (bmp or img) which is part of cnt */
	  /* cnt,txt,img,bmp */
        INT  cx, tx, ix, bx;
	UINT cw, tw, iw, bw;
        INT img_cx, img_cy;
        INT sort_w, sort_x, sort_h;
	BITMAP bmp;

        HEADER_PrepareCallbackItems(infoPtr, iItem, HDI_TEXT|HDI_IMAGE);
        cw = iw = bw = sort_w = sort_h = 0;
	rw = r.right - r.left;
	rh = r.bottom - r.top;

	if (phdi->fmt & HDF_STRING) {
	    RECT textRect;

            SetRectEmpty(&textRect);

	    if (theme) {
		GetThemeTextExtent(theme, hdc, HP_HEADERITEM, state, phdi->pszText, -1,
		    DT_LEFT|DT_VCENTER|DT_SINGLELINE, NULL, &textRect);
	    } else {
		DrawTextW (hdc, phdi->pszText, -1,
			&textRect, DT_LEFT|DT_VCENTER|DT_SINGLELINE|DT_CALCRECT);
	    }
	    cw = textRect.right - textRect.left + 2 * infoPtr->iMargin;
	}

        if (phdi->fmt & (HDF_SORTUP | HDF_SORTDOWN)) {
            sort_h = MulDiv( infoPtr->nHeight - VERT_BORDER, 4, 13 );
            sort_w = 2 * sort_h - 1 + infoPtr->iMargin * 2;
            cw += sort_w;
        } else { /* sort arrows take precedent over images/bitmaps */
            if ((phdi->fmt & HDF_IMAGE) && ImageList_GetIconSize( infoPtr->himl, &img_cx, &img_cy )) {
                iw = img_cx + 2 * infoPtr->iMargin;
                x = &ix;
                w = &iw;
            }

            if ((phdi->fmt & HDF_BITMAP) && (phdi->hbm)) {
                GetObjectW (phdi->hbm, sizeof(BITMAP), &bmp);
                bw = bmp.bmWidth + 2 * infoPtr->iMargin;
                if (!iw) {
                    x = &bx;
                    w = &bw;
                }
            }
            if (bw || iw)
                cw += *w;
        }

	/* align cx using the unclipped cw */
	if ((phdi->fmt & HDF_JUSTIFYMASK) == HDF_LEFT)
	    cx = r.left;
	else if ((phdi->fmt & HDF_JUSTIFYMASK) == HDF_CENTER)
	    cx = r.left + rw / 2 - cw / 2;
	else /* HDF_RIGHT */
	    cx = r.right - cw;
        
	/* clip cx & cw */
	if (cx < r.left)
	    cx = r.left;
	if (cx + cw > r.right)
	    cw = r.right - cx;
	
	tx = cx + infoPtr->iMargin;
	/* since cw might have changed we have to recalculate tw */
	tw = cw - infoPtr->iMargin * 2;

        tw -= sort_w;
        sort_x = cx + tw + infoPtr->iMargin * 3;

	if (iw || bw) {
	    tw -= *w;
	    if (phdi->fmt & HDF_BITMAP_ON_RIGHT) {
		/* put pic behind text */
		*x = cx + tw + infoPtr->iMargin * 3;
	    } else {
		*x = cx + infoPtr->iMargin;
		/* move text behind pic */
		tx += *w;
	    }
	}

	if (iw && bw) {
	    /* since we're done with the layout we can
	       now calculate the position of bmp which
	       has no influence on alignment and layout
	       because of img */
	    if ((phdi->fmt & HDF_JUSTIFYMASK) == HDF_RIGHT)
	        bx = cx - bw + infoPtr->iMargin;
	    else
	        bx = cx + cw + infoPtr->iMargin;
	}

	if (sort_w || iw || bw) {
	    HDC hClipDC = GetDC(infoPtr->hwndSelf);
	    HRGN hClipRgn = CreateRectRgn(r.left, r.top, r.right, r.bottom);
	    SelectClipRgn(hClipDC, hClipRgn);
	    
            if (sort_w) {
                HRGN arrow = create_sort_arrow( sort_x, r.top + (rh - sort_h) / 2,
                                                sort_h, phdi->fmt & HDF_SORTUP );
                if (arrow) {
                    FillRgn( hClipDC, arrow, GetSysColorBrush( COLOR_GRAYTEXT ) );
                    DeleteObject( arrow );
                }
            }

	    if (bw) {
	        HDC hdcBitmap = CreateCompatibleDC (hClipDC);
	        SelectObject (hdcBitmap, phdi->hbm);
	        BitBlt (hClipDC, bx, r.top + (rh - bmp.bmHeight) / 2,
		        bmp.bmWidth, bmp.bmHeight, hdcBitmap, 0, 0, SRCCOPY);
	        DeleteDC (hdcBitmap);
	    }

	    if (iw) {
	        ImageList_DrawEx (infoPtr->himl, phdi->iImage, hClipDC, 
	                          ix, r.top + (rh - img_cy) / 2,
	                          img_cx, img_cy, CLR_DEFAULT, CLR_DEFAULT, 0);
	    }

	    DeleteObject(hClipRgn);
	    ReleaseDC(infoPtr->hwndSelf, hClipDC);
	}
        
	if (((phdi->fmt & HDF_STRING)
		|| (!(phdi->fmt & (HDF_OWNERDRAW|HDF_STRING|HDF_BITMAP|
				   HDF_BITMAP_ON_RIGHT|HDF_IMAGE)))) /* no explicit format specified? */
	    && (phdi->pszText)) {
	    oldBkMode = SetBkMode(hdc, TRANSPARENT);
	    r.left  = tx;
	    r.right = tx + tw;
	    if (theme) {
		DrawThemeText(theme, hdc, HP_HEADERITEM, state, phdi->pszText,
			    -1, DT_LEFT|DT_END_ELLIPSIS|DT_VCENTER|DT_SINGLELINE,
			    0, &r);
	    } else {
		DrawTextW (hdc, phdi->pszText, -1,
			&r, DT_LEFT|DT_END_ELLIPSIS|DT_VCENTER|DT_SINGLELINE);
	    }
	    if (oldBkMode != TRANSPARENT)
	        SetBkMode(hdc, oldBkMode);
        }
        HEADER_FreeCallbackItems(phdi);
    }

    return phdi->rect.right;
}