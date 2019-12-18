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
struct TYPE_3__ {int /*<<< orphan*/  dwAttribs; } ;
typedef  int /*<<< orphan*/  TCHAR ;
typedef  TYPE_1__* PDNODE ;
typedef  long LPARAM ;
typedef  int INT ;
typedef  scalar_t__ HWND ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GW_CHILD ; 
 int /*<<< orphan*/  GW_HWNDNEXT ; 
 scalar_t__ GetDlgItem (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetFileAttributes (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetTreePath (TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ GetWindow (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ HasTreeWindow (scalar_t__) ; 
 int /*<<< orphan*/  IDCW_TREELISTBOX ; 
 int /*<<< orphan*/  INVALID_FILE_ATTRIBUTES ; 
 int /*<<< orphan*/  InvalidateRect (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LB_GETCOUNT ; 
 int /*<<< orphan*/  LB_GETTEXT ; 
 int MAXPATHLEN ; 
 scalar_t__ SendMessage (scalar_t__,int /*<<< orphan*/ ,int,long) ; 
 scalar_t__ hwndMDIClient ; 

VOID RedrawAllTreeWindows()
{
    HWND hwnd, hwndTree, hwndLB;
    int cItems, ctr;
    PDNODE pNode;
    DWORD dwAttribs;
    TCHAR szPathName[MAXPATHLEN * 2];


    for (hwnd = GetWindow(hwndMDIClient, GW_CHILD);
         hwnd;
         hwnd = GetWindow(hwnd, GW_HWNDNEXT))
    {
       if (hwndTree = HasTreeWindow(hwnd))
       {
           hwndLB = GetDlgItem(hwndTree, IDCW_TREELISTBOX);

           //
           //  Search through all of the pNodes and update the
           //  attributes.
           //
           cItems = (INT)SendMessage(hwndLB, LB_GETCOUNT, 0, 0L);
           for (ctr = 0; ctr < cItems; ctr++)
           {
               SendMessage(hwndLB, LB_GETTEXT, ctr, (LPARAM)&pNode);

               //
               //  Set the attributes for this directory.
               //
               GetTreePath(pNode, szPathName);
               if ((dwAttribs = GetFileAttributes(szPathName)) != INVALID_FILE_ATTRIBUTES)
               {
                   pNode->dwAttribs = dwAttribs;
               }
           }

           InvalidateRect(hwndLB, NULL, FALSE);
       }
    }
}