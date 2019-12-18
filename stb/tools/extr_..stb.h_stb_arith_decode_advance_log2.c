#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned int range; unsigned int code; } ;
typedef  TYPE_1__ stb_arith ;

/* Variables and functions */
 int /*<<< orphan*/  stb__renorm_decoder (TYPE_1__*) ; 

void stb_arith_decode_advance_log2(stb_arith *a, unsigned int totalfreq2, unsigned int freq, unsigned int cumfreq)
{
   unsigned int freqsize = a->range >> totalfreq2;
   a->code -= freqsize * cumfreq;
   a->range = freqsize * freq;
   while (a->range < 0x1000000)
      stb__renorm_decoder(a);
}