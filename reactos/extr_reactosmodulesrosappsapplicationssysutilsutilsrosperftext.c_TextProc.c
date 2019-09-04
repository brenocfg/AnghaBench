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
struct TYPE_3__ {int WndHeight; int /*<<< orphan*/  Wnd; int /*<<< orphan*/ * ForegroundDc; int /*<<< orphan*/ * BackgroundDc; } ;
typedef  TYPE_1__* PPERF_INFO ;
typedef  int /*<<< orphan*/  HFONT ;
typedef  int /*<<< orphan*/ * HDC ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_GUI_FONT ; 
 int /*<<< orphan*/  GetStockObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InvalidateRect (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SelectObject (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  TextOut (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char*,int) ; 
 int /*<<< orphan*/  UpdateWindow (int /*<<< orphan*/ ) ; 

void
TextProc(void *Context, PPERF_INFO PerfInfo, unsigned Reps)
{
  unsigned Rep;
  int y;
  HDC Dc = NULL;
  HFONT hfFont = GetStockObject(DEFAULT_GUI_FONT);

  for (Rep = 0; Rep < Reps; )
    {
      Dc = (Rep & 0x10000) ? PerfInfo->BackgroundDc : PerfInfo->ForegroundDc;
      SelectObject(Dc, hfFont);

      for (y = 0; y < PerfInfo->WndHeight && Rep < Reps; Rep++, y += 15)
        {
		TextOut(Dc, 0, y, L"AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz:?<>0123456789", 66);
        }
    InvalidateRect(PerfInfo->Wnd, NULL, TRUE);
    UpdateWindow(PerfInfo->Wnd);
    }
}