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
typedef  int /*<<< orphan*/  cbi ;
typedef  int ULONG ;
struct TYPE_3__ {int cbSize; scalar_t__ stateButton; int /*<<< orphan*/  rcButton; int /*<<< orphan*/  rcItem; } ;
typedef  int /*<<< orphan*/  RECT ;
typedef  int /*<<< orphan*/  PAINTSTRUCT ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  HTHEME ;
typedef  scalar_t__ HDC ;
typedef  int DWORD ;
typedef  TYPE_1__ COMBOBOXINFO ;

/* Variables and functions */
 scalar_t__ BeginPaint (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int CBS_DROPDOWNLIST ; 
 int CBS_SIMPLE ; 
 int CBXS_DISABLED ; 
 int CBXS_HOT ; 
 int CBXS_NORMAL ; 
 int CBXS_PRESSED ; 
 int /*<<< orphan*/  CB_GETCOMBOBOXINFO ; 
 scalar_t__ COMBO_XBORDERSIZE ; 
 scalar_t__ COMBO_YBORDERSIZE ; 
 int /*<<< orphan*/  CP_DROPDOWNBUTTON ; 
 int /*<<< orphan*/  DrawThemeBackground (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ EDIT_CONTROL_PADDING ; 
 int /*<<< orphan*/  EndPaint (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GWL_STYLE ; 
 int /*<<< orphan*/  GetClientRect (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int GetWindowLongW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InflateRect (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 scalar_t__ IsWindowEnabled (int /*<<< orphan*/ ) ; 
 int STATE_HOT ; 
 int STATE_NOREDRAW ; 
 scalar_t__ STATE_SYSTEM_INVISIBLE ; 
 scalar_t__ STATE_SYSTEM_PRESSED ; 
 int /*<<< orphan*/  SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,scalar_t__) ; 
 int /*<<< orphan*/  paint_text (int /*<<< orphan*/ ,scalar_t__,int,TYPE_1__*) ; 

__attribute__((used)) static LRESULT paint (HTHEME theme, HWND hwnd, HDC hParamDC, ULONG state)
{
  PAINTSTRUCT ps;
  HDC   hDC;
  COMBOBOXINFO cbi;
  DWORD dwStyle = GetWindowLongW (hwnd, GWL_STYLE);

  hDC = (hParamDC) ? hParamDC
                   : BeginPaint( hwnd, &ps);

  TRACE("hdc=%p\n", hDC);

  if( hDC && !(state & STATE_NOREDRAW) )
  {
      RECT frameRect;
      int buttonState;
  
      cbi.cbSize = sizeof (cbi);
      SendMessageW (hwnd, CB_GETCOMBOBOXINFO, 0, (LPARAM)&cbi);
      
      /* paint border */
      if ((dwStyle & CBS_DROPDOWNLIST) != CBS_SIMPLE)
          GetClientRect (hwnd, &frameRect);
      else
      {
          frameRect = cbi.rcItem;
          InflateRect(&frameRect, 
              EDIT_CONTROL_PADDING + COMBO_XBORDERSIZE, 
              EDIT_CONTROL_PADDING + COMBO_YBORDERSIZE);
      }
      
      DrawThemeBackground (theme, hDC, 0, 
          IsWindowEnabled (hwnd) ? CBXS_NORMAL : CBXS_DISABLED, &frameRect, NULL);
      
      /* paint button */
      if (cbi.stateButton != STATE_SYSTEM_INVISIBLE)
      {
          if (!IsWindowEnabled (hwnd))
              buttonState = CBXS_DISABLED;
          else if (cbi.stateButton == STATE_SYSTEM_PRESSED)
              buttonState = CBXS_PRESSED;
          else if (state & STATE_HOT)
              buttonState = CBXS_HOT;
          else
              buttonState = CBXS_NORMAL;
          DrawThemeBackground (theme, hDC, CP_DROPDOWNBUTTON, buttonState, 
              &cbi.rcButton, NULL);
      }

      /* paint text, if we need to */
      if ((dwStyle & CBS_DROPDOWNLIST) == CBS_DROPDOWNLIST)
          paint_text (hwnd, hDC, dwStyle, &cbi);
  }

  if( !hParamDC )
    EndPaint(hwnd, &ps);

  return 0;
}