#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_8__ {scalar_t__ WndHeight; scalar_t__ WndWidth; int /*<<< orphan*/  ForegroundDc; } ;
struct TYPE_7__ {int Red; int Green; int Blue; scalar_t__ Alpha; scalar_t__ y; scalar_t__ x; } ;
typedef  TYPE_1__ TRIVERTEX ;
typedef  TYPE_2__* PPERF_INFO ;
typedef  int /*<<< orphan*/  HDC ;
typedef  TYPE_3__ GRADIENT_RECT ;

/* Variables and functions */
 int /*<<< orphan*/  GRADIENT_FILL_RECT_V ; 
 int /*<<< orphan*/  GradientFill (int /*<<< orphan*/ ,TYPE_1__*,int,TYPE_3__*,int,int /*<<< orphan*/ ) ; 

void
GradientVerticalProc(void *Context, PPERF_INFO PerfInfo, unsigned Reps)
{
  unsigned Rep;
  HDC Dc;
  TRIVERTEX vert[2];
  static GRADIENT_RECT gcap = {0, 1};

  Dc = PerfInfo->ForegroundDc;
  for (Rep = 0; Rep < Reps; Rep++)
    {
      vert[0].x = 0;
      vert[0].y = 0;
      vert[0].Red = 0xff00 * Rep / Reps;
      vert[0].Green = 0xff00 - 0xff00 * Rep / Reps;
      vert[0].Blue = 0xff00;
      vert[0].Alpha = 0;

      vert[1].x = PerfInfo->WndWidth;
      vert[1].y = PerfInfo->WndHeight;
      vert[1].Red = 0xff00 - 0xff00 * Rep / Reps;
      vert[1].Green = 0xff00;
      vert[1].Blue = 0xff00 * Rep / Reps;
      vert[1].Alpha = 0;

      GradientFill(Dc, vert, 2, &gcap, 1, GRADIENT_FILL_RECT_V);
    }
}