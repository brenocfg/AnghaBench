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
 char*** __p__environ () ; 
 int /*<<< orphan*/  _strnicmp (char*,char const*,size_t) ; 
 char* strchr (char*,char) ; 
 size_t strlen (char const*) ; 

char *getenv(const char *name)
{
   char **env;
   size_t length = strlen(name);

   for (env = *__p__environ(); *env; env++)
   {
      char *str = *env;
      char *pos = strchr(str,'=');
      if (pos && ((unsigned int)(pos - str) == length) && !_strnicmp(str, name, length))
         return pos + 1;
   }
   return NULL;
}