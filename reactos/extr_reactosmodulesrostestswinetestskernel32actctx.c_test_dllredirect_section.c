#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct strsection_header {int count; int size; } ;
typedef  int /*<<< orphan*/  data2 ;
typedef  int /*<<< orphan*/  data ;
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  ULONG_PTR ;
struct TYPE_4__ {int cbSize; int /*<<< orphan*/  ulSectionTotalLength; scalar_t__ lpSectionBase; } ;
typedef  scalar_t__ HANDLE ;
typedef  int BOOL ;
typedef  TYPE_1__ ACTCTX_SECTION_KEYED_DATA ;

/* Variables and functions */
 int /*<<< orphan*/  ACTIVATION_CONTEXT_SECTION_DLL_REDIRECTION ; 
 int /*<<< orphan*/  DeleteFileA (char*) ; 
 int GetLastError () ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  create_manifest_file (char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  manifest_wndcls1 ; 
 int /*<<< orphan*/  manifest_wndcls2 ; 
 int /*<<< orphan*/  manifest_wndcls_main ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ok (int,char*,int,...) ; 
 int pActivateActCtx (scalar_t__,int /*<<< orphan*/ *) ; 
 int pDeactivateActCtx (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pFindActCtxSectionStringW (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,TYPE_1__*) ; 
 int /*<<< orphan*/  pReleaseActCtx (scalar_t__) ; 
 scalar_t__ test_create (char*) ; 

__attribute__((used)) static void test_dllredirect_section(void)
{
    static const WCHAR testlib1W[] = {'t','e','s','t','l','i','b','1','.','d','l','l',0};
    static const WCHAR testlib2W[] = {'t','e','s','t','l','i','b','2','.','d','l','l',0};
    ACTCTX_SECTION_KEYED_DATA data, data2;
    struct strsection_header *section;
    ULONG_PTR cookie;
    HANDLE handle;
    BOOL ret;

    /* use two dependent manifests, 4 'files' total */
    create_manifest_file("testdep1.manifest", manifest_wndcls1, -1, NULL, NULL);
    create_manifest_file("testdep2.manifest", manifest_wndcls2, -1, NULL, NULL);
    create_manifest_file("main_wndcls.manifest", manifest_wndcls_main, -1, NULL, NULL);

    handle = test_create("main_wndcls.manifest");
    ok(handle != INVALID_HANDLE_VALUE, "handle == INVALID_HANDLE_VALUE, error %u\n", GetLastError());

    DeleteFileA("testdep1.manifest");
    DeleteFileA("testdep2.manifest");
    DeleteFileA("main_wndcls.manifest");

    ret = pActivateActCtx(handle, &cookie);
    ok(ret, "ActivateActCtx failed: %u\n", GetLastError());

    memset(&data, 0, sizeof(data));
    memset(&data2, 0, sizeof(data2));
    data.cbSize = sizeof(data);
    data2.cbSize = sizeof(data2);

    /* get data for two files from different assemblies */
    ret = pFindActCtxSectionStringW(0, NULL,
                                    ACTIVATION_CONTEXT_SECTION_DLL_REDIRECTION,
                                    testlib1W, &data);
    ok(ret, "got %d\n", ret);
    ret = pFindActCtxSectionStringW(0, NULL,
                                    ACTIVATION_CONTEXT_SECTION_DLL_REDIRECTION,
                                    testlib2W, &data2);
    ok(ret, "got %d\n", ret);

    section = (struct strsection_header*)data.lpSectionBase;
    ok(section->count == 4, "got %d\n", section->count);
    ok(section->size == sizeof(*section), "got %d\n", section->size);

    /* For both string same section is returned, meaning it's one dll redirect section per context */
    ok(data.lpSectionBase == data2.lpSectionBase, "got %p, %p\n", data.lpSectionBase, data2.lpSectionBase);
    ok(data.ulSectionTotalLength == data2.ulSectionTotalLength, "got %u, %u\n", data.ulSectionTotalLength,
        data2.ulSectionTotalLength);

    ret = pDeactivateActCtx(0, cookie);
    ok(ret, "DeactivateActCtx failed: %u\n", GetLastError());

    pReleaseActCtx(handle);
}