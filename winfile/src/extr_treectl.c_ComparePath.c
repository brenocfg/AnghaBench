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
struct TYPE_4__ {int /*<<< orphan*/  szName; struct TYPE_4__* pParent; } ;
typedef  int /*<<< orphan*/  TCHAR ;
typedef  TYPE_1__* PDNODE ;
typedef  scalar_t__ INT ;

/* Variables and functions */
 int /*<<< orphan*/  OutputDebugString (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEXT (char*) ; 
 scalar_t__ lstrcmpi (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wsprintf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

INT
ComparePath(PDNODE p1, PDNODE p2)
{
   INT ret;

   if ((p1 == p2) || (!p1) || (!p2)) {

      return 0;       // equal (base case)

   } else {

      ret = ComparePath(p1->pParent, p2->pParent);

      if (ret == 0) {
         // parents are equal

         ret = lstrcmpi(p1->szName, p2->szName);
#if 0
         {
            TCHAR buf[200];
            wsprintf(buf, TEXT("Compare(%s, %s) -> %d\r\n"), p1->szName, p2->szName, ret);
            OutputDebugString(buf);
         }
#endif

      }

      // not equal parents, propagate up the call tree
      return ret;
   }
}