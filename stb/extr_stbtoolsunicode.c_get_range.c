#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {void* lo; void* hi; } ;
typedef  TYPE_1__ char_range ;

/* Variables and functions */
 char* stb_skipwhite (char*) ; 
 void* strtol (char*,char**,int) ; 

char_range get_range(char *str)
{
   char_range cr;
   char *p;
   cr.lo = strtol(str, &p, 16);
   p = stb_skipwhite(p);
   if (*p == '.')
      cr.hi = strtol(p+2, NULL, 16);
   else
      cr.hi = cr.lo;
   return cr;
}