#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int UINT ;
struct TYPE_7__ {int /*<<< orphan*/  lfFaceName; int /*<<< orphan*/  lfCharSet; int /*<<< orphan*/  lfWeight; scalar_t__ lfWidth; int /*<<< orphan*/  lfHeight; } ;
struct TYPE_6__ {scalar_t__ top; scalar_t__ left; } ;
typedef  char TCHAR ;
typedef  TYPE_1__ RECT ;
typedef  int /*<<< orphan*/  LPRECT ;
typedef  TYPE_2__ LOGFONTW ;
typedef  int /*<<< orphan*/  INT ;
typedef  int /*<<< orphan*/  HFONT ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  COLOR_BTNHIGHLIGHT ; 
 int /*<<< orphan*/  COLOR_BTNSHADOW ; 
 int /*<<< orphan*/  COLOR_BTNTEXT ; 
 int /*<<< orphan*/  CreateFontIndirect (TYPE_2__*) ; 
 int /*<<< orphan*/  DEFAULT_CHARSET ; 
 int DFCS_INACTIVE ; 
#define  DFCS_MENUARROW 133 
#define  DFCS_MENUARROWDOWN 132 
#define  DFCS_MENUARROWRIGHT 131 
#define  DFCS_MENUARROWUP 130 
#define  DFCS_MENUBULLET 129 
#define  DFCS_MENUCHECK 128 
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FW_NORMAL ; 
 int /*<<< orphan*/  GetSysColor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SelectObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetTextColor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEXT (char*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  TextOut (int /*<<< orphan*/ ,scalar_t__,scalar_t__,char*,int) ; 
 int /*<<< orphan*/  UITOOLS_MakeSquareRect (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  WARN (char*,int) ; 
 int /*<<< orphan*/  ZeroMemory (TYPE_2__*,int) ; 
 int /*<<< orphan*/  lstrcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOL UITOOLS95_DrawFrameMenu(HDC dc, LPRECT r, UINT uFlags)
{
    // TODO: DFCS_TRANSPARENT upon DFCS_MENUARROWUP or DFCS_MENUARROWDOWN
    LOGFONTW lf;
    HFONT hFont, hOldFont;
    TCHAR Symbol;
    RECT myr;
    INT cxy;
    cxy = UITOOLS_MakeSquareRect(r, &myr);
    switch(uFlags & 0xff)
    {
        case DFCS_MENUARROWUP:
            Symbol = '5';
            break;

        case DFCS_MENUARROWDOWN:
            Symbol = '6';
            break;

        case DFCS_MENUARROW:
            Symbol = '8';
            break;

        case DFCS_MENUARROWRIGHT:
	    Symbol = 'w'; // FIXME: needs to confirm
	    break;

        case DFCS_MENUBULLET:
            Symbol = 'h';
            break;

        case DFCS_MENUCHECK:
            Symbol = 'a';
            break;

        default:
            WARN("Invalid menu; flags=0x%04x\n", uFlags);
            return FALSE;
    }
    /* acquire ressources only if valid menu */
    ZeroMemory(&lf, sizeof(LOGFONTW));
    lf.lfHeight = cxy;
    lf.lfWidth = 0;
    lf.lfWeight = FW_NORMAL;
    lf.lfCharSet = DEFAULT_CHARSET;
    lstrcpy(lf.lfFaceName, TEXT("Marlett"));
    hFont = CreateFontIndirect(&lf);
    /* save font */
    hOldFont = SelectObject(dc, hFont);

    if ((uFlags & 0xff) == DFCS_MENUARROWUP ||  
        (uFlags & 0xff) == DFCS_MENUARROWDOWN ) 
    {
#if 0
       if (uFlags & DFCS_INACTIVE)
       {
           /* draw shadow */
           SetTextColor(dc, GetSysColor(COLOR_BTNHIGHLIGHT));
           TextOut(dc, myr.left + 1, myr.top + 1, &Symbol, 1);
       }
#endif
       SetTextColor(dc, GetSysColor((uFlags & DFCS_INACTIVE) ? COLOR_BTNSHADOW : COLOR_BTNTEXT));
    }
    /* draw selected symbol */
    TextOut(dc, myr.left, myr.top, &Symbol, 1);
    /* restore previous settings */
    SelectObject(dc, hOldFont);
    DeleteObject(hFont);
    return TRUE;
}