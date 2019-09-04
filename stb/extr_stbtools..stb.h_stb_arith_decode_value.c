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

unsigned int stb_arith_decode_value(stb_arith *a, unsigned int totalfreq)
{
   unsigned int freqsize = a->range / totalfreq;
   unsigned int z = a->code / freqsize;
   return z >= totalfreq ? totalfreq-1 : z;
}