#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  XDTALINK ;
struct TYPE_7__ {scalar_t__ dwSize; } ;
struct TYPE_6__ {struct TYPE_6__* next; scalar_t__ dwNextFree; } ;
typedef  scalar_t__ PBYTE ;
typedef  TYPE_1__* LPXDTALINK ;
typedef  TYPE_2__* LPXDTA ;
typedef  scalar_t__ INT ;

/* Variables and functions */

LPXDTA
MemNext(register LPXDTALINK* plpLink, register LPXDTA lpxdta)
{
   register LPXDTALINK lpLinkCur = *plpLink;

   if ((PBYTE)lpxdta + lpxdta->dwSize - (PBYTE)lpLinkCur == (INT)lpLinkCur->dwNextFree)
   {
      *plpLink = lpLinkCur->next;
      return (LPXDTA)(((PBYTE)*plpLink)+sizeof(XDTALINK));
   }
   else
   {
      return (LPXDTA)((PBYTE)lpxdta + lpxdta->dwSize);
   }
}