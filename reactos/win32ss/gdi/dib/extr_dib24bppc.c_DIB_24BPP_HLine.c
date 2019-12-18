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
typedef  int ULONG_PTR ;
typedef  int ULONG ;
struct TYPE_3__ {int lDelta; scalar_t__ pvScan0; } ;
typedef  TYPE_1__ SURFOBJ ;
typedef  int* PUSHORT ;
typedef  int* PULONG ;
typedef  int* PBYTE ;
typedef  int LONG ;

/* Variables and functions */

VOID
DIB_24BPP_HLine(SURFOBJ *SurfObj, LONG x1, LONG x2, LONG y, ULONG c)
{
  PBYTE addr = (PBYTE)SurfObj->pvScan0 + y * SurfObj->lDelta + (x1 << 1) + x1;
  ULONG Count = x2 - x1;

  if (Count < 8)
  {
    /* For small fills, don't bother doing anything fancy */
    while (Count--)
    {
      *(PUSHORT)(addr) = c;
      addr += 2;
      *(addr) = c >> 16;
      addr += 1;
    }
  }
  else
  {
    ULONG Fill[3];
    ULONG MultiCount;

    /* Align to 4-byte address */
    while (0 != ((ULONG_PTR) addr & 0x3))
    {
      *(PUSHORT)(addr) = c;
      addr += 2;
      *(addr) = c >> 16;
      addr += 1;
      Count--;
    }
    /* If the color we need to fill with is 0ABC, then the final mem pattern
    * (note little-endianness) would be:
    *
    * |C.B.A|C.B.A|C.B.A|C.B.A|   <- pixel borders
    * |C.B.A.C|B.A.C.B|A.C.B.A|   <- ULONG borders
    *
    * So, taking endianness into account again, we need to fill with these
    * ULONGs: CABC BCAB ABCA */

    c = c & 0xffffff;                /* 0ABC */
    Fill[0] = c | (c << 24);         /* CABC */
    Fill[1] = (c >> 8) | (c << 16);  /* BCAB */
    Fill[2] = (c << 8) | (c >> 16);  /* ABCA */
    MultiCount = Count / 4;
    do
    {
      *(PULONG)addr = Fill[0];
      addr += 4;
      *(PULONG)addr = Fill[1];
      addr += 4;
      *(PULONG)addr = Fill[2];
      addr += 4;
    }
    while (0 != --MultiCount);

    Count = Count & 0x03;
    while (0 != Count--)
    {
      *(PUSHORT)(addr) = c;
      addr += 2;
      *(addr) = c >> 16;
      addr += 1;
    }
  }
}