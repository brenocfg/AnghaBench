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
 int /*<<< orphan*/  free (void*) ; 

void stb_pointer_array_free(void *q, int len)
{
   void **p = (void **) q;
   int i;
   for (i=0; i < len; ++i)
      free(p[i]);
}