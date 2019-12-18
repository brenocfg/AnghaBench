#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_9__ {scalar_t__ nLevels; int wFlags; scalar_t__ dwAttribs; int /*<<< orphan*/  szName; scalar_t__ dwNetType; struct TYPE_9__* pParent; } ;
typedef  int /*<<< orphan*/  TCHAR ;
typedef  TYPE_1__* PDNODE ;
typedef  int /*<<< orphan*/  LPTSTR ;
typedef  long LPARAM ;
typedef  int INT ;
typedef  int /*<<< orphan*/  HWND ;
typedef  scalar_t__ DWORD ;
typedef  int /*<<< orphan*/  DNODE ;
typedef  scalar_t__ BYTE ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ ByteCountOf (scalar_t__) ; 
 scalar_t__ CALC_EXTENT (TYPE_1__*) ; 
 int CompareNodes (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  GWL_XTREEMAX ; 
 int /*<<< orphan*/  GetDlgItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ GetFileAttributes (int /*<<< orphan*/ *) ; 
 scalar_t__ GetRealExtent (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  GetTreePath (TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ GetWindowLongPtr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDCW_TREELISTBOX ; 
 scalar_t__ INVALID_FILE_ATTRIBUTES ; 
 scalar_t__ IsLFN (int /*<<< orphan*/ ) ; 
 int LB_ERR ; 
 int /*<<< orphan*/  LB_GETCOUNT ; 
 int /*<<< orphan*/  LB_GETTEXT ; 
 int /*<<< orphan*/  LB_INSERTSTRING ; 
 int /*<<< orphan*/  LB_SETHORIZONTALEXTENT ; 
 int /*<<< orphan*/  LPTR ; 
 scalar_t__ LocalAlloc (int /*<<< orphan*/ ,scalar_t__) ; 
 int MAXPATHLEN ; 
 scalar_t__ SendMessage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,long) ; 
 int /*<<< orphan*/  SetWindowLongPtr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int TF_EXPANDED ; 
 int TF_HASCHILDREN ; 
 int TF_LASTLEVELENTRY ; 
 int TF_LFN ; 
 int TF_LOWERCASE ; 
 int /*<<< orphan*/  lstrcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ lstrlen (int /*<<< orphan*/ ) ; 

INT
InsertDirectory(
   HWND hwndTreeCtl,
   PDNODE pParentNode,
   INT iParentNode,
   LPTSTR szName,
   PDNODE *ppNode,
   BOOL bCasePreserved,
   BOOL bPartialSort,
   DWORD dwAttribs)
{
   UINT len, x, xTreeMax;
   PDNODE pNode, pMid;
   HWND hwndLB;
   INT iMin, iMax, iMid;
   TCHAR szPathName[MAXPATHLEN * 2];


   len = lstrlen(szName);

   pNode = (PDNODE)LocalAlloc(LPTR, sizeof(DNODE) + ByteCountOf(len));
   if (!pNode)
   {
      if (ppNode)
      {
         *ppNode = NULL;
      }
      return (0);
   }

   pNode->pParent = pParentNode;
   pNode->nLevels = pParentNode ? (pParentNode->nLevels + (BYTE)1) : (BYTE)0;
   pNode->wFlags  = 0;
   pNode->dwNetType = (DWORD)-1;

#ifdef USE_TF_LFN
   if (IsLFN(szName))
   {
      pNode->wFlags |= TF_LFN;
   }
#endif

   if (!bCasePreserved)
      pNode->wFlags |= TF_LOWERCASE;

   lstrcpy(pNode->szName, szName);

   if (pParentNode)
      pParentNode->wFlags |= TF_HASCHILDREN | TF_EXPANDED;      // mark the parent

   hwndLB = GetDlgItem(hwndTreeCtl, IDCW_TREELISTBOX);

   /*
    *  Get the real text extent for the current directory and save it
    *  in the pNode.
    */
   x = GetRealExtent(pNode, hwndLB, NULL, &len);
   x = CALC_EXTENT(pNode);

   xTreeMax = GetWindowLongPtr(hwndTreeCtl, GWL_XTREEMAX);
   if (x > xTreeMax)
   {
       SetWindowLongPtr(hwndTreeCtl, GWL_XTREEMAX, x);
       SendMessage(hwndLB, LB_SETHORIZONTALEXTENT, x, 0L);
   }

   iMax = (INT)SendMessage(hwndLB, LB_GETCOUNT, 0, 0L);

   if (iMax > 0)
   {
      // do a binary insert

      iMin = iParentNode + 1;
      iMax--;         // last index

      //
      // Hack speedup: check if goes last.
      //
      SendMessage(hwndLB, LB_GETTEXT, iMax, (LPARAM)&pMid);

      if (bPartialSort && CompareNodes(pNode, pMid) > 0)
      {
         iMax++;
      }
      else
      {
	     int iCmp;
         do
         {
            iMid = (iMax + iMin) / 2;

            SendMessage(hwndLB, LB_GETTEXT, iMid, (LPARAM)&pMid);

            iCmp = CompareNodes(pNode, pMid);
            if (iCmp == 0)
            {
                iMax = iMin = iMid;
            }
            else if (iCmp > 0)
               iMin = iMid + 1;
            else
               iMax = iMid - 1;

         } while (iMax > iMin);

         // result is that new node may be:
         // a. inserted before iMax (normal case)
         // b. inserted after iMax (if at end of list)
         // c. same as iMax -- return right away
         SendMessage(hwndLB, LB_GETTEXT, iMax, (LPARAM)&pMid);
         iCmp = CompareNodes(pNode, pMid);
         if (iCmp == 0)
         {
             if (ppNode)
             {
                 *ppNode = pMid;
             }
             return iMax;
         }

        if (iCmp > 0)
        {
            iMax++;         // insert after this one
        }
      }
   }

   // now reset the TF_LASTLEVEL flags as appropriate

   // look for the first guy on our level above us and turn off
   // his TF_LASTLEVELENTRY flag so he draws a line down to us

   iMid = iMax - 1;

   while (iMid >= 0)
   {
      SendMessage(hwndLB, LB_GETTEXT, iMid--, (LPARAM)&pMid);
      if (pMid->nLevels == pNode->nLevels)
      {
         pMid->wFlags &= ~TF_LASTLEVELENTRY;
         break;
      }
      else if (pMid->nLevels < pNode->nLevels)
      {
         break;
      }
   }

   // if no one below me or the level of the guy below is less, then
   // this is the last entry for this level

   if (((INT)SendMessage(hwndLB, LB_GETTEXT, iMax, (LPARAM)&pMid) == LB_ERR) ||
       (pMid->nLevels < pNode->nLevels))
   {
      pNode->wFlags |=  TF_LASTLEVELENTRY;
   }

   //
   //  Set the attributes for this directory.
   //
   if (dwAttribs == INVALID_FILE_ATTRIBUTES)
   {
       GetTreePath(pNode, szPathName);
       if ((pNode->dwAttribs = GetFileAttributes(szPathName)) == INVALID_FILE_ATTRIBUTES)
       {
           pNode->dwAttribs = 0;
       }
   }
   else
   {
       pNode->dwAttribs = dwAttribs;
   }

   SendMessage(hwndLB, LB_INSERTSTRING, iMax, (LPARAM)pNode);

   if (ppNode)
   {
      *ppNode = pNode;
   }

   return (iMax);
}