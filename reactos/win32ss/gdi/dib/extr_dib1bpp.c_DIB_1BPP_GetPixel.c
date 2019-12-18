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
typedef  int ULONG ;
struct TYPE_3__ {int lDelta; scalar_t__ pvScan0; } ;
typedef  TYPE_1__ SURFOBJ ;
typedef  int* PBYTE ;
typedef  int LONG ;

/* Variables and functions */
 int MASK1BPP (int) ; 

ULONG
DIB_1BPP_GetPixel(SURFOBJ *SurfObj, LONG x, LONG y)
{
  PBYTE addr = (PBYTE)SurfObj->pvScan0 + y * SurfObj->lDelta + (x >> 3);

  return (*addr & MASK1BPP(x) ? 1 : 0);
}