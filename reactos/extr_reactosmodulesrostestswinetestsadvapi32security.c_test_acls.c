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
typedef  int /*<<< orphan*/  buffer ;
typedef  int /*<<< orphan*/  PACL ;
typedef  int BOOL ;
typedef  int /*<<< orphan*/  ACL ;

/* Variables and functions */
 int ACL_REVISION ; 
 int ACL_REVISION1 ; 
 int ACL_REVISION2 ; 
 int ACL_REVISION3 ; 
 int ACL_REVISION4 ; 
 scalar_t__ ERROR_CALL_NOT_IMPLEMENTED ; 
 scalar_t__ ERROR_INSUFFICIENT_BUFFER ; 
 scalar_t__ ERROR_INVALID_PARAMETER ; 
 scalar_t__ GetLastError () ; 
 int InitializeAcl (int /*<<< orphan*/ ,int,int) ; 
 int IsValidAcl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_acls(void)
{
    char buffer[256];
    PACL pAcl = (PACL)buffer;
    BOOL ret;

    SetLastError(0xdeadbeef);
    ret = InitializeAcl(pAcl, sizeof(ACL) - 1, ACL_REVISION);
    if (!ret && GetLastError() == ERROR_CALL_NOT_IMPLEMENTED)
    {
        win_skip("InitializeAcl is not implemented\n");
        return;
    }

    ok(!ret && GetLastError() == ERROR_INSUFFICIENT_BUFFER, "InitializeAcl with too small a buffer should have failed with ERROR_INSUFFICIENT_BUFFER instead of %d\n", GetLastError());

    SetLastError(0xdeadbeef);
    ret = InitializeAcl(pAcl, 0xffffffff, ACL_REVISION);
    ok(!ret && GetLastError() == ERROR_INVALID_PARAMETER, "InitializeAcl with too large a buffer should have failed with ERROR_INVALID_PARAMETER instead of %d\n", GetLastError());

    SetLastError(0xdeadbeef);
    ret = InitializeAcl(pAcl, sizeof(buffer), ACL_REVISION1);
    ok(!ret && GetLastError() == ERROR_INVALID_PARAMETER, "InitializeAcl(ACL_REVISION1) should have failed with ERROR_INVALID_PARAMETER instead of %d\n", GetLastError());

    ret = InitializeAcl(pAcl, sizeof(buffer), ACL_REVISION2);
    ok(ret, "InitializeAcl(ACL_REVISION2) failed with error %d\n", GetLastError());

    ret = IsValidAcl(pAcl);
    ok(ret, "IsValidAcl failed with error %d\n", GetLastError());

    ret = InitializeAcl(pAcl, sizeof(buffer), ACL_REVISION3);
    ok(ret, "InitializeAcl(ACL_REVISION3) failed with error %d\n", GetLastError());

    ret = IsValidAcl(pAcl);
    ok(ret, "IsValidAcl failed with error %d\n", GetLastError());

    SetLastError(0xdeadbeef);
    ret = InitializeAcl(pAcl, sizeof(buffer), ACL_REVISION4);
    if (GetLastError() != ERROR_INVALID_PARAMETER)
    {
        ok(ret, "InitializeAcl(ACL_REVISION4) failed with error %d\n", GetLastError());

        ret = IsValidAcl(pAcl);
        ok(ret, "IsValidAcl failed with error %d\n", GetLastError());
    }
    else
        win_skip("ACL_REVISION4 is not implemented on NT4\n");

    SetLastError(0xdeadbeef);
    ret = InitializeAcl(pAcl, sizeof(buffer), -1);
    ok(!ret && GetLastError() == ERROR_INVALID_PARAMETER, "InitializeAcl(-1) failed with error %d\n", GetLastError());
}