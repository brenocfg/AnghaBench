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
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  stb_arr_free (char**) ; 
 int stb_arr_len (char**) ; 

void   stb_getopt_free(char **opts)
{
   int i;
   char ** o2 = opts;
   for (i=0; i < stb_arr_len(o2); ++i)
      free(o2[i]);
   stb_arr_free(o2);
}