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
 int STB_FALSE ; 
 int STB_TRUE ; 
 int /*<<< orphan*/ * _fullpath (char*,char*,int) ; 
 int /*<<< orphan*/  getcwd (char*,int) ; 
 int /*<<< orphan*/  stb_p_strcpy_s (char*,int,char*) ; 
 int strlen (char*) ; 

int stb_fullpath(char *abs, int abs_size, char *rel)
{
   #ifdef _WIN32
   return _fullpath(abs, rel, abs_size) != NULL;
   #else
   if (rel[0] == '/' || rel[0] == '~') {
      if ((int) strlen(rel) >= abs_size)
         return 0;
      stb_p_strcpy_s(abs,65536,rel);
      return STB_TRUE;
   } else {
      int n;
      getcwd(abs, abs_size);
      n = strlen(abs);
      if (n+(int) strlen(rel)+2 <= abs_size) {
         abs[n] = '/';
         stb_p_strcpy_s(abs+n+1, 65536,rel);
         return STB_TRUE;
      } else {
         return STB_FALSE;
      }
   }
   #endif
}