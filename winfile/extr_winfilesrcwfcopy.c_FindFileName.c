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

/* Variables and functions */
 scalar_t__ CHAR_BACKSLASH ; 
 scalar_t__ CHAR_COLON ; 

LPTSTR
FindFileName(register LPTSTR pPath)
{
   register LPTSTR pT;

   for (pT=pPath; *pPath; pPath++) {
      if ((pPath[0] == CHAR_BACKSLASH || pPath[0] == CHAR_COLON) && pPath[1])
         pT = pPath+1;
   }

   return(pT);
}