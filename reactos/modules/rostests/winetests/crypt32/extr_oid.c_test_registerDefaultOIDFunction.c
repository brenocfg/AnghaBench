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
typedef  scalar_t__ LSTATUS ;
typedef  char* LPSTR ;
typedef  int /*<<< orphan*/  LPBYTE ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  scalar_t__ DWORD ;
typedef  char CHAR ;
typedef  int BOOL ;

/* Variables and functions */
 scalar_t__ ARRAY_SIZE (char*) ; 
 int CryptRegisterDefaultOIDFunction (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *) ; 
 int CryptUnregisterDefaultOIDFunction (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ ERROR_ACCESS_DENIED ; 
 scalar_t__ ERROR_FILE_EXISTS ; 
 scalar_t__ ERROR_FILE_NOT_FOUND ; 
 scalar_t__ E_INVALIDARG ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  HKEY_LOCAL_MACHINE ; 
 int MAX_PATH ; 
 scalar_t__ REG_MULTI_SZ ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 scalar_t__ RegOpenKeyA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ RegQueryValueExA (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  X509_ASN_ENCODING ; 
 int /*<<< orphan*/ * bogus2Dll ; 
 int /*<<< orphan*/ * bogusDll ; 
 int /*<<< orphan*/  lstrcmpiA (char*,char const*) ; 
 scalar_t__ lstrlenA (char*) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  skip (char*) ; 
 int /*<<< orphan*/  sprintf (char*,char const*,int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static void test_registerDefaultOIDFunction(void)
{
    static const char fmt[] =
     "Software\\Microsoft\\Cryptography\\OID\\EncodingType %d\\%s\\DEFAULT";
    static const char func[] = "CertDllOpenStoreProv";
    char buf[MAX_PATH];
    BOOL ret;
    LSTATUS rc;
    HKEY key;

    ret = CryptRegisterDefaultOIDFunction(0, NULL, 0, NULL);
    ok(!ret && GetLastError() == E_INVALIDARG,
     "Expected E_INVALIDARG, got %08x\n", GetLastError());
    /* This succeeds on WinXP, although the bogus entry is unusable.
    ret = CryptRegisterDefaultOIDFunction(0, NULL, 0, bogusDll);
     */
    /* Register one at index 0 */
    SetLastError(0xdeadbeef);
    ret = CryptRegisterDefaultOIDFunction(0, "CertDllOpenStoreProv", 0,
     bogusDll);
    if (!ret && GetLastError() == ERROR_ACCESS_DENIED)
    {
        skip("Need admin rights\n");
        return;
    }
    ok(ret, "CryptRegisterDefaultOIDFunction failed: %08x\n", GetLastError());
    /* Reregistering should fail */
    ret = CryptRegisterDefaultOIDFunction(0, "CertDllOpenStoreProv", 0,
     bogusDll);
    ok(!ret && GetLastError() == ERROR_FILE_EXISTS,
     "Expected ERROR_FILE_EXISTS, got %08x\n", GetLastError());
    /* Registering the same one at index 1 should also fail */
    ret = CryptRegisterDefaultOIDFunction(0, "CertDllOpenStoreProv", 1,
     bogusDll);
    ok(!ret && GetLastError() == ERROR_FILE_EXISTS,
     "Expected ERROR_FILE_EXISTS, got %08x\n", GetLastError());
    /* Registering a different one at index 1 succeeds */
    ret = CryptRegisterDefaultOIDFunction(0, "CertDllOpenStoreProv", 1,
     bogus2Dll);
    ok(ret, "CryptRegisterDefaultOIDFunction failed: %08x\n", GetLastError());
    sprintf(buf, fmt, 0, func);
    rc = RegOpenKeyA(HKEY_LOCAL_MACHINE, buf, &key);
    ok(rc == 0, "Expected key to exist, RegOpenKeyA failed: %d\n", rc);
    if (rc == 0)
    {
        static const CHAR dllA[] = "Dll";
        static const CHAR bogusDll_A[] = "bogus.dll";
        static const CHAR bogus2Dll_A[] = "bogus2.dll";
        CHAR dllBuf[MAX_PATH];
        DWORD type, size;
        LPSTR ptr;

        size = ARRAY_SIZE(dllBuf);
        rc = RegQueryValueExA(key, dllA, NULL, &type, (LPBYTE)dllBuf, &size);
        ok(rc == 0,
         "Expected Dll value to exist, RegQueryValueExA failed: %d\n", rc);
        ok(type == REG_MULTI_SZ, "Expected type REG_MULTI_SZ, got %d\n", type);
        /* bogusDll was registered first, so that should be first */
        ptr = dllBuf;
        ok(!lstrcmpiA(ptr, bogusDll_A), "Unexpected dll\n");
        ptr += lstrlenA(ptr) + 1;
        ok(!lstrcmpiA(ptr, bogus2Dll_A), "Unexpected dll\n");
        RegCloseKey(key);
    }
    /* Unregister both of them */
    ret = CryptUnregisterDefaultOIDFunction(0, "CertDllOpenStoreProv",
     bogusDll);
    ok(ret, "CryptUnregisterDefaultOIDFunction failed: %08x\n",
     GetLastError());
    ret = CryptUnregisterDefaultOIDFunction(0, "CertDllOpenStoreProv",
     bogus2Dll);
    ok(ret, "CryptUnregisterDefaultOIDFunction failed: %08x\n",
     GetLastError());
    /* Now that they're both unregistered, unregistering should fail */
    ret = CryptUnregisterDefaultOIDFunction(0, "CertDllOpenStoreProv",
     bogusDll);
    ok(!ret && GetLastError() == ERROR_FILE_NOT_FOUND,
     "Expected ERROR_FILE_NOT_FOUND, got %d\n", GetLastError());

    /* Repeat a few tests on the normal encoding type */
    ret = CryptRegisterDefaultOIDFunction(X509_ASN_ENCODING,
     "CertDllOpenStoreProv", 0, bogusDll);
    ok(ret, "CryptRegisterDefaultOIDFunction failed\n");
    ret = CryptUnregisterDefaultOIDFunction(X509_ASN_ENCODING,
     "CertDllOpenStoreProv", bogusDll);
    ok(ret, "CryptUnregisterDefaultOIDFunction failed\n");
    ret = CryptUnregisterDefaultOIDFunction(X509_ASN_ENCODING,
     "CertDllOpenStoreProv", bogusDll);
    ok(!ret && GetLastError() == ERROR_FILE_NOT_FOUND,
     "Expected ERROR_FILE_NOT_FOUND, got %08x\n", GetLastError());
}