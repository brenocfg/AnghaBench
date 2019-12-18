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
typedef  int /*<<< orphan*/ * LPITEMIDLIST ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int CSIDL_FAVORITES ; 
 int CSIDL_FLAG_CREATE ; 
 int /*<<< orphan*/  CreateDirectoryA (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DeleteFileA (char*) ; 
 scalar_t__ ERROR_ALREADY_EXISTS ; 
 int /*<<< orphan*/  ERROR_FILE_NOT_FOUND ; 
 scalar_t__ E_FAIL ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FILE_ATTRIBUTE_NORMAL ; 
 scalar_t__ GetLastError () ; 
 scalar_t__ HRESULT_FROM_WIN32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IMalloc_Free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  RemoveDirectoryA (char*) ; 
 int /*<<< orphan*/  SHGFP_TYPE_CURRENT ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  SetFileAttributesA (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  pMalloc ; 
 scalar_t__ pSHGetFolderLocation (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ pSHGetFolderPathA (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ pSHGetSpecialFolderLocation (int /*<<< orphan*/ *,int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  pSHGetSpecialFolderPathA (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  trace (char*,char*) ; 

__attribute__((used)) static void doChild(const char *arg)
{
    char path[MAX_PATH];
    HRESULT hr;

    if (arg[0] == '1')
    {
        LPITEMIDLIST pidl;
        char *p;

        /* test what happens when CSIDL_FAVORITES is set to a nonexistent directory */

        /* test some failure cases first: */
        hr = pSHGetFolderPathA(NULL, CSIDL_FAVORITES, NULL, SHGFP_TYPE_CURRENT, path);
        ok(hr == HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND),
            "SHGetFolderPath returned 0x%08x, expected 0x80070002\n", hr);

        pidl = NULL;
        hr = pSHGetFolderLocation(NULL, CSIDL_FAVORITES, NULL, 0, &pidl);
        ok(hr == E_FAIL || hr == HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND),
            "SHGetFolderLocation returned 0x%08x\n", hr);
        if (hr == S_OK && pidl) IMalloc_Free(pMalloc, pidl);

        ok(!pSHGetSpecialFolderPathA(NULL, path, CSIDL_FAVORITES, FALSE),
            "SHGetSpecialFolderPath succeeded, expected failure\n");

        pidl = NULL;
        hr = pSHGetSpecialFolderLocation(NULL, CSIDL_FAVORITES, &pidl);
        ok(hr == E_FAIL || hr == HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND),
            "SHGetFolderLocation returned 0x%08x\n", hr);

        if (hr == S_OK && pidl) IMalloc_Free(pMalloc, pidl);

        /* now test success: */
        hr = pSHGetFolderPathA(NULL, CSIDL_FAVORITES | CSIDL_FLAG_CREATE, NULL,
                               SHGFP_TYPE_CURRENT, path);
        ok (hr == S_OK, "got 0x%08x\n", hr);
        if (hr == S_OK)
        {
            BOOL ret;

            trace("CSIDL_FAVORITES was changed to %s\n", path);
            ret = CreateDirectoryA(path, NULL);
            ok(!ret, "expected failure with ERROR_ALREADY_EXISTS\n");
            if (!ret)
                ok(GetLastError() == ERROR_ALREADY_EXISTS,
                  "got %d, expected ERROR_ALREADY_EXISTS\n", GetLastError());

            p = path + strlen(path);
            strcpy(p, "\\desktop.ini");
            DeleteFileA(path);
            *p = 0;
            SetFileAttributesA( path, FILE_ATTRIBUTE_NORMAL );
            ret = RemoveDirectoryA(path);
            ok( ret, "failed to remove %s error %u\n", path, GetLastError() );
        }
    }
    else if (arg[0] == '2')
    {
        /* make sure SHGetFolderPath still succeeds when the
           original value of CSIDL_FAVORITES is restored. */
        hr = pSHGetFolderPathA(NULL, CSIDL_FAVORITES | CSIDL_FLAG_CREATE, NULL,
            SHGFP_TYPE_CURRENT, path);
        ok(hr == S_OK, "SHGetFolderPath failed: 0x%08x\n", hr);
    }
}