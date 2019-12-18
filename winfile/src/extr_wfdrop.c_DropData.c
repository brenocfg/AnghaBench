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
struct TYPE_3__ {int m_iItemSelected; int /*<<< orphan*/ * m_hWnd; } ;
typedef  TYPE_1__ WF_IDropTarget ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  PDNODE ;
typedef  int /*<<< orphan*/  LPXDTA ;
typedef  int /*<<< orphan*/ * LPWSTR ;
typedef  scalar_t__ LPTSTR ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/  IDataObject ;
typedef  int /*<<< orphan*/ * HWND ;
typedef  int /*<<< orphan*/  HLOCAL ;
typedef  scalar_t__ DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  AddBackslash (int /*<<< orphan*/ *) ; 
 int COUNTOF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CheckEsc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DMMoveCopyHelper (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ DROPEFFECT_COPY ; 
 scalar_t__ DROPEFFECT_MOVE ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  FS_GETDIRECTORY ; 
 int /*<<< orphan*/ * GetDlgItem (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetTreePath (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDCW_LISTBOX ; 
 int /*<<< orphan*/  IDCW_TREELISTBOX ; 
 scalar_t__ LB_ERR ; 
 int /*<<< orphan*/  LB_GETTEXT ; 
 int /*<<< orphan*/  LocalFree (int /*<<< orphan*/ ) ; 
 int MAXPATHLEN ; 
 int /*<<< orphan*/  MemGetFileName (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * QuotedContentList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * QuotedDropList (int /*<<< orphan*/ *) ; 
 scalar_t__ SendMessage (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetFocus (int /*<<< orphan*/ *) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  lstrcat (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  szStarDotStar ; 

void DropData(WF_IDropTarget *This, IDataObject *pDataObject, DWORD dwEffect)
{
	// construct a FORMATETC object
	HWND hwndLB;
	BOOL fTree;
	LPWSTR szFiles = NULL;
	WCHAR     szDest[MAXPATHLEN];

	hwndLB = GetDlgItem(This->m_hWnd, IDCW_LISTBOX);
	fTree = FALSE;
	if (hwndLB == NULL)
	{
		hwndLB = GetDlgItem(This->m_hWnd, IDCW_TREELISTBOX);
		fTree = TRUE;

		if (hwndLB == NULL)
			return;
	}

	// if item selected, add path
	if (fTree)
	{
	    PDNODE pNode;
		
		// odd
		if (This->m_iItemSelected == -1)
			return;

		if (SendMessage(hwndLB, LB_GETTEXT, This->m_iItemSelected, (LPARAM)&pNode) == LB_ERR)
			return;

		GetTreePath(pNode, szDest);
	}
	else
	{
		LPXDTA    lpxdta;

		SendMessage(This->m_hWnd, FS_GETDIRECTORY, COUNTOF(szDest), (LPARAM)szDest);

		if (This->m_iItemSelected != -1)
		{
			SendMessage(hwndLB, LB_GETTEXT, This->m_iItemSelected,
				(LPARAM)(LPTSTR)&lpxdta);
		
			AddBackslash(szDest);
			lstrcat(szDest, MemGetFileName(lpxdta));
		}
	}

    AddBackslash(szDest);
    lstrcat(szDest, szStarDotStar);   // put files in this dir

    CheckEsc(szDest);

	// See if the dataobject contains any TEXT stored as a HGLOBAL
	if ((szFiles = QuotedDropList(pDataObject)) == NULL)
	{
		szFiles = QuotedContentList(pDataObject);
		dwEffect = DROPEFFECT_MOVE; 
	}

	if (szFiles != NULL)
	{
		SetFocus(This->m_hWnd);

		DMMoveCopyHelper(szFiles, szDest, dwEffect == DROPEFFECT_COPY);

		LocalFree((HLOCAL)szFiles);
	}
}