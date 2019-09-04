#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  LPITEMIDLIST ;
typedef  int /*<<< orphan*/  HGLOBAL ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int GHND ; 
 int GMEM_SHARE ; 
 int /*<<< orphan*/  GlobalAlloc (int,int) ; 
 char* GlobalLock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GlobalUnlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ILCombine (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  SHFree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SHGetPathFromIDListA (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int strlen (char*) ; 

HGLOBAL RenderFILENAMEA (LPITEMIDLIST pidlRoot, LPITEMIDLIST * apidl, UINT cidl)
{
	int size = 0;
	char szTemp[MAX_PATH], *szFileName;
	LPITEMIDLIST pidl;
	HGLOBAL hGlobal;
	BOOL bSuccess;

	TRACE("(%p,%p,%u)\n", pidlRoot, apidl, cidl);

	/* get path of combined pidl */
	pidl = ILCombine(pidlRoot, apidl[0]);
	if (!pidl)
		return 0;

	bSuccess = SHGetPathFromIDListA(pidl, szTemp);
	SHFree(pidl);
	if (!bSuccess)
		return 0;

	size = strlen(szTemp) + 1;

	/* fill the structure */
	hGlobal = GlobalAlloc(GHND|GMEM_SHARE, size);
	if(!hGlobal) return hGlobal;
	szFileName = GlobalLock(hGlobal);
	memcpy(szFileName, szTemp, size);
	GlobalUnlock(hGlobal);

	return hGlobal;
}