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
struct TYPE_3__ {unsigned int range; unsigned int code; } ;
typedef  TYPE_1__ stb_arith ;

/* Variables and functions */

unsigned int stb_arith_decode_value_log2(stb_arith *a, unsigned int totalfreq2)
{
   unsigned int freqsize = a->range >> totalfreq2;
   unsigned int z = a->code / freqsize;
   return z >= (1U<<totalfreq2) ? (1U<<totalfreq2)-1 : z;
}