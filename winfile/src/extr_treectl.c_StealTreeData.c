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
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_3__ {scalar_t__ nLevels; struct TYPE_3__* pParent; int /*<<< orphan*/  szName; } ;
typedef  TYPE_1__* PDNODE ;
typedef  int /*<<< orphan*/  LPWSTR ;
typedef  long LPARAM ;
typedef  scalar_t__ INT ;
typedef  scalar_t__ HWND ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  DNODE ;
typedef  scalar_t__ BYTE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int ATTR_HS ; 
 scalar_t__ ByteCountOf (int /*<<< orphan*/ ) ; 
 scalar_t__ COUNTOF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FS_GETDIRECTORY ; 
 TYPE_1__* FindParent (scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  GWL_ATTRIBS ; 
 int /*<<< orphan*/  GWL_READLEVEL ; 
 int /*<<< orphan*/  GWL_VIEW ; 
 int /*<<< orphan*/  GW_CHILD ; 
 int /*<<< orphan*/  GW_HWNDNEXT ; 
 scalar_t__ GetDlgItem (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ GetParent (scalar_t__) ; 
 scalar_t__ GetWindow (scalar_t__,int /*<<< orphan*/ ) ; 
 int GetWindowLongPtr (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ HasTreeWindow (scalar_t__) ; 
 int /*<<< orphan*/  IDCW_TREELISTBOX ; 
 scalar_t__ LB_ERR ; 
 int /*<<< orphan*/  LB_GETCOUNT ; 
 int /*<<< orphan*/  LB_GETITEMDATA ; 
 int /*<<< orphan*/  LB_GETTEXT ; 
 int /*<<< orphan*/  LB_INSERTSTRING ; 
 int /*<<< orphan*/  LPTR ; 
 scalar_t__ LocalAlloc (int /*<<< orphan*/ ,scalar_t__) ; 
 int MAXPATHLEN ; 
 int /*<<< orphan*/  ResetTreeMax (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ SendMessage (scalar_t__,int /*<<< orphan*/ ,scalar_t__,long) ; 
 int /*<<< orphan*/  StripBackslash (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 
 int VIEW_PLUSES ; 
 scalar_t__ hwndMDIClient ; 
 int /*<<< orphan*/  lstrcmpi (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lstrcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lstrlen (int /*<<< orphan*/ ) ; 

BOOL
StealTreeData(
   HWND hwndTC,
   HWND hwndLB,
   LPWSTR szDir)
{
   HWND hwndSrc, hwndT;
   WCHAR szSrc[MAXPATHLEN];
   DWORD dwView;
   DWORD dwAttribs;

   //
   // we need to match on these attributes as well as the name
   //
   dwView    = GetWindowLongPtr(GetParent(hwndTC), GWL_VIEW) & VIEW_PLUSES;
   dwAttribs = GetWindowLongPtr(GetParent(hwndTC), GWL_ATTRIBS) & ATTR_HS;

   //
   // get the dir of this new window for compare below
   //
   for (hwndSrc = GetWindow(hwndMDIClient, GW_CHILD); hwndSrc;
      hwndSrc = GetWindow(hwndSrc, GW_HWNDNEXT)) {

      //
      // avoid finding ourselves, make sure has a tree
      // and make sure the tree attributes match
      //
      if ((hwndT = HasTreeWindow(hwndSrc)) &&
         (hwndT != hwndTC) &&
         !GetWindowLongPtr(hwndT, GWL_READLEVEL) &&
         (dwView  == (DWORD)(GetWindowLongPtr(hwndSrc, GWL_VIEW) & VIEW_PLUSES)) &&
         (dwAttribs == (DWORD)(GetWindowLongPtr(hwndSrc, GWL_ATTRIBS) & ATTR_HS))) {

         SendMessage(hwndSrc, FS_GETDIRECTORY, COUNTOF(szSrc), (LPARAM)szSrc);
         StripBackslash(szSrc);

         if (!lstrcmpi(szDir, szSrc))     // are they the same?
            break;                  // yes, do stuff below
      }
   }

   if (hwndSrc) {

      HWND hwndLBSrc;
      PDNODE pNode, pNewNode, pLastParent;
      INT i;

      hwndLBSrc = GetDlgItem(hwndT, IDCW_TREELISTBOX);

      //
      // don't seal from a tree that hasn't been read yet!
      //
      if ((INT)SendMessage(hwndLBSrc, LB_GETCOUNT, 0, 0L) == 0) {
         return FALSE;
      }

      pLastParent = NULL;

      for (i = 0; SendMessage(hwndLBSrc, LB_GETTEXT, i, (LPARAM)&pNode) != LB_ERR; i++) {

         if (pNewNode = (PDNODE)LocalAlloc(LPTR, sizeof(DNODE) + ByteCountOf(lstrlen(pNode->szName)))) {

            *pNewNode = *pNode;                             // dup the node
            lstrcpy(pNewNode->szName, pNode->szName);       // and the name

            //
            // accelerate the case where we are on the same level to avoid
            // slow linear search!
            //
            if (pLastParent && pLastParent->nLevels == (BYTE)(pNode->nLevels - (BYTE)1)) {
               pNewNode->pParent = pLastParent;
            } else {
               pNewNode->pParent = pLastParent = FindParent(pNode->nLevels-1, i-1, hwndLB);
            }

            SendMessage(hwndLB, LB_INSERTSTRING, i, (LPARAM)pNewNode);
            ASSERT((PDNODE)SendMessage(hwndLB, LB_GETITEMDATA, i, 0L) == pNewNode);
         }
      }

      /*
       *  Reset the max text extent value for the new window.
       */
      ResetTreeMax(hwndLB, FALSE);

      return TRUE;    // successful steal
   }

   return FALSE;
}