#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_2__ {int /*<<< orphan*/  hbrGray; } ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int /*<<< orphan*/  HBRUSH ;
typedef  scalar_t__ COLORREF ;

/* Variables and functions */
 int /*<<< orphan*/  COLOR_3DFACE ; 
 int /*<<< orphan*/  COLOR_3DHILIGHT ; 
 int /*<<< orphan*/  COLOR_SCROLLBAR ; 
 int /*<<< orphan*/  COLOR_WINDOW ; 
 int /*<<< orphan*/  COLOR_WINDOWTEXT ; 
 scalar_t__ CTLCOLOR_EDIT ; 
 scalar_t__ CTLCOLOR_LISTBOX ; 
 scalar_t__ CTLCOLOR_SCROLLBAR ; 
 scalar_t__ GetSysColor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetSysColorBrush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetBkColor (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  SetTextColor (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  UnrealizeObject (int /*<<< orphan*/ ) ; 
 TYPE_1__* gpsi ; 

HBRUSH
DefWndControlColor(HDC hDC, UINT ctlType)
{
  if (ctlType == CTLCOLOR_SCROLLBAR)
  {
      HBRUSH hb = GetSysColorBrush(COLOR_SCROLLBAR);
      COLORREF bk = GetSysColor(COLOR_3DHILIGHT);
      SetTextColor(hDC, GetSysColor(COLOR_3DFACE));
      SetBkColor(hDC, bk);

      /* if COLOR_WINDOW happens to be the same as COLOR_3DHILIGHT
       * we better use 0x55aa bitmap brush to make scrollbar's background
       * look different from the window background.
       */
      if ( bk == GetSysColor(COLOR_WINDOW))
          return gpsi->hbrGray;

      UnrealizeObject( hb );
      return hb;
  }

  SetTextColor(hDC, GetSysColor(COLOR_WINDOWTEXT));

  if ((ctlType == CTLCOLOR_EDIT) || (ctlType == CTLCOLOR_LISTBOX))
  {
      SetBkColor(hDC, GetSysColor(COLOR_WINDOW));
  }
  else
  {
      SetBkColor(hDC, GetSysColor(COLOR_3DFACE));
      return GetSysColorBrush(COLOR_3DFACE);
  }

  return GetSysColorBrush(COLOR_WINDOW);
}