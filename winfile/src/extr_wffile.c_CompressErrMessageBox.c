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
typedef  scalar_t__* PHANDLE ;
typedef  scalar_t__ LPTSTR ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int /*<<< orphan*/  COMPRESSERRDLG ; 
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 int /*<<< orphan*/  CompressErrDialogProc ; 
 int DialogBoxParam (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int IDRETRY ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 scalar_t__ MAKEINTRESOURCE (int /*<<< orphan*/ ) ; 
 int WF_RETRY_CREATE ; 
 int WF_RETRY_DEVIO ; 
 int /*<<< orphan*/  hAppInstance ; 
 int /*<<< orphan*/  hwndFrame ; 

int CompressErrMessageBox(
    HWND hwndActive,
    LPTSTR szFile,
    PHANDLE phFile)
{
    int rc;


    //
    //  Put up the error message box - ABORT, RETRY, IGNORE, IGNORE ALL.
    //
    rc = DialogBoxParam( hAppInstance,
                         (LPTSTR) MAKEINTRESOURCE(COMPRESSERRDLG),
                         hwndFrame,
                         CompressErrDialogProc,
                         (LPARAM)szFile );

    //
    //  Return the user preference.
    //
    if (rc == IDRETRY)
    {
        if (*phFile == INVALID_HANDLE_VALUE)
        {
            return (WF_RETRY_CREATE);
        }
        else
        {
            return (WF_RETRY_DEVIO);
        }
    }
    else
    {
        //
        //  IDABORT or IDIGNORE
        //
        //  Close the file handle and return the message box result.
        //
        if (*phFile != INVALID_HANDLE_VALUE)
        {
            CloseHandle(*phFile);
            *phFile = INVALID_HANDLE_VALUE;
        }

        return (rc);
    }
}