#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int len; } ;

/* Variables and functions */
 int /*<<< orphan*/  memmove (char*,char*,int) ; 
 int stb_arr_len2 (void*) ; 
 TYPE_1__* stb_arrhead2 (void*) ; 

void stb__arr_deleten_(void **pp, int size, int i, int n)
{
   void *p = *pp;
   if (n) {
      memmove((char *) p + i*size, (char *) p + (i+n)*size, size * (stb_arr_len2(p)-(i+n)));
      stb_arrhead2(p)->len -= n;
   }
   *pp = p;
}