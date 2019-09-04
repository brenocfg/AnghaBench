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

void gl_init_eval( void )
{
  static int init_flag = 0;

  /* Compute a table of nCr (combination) values used by the
   * Bernstein polynomial generator.
   */

  if (init_flag==0) 
  { /* no initialization needed */ 
  }

  init_flag = 1;
}