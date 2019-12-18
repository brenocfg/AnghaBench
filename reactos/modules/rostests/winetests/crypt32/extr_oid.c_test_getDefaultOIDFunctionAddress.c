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
typedef  scalar_t__ HCRYPTOIDFUNCSET ;
typedef  scalar_t__ HCRYPTOIDFUNCADDR ;
typedef  int BOOL ;

/* Variables and functions */
 int CryptGetDefaultOIDFunctionAddress (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void**,scalar_t__*) ; 
 scalar_t__ CryptInitOIDFunctionSet (char*,int /*<<< orphan*/ ) ; 
 int CryptRegisterDefaultOIDFunction (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CryptUnregisterDefaultOIDFunction (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ ERROR_ACCESS_DENIED ; 
 scalar_t__ ERROR_FILE_NOT_FOUND ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  X509_ASN_ENCODING ; 
 int /*<<< orphan*/  bogusDll ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  skip (char*) ; 

__attribute__((used)) static void test_getDefaultOIDFunctionAddress(void)
{
    BOOL ret;
    HCRYPTOIDFUNCSET set;
    void *funcAddr;
    HCRYPTOIDFUNCADDR hFuncAddr;

    /* Crash
    ret = CryptGetDefaultOIDFunctionAddress(0, 0, NULL, 0, NULL, NULL);
    ret = CryptGetDefaultOIDFunctionAddress(0, 0, NULL, 0, &funcAddr, NULL);
    ret = CryptGetDefaultOIDFunctionAddress(0, 0, NULL, 0, NULL, &hFuncAddr);
    ret = CryptGetDefaultOIDFunctionAddress(0, 0, NULL, 0, &funcAddr,
     &hFuncAddr);
     */
    set = CryptInitOIDFunctionSet("CertDllOpenStoreProv", 0);
    ok(set != 0, "CryptInitOIDFunctionSet failed: %d\n", GetLastError());
    /* This crashes if hFuncAddr is not 0 to begin with */
    hFuncAddr = 0;
    ret = CryptGetDefaultOIDFunctionAddress(set, 0, NULL, 0, &funcAddr,
     &hFuncAddr);
    ok(!ret && GetLastError() == ERROR_FILE_NOT_FOUND,
     "Expected ERROR_FILE_NOT_FOUND, got %d\n", GetLastError());
    /* This fails with the normal encoding too, so built-in functions aren't
     * returned.
     */
    ret = CryptGetDefaultOIDFunctionAddress(set, X509_ASN_ENCODING, NULL, 0,
     &funcAddr, &hFuncAddr);
    ok(!ret && GetLastError() == ERROR_FILE_NOT_FOUND,
     "Expected ERROR_FILE_NOT_FOUND, got %d\n", GetLastError());

    /* Even with a registered dll, this fails (since the dll doesn't exist) */
    SetLastError(0xdeadbeef);
    ret = CryptRegisterDefaultOIDFunction(0, "CertDllOpenStoreProv", 0,
     bogusDll);
    if (!ret && GetLastError() == ERROR_ACCESS_DENIED)
        skip("Need admin rights\n");
    else
        ok(ret, "CryptRegisterDefaultOIDFunction failed: %08x\n", GetLastError());
    ret = CryptGetDefaultOIDFunctionAddress(set, 0, NULL, 0, &funcAddr,
     &hFuncAddr);
    ok(!ret && GetLastError() == ERROR_FILE_NOT_FOUND,
     "Expected ERROR_FILE_NOT_FOUND, got %d\n", GetLastError());
    CryptUnregisterDefaultOIDFunction(0, "CertDllOpenStoreProv", bogusDll);
}