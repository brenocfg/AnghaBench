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
struct TYPE_3__ {int /*<<< orphan*/  szName; struct TYPE_3__* pParent; } ;
typedef  scalar_t__ TCHAR ;
typedef  TYPE_1__* PDNODE ;
typedef  scalar_t__* LPTSTR ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/  HWND ;
typedef  scalar_t__ DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ CHAR_BACKSLASH ; 
 scalar_t__ CHAR_COLON ; 
 scalar_t__ CHAR_NULL ; 
 scalar_t__ FALSE ; 
 scalar_t__ LB_ERR ; 
 int /*<<< orphan*/  LB_GETTEXT ; 
 int /*<<< orphan*/  MAXFILENAMELEN ; 
 scalar_t__ SendMessage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  lstrcmpi (scalar_t__*,int /*<<< orphan*/ ) ; 
 int lstrlen (scalar_t__*) ; 

BOOL
FindItemFromPath(
   HWND hwndLB,
   LPTSTR lpszPath,
   BOOL bReturnParent,
   DWORD *pIndex,
   PDNODE *ppNode)
{
  register DWORD     i;
  register LPTSTR    p;
  PDNODE             pNode;
  DWORD              iPreviousNode;
  PDNODE             pPreviousNode;
  TCHAR              szElement[1+MAXFILENAMELEN+1];

  if (pIndex) {
	  *pIndex = (DWORD)-1;
  }
  if (ppNode) {
	  *ppNode = NULL;
  }

  if (!lpszPath || lstrlen(lpszPath) < 3 || lpszPath[1] != CHAR_COLON) {
      return FALSE;
  }

  i = 0;
  iPreviousNode = (DWORD)-1;
  pPreviousNode = NULL;

  while (*lpszPath)
    {
      /* NULL out szElement[1] so the backslash hack isn't repeated with
       * a first level directory of length 1.
       */
      szElement[1] = CHAR_NULL;

      /* Copy the next section of the path into 'szElement' */
      p = szElement;

      while (*lpszPath && *lpszPath != CHAR_BACKSLASH)
          *p++ = *lpszPath++;

      /* Add a backslash for the Root directory. */

      if (szElement[1] == CHAR_COLON)
          *p++ = CHAR_BACKSLASH;

      /* NULL terminate 'szElement' */
      *p = CHAR_NULL;

      /* Skip over the path's next Backslash. */

      if (*lpszPath)
          lpszPath++;

      else if (bReturnParent)
        {
          /* We're at the end of a path which includes a filename.  Return
           * the previously found parent.
           */
		  if (pIndex) {
			  *pIndex = iPreviousNode;
		  }
          if (ppNode) {
              *ppNode = pPreviousNode;
          }
          return TRUE;
        }

      while (TRUE)
        {
          /* Out of LB items?  Not found. */
		  if (SendMessage(hwndLB, LB_GETTEXT, i, (LPARAM)&pNode) == LB_ERR)
		  {
			  if (pIndex) {
				  *pIndex = iPreviousNode;
			  }
			  if (ppNode) {
				  *ppNode = pPreviousNode;
			  }
              return FALSE;
		  }

          if (pNode->pParent == pPreviousNode)
            {
              if (!lstrcmpi(szElement, pNode->szName))
                {
                  /* We've found the element... */
				  iPreviousNode = i;
                  pPreviousNode = pNode;
                  break;
                }
            }
          i++;
        }
    }
  if (pIndex) {
	  *pIndex = iPreviousNode;
  }
  if (ppNode) {
      *ppNode = pPreviousNode;
  }

  return TRUE;
}