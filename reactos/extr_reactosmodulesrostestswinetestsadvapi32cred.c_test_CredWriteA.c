#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* TargetName; char* Comment; char* UserName; void* Type; int /*<<< orphan*/  Persist; int /*<<< orphan*/ * TargetAlias; int /*<<< orphan*/ * Attributes; scalar_t__ AttributeCount; int /*<<< orphan*/ * CredentialBlob; scalar_t__ CredentialBlobSize; scalar_t__ Flags; } ;
typedef  TYPE_1__ CREDENTIALA ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CRED_PERSIST_ENTERPRISE ; 
 int /*<<< orphan*/  CRED_PERSIST_LOCAL_MACHINE ; 
 int /*<<< orphan*/  CRED_PERSIST_SESSION ; 
 void* CRED_TYPE_DOMAIN_PASSWORD ; 
 void* CRED_TYPE_GENERIC ; 
 scalar_t__ ERROR_BAD_USERNAME ; 
 scalar_t__ ERROR_INVALID_PARAMETER ; 
 scalar_t__ ERROR_IO_PENDING ; 
 scalar_t__ ERROR_NO_SUCH_LOGON_SESSION ; 
 scalar_t__ ERROR_SUCCESS ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 scalar_t__ TEST_TARGET_NAME ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int pCredDeleteA (scalar_t__,void*,int /*<<< orphan*/ ) ; 
 int pCredWriteA (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_CredWriteA(void)
{
    CREDENTIALA new_cred;
    BOOL ret;

    SetLastError(0xdeadbeef);
    ret = pCredWriteA(NULL, 0);
    ok(!ret && GetLastError() == ERROR_INVALID_PARAMETER,
        "CredWriteA should have failed with ERROR_INVALID_PARAMETER instead of %d\n",
        GetLastError());

    new_cred.Flags = 0;
    new_cred.Type = CRED_TYPE_GENERIC;
    new_cred.TargetName = NULL;
    new_cred.Comment = (char *)"Comment";
    new_cred.CredentialBlobSize = 0;
    new_cred.CredentialBlob = NULL;
    new_cred.Persist = CRED_PERSIST_ENTERPRISE;
    new_cred.AttributeCount = 0;
    new_cred.Attributes = NULL;
    new_cred.TargetAlias = NULL;
    new_cred.UserName = (char *)"winetest";

    SetLastError(0xdeadbeef);
    ret = pCredWriteA(&new_cred, 0);
    ok(!ret && GetLastError() == ERROR_INVALID_PARAMETER,
        "CredWriteA should have failed with ERROR_INVALID_PARAMETER instead of %d\n",
        GetLastError());

    new_cred.TargetName = (char *)TEST_TARGET_NAME;
    new_cred.Type = CRED_TYPE_DOMAIN_PASSWORD;

    SetLastError(0xdeadbeef);
    ret = pCredWriteA(&new_cred, 0);
    if (ret)
    {
        ok(GetLastError() == ERROR_SUCCESS ||
           GetLastError() == ERROR_IO_PENDING, /* Vista */
           "Expected ERROR_IO_PENDING, got %d\n", GetLastError());
    }
    else
    {
        ok(GetLastError() == ERROR_BAD_USERNAME ||
           GetLastError() == ERROR_NO_SUCH_LOGON_SESSION, /* Vista */
           "CredWrite with username without domain should return ERROR_BAD_USERNAME"
           "or ERROR_NO_SUCH_LOGON_SESSION not %d\n", GetLastError());
    }

    new_cred.UserName = NULL;
    SetLastError(0xdeadbeef);
    ret = pCredWriteA(&new_cred, 0);
    ok(!ret && GetLastError() == ERROR_BAD_USERNAME,
        "CredWriteA with NULL username should have failed with ERROR_BAD_USERNAME instead of %d\n",
        GetLastError());

    new_cred.UserName = (char *)"winetest";
    new_cred.Persist = CRED_PERSIST_LOCAL_MACHINE;
    SetLastError(0xdeadbeef);
    ret = pCredWriteA(&new_cred, 0);
    ok(ret || broken(!ret), "CredWriteA failed with error %u\n", GetLastError());
    if (ret)
    {
        ret = pCredDeleteA(TEST_TARGET_NAME, CRED_TYPE_DOMAIN_PASSWORD, 0);
        ok(ret, "CredDeleteA failed with error %u\n", GetLastError());
    }
    new_cred.Type = CRED_TYPE_GENERIC;
    SetLastError(0xdeadbeef);
    ret = pCredWriteA(&new_cred, 0);
    ok(ret || broken(!ret), "CredWriteA failed with error %u\n", GetLastError());
    if  (ret)
    {
        ret = pCredDeleteA(TEST_TARGET_NAME, CRED_TYPE_GENERIC, 0);
        ok(ret, "CredDeleteA failed with error %u\n", GetLastError());
    }
    new_cred.Persist = CRED_PERSIST_SESSION;
    ret = pCredWriteA(&new_cred, 0);
    ok(ret, "CredWriteA failed with error %u\n", GetLastError());

    ret = pCredDeleteA(TEST_TARGET_NAME, CRED_TYPE_GENERIC, 0);
    ok(ret, "CredDeleteA failed with error %u\n", GetLastError());

    new_cred.Type = CRED_TYPE_DOMAIN_PASSWORD;
    SetLastError(0xdeadbeef);
    ret = pCredWriteA(&new_cred, 0);
    ok(ret || broken(!ret), "CredWriteA failed with error %u\n", GetLastError());
    if (ret)
    {
        ret = pCredDeleteA(TEST_TARGET_NAME, CRED_TYPE_DOMAIN_PASSWORD, 0);
        ok(ret, "CredDeleteA failed with error %u\n", GetLastError());
    }
    new_cred.UserName = NULL;
    SetLastError(0xdeadbeef);
    ret = pCredWriteA(&new_cred, 0);
    ok(!ret, "CredWriteA succeeded\n");
    ok(GetLastError() == ERROR_BAD_USERNAME, "got %u\n", GetLastError());
}