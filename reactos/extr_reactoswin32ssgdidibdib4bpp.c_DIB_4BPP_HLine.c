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
typedef  int* PBYTE ;
typedef  int LONG ;
typedef  int BYTE ;

/* Variables and functions */
 int* notmask ; 

VOID
DIB_4BPP_HLine(SURFOBJ *SurfObj, LONG x1, LONG x2, LONG y, ULONG c)
{
  PBYTE  addr = (PBYTE)SurfObj->pvScan0 + (x1>>1) + y * SurfObj->lDelta;
  LONG  cx = x1;

  while(cx < x2)
  {
    *addr = (*addr & notmask[x1&1]) | (BYTE)(c << ((1-(x1&1))<<2));
    if((++x1 & 1) == 0)
      ++addr;
    ++cx;
  }
}