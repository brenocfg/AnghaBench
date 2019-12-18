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
typedef  int /*<<< orphan*/  TCHAR ;
typedef  int /*<<< orphan*/ * LPTSTR ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ChangeFileSystem (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ CopyFile (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ERROR_INVALID_NAME ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FSC_CREATE ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  IDS_COPYINGMSG ; 
 int MAXPATHLEN ; 
 int /*<<< orphan*/  Notify (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RemoveLast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hdlgProgress ; 
 int /*<<< orphan*/  lstrcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

DWORD
WFCopy(LPTSTR pszFrom, LPTSTR pszTo)
{
    DWORD dwRet;
    TCHAR szTemp[MAXPATHLEN];

    Notify(hdlgProgress, IDS_COPYINGMSG, pszFrom, pszTo);

    if (CopyFile(pszFrom, pszTo, FALSE))
    {
        ChangeFileSystem(FSC_CREATE, pszTo, NULL);
        dwRet = 0;
    }
    else
    {
        dwRet = GetLastError();
        if (dwRet == ERROR_INVALID_NAME)
        {
            //
            //  Try copying without the file name in the TO field.
            //  This is for the case where it's trying to copy to a print
            //  share.  CopyFile fails if the file name is tacked onto the
            //  end in the case of printer shares.
            //
            lstrcpy(szTemp, pszTo);
            RemoveLast(szTemp);
            if (CopyFile(pszFrom, szTemp, FALSE))
            {
                ChangeFileSystem(FSC_CREATE, szTemp, NULL);
                dwRet = 0;
            }

            // else ... use the original dwRet value.
        }
    }

    return (dwRet);
}