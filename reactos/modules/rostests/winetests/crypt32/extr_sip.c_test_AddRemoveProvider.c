#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  char WCHAR ;
struct TYPE_7__ {int member_0; int member_1; int member_2; int member_3; int member_4; int member_5; int member_6; int member_7; } ;
struct TYPE_9__ {int member_0; int member_1; int member_2; TYPE_1__ member_3; } ;
struct TYPE_8__ {int cbStruct; char* pwszDLLFileName; char* pwszGetFuncName; char* pwszPutFuncName; char* pwszCreateFuncName; char* pwszVerifyFuncName; char* pwszRemoveFuncName; char* pwszIsFunctionNameFmt2; char* pwszIsFunctionName; char* pwszGetCapFuncName; TYPE_3__* pgSubject; } ;
typedef  TYPE_2__ SIP_ADD_NEWPROVIDER ;
typedef  TYPE_3__ GUID ;
typedef  int BOOL ;

/* Variables and functions */
 int CryptSIPAddProvider (TYPE_2__*) ; 
 int CryptSIPRemoveProvider (TYPE_3__*) ; 
 scalar_t__ ERROR_ACCESS_DENIED ; 
 scalar_t__ ERROR_FILE_NOT_FOUND ; 
 scalar_t__ ERROR_INVALID_PARAMETER ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  skip (char*) ; 

__attribute__((used)) static void test_AddRemoveProvider(void)
{
    BOOL ret;
    SIP_ADD_NEWPROVIDER newprov;
    GUID actionid = { 0xdeadbe, 0xefde, 0xadbe, { 0xef,0xde,0xad,0xbe,0xef,0xde,0xad,0xbe }};
    static WCHAR dummydll[]      = {'d','e','a','d','b','e','e','f','.','d','l','l',0 };
    static WCHAR dummyfunction[] = {'d','u','m','m','y','f','u','n','c','t','i','o','n',0 };

    /* NULL check */
    SetLastError(0xdeadbeef);
    ret = CryptSIPRemoveProvider(NULL);
    ok (!ret, "Expected CryptSIPRemoveProvider to fail.\n");
    ok (GetLastError() == ERROR_INVALID_PARAMETER,
        "Expected ERROR_INVALID_PARAMETER, got %d.\n", GetLastError());

    /* nonexistent provider should result in a registry error */
    SetLastError(0xdeadbeef);
    ret = CryptSIPRemoveProvider(&actionid);
    if (!ret && GetLastError() == ERROR_ACCESS_DENIED)
    {
        /* Apparently the needed rights are checked before the existence of the provider */
        skip("Need admin rights\n");
    }
    else
    {
        /* On some Win98 systems, CryptSIPRemoveProvider always succeeds if
         * the arguments are correct, whether or not the registry key is
         * present, so don't test ret, just check the last error if it does
         * return FALSE.
         */
        if (!ret)
            ok (GetLastError() == ERROR_FILE_NOT_FOUND,
                "Expected ERROR_FILE_NOT_FOUND, got %d.\n", GetLastError());
    }

    /* Everything OK, pwszIsFunctionName and pwszIsFunctionNameFmt2 are left NULL
     * as allowed */

    memset(&newprov, 0, sizeof(SIP_ADD_NEWPROVIDER));
    newprov.cbStruct = sizeof(SIP_ADD_NEWPROVIDER);
    newprov.pgSubject = &actionid;
    newprov.pwszDLLFileName = dummydll;
    newprov.pwszGetFuncName = dummyfunction;
    newprov.pwszPutFuncName = dummyfunction;
    newprov.pwszCreateFuncName = dummyfunction;
    newprov.pwszVerifyFuncName = dummyfunction;
    newprov.pwszRemoveFuncName = dummyfunction;
    SetLastError(0xdeadbeef);
    ret = CryptSIPAddProvider(&newprov);
    if (!ret && GetLastError() == ERROR_ACCESS_DENIED)
    {
        skip("Need admin rights\n");
        return;
    }
    ok ( ret, "CryptSIPAddProvider should have succeeded, last error %d\n", GetLastError());

    /* Dummy provider will be deleted, but the function still fails because
     * pwszIsFunctionName and pwszIsFunctionNameFmt2 are not present in the
     * registry.
     */
    SetLastError(0xdeadbeef);
    ret = CryptSIPRemoveProvider(&actionid);
    /* On some Win98 systems, CryptSIPRemoveProvider always succeeds if
     * the arguments are correct, whether or not the registry key is
     * present, so don't test ret, just check the last error if it does
     * return FALSE.
     */
    if (!ret)
        ok (GetLastError() == ERROR_FILE_NOT_FOUND,
            "Expected ERROR_FILE_NOT_FOUND, got %d.\n", GetLastError());

    /* Everything OK */
    memset(&newprov, 0, sizeof(SIP_ADD_NEWPROVIDER));
    newprov.cbStruct = sizeof(SIP_ADD_NEWPROVIDER);
    newprov.pgSubject = &actionid;
    newprov.pwszDLLFileName = dummydll;
    newprov.pwszGetFuncName = dummyfunction;
    newprov.pwszPutFuncName = dummyfunction;
    newprov.pwszCreateFuncName = dummyfunction;
    newprov.pwszVerifyFuncName = dummyfunction;
    newprov.pwszRemoveFuncName = dummyfunction;
    newprov.pwszIsFunctionNameFmt2 = dummyfunction;
    newprov.pwszIsFunctionName = dummyfunction;
    /* If GetCapFuncName set to NULL, then CryptSIPRemoveProvider fails on win 8 */
    newprov.pwszGetCapFuncName = dummyfunction;

    SetLastError(0xdeadbeef);
    ret = CryptSIPAddProvider(&newprov);
    ok ( ret, "CryptSIPAddProvider should have succeeded, last error %d\n", GetLastError());

    /* Dummy provider should be deleted */
    SetLastError(0xdeadbeef);
    ret = CryptSIPRemoveProvider(&actionid);
    ok ( ret, "CryptSIPRemoveProvider should have succeeded, last error %d\n", GetLastError());
}