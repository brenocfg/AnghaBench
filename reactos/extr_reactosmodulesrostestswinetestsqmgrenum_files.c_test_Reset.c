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
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 scalar_t__ IEnumBackgroundCopyFiles_Reset (int /*<<< orphan*/ ) ; 
 scalar_t__ IEnumBackgroundCopyFiles_Skip (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  test_enumFiles ; 
 int /*<<< orphan*/  test_fileCount ; 

__attribute__((used)) static void test_Reset(void)
{
    HRESULT hres;

    hres = IEnumBackgroundCopyFiles_Skip(test_enumFiles, test_fileCount);
    ok(hres == S_OK, "Skip failed: %08x\n", hres);
    hres = IEnumBackgroundCopyFiles_Reset(test_enumFiles);
    ok(hres == S_OK, "Reset failed: %08x\n", hres);
    hres = IEnumBackgroundCopyFiles_Skip(test_enumFiles, test_fileCount);
    ok(hres == S_OK, "Reset failed: %08x\n", hres);
}