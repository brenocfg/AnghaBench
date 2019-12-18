#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int wState; int /*<<< orphan*/  self; int /*<<< orphan*/  textRect; int /*<<< orphan*/  buttonRect; } ;
typedef  int /*<<< orphan*/  RECT ;
typedef  int /*<<< orphan*/  PAINTSTRUCT ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  TYPE_1__* LPHEADCOMBO ;
typedef  scalar_t__ HDC ;
typedef  scalar_t__ HBRUSH ;

/* Variables and functions */
 scalar_t__ BeginPaint (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int CBF_EDIT ; 
 int CBF_NOREDRAW ; 
 int /*<<< orphan*/  CBPaintBorder (int /*<<< orphan*/ ,TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  CBPaintButton (TYPE_1__*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CBPaintText (TYPE_1__*,scalar_t__) ; 
 scalar_t__ CBS_DROPDOWNLIST ; 
 scalar_t__ CB_GETTYPE (TYPE_1__*) ; 
 int /*<<< orphan*/  COLOR_WINDOW ; 
 scalar_t__ COMBO_PrepareColors (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  EDIT_CONTROL_PADDING () ; 
 int /*<<< orphan*/  EndPaint (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FillRect (scalar_t__,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  FrameRect (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetSysColorBrush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InflateRect (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IsRectEmpty (int /*<<< orphan*/ *) ; 
 scalar_t__ SelectObject (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  TRACE (char*,scalar_t__) ; 

__attribute__((used)) static LRESULT COMBO_Paint(LPHEADCOMBO lphc, HDC hParamDC)
{
  PAINTSTRUCT ps;
  HDC 	hDC;

  hDC = (hParamDC) ? hParamDC
		   : BeginPaint( lphc->self, &ps);

  TRACE("hdc=%p\n", hDC);

  if( hDC && !(lphc->wState & CBF_NOREDRAW) )
  {
      HBRUSH	hPrevBrush, hBkgBrush;

      /*
       * Retrieve the background brush and select it in the
       * DC.
       */
      hBkgBrush = COMBO_PrepareColors(lphc, hDC);

      hPrevBrush = SelectObject( hDC, hBkgBrush );
      if (!(lphc->wState & CBF_EDIT))
        FillRect(hDC, &lphc->textRect, hBkgBrush);

      /*
       * In non 3.1 look, there is a sunken border on the combobox
       */
      CBPaintBorder(lphc->self, lphc, hDC);

      if( !IsRectEmpty(&lphc->buttonRect) )
      {
	CBPaintButton(lphc, hDC, lphc->buttonRect);
      }

      /* paint the edit control padding area */
      if (CB_GETTYPE(lphc) != CBS_DROPDOWNLIST)
      {
          RECT rPadEdit = lphc->textRect;

          InflateRect(&rPadEdit, EDIT_CONTROL_PADDING(), EDIT_CONTROL_PADDING());

          FrameRect( hDC, &rPadEdit, GetSysColorBrush(COLOR_WINDOW) );
      }

      if( !(lphc->wState & CBF_EDIT) )
	CBPaintText( lphc, hDC );

      if( hPrevBrush )
	SelectObject( hDC, hPrevBrush );
  }

  if( !hParamDC )
    EndPaint(lphc->self, &ps);

  return 0;
}