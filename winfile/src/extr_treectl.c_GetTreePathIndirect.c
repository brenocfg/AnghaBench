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
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_3__ {int /*<<< orphan*/  szName; struct TYPE_3__* pParent; } ;
typedef  TYPE_1__* PDNODE ;
typedef  int /*<<< orphan*/  LPTSTR ;

/* Variables and functions */
 int /*<<< orphan*/  SZ_BACKSLASH ; 
 int /*<<< orphan*/  lstrcat (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

VOID
GetTreePathIndirect(PDNODE pNode, register LPTSTR szDest)
{
   register PDNODE    pParent;

   pParent = pNode->pParent;

   if (pParent)
      GetTreePathIndirect(pParent, szDest);

   lstrcat(szDest, pNode->szName);

   if (pParent)
      lstrcat(szDest, SZ_BACKSLASH);
}