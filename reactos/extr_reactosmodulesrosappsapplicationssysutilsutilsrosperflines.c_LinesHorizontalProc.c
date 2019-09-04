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
struct TYPE_3__ {int WndHeight; int /*<<< orphan*/  WndWidth; int /*<<< orphan*/  ForegroundDc; int /*<<< orphan*/  BackgroundDc; } ;
typedef  TYPE_1__* PPERF_INFO ;
typedef  int /*<<< orphan*/  HDC ;

/* Variables and functions */
 int /*<<< orphan*/  LineTo (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MoveToEx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

void
LinesHorizontalProc(void *Context, PPERF_INFO PerfInfo, unsigned Reps)
{
  unsigned Rep;
  int y;
  HDC Dc;

  for (Rep = 0; Rep < Reps; )
    {
      Dc = (Rep & 0x10000) ? PerfInfo->BackgroundDc : PerfInfo->ForegroundDc;

      for (y = 0; y < PerfInfo->WndHeight && Rep < Reps; Rep++, y += 3)
        {
          MoveToEx(Dc, 0, y, NULL);
          LineTo(Dc, PerfInfo->WndWidth, y);
        }
    }
}