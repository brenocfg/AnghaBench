#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int UINT ;
struct TYPE_8__ {int /*<<< orphan*/  lfFaceName; void* lfCharSet; void* lfWeight; scalar_t__ lfWidth; scalar_t__ lfHeight; } ;
struct TYPE_7__ {int right; scalar_t__ top; scalar_t__ left; scalar_t__ bottom; } ;
typedef  char TCHAR ;
typedef  TYPE_1__ RECT ;
typedef  int /*<<< orphan*/  LPRECT ;
typedef  TYPE_2__ LOGFONTW ;
typedef  int /*<<< orphan*/  INT ;
typedef  int /*<<< orphan*/  HFONT ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int /*<<< orphan*/  COLORREF ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int BF_MIDDLE ; 
 int BF_RECT ; 
 int /*<<< orphan*/  COLOR_BTNHIGHLIGHT ; 
 int /*<<< orphan*/  COLOR_BTNSHADOW ; 
 int /*<<< orphan*/  COLOR_BTNTEXT ; 
 int /*<<< orphan*/  COLOR_WINDOWFRAME ; 
 int /*<<< orphan*/  CreateFontIndirect (TYPE_2__*) ; 
 void* DEFAULT_CHARSET ; 
 int DFCS_FLAT ; 
 int DFCS_INACTIVE ; 
 int DFCS_MONO ; 
 int DFCS_PUSHED ; 
#define  DFCS_SCROLLCOMBOBOX 134 
#define  DFCS_SCROLLDOWN 133 
#define  DFCS_SCROLLLEFT 132 
#define  DFCS_SCROLLRIGHT 131 
#define  DFCS_SCROLLSIZEGRIP 130 
#define  DFCS_SCROLLSIZEGRIPRIGHT 129 
#define  DFCS_SCROLLUP 128 
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EDGE_RAISED ; 
 int /*<<< orphan*/  EDGE_SUNKEN ; 
 int /*<<< orphan*/  FALSE ; 
 void* FW_NORMAL ; 
 int /*<<< orphan*/  GetBkMode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetSysColor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetTextColor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IntDrawRectEdge (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  OffsetRect (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  SelectObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetBkMode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetTextColor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEXT (char*) ; 
 int /*<<< orphan*/  TRANSPARENT ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  TextOut (int /*<<< orphan*/ ,scalar_t__,scalar_t__,char*,int) ; 
 int /*<<< orphan*/  UITOOLS_MakeSquareRect (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  WARN (char*,int) ; 
 int /*<<< orphan*/  ZeroMemory (TYPE_2__*,int) ; 
 int /*<<< orphan*/  lstrcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOL UITOOLS95_DrawFrameScroll(HDC dc, LPRECT r, UINT uFlags)
{
    LOGFONTW lf;
    HFONT hFont, hOldFont;
    COLORREF clrsave;
    RECT myr;
    INT bkmode;
    TCHAR Symbol;
    switch(uFlags & 0xff)
    {
        case DFCS_SCROLLCOMBOBOX:
        case DFCS_SCROLLDOWN:
		Symbol = '6';
		break;

	case DFCS_SCROLLUP:
		Symbol = '5';
		break;

	case DFCS_SCROLLLEFT:
		Symbol = '3';
		break;

	case DFCS_SCROLLRIGHT:
		Symbol = '4';
		break;

	case DFCS_SCROLLSIZEGRIP:
	case DFCS_SCROLLSIZEGRIPRIGHT:
		ZeroMemory(&lf, sizeof(LOGFONTW));
		UITOOLS_MakeSquareRect(r, &myr);
		lf.lfHeight = myr.bottom - myr.top;
		lf.lfWidth = 0;
		lf.lfWeight = FW_NORMAL;
		lf.lfCharSet = DEFAULT_CHARSET;
		lstrcpy(lf.lfFaceName, TEXT("Marlett"));
		hFont = CreateFontIndirect(&lf);
		/* save font and text color */
		hOldFont = SelectObject(dc, hFont);
		clrsave = GetTextColor(dc);
		bkmode = GetBkMode(dc);
		/* set color and drawing mode */
		SetBkMode(dc, TRANSPARENT);
		if (!(uFlags & (DFCS_MONO | DFCS_FLAT)))
		{
			SetTextColor(dc, GetSysColor(COLOR_BTNHIGHLIGHT));
			/* draw selected symbol */
			Symbol = ((uFlags & 0xff) == DFCS_SCROLLSIZEGRIP) ? 'o' : 'x';
			TextOut(dc, myr.left, myr.top, &Symbol, 1);
			SetTextColor(dc, GetSysColor(COLOR_BTNSHADOW));
		} else
			SetTextColor(dc, GetSysColor(COLOR_WINDOWFRAME));
		/* draw selected symbol */
		Symbol = ((uFlags & 0xff) == DFCS_SCROLLSIZEGRIP) ? 'p' : 'y';
		TextOut(dc, myr.left, myr.top, &Symbol, 1);
		/* restore previous settings */
		SetTextColor(dc, clrsave);
		SelectObject(dc, hOldFont);
		SetBkMode(dc, bkmode);
		DeleteObject(hFont);
            return TRUE;
	default:
	    WARN("Invalid scroll; flags=0x%04x\n", uFlags);
            return FALSE;
    }
    IntDrawRectEdge(dc, r, (uFlags & DFCS_PUSHED) ? EDGE_SUNKEN : EDGE_RAISED, (uFlags&DFCS_FLAT) | BF_MIDDLE | BF_RECT, 1);
    ZeroMemory(&lf, sizeof(LOGFONTW));
    UITOOLS_MakeSquareRect(r, &myr);
    myr.left += 1;
    myr.top += 1;
    myr.right -= 1;
    myr.bottom -= 1;
    if(uFlags & DFCS_PUSHED)
       OffsetRect(&myr,1,1);
    lf.lfHeight = myr.bottom - myr.top;
    lf.lfWidth = 0;
    lf.lfWeight = FW_NORMAL;
    lf.lfCharSet = DEFAULT_CHARSET;
    lstrcpy(lf.lfFaceName, TEXT("Marlett"));
    hFont = CreateFontIndirect(&lf);
    /* save font and text color */
    hOldFont = SelectObject(dc, hFont);
    clrsave = GetTextColor(dc);
    bkmode = GetBkMode(dc);
    /* set color and drawing mode */
    SetBkMode(dc, TRANSPARENT);
    if(uFlags & DFCS_INACTIVE)
    {
        /* draw shadow */
        SetTextColor(dc, GetSysColor(COLOR_BTNHIGHLIGHT));
        TextOut(dc, myr.left + 1, myr.top + 1, &Symbol, 1);
    }
    SetTextColor(dc, GetSysColor((uFlags & DFCS_INACTIVE) ? COLOR_BTNSHADOW : COLOR_BTNTEXT));
    /* draw selected symbol */
    TextOut(dc, myr.left, myr.top, &Symbol, 1);
    /* restore previous settings */
    SetTextColor(dc, clrsave);
    SelectObject(dc, hOldFont);
    SetBkMode(dc, bkmode);
    DeleteObject(hFont);
    return TRUE;
}