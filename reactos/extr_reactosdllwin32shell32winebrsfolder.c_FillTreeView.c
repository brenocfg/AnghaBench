#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* lpBrowseInfo; int /*<<< orphan*/  hwndTreeView; } ;
typedef  TYPE_2__ browse_info ;
typedef  int ULONG ;
struct TYPE_5__ {int /*<<< orphan*/  ulFlags; } ;
typedef  int /*<<< orphan*/  LPWSTR ;
typedef  int /*<<< orphan*/  LPVOID ;
typedef  int /*<<< orphan*/  LPSTR ;
typedef  int /*<<< orphan*/ * LPITEMIDLIST ;
typedef  int /*<<< orphan*/  LPCITEMIDLIST ;
typedef  int /*<<< orphan*/  IShellFolder ;
typedef  int /*<<< orphan*/  IEnumIDList ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  HTREEITEM ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  BrowseFlagsToSHCONTF (int /*<<< orphan*/ ) ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetParent (int /*<<< orphan*/ ) ; 
 scalar_t__ IDC_ARROW ; 
 scalar_t__ IDC_WAIT ; 
 scalar_t__ IEnumIDList_Next (int /*<<< orphan*/ *,int,int /*<<< orphan*/ **,int*) ; 
 int /*<<< orphan*/  IEnumIDList_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IEnumIDList_Reset (int /*<<< orphan*/ *) ; 
 scalar_t__ IEnumIDList_Skip (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  IID_IShellFolder ; 
 scalar_t__ IShellFolder_BindToObject (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ IShellFolder_EnumObjects (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IShellFolder_GetAttributesOf (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  IShellFolder_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InsertTreeViewItem (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LoadCursorA (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LoadCursorW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseCapture () ; 
 int SFGAO_FOLDER ; 
 int SFGAO_HASSUBFOLDER ; 
 int /*<<< orphan*/  SHFree (int /*<<< orphan*/ *) ; 
 scalar_t__ SUCCEEDED (scalar_t__) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  SetCapture (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetCursor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void FillTreeView( browse_info *info, IShellFolder * lpsf,
                 LPITEMIDLIST  pidl, HTREEITEM hParent, IEnumIDList* lpe)
{
	LPITEMIDLIST	pidlTemp = 0;
	ULONG		ulFetched;
	HRESULT		hr;
	HWND		hwnd = GetParent( info->hwndTreeView );

	TRACE("%p %p %p %p\n",lpsf, pidl, hParent, lpe);

	/* No IEnumIDList -> No children */
	if (!lpe) return;
	
	SetCapture( hwnd );
	SetCursor( LoadCursorA( 0, (LPSTR)IDC_WAIT ) );

	while (S_OK == IEnumIDList_Next(lpe,1,&pidlTemp,&ulFetched))
	{
	    ULONG ulAttrs = SFGAO_HASSUBFOLDER | SFGAO_FOLDER;
	    IEnumIDList* pEnumIL = NULL;
	    IShellFolder* pSFChild = NULL;
	    IShellFolder_GetAttributesOf(lpsf, 1, (LPCITEMIDLIST*)&pidlTemp, &ulAttrs);
	    if (ulAttrs & SFGAO_FOLDER)
	    {
	        hr = IShellFolder_BindToObject(lpsf,pidlTemp,NULL,&IID_IShellFolder,(LPVOID*)&pSFChild);
	        if (SUCCEEDED(hr))
                {
	            DWORD flags = BrowseFlagsToSHCONTF(info->lpBrowseInfo->ulFlags);
	            hr = IShellFolder_EnumObjects(pSFChild, hwnd, flags, &pEnumIL);
                    if (hr == S_OK)
                    {
                        if ((IEnumIDList_Skip(pEnumIL, 1) != S_OK) ||
                             FAILED(IEnumIDList_Reset(pEnumIL)))
                        {
                            IEnumIDList_Release(pEnumIL);
                            pEnumIL = NULL;
                        }
                    }
                    IShellFolder_Release(pSFChild);
                }
	    }

	    if (!InsertTreeViewItem(info, lpsf, pidlTemp, pidl, pEnumIL, hParent))
	        goto done;
	    SHFree(pidlTemp);  /* Finally, free the pidl that the shell gave us... */
	    pidlTemp=NULL;
	}

done:
	ReleaseCapture();
	SetCursor(LoadCursorW(0, (LPWSTR)IDC_ARROW));
    SHFree(pidlTemp);
}