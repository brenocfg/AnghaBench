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
 int strlen (char*) ; 

char *stb_strip_final_slash_regardless(char *t)
{
   if (t[0]) {
      char *z = t + strlen(t) - 1;
      // *z is the last character
      if (*z == '\\' || *z == '/')
         *z = 0;
      if (*z == '\\')
         *z = '/'; // canonicalize to make sure it matches db
   }
   return t;
}