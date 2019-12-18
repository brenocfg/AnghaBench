#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  logBrush ;
typedef  int /*<<< orphan*/  buffer ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_3__ {int /*<<< orphan*/  lbColor; } ;
typedef  int /*<<< orphan*/  RECT ;
typedef  int /*<<< orphan*/  LPPOINT ;
typedef  TYPE_1__ LOGBRUSH ;
typedef  int INT ;
typedef  int /*<<< orphan*/  HWND ;
typedef  scalar_t__ HFONT ;
typedef  int /*<<< orphan*/  HDC ;
typedef  scalar_t__ HBRUSH ;
typedef  int /*<<< orphan*/  COLORREF ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  BLACK_BRUSH ; 
 int /*<<< orphan*/  COLOR_ACTIVECAPTION ; 
 int /*<<< orphan*/  COLOR_CAPTIONTEXT ; 
 int /*<<< orphan*/  DPtoLP (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int DT_CENTER ; 
 int DT_NOPREFIX ; 
 int DT_SINGLELINE ; 
 int DT_WORDBREAK ; 
 int /*<<< orphan*/  DrawTextW (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  FillRect (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  GCLP_HBRBACKGROUND ; 
 int /*<<< orphan*/  GWL_STYLE ; 
 int GetBValue (int /*<<< orphan*/ ) ; 
 scalar_t__ GetClassLongPtrW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetClientRect (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int GetGValue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetObjectA (scalar_t__,int,TYPE_1__*) ; 
 int GetRValue (int /*<<< orphan*/ ) ; 
 scalar_t__ GetStockObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetSysColor (int /*<<< orphan*/ ) ; 
 scalar_t__ GetSysColorBrush (int /*<<< orphan*/ ) ; 
 int GetWindowLongPtrA (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int GetWindowTextW (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  RGB (int,int,int) ; 
 scalar_t__ SelectObject (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  SetBkMode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetTextColor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRANSPARENT ; 
 int /*<<< orphan*/  WHITE_BRUSH ; 
 int WS_CHILD ; 
 scalar_t__ bMultiLineTitle ; 
 scalar_t__ hIconTitleFont ; 

__attribute__((used)) static BOOL ICONTITLE_Paint( HWND hwnd, HWND owner, HDC hDC, BOOL bActive )
{
    RECT rect;
    HFONT hPrevFont;
    HBRUSH hBrush;
    COLORREF textColor = 0;

    if( bActive )
    {
	hBrush = GetSysColorBrush(COLOR_ACTIVECAPTION);
	textColor = GetSysColor(COLOR_CAPTIONTEXT);
    }
    else
    {
        if( GetWindowLongPtrA( hwnd, GWL_STYLE ) & WS_CHILD )
	{
	    hBrush = (HBRUSH) GetClassLongPtrW(hwnd, GCLP_HBRBACKGROUND);
	    if( hBrush )
	    {
		INT level;
		LOGBRUSH logBrush;
		GetObjectA( hBrush, sizeof(logBrush), &logBrush );
		level = GetRValue(logBrush.lbColor) +
			   GetGValue(logBrush.lbColor) +
			      GetBValue(logBrush.lbColor);
		if( level < (0x7F * 3) )
		    textColor = RGB( 0xFF, 0xFF, 0xFF );
	    }
	    else
		hBrush = GetStockObject( WHITE_BRUSH );
	}
	else
	{
	    hBrush = GetStockObject( BLACK_BRUSH );
	    textColor = RGB( 0xFF, 0xFF, 0xFF );
	}
    }

    GetClientRect( hwnd, &rect );
    DPtoLP( hDC, (LPPOINT)&rect, 2 );
    FillRect( hDC, &rect, hBrush );

    hPrevFont = SelectObject( hDC, hIconTitleFont );
    if( hPrevFont )
    {
	WCHAR buffer[80];

        INT length = GetWindowTextW( owner, buffer, sizeof(buffer)/sizeof(buffer[0]) );
        SetTextColor( hDC, textColor );
        SetBkMode( hDC, TRANSPARENT );

        DrawTextW( hDC, buffer, length, &rect, DT_CENTER | DT_NOPREFIX |
                   DT_WORDBREAK | ((bMultiLineTitle) ? 0 : DT_SINGLELINE) );

	SelectObject( hDC, hPrevFont );
    }
    return (hPrevFont != 0);
}