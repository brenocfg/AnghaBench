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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int INT ;
typedef  int /*<<< orphan*/  INFCONTEXT ;
typedef  int /*<<< orphan*/  HINF ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAYSIZE (int /*<<< orphan*/ *) ; 
 int CSIDL_FLAG_CREATE ; 
 int /*<<< orphan*/  CoInitialize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CoUninitialize () ; 
 int /*<<< orphan*/  CreateShortcutsFromSection (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  SHGFP_TYPE_DEFAULT ; 
 int /*<<< orphan*/  SHGetFolderPathAndSubDirW (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetupFindFirstLine (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ SetupFindNextLine (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int SetupGetFieldCount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetupGetIntField (int /*<<< orphan*/ *,int,int*) ; 
 int /*<<< orphan*/  SetupGetStringFieldW (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static BOOL CreateShortcuts(HINF hinf, LPCWSTR szSection)
{
    INFCONTEXT Context;
    WCHAR szPath[MAX_PATH];
    WCHAR szFolder[MAX_PATH];
    WCHAR szFolderSection[MAX_PATH];
    INT csidl;

    CoInitialize(NULL);

    if (!SetupFindFirstLine(hinf, szSection, NULL, &Context))
        return FALSE;

    do
    {
        if (SetupGetFieldCount(&Context) < 2)
            continue;

        if (!SetupGetStringFieldW(&Context, 0, szFolderSection, ARRAYSIZE(szFolderSection), NULL))
            continue;

        if (!SetupGetIntField(&Context, 1, &csidl))
            continue;

        if (!SetupGetStringFieldW(&Context, 2, szFolder, ARRAYSIZE(szFolder), NULL))
            continue;

        if (FAILED(SHGetFolderPathAndSubDirW(NULL, csidl|CSIDL_FLAG_CREATE, (HANDLE)-1, SHGFP_TYPE_DEFAULT, szFolder, szPath)))
            continue;

        CreateShortcutsFromSection(hinf, szFolderSection, szPath);

    } while (SetupFindNextLine(&Context, &Context));

    CoUninitialize();

    return TRUE;
}