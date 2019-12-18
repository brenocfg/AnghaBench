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
 int stb__compare (void*,void*) ; 

__attribute__((used)) static int stb__dupe_compare(const void *a, const void *b)
{
   void *p = *(void **) a;
   void *q = *(void **) b;

   return stb__compare(p,q);
}