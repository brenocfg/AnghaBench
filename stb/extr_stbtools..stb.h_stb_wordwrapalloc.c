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
 int /*<<< orphan*/  stb_arr_setlen (int*,int) ; 
 int stb_wordwrap (int*,int,int,char*) ; 

int *stb_wordwrapalloc(int count, char *str)
{
   int n = stb_wordwrap(NULL,0,count,str);
   int *z = NULL;
   stb_arr_setlen(z, n*2);
   stb_wordwrap(z, n, count, str);
   return z;
}