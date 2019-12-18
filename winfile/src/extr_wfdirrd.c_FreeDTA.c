#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_2__ {int fdwStatus; } ;
typedef  scalar_t__ LPXDTALINK ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int /*<<< orphan*/  GWL_HDTA ; 
 scalar_t__ GetWindowLongPtr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int LPXDTA_STATUS_CLOSE ; 
 int LPXDTA_STATUS_READING ; 
 int /*<<< orphan*/  MemDelete (scalar_t__) ; 
 TYPE_1__* MemLinkToHead (scalar_t__) ; 
 int /*<<< orphan*/  SetWindowLongPtr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,long) ; 

VOID
FreeDTA(HWND hwnd)
{
   register LPXDTALINK lpxdtaLink;

   lpxdtaLink = (LPXDTALINK)GetWindowLongPtr(hwnd, GWL_HDTA);

   SetWindowLongPtr(hwnd, GWL_HDTA, 0L);

   //
   // Only delete it if it's not in use.
   //
   if (lpxdtaLink) {

       if (MemLinkToHead(lpxdtaLink)->fdwStatus & LPXDTA_STATUS_READING) {

           MemLinkToHead(lpxdtaLink)->fdwStatus |= LPXDTA_STATUS_CLOSE;

       } else {

           MemDelete(lpxdtaLink);
       }
   }
}