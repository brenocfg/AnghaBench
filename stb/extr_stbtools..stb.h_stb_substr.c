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
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  stb_p_strncpy_s (char*,int,char*,int) ; 
 scalar_t__ strlen (char*) ; 

char *stb_substr(char *t, int n)
{
   char *a;
   int z = (int) strlen(t);
   if (z < n) n = z;
   a = (char *) malloc(n+1);
   stb_p_strncpy_s(a,n+1,t,n);
   a[n] = 0;
   return a;
}