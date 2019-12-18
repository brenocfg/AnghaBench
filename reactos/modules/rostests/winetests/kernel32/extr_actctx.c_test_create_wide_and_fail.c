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
typedef  int /*<<< orphan*/  BOOL ;
typedef  TYPE_1__ ACTCTXW ;

/* Variables and functions */
 int /*<<< orphan*/  CP_ACP ; 
 int /*<<< orphan*/  DeleteFileA (char*) ; 
 scalar_t__ ERROR_SXS_CANT_GEN_ACTCTX ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ GetLastError () ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  create_wide_manifest (char*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 scalar_t__ pCreateActCtxW (TYPE_1__*) ; 
 int /*<<< orphan*/  pReleaseActCtx (scalar_t__) ; 

__attribute__((used)) static void test_create_wide_and_fail(const char *manifest, BOOL fBOM)
{
    ACTCTXW actctx;
    HANDLE handle;
    WCHAR path[MAX_PATH];

    MultiByteToWideChar( CP_ACP, 0, "bad.manifest", -1, path, MAX_PATH );
    memset(&actctx, 0, sizeof(ACTCTXW));
    actctx.cbSize = sizeof(ACTCTXW);
    actctx.lpSource = path;

    create_wide_manifest("bad.manifest", manifest, fBOM, FALSE);
    handle = pCreateActCtxW(&actctx);
    ok(handle == INVALID_HANDLE_VALUE, "handle != INVALID_HANDLE_VALUE\n");
    ok(GetLastError() == ERROR_SXS_CANT_GEN_ACTCTX, "GetLastError == %u\n", GetLastError());

    if (handle != INVALID_HANDLE_VALUE) pReleaseActCtx( handle );
    DeleteFileA("bad.manifest");
}