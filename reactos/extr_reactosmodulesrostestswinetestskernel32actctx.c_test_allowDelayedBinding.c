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
typedef  scalar_t__ HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteFileA (char*) ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  create_manifest_file (char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  manifest5 ; 
 int /*<<< orphan*/  pReleaseActCtx (scalar_t__) ; 
 int /*<<< orphan*/  skip (char*) ; 
 int /*<<< orphan*/  test_basic_info (scalar_t__,int) ; 
 scalar_t__ test_create (char*) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_allowDelayedBinding(void)
{
    HANDLE handle;

    if (!create_manifest_file("test5.manifest", manifest5, -1, NULL, NULL)) {
        skip("Could not create manifest file\n");
        return;
    }

    handle = test_create("test5.manifest");
    if (handle == INVALID_HANDLE_VALUE) {
        win_skip("allowDelayedBinding attribute is not supported.\n");
        return;
    }

    DeleteFileA("test5.manifest");
    DeleteFileA("testdep.manifest");
    if (handle != INVALID_HANDLE_VALUE) {
        test_basic_info(handle, __LINE__);
        pReleaseActCtx(handle);
    }
}