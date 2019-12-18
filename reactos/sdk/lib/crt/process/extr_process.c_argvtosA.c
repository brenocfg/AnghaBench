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
typedef  scalar_t__ _TCHAR ;

/* Variables and functions */
 int _tcslen (scalar_t__ const* const) ; 
 scalar_t__ malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,scalar_t__ const* const,size_t) ; 

__attribute__((used)) static _TCHAR*
argvtosT(const _TCHAR* const* argv, _TCHAR delim)
{
   int i;
   size_t len;
   _TCHAR *ptr, *str;

   if (argv == NULL)
      return NULL;

   for (i = 0, len = 0; argv[i]; i++)
   {
      len += _tcslen(argv[i]) + 1;
   }

   str = ptr = (_TCHAR*) malloc((len + 1) * sizeof(_TCHAR));
   if (str == NULL)
      return NULL;

   for(i = 0; argv[i]; i++)
   {
      len = _tcslen(argv[i]);
      memcpy(ptr, argv[i], len * sizeof(_TCHAR));
      ptr += len;
      *ptr++ = delim;
   }
   *ptr = 0;

   return str;
}