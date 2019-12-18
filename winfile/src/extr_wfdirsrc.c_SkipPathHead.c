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
typedef  scalar_t__* LPTSTR ;
typedef  int INT ;

/* Variables and functions */
 scalar_t__ CHAR_BACKSLASH ; 
 scalar_t__ CHAR_COLON ; 
 scalar_t__ ISUNCPATH (scalar_t__*) ; 

LPTSTR
SkipPathHead(LPTSTR lpszPath)
{
   LPTSTR p = lpszPath;
   INT i;

   if (ISUNCPATH(p)) {

      for(i=0, p+=2; *p && i<2; p++) {

         if (CHAR_BACKSLASH == *p)
            i++;
      }

      //
      // If we ran out of string, punt.
      //
      if (!*p)
         return NULL;
      else
         return p;

   } else if (CHAR_COLON == lpszPath[1] && CHAR_BACKSLASH == lpszPath[2]) {

      //
      // Regular pathname
      //

      return lpszPath+3;
   }

   return NULL;
}