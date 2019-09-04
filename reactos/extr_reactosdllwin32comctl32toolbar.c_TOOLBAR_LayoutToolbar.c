#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
struct TYPE_22__ {size_t cx; } ;
struct TYPE_21__ {int fsState; int fsStyle; scalar_t__ iBitmap; size_t cx; size_t nRow; int /*<<< orphan*/  rect; } ;
struct TYPE_19__ {size_t top; size_t left; size_t bottom; size_t right; } ;
struct TYPE_20__ {size_t nIndent; size_t iTopMargin; size_t nButtonWidth; size_t nButtonHeight; size_t nNumButtons; int dwStyle; size_t nRows; TYPE_1__ rcBound; TYPE_3__* buttons; int /*<<< orphan*/  hwndSelf; int /*<<< orphan*/  hFont; } ;
typedef  TYPE_2__ TOOLBAR_INFO ;
typedef  TYPE_3__ TBUTTON_INFO ;
typedef  TYPE_4__ SIZE ;
typedef  size_t INT ;
typedef  int /*<<< orphan*/  HFONT ;
typedef  int /*<<< orphan*/  HDC ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int BTNS_AUTOSIZE ; 
 int BTNS_SEP ; 
 int CCS_VERT ; 
 size_t DDARROW_WIDTH ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  GetDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int SEPARATOR_WIDTH ; 
 int /*<<< orphan*/  SelectObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetRect (int /*<<< orphan*/ *,size_t,size_t,size_t,size_t) ; 
 int /*<<< orphan*/  SetRectEmpty (int /*<<< orphan*/ *) ; 
 int TBSTATE_HIDDEN ; 
 int TBSTATE_WRAP ; 
 int /*<<< orphan*/  TOOLBAR_IsValidBitmapIndex (TYPE_2__*,scalar_t__) ; 
 scalar_t__ TOOLBAR_IsValidImageList (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_4__ TOOLBAR_MeasureButton (TYPE_2__*,TYPE_4__,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  TOOLBAR_MeasureString (TYPE_2__*,TYPE_3__*,int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  TOOLBAR_TooltipSetRect (TYPE_2__*,TYPE_3__*) ; 
 int /*<<< orphan*/  TOOLBAR_WrapToolbar (TYPE_2__*) ; 
 int /*<<< orphan*/  TRACE (char*,size_t,...) ; 
 scalar_t__ TRUE ; 
 scalar_t__ button_has_ddarrow (TYPE_2__*,TYPE_3__*) ; 

__attribute__((used)) static void
TOOLBAR_LayoutToolbar(TOOLBAR_INFO *infoPtr)
{
    TBUTTON_INFO *btnPtr;
    SIZE sizeButton;
    INT i, nRows, nSepRows;
    INT x, y, cx, cy;
    BOOL bWrap;
    BOOL validImageList = TOOLBAR_IsValidImageList(infoPtr, 0);

    TOOLBAR_WrapToolbar(infoPtr);

    x  = infoPtr->nIndent;
    y  = infoPtr->iTopMargin;
    cx = infoPtr->nButtonWidth;
    cy = infoPtr->nButtonHeight;

    nRows = nSepRows = 0;

    infoPtr->rcBound.top = y;
    infoPtr->rcBound.left = x;
    infoPtr->rcBound.bottom = y + cy;
    infoPtr->rcBound.right = x;

    btnPtr = infoPtr->buttons;

    TRACE("cy=%d\n", cy);

    for (i = 0; i < infoPtr->nNumButtons; i++, btnPtr++ )
    {
	bWrap = FALSE;
	if (btnPtr->fsState & TBSTATE_HIDDEN)
	{
	    SetRectEmpty (&btnPtr->rect);
	    TOOLBAR_TooltipSetRect(infoPtr, btnPtr);
	    continue;
	}

	cy = infoPtr->nButtonHeight;

	if (btnPtr->fsStyle & BTNS_SEP) {
	    if (infoPtr->dwStyle & CCS_VERT) {
                cy = (btnPtr->iBitmap > 0) ? btnPtr->iBitmap : SEPARATOR_WIDTH;
                cx = (btnPtr->cx > 0) ? btnPtr->cx : infoPtr->nButtonWidth;
	    }
	    else
                cx = (btnPtr->cx > 0) ? btnPtr->cx :
                    (btnPtr->iBitmap > 0) ? btnPtr->iBitmap : SEPARATOR_WIDTH;
	}
	else
	{
            if (btnPtr->cx)
              cx = btnPtr->cx;
#ifdef __REACTOS__
            /* Revert Wine Commit 5b7b911 as it breaks Explorer Toolbar Buttons
               FIXME: Revisit this when the bug is fixed. CORE-9970 */
            else if ((infoPtr->dwExStyle & TBSTYLE_EX_MIXEDBUTTONS) || 
                (btnPtr->fsStyle & BTNS_AUTOSIZE))
#else
            else if (btnPtr->fsStyle & BTNS_AUTOSIZE)
#endif
            {
              SIZE sz;
	      HDC hdc;
	      HFONT hOldFont;

	      hdc = GetDC (infoPtr->hwndSelf);
	      hOldFont = SelectObject (hdc, infoPtr->hFont);

              TOOLBAR_MeasureString(infoPtr, btnPtr, hdc, &sz);

	      SelectObject (hdc, hOldFont);
	      ReleaseDC (infoPtr->hwndSelf, hdc);

              sizeButton = TOOLBAR_MeasureButton(infoPtr, sz,
                  TOOLBAR_IsValidBitmapIndex(infoPtr, infoPtr->buttons[i].iBitmap),
                  validImageList);
              cx = sizeButton.cx;
            }
            else
	      cx = infoPtr->nButtonWidth;

            /* if size has been set manually then don't add on extra space
             * for the drop down arrow */
            if (!btnPtr->cx && button_has_ddarrow( infoPtr, btnPtr ))
              cx += DDARROW_WIDTH;
	}
	if (btnPtr->fsState & TBSTATE_WRAP)
		    bWrap = TRUE;

	SetRect (&btnPtr->rect, x, y, x + cx, y + cy);

	if (infoPtr->rcBound.left > x)
	    infoPtr->rcBound.left = x;
	if (infoPtr->rcBound.right < x + cx)
	    infoPtr->rcBound.right = x + cx;
	if (infoPtr->rcBound.bottom < y + cy)
	    infoPtr->rcBound.bottom = y + cy;

        TOOLBAR_TooltipSetRect(infoPtr, btnPtr);

	/* btnPtr->nRow is zero based. The space between the rows is 	*/
	/* also considered as a row. 					*/
	btnPtr->nRow = nRows + nSepRows;

	TRACE("button %d style=%x, bWrap=%d, nRows=%d, nSepRows=%d, btnrow=%d, (%d,%d)-(%d,%d)\n",
	      i, btnPtr->fsStyle, bWrap, nRows, nSepRows, btnPtr->nRow,
	      x, y, x+cx, y+cy);

	if( bWrap )
	{
	    if ( !(btnPtr->fsStyle & BTNS_SEP) )
#ifdef __REACTOS__
	        y += cy + infoPtr->szSpacing.cy;
#else
	        y += cy;
#endif
	    else
	    {
               if ( !(infoPtr->dwStyle & CCS_VERT))
                    y += cy + ( (btnPtr->cx > 0 ) ?
                                btnPtr->cx : SEPARATOR_WIDTH) * 2 /3;
		else
#ifdef __REACTOS__
		    y += cy + infoPtr->szSpacing.cy;
#else
		    y += cy;
#endif

		/* nSepRows is used to calculate the extra height following  */
		/* the last row.					     */
		nSepRows++;
	    }
	    x = infoPtr->nIndent;

	    /* Increment row number unless this is the last button    */
	    /* and it has Wrap set.                                   */
	    if (i != infoPtr->nNumButtons-1)
		nRows++;
	}
	else
#ifdef __REACTOS__
	    x += cx + infoPtr->szSpacing.cx;
#else
	    x += cx;
#endif
    }

    /* infoPtr->nRows is the number of rows on the toolbar */
    infoPtr->nRows = nRows + nSepRows + 1;

    TRACE("toolbar button width %d\n", infoPtr->nButtonWidth);
}