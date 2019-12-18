#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int UINT ;
struct TYPE_2__ {int pFiles; int /*<<< orphan*/  fWide; int /*<<< orphan*/  fNC; int /*<<< orphan*/  pt; } ;
typedef  int /*<<< orphan*/  TCHAR ;
typedef  int /*<<< orphan*/  POINT ;
typedef  int /*<<< orphan*/  LPTSTR ;
typedef  TYPE_1__* LPDROPFILES ;
typedef  scalar_t__ LPBYTE ;
typedef  int /*<<< orphan*/ * HDROP ;
typedef  int /*<<< orphan*/ * HANDLE ;
typedef  int /*<<< orphan*/  DROPFILES ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  COUNTOF (int /*<<< orphan*/ *) ; 
 int GMEM_DDESHARE ; 
 int GMEM_MOVEABLE ; 
 int GMEM_ZEROINIT ; 
 int /*<<< orphan*/  GetNextFile (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * GlobalAlloc (int,int) ; 
 scalar_t__ GlobalLock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GlobalUnlock (int /*<<< orphan*/ *) ; 
 int MAXPATHLEN ; 
 int /*<<< orphan*/  QualifyPath (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  lstrcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int wcslen (int /*<<< orphan*/ *) ; 

HDROP CreateDropFiles(POINT pt, BOOL fNC, LPTSTR pszFiles)
{
    HANDLE hDrop;
    LPBYTE lpList;
    UINT cbList;
	LPTSTR szSrc;

    LPDROPFILES lpdfs;
    TCHAR szFile[MAXPATHLEN];

	cbList = sizeof(DROPFILES) + sizeof(TCHAR);

	szSrc = pszFiles;
    while (szSrc = GetNextFile(szSrc, szFile, COUNTOF(szFile))) 
	{
        QualifyPath(szFile);

		cbList += (wcslen(szFile) + 1)*sizeof(TCHAR);
	}

    hDrop = GlobalAlloc(GMEM_DDESHARE|GMEM_MOVEABLE|GMEM_ZEROINIT, cbList);
    if (!hDrop)
        return NULL;

    lpdfs = (LPDROPFILES)GlobalLock(hDrop);

    lpdfs->pFiles = sizeof(DROPFILES);
	lpdfs->pt = pt;
	lpdfs->fNC = fNC;
    lpdfs->fWide = TRUE;

	lpList = (LPBYTE)lpdfs + sizeof(DROPFILES);
	szSrc = pszFiles;

    while (szSrc = GetNextFile(szSrc, szFile, COUNTOF(szFile))) {

       QualifyPath(szFile);

       lstrcpy((LPTSTR)lpList, szFile);

       lpList += (wcslen(szFile) + 1)*sizeof(TCHAR);
    }

	GlobalUnlock(hDrop);

	return hDrop;
}