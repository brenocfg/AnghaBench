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
typedef  int /*<<< orphan*/  stbfile ;
struct TYPE_3__ {int range_high; int pending_ffs; int /*<<< orphan*/ * output; scalar_t__ range_low; } ;
typedef  TYPE_1__ stb_arith ;

/* Variables and functions */

void stb_arith_init_encode(stb_arith *a, stbfile *out)
{
   a->range_low = 0;
   a->range_high = 0xffffffff;
   a->pending_ffs = -1; // means no buffered character currently, to speed up normal case
   a->output = out;
}