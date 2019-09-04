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
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  ULONG_PTR ;
typedef  int /*<<< orphan*/ * HANDLE ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CLSID_clrclass ; 
 int CloseHandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CreateDirectoryW (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DeleteFileA (char*) ; 
 int /*<<< orphan*/ * ERROR_INVALID_HANDLE ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/ * GetLastError () ; 
 int /*<<< orphan*/  IID_CoTest ; 
 int /*<<< orphan*/  IID_CoTest2 ; 
 int /*<<< orphan*/  IID_Ibifaceps ; 
 int /*<<< orphan*/  IID_Iiface ; 
 int /*<<< orphan*/  IID_Iifaceps ; 
 int /*<<< orphan*/  IID_Iifaceps2 ; 
 int /*<<< orphan*/  IID_Iifaceps3 ; 
 int /*<<< orphan*/  IID_PS32 ; 
 int /*<<< orphan*/  IID_TlibTest ; 
 int /*<<< orphan*/  IID_TlibTest4 ; 
 int /*<<< orphan*/ * INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  RemoveDirectoryW (int /*<<< orphan*/ ) ; 
 scalar_t__ SetCurrentDirectoryW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ broken (int) ; 
 scalar_t__ create_manifest_file (char*,int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  create_wide_manifest (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  depmanifest1_info ; 
 int /*<<< orphan*/  depmanifest2_info ; 
 int /*<<< orphan*/  depmanifest3_info ; 
 int /*<<< orphan*/  detailed_info0 ; 
 int /*<<< orphan*/  detailed_info1 ; 
 int /*<<< orphan*/  detailed_info2 ; 
 int /*<<< orphan*/  manifest1 ; 
 int /*<<< orphan*/  manifest1_1 ; 
 int /*<<< orphan*/  manifest1_info ; 
 int /*<<< orphan*/  manifest2 ; 
 int /*<<< orphan*/  manifest2_info ; 
 int /*<<< orphan*/  manifest3 ; 
 int /*<<< orphan*/  manifest3_info ; 
 int /*<<< orphan*/  manifest4 ; 
 int /*<<< orphan*/  manifest4_info ; 
 int /*<<< orphan*/  manifest6 ; 
 int /*<<< orphan*/  manifest7 ; 
 int /*<<< orphan*/  manifest8 ; 
 int /*<<< orphan*/  manifest9 ; 
 int /*<<< orphan*/  manifest_comctrl_info ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int pActivateActCtx (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int pDeactivateActCtx (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pGetCurrentActCtx (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  pIsDebuggerPresent () ; 
 int /*<<< orphan*/  pReleaseActCtx (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  runlevel_info0 ; 
 int /*<<< orphan*/  runlevel_info6 ; 
 int /*<<< orphan*/  runlevel_info7 ; 
 int /*<<< orphan*/  runlevel_info8 ; 
 int /*<<< orphan*/  runlevel_info9 ; 
 int /*<<< orphan*/  skip (char*) ; 
 int /*<<< orphan*/  test_allowDelayedBinding () ; 
 int /*<<< orphan*/  test_basic_info (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * test_create (char*) ; 
 int /*<<< orphan*/  test_detailed_info (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  test_dllredirect_section () ; 
 int /*<<< orphan*/  test_file_info (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  test_find_com_redirection (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int,int) ; 
 int /*<<< orphan*/  test_find_dll_redirection (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  test_find_ifaceps_redirection (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  test_find_progid_redirection (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int,int) ; 
 int /*<<< orphan*/  test_find_string_fail () ; 
 int /*<<< orphan*/  test_find_surrogate (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,char const*,int,int) ; 
 int /*<<< orphan*/  test_find_window_class (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  test_info_in_assembly (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  test_runlevel_info (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  test_typelib_section () ; 
 int /*<<< orphan*/  test_wndclass_section () ; 
 int /*<<< orphan*/ * testdep_manifest1 ; 
 int /*<<< orphan*/ * testdep_manifest2 ; 
 int /*<<< orphan*/ * testdep_manifest3 ; 
 int /*<<< orphan*/  testlib2_dll ; 
 int /*<<< orphan*/  testlib_dll ; 
 int /*<<< orphan*/  trace (char*) ; 
 int /*<<< orphan*/  win_skip (char*) ; 
 int /*<<< orphan*/  wndClass2W ; 
 int /*<<< orphan*/  wndClassW ; 
 int /*<<< orphan*/  work_dir ; 
 int /*<<< orphan*/  work_dir_subdir ; 

__attribute__((used)) static void test_actctx(void)
{
    ULONG_PTR cookie;
    HANDLE handle;
    BOOL b;

    trace("default actctx\n");

    b = pGetCurrentActCtx(&handle);
    ok(handle == NULL, "handle = %p, expected NULL\n", handle);
    ok(b, "GetCurrentActCtx failed: %u\n", GetLastError());
    if(b) {
        test_basic_info(handle, __LINE__);
        test_detailed_info(handle, &detailed_info0, __LINE__);
        test_runlevel_info(handle, &runlevel_info0, __LINE__);
        pReleaseActCtx(handle);
    }

    /* test for whitespace handling in Eq ::= S? '=' S? */
    create_manifest_file("test1_1.manifest", manifest1_1, -1, NULL, NULL);
    handle = test_create("test1_1.manifest");
    ok(handle != INVALID_HANDLE_VALUE, "handle == INVALID_HANDLE_VALUE, error %u\n", GetLastError());
    DeleteFileA("test1_1.manifest");
    pReleaseActCtx(handle);

    if(!create_manifest_file("test1.manifest", manifest1, -1, NULL, NULL)) {
        skip("Could not create manifest file\n");
        return;
    }

    trace("manifest1\n");

    handle = test_create("test1.manifest");
    ok(handle != INVALID_HANDLE_VALUE, "handle == INVALID_HANDLE_VALUE, error %u\n", GetLastError());
    DeleteFileA("test1.manifest");
    if(handle != INVALID_HANDLE_VALUE) {
        test_basic_info(handle, __LINE__);
        test_detailed_info(handle, &detailed_info1, __LINE__);
        test_info_in_assembly(handle, 1, &manifest1_info, __LINE__);

        if (pIsDebuggerPresent && !pIsDebuggerPresent())
        {
            /* CloseHandle will generate an exception if a debugger is present */
            b = CloseHandle(handle);
            ok(!b, "CloseHandle succeeded\n");
            ok(GetLastError() == ERROR_INVALID_HANDLE, "GetLastError() == %u\n", GetLastError());
        }

        pReleaseActCtx(handle);
    }

    if(!create_manifest_file("test2.manifest", manifest2, -1, "testdep.manifest", testdep_manifest1)) {
        skip("Could not create manifest file\n");
        return;
    }

    trace("manifest2 depmanifest1\n");

    handle = test_create("test2.manifest");
    ok(handle != INVALID_HANDLE_VALUE, "handle == INVALID_HANDLE_VALUE, error %u\n", GetLastError());
    DeleteFileA("test2.manifest");
    DeleteFileA("testdep.manifest");
    if(handle != INVALID_HANDLE_VALUE) {
        test_basic_info(handle, __LINE__);
        test_detailed_info(handle, &detailed_info2, __LINE__);
        test_info_in_assembly(handle, 1, &manifest2_info, __LINE__);
        test_info_in_assembly(handle, 2, &depmanifest1_info, __LINE__);
        pReleaseActCtx(handle);
    }

    if(!create_manifest_file("test2-2.manifest", manifest2, -1, "testdep.manifest", testdep_manifest2)) {
        skip("Could not create manifest file\n");
        return;
    }

    trace("manifest2 depmanifest2\n");

    handle = test_create("test2-2.manifest");
    ok(handle != INVALID_HANDLE_VALUE, "handle == INVALID_HANDLE_VALUE, error %u\n", GetLastError());
    DeleteFileA("test2-2.manifest");
    DeleteFileA("testdep.manifest");
    if(handle != INVALID_HANDLE_VALUE) {
        test_basic_info(handle, __LINE__);
        test_detailed_info(handle, &detailed_info2, __LINE__);
        test_info_in_assembly(handle, 1, &manifest2_info, __LINE__);
        test_info_in_assembly(handle, 2, &depmanifest2_info, __LINE__);
        test_file_info(handle, 1, 0, testlib_dll, __LINE__);
        test_file_info(handle, 1, 1, testlib2_dll, __LINE__);

        b = pActivateActCtx(handle, &cookie);
        ok(b, "ActivateActCtx failed: %u\n", GetLastError());
        test_find_dll_redirection(handle, testlib_dll, 2, __LINE__);
        test_find_dll_redirection(handle, testlib2_dll, 2, __LINE__);
        b = pDeactivateActCtx(0, cookie);
        ok(b, "DeactivateActCtx failed: %u\n", GetLastError());

        pReleaseActCtx(handle);
    }

    trace("manifest2 depmanifest3\n");

    if(!create_manifest_file("test2-3.manifest", manifest2, -1, "testdep.manifest", testdep_manifest3)) {
        skip("Could not create manifest file\n");
        return;
    }

    handle = test_create("test2-3.manifest");
    ok(handle != INVALID_HANDLE_VALUE, "handle == INVALID_HANDLE_VALUE, error %u\n", GetLastError());
    DeleteFileA("test2-3.manifest");
    DeleteFileA("testdep.manifest");
    if(handle != INVALID_HANDLE_VALUE) {
        test_basic_info(handle, __LINE__);
        test_detailed_info(handle, &detailed_info2, __LINE__);
        test_info_in_assembly(handle, 1, &manifest2_info, __LINE__);
        test_info_in_assembly(handle, 2, &depmanifest3_info, __LINE__);
        test_file_info(handle, 1, 0, testlib_dll, __LINE__);
        test_file_info(handle, 1, 1, testlib2_dll, __LINE__);

        b = pActivateActCtx(handle, &cookie);
        ok(b, "ActivateActCtx failed: %u\n", GetLastError());
        test_find_dll_redirection(handle, testlib_dll, 2, __LINE__);
        test_find_dll_redirection(handle, testlib2_dll, 2, __LINE__);
        test_find_window_class(handle, wndClassW, 2, __LINE__);
        test_find_window_class(handle, wndClass2W, 2, __LINE__);
        b = pDeactivateActCtx(0, cookie);
        ok(b, "DeactivateActCtx failed: %u\n", GetLastError());

        pReleaseActCtx(handle);
    }

    trace("manifest3\n");

    if(!create_manifest_file("test3.manifest", manifest3, -1, NULL, NULL)) {
        skip("Could not create manifest file\n");
        return;
    }

    handle = test_create("test3.manifest");
    ok(handle != INVALID_HANDLE_VALUE || broken(handle == INVALID_HANDLE_VALUE) /* XP pre-SP2, win2k3 w/o SP */,
        "handle == INVALID_HANDLE_VALUE, error %u\n", GetLastError());
    if (handle == INVALID_HANDLE_VALUE)
        win_skip("Some activation context features not supported, skipping a test (possibly old XP/Win2k3 system\n");
    DeleteFileA("test3.manifest");
    if(handle != INVALID_HANDLE_VALUE) {
        static const WCHAR nameW[] = {'t','e','s','t','s','u','r','r','o','g','a','t','e',0};
        static const WCHAR versionW[] = {'v','2','.','0','.','5','0','7','2','7',0};
        static const WCHAR progidW[] = {'P','r','o','g','I','d','.','P','r','o','g','I','d',0};
        static const WCHAR clrprogidW[] = {'c','l','r','p','r','o','g','i','d',0};

        test_basic_info(handle, __LINE__);
        test_detailed_info(handle, &detailed_info1, __LINE__);
        test_info_in_assembly(handle, 1, &manifest3_info, __LINE__);
        test_file_info(handle, 0, 0, testlib_dll, __LINE__);

        b = pActivateActCtx(handle, &cookie);
        ok(b, "ActivateActCtx failed: %u\n", GetLastError());
        test_find_dll_redirection(handle, testlib_dll, 1, __LINE__);
        test_find_dll_redirection(handle, testlib_dll, 1, __LINE__);
        test_find_com_redirection(handle, &IID_CoTest, &IID_TlibTest, progidW, 1, __LINE__);
        test_find_com_redirection(handle, &IID_CoTest2, NULL, NULL, 1, __LINE__);
        test_find_com_redirection(handle, &CLSID_clrclass, &IID_TlibTest, clrprogidW, 1, __LINE__);
        test_find_progid_redirection(handle, &IID_CoTest, "ProgId.ProgId", 1, __LINE__);
        test_find_progid_redirection(handle, &IID_CoTest, "ProgId.ProgId.1", 1, __LINE__);
        test_find_progid_redirection(handle, &IID_CoTest, "ProgId.ProgId.2", 1, __LINE__);
        test_find_progid_redirection(handle, &IID_CoTest, "ProgId.ProgId.3", 1, __LINE__);
        test_find_progid_redirection(handle, &IID_CoTest, "ProgId.ProgId.4", 1, __LINE__);
        test_find_progid_redirection(handle, &IID_CoTest, "ProgId.ProgId.5", 1, __LINE__);
        test_find_progid_redirection(handle, &IID_CoTest, "ProgId.ProgId.6", 1, __LINE__);
        test_find_progid_redirection(handle, &CLSID_clrclass, "clrprogid", 1, __LINE__);
        test_find_progid_redirection(handle, &CLSID_clrclass, "clrprogid.1", 1, __LINE__);
        test_find_progid_redirection(handle, &CLSID_clrclass, "clrprogid.2", 1, __LINE__);
        test_find_progid_redirection(handle, &CLSID_clrclass, "clrprogid.3", 1, __LINE__);
        test_find_progid_redirection(handle, &CLSID_clrclass, "clrprogid.4", 1, __LINE__);
        test_find_progid_redirection(handle, &CLSID_clrclass, "clrprogid.5", 1, __LINE__);
        test_find_progid_redirection(handle, &CLSID_clrclass, "clrprogid.6", 1, __LINE__);
        test_find_surrogate(handle, &IID_Iiface, nameW, versionW, 1, __LINE__);
        test_find_ifaceps_redirection(handle, &IID_Iifaceps, &IID_TlibTest4, &IID_Ibifaceps, NULL, 1, __LINE__);
        test_find_ifaceps_redirection(handle, &IID_Iifaceps2, &IID_TlibTest4, &IID_Ibifaceps, &IID_PS32, 1, __LINE__);
        test_find_ifaceps_redirection(handle, &IID_Iifaceps3, &IID_TlibTest4, &IID_Ibifaceps, NULL, 1, __LINE__);
        test_find_string_fail();

        b = pDeactivateActCtx(0, cookie);
        ok(b, "DeactivateActCtx failed: %u\n", GetLastError());
        pReleaseActCtx(handle);
    }

    trace("manifest6\n");

    if(create_manifest_file("test6.manifest", manifest6, -1, NULL, NULL)) {
        handle = test_create("test6.manifest");
        ok(handle != INVALID_HANDLE_VALUE || broken(handle == INVALID_HANDLE_VALUE) /* WinXP */,
            "Unexpected context handle %p.\n", handle);
        DeleteFileA("test6.manifest");
        DeleteFileA("testdep.manifest");
        if(handle != INVALID_HANDLE_VALUE)
        {
            test_runlevel_info(handle, &runlevel_info6, __LINE__);
            pReleaseActCtx(handle);
        }
    }
    else
        skip("Could not create manifest file 6\n");

    trace("manifest7\n");

    if(create_manifest_file("test7.manifest", manifest7, -1, NULL, NULL)) {
        handle = test_create("test7.manifest");
        ok(handle != INVALID_HANDLE_VALUE, "handle == INVALID_HANDLE_VALUE, error %u\n", GetLastError());
        DeleteFileA("test7.manifest");
        DeleteFileA("testdep.manifest");
        if(handle != INVALID_HANDLE_VALUE)
        {
            test_runlevel_info(handle, &runlevel_info7, __LINE__);
            pReleaseActCtx(handle);
        }
    }
    else
        skip("Could not create manifest file 7\n");

    trace("manifest8\n");

    if(create_manifest_file("test8.manifest", manifest8, -1, NULL, NULL)) {
        handle = test_create("test8.manifest");
        ok(handle != INVALID_HANDLE_VALUE, "handle == INVALID_HANDLE_VALUE, error %u\n", GetLastError());
        DeleteFileA("test8.manifest");
        DeleteFileA("testdep.manifest");
        if(handle != INVALID_HANDLE_VALUE)
        {
            test_runlevel_info(handle, &runlevel_info8, __LINE__);
            pReleaseActCtx(handle);
        }
    }
    else
        skip("Could not create manifest file 8\n");

    trace("manifest9\n");

    if(create_manifest_file("test9.manifest", manifest9, -1, NULL, NULL)) {
        handle = test_create("test9.manifest");
        ok(handle != INVALID_HANDLE_VALUE, "handle == INVALID_HANDLE_VALUE, error %u\n", GetLastError());
        DeleteFileA("test9.manifest");
        DeleteFileA("testdep.manifest");
        if(handle != INVALID_HANDLE_VALUE)
        {
            test_runlevel_info(handle, &runlevel_info9, __LINE__);
            pReleaseActCtx(handle);
        }
    }
    else
        skip("Could not create manifest file 9\n");

    trace("manifest4\n");

    if(!create_manifest_file("test4.manifest", manifest4, -1, NULL, NULL)) {
        skip("Could not create manifest file\n");
        return;
    }

    handle = test_create("test4.manifest");
    ok(handle != INVALID_HANDLE_VALUE, "handle == INVALID_HANDLE_VALUE, error %u\n", GetLastError());
    DeleteFileA("test4.manifest");
    DeleteFileA("testdep.manifest");
    if(handle != INVALID_HANDLE_VALUE) {
        test_basic_info(handle, __LINE__);
        test_detailed_info(handle, &detailed_info2, __LINE__);
        test_info_in_assembly(handle, 1, &manifest4_info, __LINE__);
        test_info_in_assembly(handle, 2, &manifest_comctrl_info, __LINE__);
        pReleaseActCtx(handle);
    }

    trace("manifest1 in subdir\n");

    CreateDirectoryW(work_dir_subdir, NULL);
    if (SetCurrentDirectoryW(work_dir_subdir))
    {
        if(!create_manifest_file("..\\test1.manifest", manifest1, -1, NULL, NULL)) {
            skip("Could not create manifest file\n");
            return;
        }
        handle = test_create("..\\test1.manifest");
        ok(handle != INVALID_HANDLE_VALUE, "handle == INVALID_HANDLE_VALUE, error %u\n", GetLastError());
        DeleteFileA("..\\test1.manifest");
        if(handle != INVALID_HANDLE_VALUE) {
            test_basic_info(handle, __LINE__);
            test_detailed_info(handle, &detailed_info1, __LINE__);
            test_info_in_assembly(handle, 1, &manifest1_info, __LINE__);
            pReleaseActCtx(handle);
        }
        SetCurrentDirectoryW(work_dir);
    }
    else
        skip("Couldn't change directory\n");
    RemoveDirectoryW(work_dir_subdir);

    trace("UTF-16 manifest1, with BOM\n");
    if(!create_wide_manifest("test1.manifest", manifest1, TRUE, FALSE)) {
        skip("Could not create manifest file\n");
        return;
    }

    handle = test_create("test1.manifest");
    ok(handle != INVALID_HANDLE_VALUE, "handle == INVALID_HANDLE_VALUE, error %u\n", GetLastError());
    DeleteFileA("test1.manifest");
    if (handle != INVALID_HANDLE_VALUE) {
        test_basic_info(handle, __LINE__);
        test_detailed_info(handle, &detailed_info1, __LINE__);
        test_info_in_assembly(handle, 1, &manifest1_info, __LINE__);
        pReleaseActCtx(handle);
    }

    trace("UTF-16 manifest1, reverse endian, with BOM\n");
    if(!create_wide_manifest("test1.manifest", manifest1, TRUE, TRUE)) {
        skip("Could not create manifest file\n");
        return;
    }

    handle = test_create("test1.manifest");
    ok(handle != INVALID_HANDLE_VALUE, "handle == INVALID_HANDLE_VALUE, error %u\n", GetLastError());
    DeleteFileA("test1.manifest");
    if (handle != INVALID_HANDLE_VALUE) {
        test_basic_info(handle, __LINE__);
        test_detailed_info(handle, &detailed_info1, __LINE__);
        test_info_in_assembly(handle, 1, &manifest1_info, __LINE__);
        pReleaseActCtx(handle);
    }

    test_wndclass_section();
    test_dllredirect_section();
    test_typelib_section();
    test_allowDelayedBinding();
}