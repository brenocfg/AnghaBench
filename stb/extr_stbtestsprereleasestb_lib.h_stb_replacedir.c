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
 int STB_EXT ; 
 int STB_FILE ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,char*) ; 
 int /*<<< orphan*/  stb_splitpath (char*,char*,int) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

char *stb_replacedir(char *output, char *src, char *dir)
{
   char buffer[4096];
   stb_splitpath(buffer, src, STB_FILE | STB_EXT);
   if (dir)
      sprintf(output, "%s/%s", dir, buffer);
   else
      strcpy(output, buffer);
   return output;
}