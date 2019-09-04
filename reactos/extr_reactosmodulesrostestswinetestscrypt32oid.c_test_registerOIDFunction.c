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
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CryptRegisterOIDFunction (int,char*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CryptUnregisterOIDFunction (int,char*,char*) ; 
 scalar_t__ ERROR_ACCESS_DENIED ; 
 scalar_t__ E_INVALIDARG ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  HKEY_LOCAL_MACHINE ; 
 int PKCS_7_ASN_ENCODING ; 
 int /*<<< orphan*/  RegDeleteKeyA (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int X509_ASN_ENCODING ; 
 int /*<<< orphan*/ * bogusDll ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  skip (char*) ; 

__attribute__((used)) static void test_registerOIDFunction(void)
{
    BOOL ret;

    /* oddly, this succeeds under WinXP; the function name key is merely
     * omitted.  This may be a side effect of the registry code, I don't know.
     * I don't check it because I doubt anyone would depend on it.
    ret = CryptRegisterOIDFunction(X509_ASN_ENCODING, NULL,
     "1.2.3.4.5.6.7.8.9.10", bogusDll, NULL);
     */
    /* On windows XP, GetLastError is incorrectly being set with an HRESULT,
     * E_INVALIDARG
     */
    ret = CryptRegisterOIDFunction(X509_ASN_ENCODING, "foo", NULL, bogusDll,
     NULL);
    ok(!ret && GetLastError() == E_INVALIDARG,
     "Expected E_INVALIDARG: %d\n", GetLastError());
    /* This has no effect, but "succeeds" on XP */
    ret = CryptRegisterOIDFunction(X509_ASN_ENCODING, "foo",
     "1.2.3.4.5.6.7.8.9.10", NULL, NULL);
    ok(ret, "Expected pseudo-success, got %d\n", GetLastError());
    SetLastError(0xdeadbeef);
    ret = CryptRegisterOIDFunction(X509_ASN_ENCODING, "CryptDllEncodeObject",
     "1.2.3.4.5.6.7.8.9.10", bogusDll, NULL);
    if (!ret && GetLastError() == ERROR_ACCESS_DENIED)
    {
        skip("Need admin rights\n");
        return;
    }
    ok(ret, "CryptRegisterOIDFunction failed: %d\n", GetLastError());
    ret = CryptUnregisterOIDFunction(X509_ASN_ENCODING, "CryptDllEncodeObject",
     "1.2.3.4.5.6.7.8.9.10");
    ok(ret, "CryptUnregisterOIDFunction failed: %d\n", GetLastError());
    ret = CryptRegisterOIDFunction(X509_ASN_ENCODING, "bogus",
     "1.2.3.4.5.6.7.8.9.10", bogusDll, NULL);
    ok(ret, "CryptRegisterOIDFunction failed: %d\n", GetLastError());
    ret = CryptUnregisterOIDFunction(X509_ASN_ENCODING, "bogus",
     "1.2.3.4.5.6.7.8.9.10");
    ok(ret, "CryptUnregisterOIDFunction failed: %d\n", GetLastError());
    /* Unwanted Cryptography\OID\EncodingType 1\bogus\ will still be there */
    ok(!RegDeleteKeyA(HKEY_LOCAL_MACHINE,
     "SOFTWARE\\Microsoft\\Cryptography\\OID\\EncodingType 1\\bogus"),
     "Could not delete bogus key\n");
    /* Shouldn't have effect but registry keys are created */
    ret = CryptRegisterOIDFunction(PKCS_7_ASN_ENCODING, "CryptDllEncodeObject",
     "1.2.3.4.5.6.7.8.9.10", bogusDll, NULL);
    ok(ret, "CryptRegisterOIDFunction failed: %d\n", GetLastError());
    ret = CryptUnregisterOIDFunction(PKCS_7_ASN_ENCODING, "CryptDllEncodeObject",
     "1.2.3.4.5.6.7.8.9.10");
    ok(ret, "CryptUnregisterOIDFunction failed: %d\n", GetLastError());
    /* Check with bogus encoding type. Registry keys are still created */
    ret = CryptRegisterOIDFunction(0, "CryptDllEncodeObject",
     "1.2.3.4.5.6.7.8.9.10", bogusDll, NULL);
    ok(ret, "CryptRegisterOIDFunction failed: %d\n", GetLastError());
    ret = CryptUnregisterOIDFunction(0, "CryptDllEncodeObject",
     "1.2.3.4.5.6.7.8.9.10");
    ok(ret, "CryptUnregisterOIDFunction failed: %d\n", GetLastError());
    /* Unwanted Cryptography\OID\EncodingType 0\CryptDllEncodeObject\
     * will still be there
     */
    ok(!RegDeleteKeyA(HKEY_LOCAL_MACHINE,
     "SOFTWARE\\Microsoft\\Cryptography\\OID\\EncodingType 0\\CryptDllEncodeObject"),
     "Could not delete CryptDllEncodeObject key\n");
    /* This is written with value 3 verbatim.  Thus, the encoding type isn't
     * (for now) treated as a mask. Registry keys are created.
     */
    ret = CryptRegisterOIDFunction(3, "CryptDllEncodeObject",
     "1.2.3.4.5.6.7.8.9.10", bogusDll, NULL);
    ok(ret, "CryptRegisterOIDFunction failed: %d\n", GetLastError());
    ret = CryptUnregisterOIDFunction(3, "CryptDllEncodeObject",
     "1.2.3.4.5.6.7.8.9.10");
    ok(ret, "CryptUnregisterOIDFunction failed: %d\n", GetLastError());
    /* Unwanted Cryptography\OID\EncodingType 3\CryptDllEncodeObject
     * will still be there.
     */
    ok(!RegDeleteKeyA(HKEY_LOCAL_MACHINE,
     "SOFTWARE\\Microsoft\\Cryptography\\OID\\EncodingType 3\\CryptDllEncodeObject"),
     "Could not delete CryptDllEncodeObject key\n");
    ok(!RegDeleteKeyA(HKEY_LOCAL_MACHINE,
     "SOFTWARE\\Microsoft\\Cryptography\\OID\\EncodingType 3"),
     "Could not delete 'EncodingType 3' key\n");
}