#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
typedef  int /*<<< orphan*/  ULONG ;
typedef  int /*<<< orphan*/  SURFOBJ ;
typedef  scalar_t__ LONG ;

/* Variables and functions */
 int /*<<< orphan*/  DIB_1BPP_PutPixel (int /*<<< orphan*/ *,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 

VOID
DIB_1BPP_HLine(SURFOBJ *SurfObj, LONG x1, LONG x2, LONG y, ULONG c)
{
  while(x1 < x2)
  {
    DIB_1BPP_PutPixel(SurfObj, x1, y, c);
    x1++;
  }
}