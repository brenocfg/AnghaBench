#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ nLevels; } ;
typedef  TYPE_1__* PDNODE ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  scalar_t__ INT ;
typedef  int /*<<< orphan*/  HWND ;
typedef  scalar_t__ BYTE ;

/* Variables and functions */
 scalar_t__ LB_ERR ; 
 int /*<<< orphan*/  LB_GETTEXT ; 
 scalar_t__ SendMessage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ TRUE ; 

PDNODE
FindParent(
   INT iLevelParent,
   INT iStartInd,
   HWND hwndLB)
{
   PDNODE pNode;

   while (TRUE) {
      if (SendMessage(hwndLB, LB_GETTEXT, iStartInd, (LPARAM)&pNode) == LB_ERR)
         return NULL;

      if (pNode->nLevels == (BYTE)iLevelParent) {
           // NOTE: seems like a duplicate and unnecessary call to the one above
         SendMessage(hwndLB, LB_GETTEXT, iStartInd, (LPARAM)&pNode);
         return pNode;
      }

      iStartInd--;
   }
}