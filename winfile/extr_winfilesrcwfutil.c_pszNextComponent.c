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
typedef  int* LPWSTR ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CHAR_NULL ; 
 int FALSE ; 

LPWSTR
pszNextComponent(
   LPWSTR p)
{
   BOOL    bInQuotes = FALSE;

   while (*p == L' ' || *p == L'\t')
      p++;

   //
   // Skip executable name
   //
   while (*p) {

      if ((*p == L' ' || *p == L'\t') && !bInQuotes)
         break;

      if (*p == L'\"')
         bInQuotes = !bInQuotes;

      p++;
   }

   if (*p) {
      *p++ = CHAR_NULL;

      while (*p == L' ' || *p == L'\t')
         p++;
   }

   return p;
}