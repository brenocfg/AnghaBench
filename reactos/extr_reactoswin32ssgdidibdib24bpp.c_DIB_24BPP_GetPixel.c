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
typedef  scalar_t__ addr ;
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_3__ {int lDelta; scalar_t__ pvScan0; } ;
typedef  TYPE_1__ SURFOBJ ;
typedef  int /*<<< orphan*/ * PUSHORT ;
typedef  int* PBYTE ;
typedef  int LONG ;

/* Variables and functions */

ULONG
DIB_24BPP_GetPixel(SURFOBJ *SurfObj, LONG x, LONG y)
{
  PBYTE addr = (PBYTE)SurfObj->pvScan0 + y * SurfObj->lDelta + (x << 1) + x;
  return *(PUSHORT)(addr) + (*(addr + 2) << 16);
}