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
typedef  int /*<<< orphan*/  wchar_t ;

/* Variables and functions */
 int /*<<< orphan*/ *** __p__wenviron () ; 
 int /*<<< orphan*/  _wcsnicmp (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/ * wcschr (int /*<<< orphan*/ *,int) ; 
 size_t wcslen (int /*<<< orphan*/  const*) ; 

wchar_t *_wgetenv(const wchar_t *name)
{
   wchar_t **env;
   size_t length = wcslen(name);

   for (env = *__p__wenviron(); *env; env++)
   {
      wchar_t *str = *env;
      wchar_t *pos = wcschr(str, L'=');
      if (pos && ((unsigned int)(pos - str) == length) && !_wcsnicmp(str, name, length))
         return pos + 1;
   }
   return NULL;
}