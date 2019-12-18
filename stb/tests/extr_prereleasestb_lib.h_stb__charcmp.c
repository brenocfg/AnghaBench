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
 int stb__ucharcmpoffset ; 

int stb__charcmp(const void *a, const void *b)
{
   const int p = *(const char *) ((const char *) a + stb__ucharcmpoffset);
   const int q = *(const char *) ((const char *) b + stb__ucharcmpoffset);
   return p < q ? -1 : p > q;
}