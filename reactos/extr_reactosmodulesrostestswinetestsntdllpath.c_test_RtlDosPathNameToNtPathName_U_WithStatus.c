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
typedef  int /*<<< orphan*/  const WCHAR ;
typedef  int /*<<< orphan*/  UNICODE_STRING ;
typedef  scalar_t__ NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  GetCurrentDirectoryW (int,int /*<<< orphan*/  const*) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  RtlFreeUnicodeString (int /*<<< orphan*/ *) ; 
 scalar_t__ STATUS_OBJECT_NAME_INVALID ; 
 scalar_t__ STATUS_OBJECT_PATH_NOT_FOUND ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 scalar_t__ pRtlDosPathNameToNtPathName_U_WithStatus (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_RtlDosPathNameToNtPathName_U_WithStatus(void)
{
    static const WCHAR emptyW[] = { 0 };
    WCHAR path[MAX_PATH];
    UNICODE_STRING nameW;
    NTSTATUS status;

    if (!pRtlDosPathNameToNtPathName_U_WithStatus)
    {
        win_skip("RtlDosPathNameToNtPathName_U_WithStatus() is not supported.\n");
        return;
    }

    GetCurrentDirectoryW( MAX_PATH, path );

    status = pRtlDosPathNameToNtPathName_U_WithStatus( path, &nameW, NULL, NULL );
    ok(!status, "Failed convert to nt path, %#x.\n", status);

    status = pRtlDosPathNameToNtPathName_U_WithStatus( NULL, &nameW, NULL, NULL );
    ok(status == STATUS_OBJECT_NAME_INVALID || broken(status == STATUS_OBJECT_PATH_NOT_FOUND) /* W2k3 */,
        "Unexpected status %#x.\n", status);

    status = pRtlDosPathNameToNtPathName_U_WithStatus( emptyW, &nameW, NULL, NULL );
    ok(status == STATUS_OBJECT_NAME_INVALID || broken(status == STATUS_OBJECT_PATH_NOT_FOUND) /* W2k3 */,
        "Unexpected status %#x.\n", status);

    RtlFreeUnicodeString( &nameW );
}