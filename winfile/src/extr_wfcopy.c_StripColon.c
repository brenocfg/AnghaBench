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
 scalar_t__ CHAR_COLON ; 
 scalar_t__ CHAR_NULL ; 
 int lstrlen (scalar_t__*) ; 

LPTSTR
StripColon(register LPTSTR pPath)
{
   register INT cb = lstrlen(pPath);

   if (cb > 2 && pPath[cb-1] == CHAR_COLON)
      pPath[cb-1] = CHAR_NULL;

   return pPath;
}