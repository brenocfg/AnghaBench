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
typedef  int /*<<< orphan*/  VOID ;
typedef  int ULONG ;
struct TYPE_3__ {int lDelta; scalar_t__ pvScan0; } ;
typedef  TYPE_1__ SURFOBJ ;
typedef  int* PUSHORT ;
typedef  scalar_t__* PBYTE ;
typedef  int LONG ;
typedef  scalar_t__ BYTE ;

/* Variables and functions */

VOID
DIB_24BPP_VLine(SURFOBJ *SurfObj, LONG x, LONG y1, LONG y2, ULONG c)
{
  PBYTE addr = (PBYTE)SurfObj->pvScan0 + y1 * SurfObj->lDelta + (x << 1) + x;
  LONG lDelta = SurfObj->lDelta;

  c &= 0xFFFFFF;
  while(y1++ < y2)
  {
    *(PUSHORT)(addr) = c & 0xFFFF;
    *(addr + 2) = (BYTE)(c >> 16);

    addr += lDelta;
  }
}