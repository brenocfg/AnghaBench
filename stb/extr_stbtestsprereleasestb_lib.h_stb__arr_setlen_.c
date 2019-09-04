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
 int /*<<< orphan*/  stb__arrsize_ (void**,int,int,int) ; 
 int /*<<< orphan*/  stb_arr_check2 (void*) ; 
 int stb_arrcurmax2 (void*) ; 
 TYPE_1__* stb_arrhead2 (void*) ; 

void stb__arr_setlen_(void **pp, int size, int newlen)
{
   void *p = *pp;
   stb_arr_check2(p);
   if (stb_arrcurmax2(p) < newlen || p == NULL) {
      stb__arrsize_(pp, size, newlen, newlen);
   } else {
      stb_arrhead2(p)->len = newlen;
   }
}