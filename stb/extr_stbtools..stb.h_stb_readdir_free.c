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

void stb_readdir_free(char **files)
{
   char **f2 = files;
   int i;
   for (i=0; i < stb_arr_len(f2); ++i)
      free(f2[i]);
   stb_arr_free(f2);
}