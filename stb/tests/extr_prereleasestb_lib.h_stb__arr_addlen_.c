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
 int /*<<< orphan*/  stb__arr_setlen_ (void**,int,scalar_t__) ; 
 scalar_t__ stb_arr_len2 (void*) ; 

void stb__arr_addlen_(void **p, int size, int addlen)
{
   stb__arr_setlen_(p, size, stb_arr_len2(*p) + addlen);
}