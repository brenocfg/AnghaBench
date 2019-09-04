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
 int /*<<< orphan*/  stb_p_strncpy_s (char*,int,char*,int) ; 

char *stb_strncpy(char *s, char *t, int n)
{
   stb_p_strncpy_s(s,n+1,t,n);
   s[n-1] = 0;
   return s;
}