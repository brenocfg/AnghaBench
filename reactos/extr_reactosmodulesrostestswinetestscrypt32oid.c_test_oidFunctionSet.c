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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/ * LPWSTR ;
typedef  scalar_t__ HCRYPTOIDFUNCSET ;
typedef  int /*<<< orphan*/  HCRYPTOIDFUNCADDR ;
typedef  int DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 int CryptGetDefaultOIDDllList (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 int CryptGetOIDFunctionAddress (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void**,int /*<<< orphan*/ *) ; 
 scalar_t__ CryptInitOIDFunctionSet (char*,int) ; 
 scalar_t__ ERROR_FILE_NOT_FOUND ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/ * HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_ASN_ENCODING ; 
 int /*<<< orphan*/  X509_CERT ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void test_oidFunctionSet(void)
{
    HCRYPTOIDFUNCSET set1, set2;
    BOOL ret;
    LPWSTR buf = NULL;
    DWORD size;

    /* This crashes
    set = CryptInitOIDFunctionSet(NULL, 0);
     */

    /* The name doesn't mean much */
    set1 = CryptInitOIDFunctionSet("funky", 0);
    ok(set1 != 0, "CryptInitOIDFunctionSet failed: %08x\n", GetLastError());
    if (set1)
    {
        /* These crash
        ret = CryptGetDefaultOIDDllList(NULL, 0, NULL, NULL);
        ret = CryptGetDefaultOIDDllList(NULL, 0, NULL, &size);
         */
        size = 0;
        ret = CryptGetDefaultOIDDllList(set1, 0, NULL, &size);
        ok(ret, "CryptGetDefaultOIDDllList failed: %08x\n", GetLastError());
        if (ret)
        {
            buf = HeapAlloc(GetProcessHeap(), 0, size * sizeof(WCHAR));
            if (buf)
            {
                ret = CryptGetDefaultOIDDllList(set1, 0, buf, &size);
                ok(ret, "CryptGetDefaultOIDDllList failed: %08x\n",
                 GetLastError());
                ok(!*buf, "Expected empty DLL list\n");
                HeapFree(GetProcessHeap(), 0, buf);
            }
        }
    }

    /* MSDN says flags must be 0, but it's not checked */
    set1 = CryptInitOIDFunctionSet("", 1);
    ok(set1 != 0, "CryptInitOIDFunctionSet failed: %08x\n", GetLastError());
    set2 = CryptInitOIDFunctionSet("", 0);
    ok(set2 != 0, "CryptInitOIDFunctionSet failed: %08x\n", GetLastError());
    /* There isn't a free function, so there must be only one set per name to
     * limit leaks.  (I guess the sets are freed when crypt32 is unloaded.)
     */
    ok(set1 == set2, "Expected identical sets\n");
    if (set1)
    {
        /* The empty name function set used here seems to correspond to
         * DEFAULT.
         */
    }

    /* There's no installed function for a built-in encoding. */
    set1 = CryptInitOIDFunctionSet("CryptDllEncodeObject", 0);
    ok(set1 != 0, "CryptInitOIDFunctionSet failed: %08x\n", GetLastError());
    if (set1)
    {
        void *funcAddr;
        HCRYPTOIDFUNCADDR hFuncAddr;

        ret = CryptGetOIDFunctionAddress(set1, X509_ASN_ENCODING, X509_CERT, 0,
         &funcAddr, &hFuncAddr);
        ok((!ret && GetLastError() == ERROR_FILE_NOT_FOUND) ||
         broken(ret) /* some Win98 */,
         "Expected ERROR_FILE_NOT_FOUND, got %08x\n", GetLastError());
    }
}