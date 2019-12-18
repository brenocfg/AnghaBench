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
DIB_4BPP_PutPixel(SURFOBJ *SurfObj, LONG x, LONG y, ULONG c)
{
   PBYTE addr = (PBYTE)SurfObj->pvScan0 + (x>>1) + y * SurfObj->lDelta;
   *addr = (*addr & notmask[x&1]) | (BYTE)(c << ((1-(x&1))<<2));
}