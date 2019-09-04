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
typedef  int /*<<< orphan*/  SECURITY_DESCRIPTOR ;
typedef  int /*<<< orphan*/  HCRYPTPROV ;
typedef  scalar_t__ DWORD ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  int BOOL ;

/* Variables and functions */
 int CRYPT_DELETEKEYSET ; 
 int CRYPT_MACHINE_KEYSET ; 
 int CRYPT_NEWKEYSET ; 
 int CryptAcquireContextA (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ,int) ; 
 int CryptGetProvParam (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ ) ; 
 int CryptReleaseContext (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ERROR_INSUFFICIENT_BUFFER ; 
 scalar_t__ ERROR_INVALID_PARAMETER ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/ * HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OWNER_SECURITY_INFORMATION ; 
 int /*<<< orphan*/  PP_KEYSET_SEC_DESCR ; 
 int /*<<< orphan*/  PROV_RSA_FULL ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void test_container_sd(void)
{
    HCRYPTPROV prov;
    SECURITY_DESCRIPTOR *sd;
    DWORD len, err;
    BOOL ret;

    ret = CryptAcquireContextA(&prov, "winetest", "Microsoft Enhanced Cryptographic Provider v1.0",
                               PROV_RSA_FULL, CRYPT_MACHINE_KEYSET|CRYPT_NEWKEYSET);
    ok(ret, "got %u\n", GetLastError());

    len = 0;
    SetLastError(0xdeadbeef);
    ret = CryptGetProvParam(prov, PP_KEYSET_SEC_DESCR, NULL, &len, OWNER_SECURITY_INFORMATION);
    err = GetLastError();
    ok(ret, "got %u\n", err);
    ok(err == ERROR_INSUFFICIENT_BUFFER || broken(err == ERROR_INVALID_PARAMETER), "got %u\n", err);
    ok(len, "expected len > 0\n");

    sd = HeapAlloc(GetProcessHeap(), 0, len);
    ret = CryptGetProvParam(prov, PP_KEYSET_SEC_DESCR, (BYTE *)sd, &len, OWNER_SECURITY_INFORMATION);
    ok(ret, "got %u\n", GetLastError());
    HeapFree(GetProcessHeap(), 0, sd);

    ret = CryptReleaseContext(prov, 0);
    ok(ret, "got %u\n", GetLastError());

    ret = CryptAcquireContextA(&prov, "winetest", "Microsoft Enhanced Cryptographic Provider v1.0",
                               PROV_RSA_FULL, CRYPT_MACHINE_KEYSET|CRYPT_DELETEKEYSET);
    ok(ret, "got %u\n", GetLastError());
}