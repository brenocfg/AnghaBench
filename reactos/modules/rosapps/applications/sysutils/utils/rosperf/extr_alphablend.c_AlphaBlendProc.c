#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int SourceConstantAlpha; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_7__ {int /*<<< orphan*/  BitmapDc; } ;
struct TYPE_6__ {int /*<<< orphan*/  WndHeight; int /*<<< orphan*/  WndWidth; int /*<<< orphan*/  BackgroundDc; } ;
typedef  TYPE_1__* PPERF_INFO ;
typedef  TYPE_2__* PALPHABLEND_CONTEXT ;
typedef  TYPE_3__ BLENDFUNCTION ;

/* Variables and functions */
 int /*<<< orphan*/  AC_SRC_OVER ; 
 int /*<<< orphan*/  AlphaBlend (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__) ; 
 int /*<<< orphan*/  DbgPrint (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  PATCOPY ; 
 int /*<<< orphan*/  PatBlt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
AlphaBlendProc(void *Context, PPERF_INFO PerfInfo, unsigned Reps)
{
  PALPHABLEND_CONTEXT ctx = Context;
  unsigned Rep;
  BLENDFUNCTION BlendFunc = { AC_SRC_OVER, 0, 0, 0 };

  for (Rep = 0; Rep < Reps; Rep++)
    {
      BlendFunc.SourceConstantAlpha = 255 * Rep / Reps;
#if 0
      PatBlt(PerfInfo->BackgroundDc, 0, 0, PerfInfo->WndWidth, PerfInfo->WndHeight, PATCOPY);
#endif
      if (!AlphaBlend(PerfInfo->BackgroundDc, 0, 0, PerfInfo->WndWidth, PerfInfo->WndHeight,
                      ctx->BitmapDc, 0, 0, PerfInfo->WndWidth, PerfInfo->WndHeight,
                      BlendFunc))
        {
          DbgPrint("AlphaBlend failed (0x%lx)\n", GetLastError());
        }
    }
}