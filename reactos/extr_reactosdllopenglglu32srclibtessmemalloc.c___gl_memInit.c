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

/* Variables and functions */

int __gl_memInit( size_t maxFast )
{
#ifndef NO_MALLOPT
/*  mallopt( M_MXFAST, maxFast );*/
#ifdef MEMORY_DEBUG
  mallopt( M_DEBUG, 1 );
#endif
#endif
   return 1;
}