#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_4__ {scalar_t__ pParent; } ;
typedef  TYPE_1__* PDNODE ;
typedef  int /*<<< orphan*/ * LPTSTR ;

/* Variables and functions */
 int /*<<< orphan*/  CHAR_NULL ; 
 int /*<<< orphan*/  GetTreePathIndirect (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int lstrlen (int /*<<< orphan*/ *) ; 

VOID
GetTreePath(PDNODE pNode, register LPTSTR szDest)
{
   szDest[0] = CHAR_NULL;
   GetTreePathIndirect(pNode, szDest);

   //
   // Remove the last backslash (unless it is the root directory).
   //
   if (pNode->pParent)
      szDest[lstrlen(szDest)-1] = CHAR_NULL;
}