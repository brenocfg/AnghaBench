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
typedef  int /*<<< orphan*/  LPWSTR ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  CoTaskMemFree (int /*<<< orphan*/ ) ; 
 scalar_t__ IBackgroundCopyFile_GetLocalName (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ S_OK ; 
 scalar_t__ lstrcmpW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  test_file ; 
 int /*<<< orphan*/  test_localFile ; 

__attribute__((used)) static void test_GetLocalName(void)
{
    HRESULT hres;
    LPWSTR name;

    hres = IBackgroundCopyFile_GetLocalName(test_file, &name);
    ok(hres == S_OK, "GetLocalName failed: %08x\n", hres);
    ok(lstrcmpW(name, test_localFile) == 0, "Got incorrect local name\n");
    CoTaskMemFree(name);
}