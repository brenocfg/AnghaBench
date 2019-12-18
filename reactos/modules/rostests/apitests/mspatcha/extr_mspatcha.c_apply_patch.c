#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wfd ;
struct TYPE_7__ {scalar_t__ len; int /*<<< orphan*/  data; } ;
struct TYPE_10__ {scalar_t__ len; int /*<<< orphan*/  data; } ;
struct TYPE_8__ {int /*<<< orphan*/  name; TYPE_1__ output; TYPE_4__ input; TYPE_4__ patch; } ;
typedef  TYPE_2__ patch_data ;
struct TYPE_9__ {int member_0; scalar_t__ nFileSizeLow; } ;
typedef  TYPE_3__ WIN32_FIND_DATAA ;
typedef  scalar_t__ HANDLE ;
typedef  scalar_t__ DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  APPLY_OPTION_TEST_ONLY ; 
 int ApplyPatchToFileA (char*,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 int /*<<< orphan*/  DeleteFileA (char*) ; 
 scalar_t__ ERROR_PATCH_CORRUPT ; 
 scalar_t__ ERROR_PATCH_WRONG_FILE ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FindClose (scalar_t__) ; 
 scalar_t__ FindFirstFileA (char*,TYPE_3__*) ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  GetTempFileNameA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int MAX_PATH ; 
 int TestApplyPatchToFileA (char*,char*,int /*<<< orphan*/ ) ; 
 int TestApplyPatchToFileByHandles (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  compare_file (char*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  extract (char*,TYPE_4__*) ; 
 int /*<<< orphan*/  extract2 (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__,...) ; 
 scalar_t__ open_file (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  temp_path ; 

__attribute__((used)) static void apply_patch(patch_data* current)
{
    char patchname[MAX_PATH], targetname[MAX_PATH], outputname[MAX_PATH];
    BOOL bResult;
    DWORD dwErr;
    HANDLE hPatch, hTarget, hFind;
    WIN32_FIND_DATAA wfd = { sizeof(wfd) };

    if (!GetTempFileNameA(temp_path, "MPO", 0, outputname))
    {
        ok(0, "GetTempFileNameA failed %lu, %s\n", GetLastError(), current->name);
        return;
    }
    DeleteFileA(outputname);

    if (!extract(patchname, &current->patch))
        return;
    if (!extract(targetname, &current->input))
    {
        DeleteFileA(patchname);
        return;
    }
    // There is a bug in 2k3, where calling 'TestApplyPatchToFileA' gives an AV...
#if 0
    bResult = TestApplyPatchToFileA(patchname, targetname, 0);
#else
    hPatch = open_file(patchname, FALSE);
    hTarget = open_file(targetname, FALSE);
    bResult = TestApplyPatchToFileByHandles(hPatch, hTarget, 0);
    CloseHandle(hPatch);
    CloseHandle(hTarget);
#endif
    ok(bResult, "TestApplyPatchToFileA failed %lu, %s\n", GetLastError(), current->name);
    // Files are not touched
    compare_file(patchname, current->patch.data, current->patch.len, current->name);
    compare_file(targetname, current->input.data, current->input.len, current->name);
    DeleteFileA(patchname);
    DeleteFileA(targetname);


    if (!extract2(patchname, current->patch.data, current->patch.len -1))
        return;
    if (!extract(targetname, &current->input))
    {
        DeleteFileA(patchname);
        return;
    }
    hPatch = open_file(patchname, FALSE);
    hTarget = open_file(targetname, FALSE);
    bResult = TestApplyPatchToFileByHandles(hPatch, hTarget, 0);
    dwErr = GetLastError();
    CloseHandle(hPatch);
    CloseHandle(hTarget);
    ok(!bResult, "TestApplyPatchToFileA succeeded, %s\n", current->name);
    ok(dwErr == ERROR_PATCH_CORRUPT, "TestApplyPatchToFileA GetLastError %lx, %s\n", dwErr, current->name);
    // Files are not touched
    compare_file(patchname, current->patch.data, current->patch.len - 1, current->name);
    compare_file(targetname, current->input.data, current->input.len, current->name);
    DeleteFileA(patchname);
    DeleteFileA(targetname);

    if (!extract(patchname, &current->patch))
        return;
    if (!extract2(targetname, current->input.data, current->input.len -1))
    {
        DeleteFileA(patchname);
        return;
    }
    hPatch = open_file(patchname, FALSE);
    hTarget = open_file(targetname, FALSE);
    bResult = TestApplyPatchToFileByHandles(hPatch, hTarget, 0);
    dwErr = GetLastError();
    CloseHandle(hPatch);
    CloseHandle(hTarget);
    ok(!bResult, "TestApplyPatchToFileA succeeded, %s\n", current->name);
    ok(dwErr == ERROR_PATCH_WRONG_FILE, "TestApplyPatchToFileA GetLastError %lx, %s\n", dwErr, current->name);
    // Files are not touched
    compare_file(patchname, current->patch.data, current->patch.len, current->name);
    compare_file(targetname, current->input.data, current->input.len -1, current->name);
    DeleteFileA(patchname);
    DeleteFileA(targetname);

    if (!extract(patchname, &current->patch))
        return;
    if (!extract(targetname, &current->input))
    {
        DeleteFileA(patchname);
        return;
    }
    bResult = ApplyPatchToFileA(patchname, targetname, outputname, APPLY_OPTION_TEST_ONLY);

    ok(bResult, "ApplyPatchToFileA failed %lu, %s\n", GetLastError(), current->name);
    // Files are not touched
    compare_file(patchname, current->patch.data, current->patch.len, current->name);
    compare_file(targetname, current->input.data, current->input.len, current->name);
    // W2k3 creates an empty file, W10 does not create a file
    hFind = FindFirstFileA(outputname, &wfd);
    ok(hFind == INVALID_HANDLE_VALUE || wfd.nFileSizeLow == 0, "Got a (non-empty) file, %s\n", current->name);
    if (hFind != INVALID_HANDLE_VALUE)
        FindClose(hFind);
    DeleteFileA(patchname);
    DeleteFileA(targetname);
    DeleteFileA(outputname);

    if (!extract(patchname, &current->patch))
        return;
    if (!extract(targetname, &current->input))
    {
        DeleteFileA(patchname);
        return;
    }
    bResult = ApplyPatchToFileA(patchname, targetname, outputname, 0);
    ok(bResult, "ApplyPatchToFileA failed %lu, %s\n", GetLastError(), current->name);
    // Files are not touched
    compare_file(patchname, current->patch.data, current->patch.len, current->name);
    compare_file(targetname, current->input.data, current->input.len, current->name);
    // One output file
    compare_file(outputname, current->output.data, current->output.len, current->name);
    DeleteFileA(patchname);
    DeleteFileA(targetname);
    DeleteFileA(outputname);
}