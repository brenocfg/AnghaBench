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
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_4__ {int cbSize; int /*<<< orphan*/ * lpSource; } ;
typedef  scalar_t__ HANDLE ;
typedef  TYPE_1__ ACTCTXW ;

/* Variables and functions */
 int /*<<< orphan*/  CP_ACP ; 
 scalar_t__ ERROR_FILE_NOT_FOUND ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ GetLastError () ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  manifest1 ; 
 int /*<<< orphan*/  manifest2 ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 scalar_t__ pCreateActCtxW (TYPE_1__*) ; 
 int /*<<< orphan*/  test_create_and_fail (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_create_wide_and_fail (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace (char*) ; 
 int /*<<< orphan*/ * wrong_depmanifest1 ; 
 int /*<<< orphan*/  wrong_manifest1 ; 
 int /*<<< orphan*/  wrong_manifest10 ; 
 int /*<<< orphan*/  wrong_manifest2 ; 
 int /*<<< orphan*/  wrong_manifest3 ; 
 int /*<<< orphan*/  wrong_manifest4 ; 
 int /*<<< orphan*/  wrong_manifest5 ; 
 int /*<<< orphan*/  wrong_manifest6 ; 
 int /*<<< orphan*/  wrong_manifest7 ; 
 int /*<<< orphan*/  wrong_manifest8 ; 
 int /*<<< orphan*/  wrong_manifest9 ; 

__attribute__((used)) static void test_create_fail(void)
{
    ACTCTXW actctx;
    HANDLE handle;
    WCHAR path[MAX_PATH];

    MultiByteToWideChar( CP_ACP, 0, "nonexistent.manifest", -1, path, MAX_PATH );
    memset(&actctx, 0, sizeof(ACTCTXW));
    actctx.cbSize = sizeof(ACTCTXW);
    actctx.lpSource = path;

    handle = pCreateActCtxW(&actctx);
    ok(handle == INVALID_HANDLE_VALUE, "handle != INVALID_HANDLE_VALUE\n");
    ok(GetLastError() == ERROR_FILE_NOT_FOUND, "GetLastError == %u\n", GetLastError());

    trace("wrong_manifest1\n");
    test_create_and_fail(wrong_manifest1, NULL, 0, FALSE);
    trace("wrong_manifest2\n");
    test_create_and_fail(wrong_manifest2, NULL, 0, FALSE);
    trace("wrong_manifest3\n");
    test_create_and_fail(wrong_manifest3, NULL, 1, FALSE);
    trace("wrong_manifest4\n");
    test_create_and_fail(wrong_manifest4, NULL, 1, FALSE);
    trace("wrong_manifest5\n");
    test_create_and_fail(wrong_manifest5, NULL, 0, FALSE);
    trace("wrong_manifest6\n");
    test_create_and_fail(wrong_manifest6, NULL, 0, FALSE);
    trace("wrong_manifest7\n");
    test_create_and_fail(wrong_manifest7, NULL, 1, FALSE);
    trace("wrong_manifest8\n");
    test_create_and_fail(wrong_manifest8, NULL, 0, FALSE);
    trace("wrong_manifest9\n");
    test_create_and_fail(wrong_manifest9, NULL, 0, TRUE /* WinXP */);
    trace("wrong_manifest10\n");
    test_create_and_fail(wrong_manifest10, NULL, 0, TRUE /* WinXP */);
    trace("UTF-16 manifest1 without BOM\n");
    test_create_wide_and_fail(manifest1, FALSE );
    trace("manifest2\n");
    test_create_and_fail(manifest2, NULL, 0, FALSE);
    trace("manifest2+depmanifest1\n");
    test_create_and_fail(manifest2, wrong_depmanifest1, 0, FALSE);
}