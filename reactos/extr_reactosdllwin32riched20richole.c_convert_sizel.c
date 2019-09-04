#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  cy; int /*<<< orphan*/  cx; } ;
struct TYPE_11__ {TYPE_1__ dpi; } ;
struct TYPE_10__ {void* cy; void* cx; } ;
struct TYPE_9__ {int /*<<< orphan*/  cy; int /*<<< orphan*/  cx; } ;
typedef  TYPE_2__ SIZEL ;
typedef  TYPE_3__ SIZE ;
typedef  TYPE_4__ ME_Context ;

/* Variables and functions */
 void* MulDiv (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void convert_sizel(const ME_Context *c, const SIZEL* szl, SIZE* sz)
{
  /* sizel is in .01 millimeters, sz in pixels */
  sz->cx = MulDiv(szl->cx, c->dpi.cx, 2540);
  sz->cy = MulDiv(szl->cy, c->dpi.cy, 2540);
}