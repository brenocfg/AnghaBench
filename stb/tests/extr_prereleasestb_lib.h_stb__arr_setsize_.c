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
 int /*<<< orphan*/  stb__arrsize_ (void**,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stb_arr_check2 (void*) ; 
 int /*<<< orphan*/  stb_arr_len2 (void*) ; 

void stb__arr_setsize_(void **pp, int size, int limit)
{
   void *p = *pp;
   stb_arr_check2(p);
   stb__arrsize_(pp, size, limit, stb_arr_len2(p));
}