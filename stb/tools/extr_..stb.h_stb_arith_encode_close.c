#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  stbfile ;
struct TYPE_5__ {int range_low; int /*<<< orphan*/ * output; } ;
typedef  TYPE_1__ stb_arith ;

/* Variables and functions */
 int /*<<< orphan*/  stb__arith_flush (TYPE_1__*) ; 
 int /*<<< orphan*/  stb__arith_putbyte (TYPE_1__*,int) ; 

stbfile *stb_arith_encode_close(stb_arith *a)
{
   // put exactly as many bytes as we'll read, so we can turn on/off arithmetic coding in a stream
   stb__arith_putbyte(a, a->range_low >> 24);
   stb__arith_putbyte(a, a->range_low >> 16);
   stb__arith_putbyte(a, a->range_low >>  8);
   stb__arith_putbyte(a, a->range_low >>  0);
   stb__arith_flush(a);
   return a->output;
}