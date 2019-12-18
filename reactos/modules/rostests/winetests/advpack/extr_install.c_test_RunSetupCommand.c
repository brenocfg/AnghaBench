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
typedef  int /*<<< orphan*/  systemdir ;
typedef  scalar_t__ ULONG_PTR ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/ * HANDLE ;

/* Variables and functions */
 char* CURR_DIR ; 
 int /*<<< orphan*/  CreateDirectoryA (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DeleteFileA (char*) ; 
 int /*<<< orphan*/  ERROR_DIRECTORY ; 
 int /*<<< orphan*/  ERROR_FILE_NOT_FOUND ; 
 int /*<<< orphan*/  ERROR_INVALID_PARAMETER ; 
 scalar_t__ ERROR_SUCCESS ; 
 scalar_t__ E_INVALIDARG ; 
 int /*<<< orphan*/  GetSystemDirectoryA (char*,int) ; 
 scalar_t__ HRESULT_FROM_WIN32 (int /*<<< orphan*/ ) ; 
 int MAX_PATH ; 
 int RSC_FLAG_INF ; 
 int RSC_FLAG_QUIET ; 
 int /*<<< orphan*/  RemoveDirectoryA (char*) ; 
 scalar_t__ S_ASYNCHRONOUS ; 
 int /*<<< orphan*/  TerminateProcess (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_inf_file (char*) ; 
 int is_spapi_err (scalar_t__) ; 
 int /*<<< orphan*/  lstrcatA (char*,char*) ; 
 int /*<<< orphan*/  lstrcpyA (char*,char*) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 scalar_t__ pRunSetupCommand (int /*<<< orphan*/ *,char*,char*,char*,char*,int /*<<< orphan*/ **,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_RunSetupCommand(void)
{
    HRESULT hr;
    HANDLE hexe;
    char path[MAX_PATH];
    char dir[MAX_PATH];
    char systemdir[MAX_PATH];

    GetSystemDirectoryA(systemdir, sizeof(systemdir));

    /* try an invalid cmd name */
    hr = pRunSetupCommand(NULL, NULL, "Install", "Dir", "Title", NULL, 0, NULL);
    ok(hr == E_INVALIDARG, "Expected E_INVALIDARG, got %d\n", hr);

    /* try an invalid directory */
    hr = pRunSetupCommand(NULL, "winver.exe", "Install", NULL, "Title", NULL, 0, NULL);
    ok(hr == E_INVALIDARG, "Expected E_INVALIDARG, got %d\n", hr);

    /* try to run a nonexistent exe */
#ifdef __REACTOS__
    hexe = (HANDLE)(ULONG_PTR)0xdeadbeefdeadbeefull;
#else
    hexe = (HANDLE)0xdeadbeef;
#endif
    hr = pRunSetupCommand(NULL, "idontexist.exe", "Install", systemdir, "Title", &hexe, 0, NULL);
    ok(hr == HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND),
       "Expected HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND), got %d\n", hr);
    ok(hexe == NULL, "Expected hexe to be NULL\n");
    ok(!TerminateProcess(hexe, 0), "Expected TerminateProcess to fail\n");

    /* try a bad directory */
#ifdef __REACTOS__
    hexe = (HANDLE)(ULONG_PTR)0xdeadbeefdeadbeefull;
#else
    hexe = (HANDLE)0xdeadbeef;
#endif
    hr = pRunSetupCommand(NULL, "winver.exe", "Install", "non\\existent\\directory", "Title", &hexe, 0, NULL);
    ok(hr == HRESULT_FROM_WIN32(ERROR_DIRECTORY),
       "Expected HRESULT_FROM_WIN32(ERROR_DIRECTORY), got %d\n", hr);
    ok(hexe == NULL, "Expected hexe to be NULL\n");
    ok(!TerminateProcess(hexe, 0), "Expected TerminateProcess to fail\n");

    /* try to run an exe with the RSC_FLAG_INF flag */
#ifdef __REACTOS__
    hexe = (HANDLE)(ULONG_PTR)0xdeadbeefdeadbeefull;
#else
    hexe = (HANDLE)0xdeadbeef;
#endif
    hr = pRunSetupCommand(NULL, "winver.exe", "Install", systemdir, "Title", &hexe, RSC_FLAG_INF | RSC_FLAG_QUIET, NULL);
    ok(is_spapi_err(hr), "Expected a setupapi error, got %d\n", hr);
#ifdef __REACTOS__
    ok(hexe == (HANDLE)(ULONG_PTR)0xdeadbeefdeadbeefull, "Expected hexe to be 0xdeadbeef\n");
#else
    ok(hexe == (HANDLE)0xdeadbeef, "Expected hexe to be 0xdeadbeef\n");
#endif
    ok(!TerminateProcess(hexe, 0), "Expected TerminateProcess to fail\n");

    /* run winver.exe */
#ifdef __REACTOS__
    hexe = (HANDLE)(ULONG_PTR)0xdeadbeefdeadbeefull;
#else
    hexe = (HANDLE)0xdeadbeef;
#endif
    hr = pRunSetupCommand(NULL, "winver.exe", "Install", systemdir, "Title", &hexe, 0, NULL);
    ok(hr == S_ASYNCHRONOUS, "Expected S_ASYNCHRONOUS, got %d\n", hr);
    ok(hexe != NULL, "Expected hexe to be non-NULL\n");
    ok(TerminateProcess(hexe, 0), "Expected TerminateProcess to succeed\n");

    CreateDirectoryA("one", NULL);
    create_inf_file("one\\test.inf");

    /* try a full path to the INF, with working dir provided */
    lstrcpyA(path, CURR_DIR);
    lstrcatA(path, "\\one\\test.inf");
    lstrcpyA(dir, CURR_DIR);
    lstrcatA(dir, "\\one");
    hr = pRunSetupCommand(NULL, path, "DefaultInstall", dir, "Title", NULL, RSC_FLAG_INF | RSC_FLAG_QUIET, NULL);
    ok(hr == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", hr);

    /* try a full path to the INF, NULL working dir */
    hr = pRunSetupCommand(NULL, path, "DefaultInstall", NULL, "Title", NULL, RSC_FLAG_INF | RSC_FLAG_QUIET, NULL);
    ok(hr == HRESULT_FROM_WIN32(ERROR_INVALID_PARAMETER),
       "Expected HRESULT_FROM_WIN32(ERROR_INVALID_PARAMETER), got %d\n", hr);

    /* try a full path to the INF, empty working dir */
    hr = pRunSetupCommand(NULL, path, "DefaultInstall", "", "Title", NULL, RSC_FLAG_INF | RSC_FLAG_QUIET, NULL);
    ok(hr == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", hr);

    /* try a relative path to the INF, with working dir provided */
    hr = pRunSetupCommand(NULL, "one\\test.inf", "DefaultInstall", dir, "Title", NULL, RSC_FLAG_INF | RSC_FLAG_QUIET, NULL);
    ok(hr == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", hr);

    /* try a relative path to the INF, NULL working dir */
    hr = pRunSetupCommand(NULL, "one\\test.inf", "DefaultInstall", NULL, "Title", NULL, RSC_FLAG_INF | RSC_FLAG_QUIET, NULL);
    ok(hr == HRESULT_FROM_WIN32(ERROR_INVALID_PARAMETER),
       "Expected HRESULT_FROM_WIN32(ERROR_INVALID_PARAMETER), got %d\n", hr);

    /* try a relative path to the INF, empty working dir */
    hr = pRunSetupCommand(NULL, "one\\test.inf", "DefaultInstall", "", "Title", NULL, RSC_FLAG_INF | RSC_FLAG_QUIET, NULL);
    ok(hr == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", hr);

    /* try only the INF filename, with working dir provided */
    hr = pRunSetupCommand(NULL, "test.inf", "DefaultInstall", dir, "Title", NULL, RSC_FLAG_INF | RSC_FLAG_QUIET, NULL);
    ok(hr == HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND), "Expected HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND), got %d\n", hr);

    /* try only the INF filename, NULL working dir */
    hr = pRunSetupCommand(NULL, "test.inf", "DefaultInstall", NULL, "Title", NULL, RSC_FLAG_INF | RSC_FLAG_QUIET, NULL);
    ok(hr == HRESULT_FROM_WIN32(ERROR_INVALID_PARAMETER),
       "Expected HRESULT_FROM_WIN32(ERROR_INVALID_PARAMETER), got %d\n", hr);

    /* try only the INF filename, empty working dir */
    hr = pRunSetupCommand(NULL, "test.inf", "DefaultInstall", "", "Title", NULL, RSC_FLAG_INF | RSC_FLAG_QUIET, NULL);
    ok(hr == HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND), "Expected HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND), got %d\n", hr);

    DeleteFileA("one\\test.inf");
    RemoveDirectoryA("one");

    create_inf_file("test.inf");

    /* try INF file in the current directory, working directory provided */
    hr = pRunSetupCommand(NULL, "test.inf", "DefaultInstall", CURR_DIR, "Title", NULL, RSC_FLAG_INF | RSC_FLAG_QUIET, NULL);
    ok(hr == HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND), "Expected HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND), got %d\n", hr);

    /* try INF file in the current directory, NULL working directory */
    hr = pRunSetupCommand(NULL, "test.inf", "DefaultInstall", NULL, "Title", NULL, RSC_FLAG_INF | RSC_FLAG_QUIET, NULL);
    ok(hr == HRESULT_FROM_WIN32(ERROR_INVALID_PARAMETER),
       "Expected HRESULT_FROM_WIN32(ERROR_INVALID_PARAMETER), got %d\n", hr);

    /* try INF file in the current directory, empty working directory */
    hr = pRunSetupCommand(NULL, "test.inf", "DefaultInstall", CURR_DIR, "Title", NULL, RSC_FLAG_INF | RSC_FLAG_QUIET, NULL);
    ok(hr == HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND), "Expected HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND), got %d\n", hr);
}