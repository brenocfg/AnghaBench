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
typedef  int /*<<< orphan*/  HCRYPTKEY ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  AT_KEYEXCHANGE ; 
 int CRYPT_DECRYPT ; 
 int CRYPT_ENCRYPT ; 
 int CRYPT_EXPORT ; 
 int /*<<< orphan*/  CRYPT_EXPORTABLE ; 
 int CRYPT_MAC ; 
 int CRYPT_READ ; 
 int CRYPT_WRITE ; 
 int /*<<< orphan*/  CryptDestroyKey (int /*<<< orphan*/ ) ; 
 int CryptExportKey (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 int CryptGetKeyParam (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ) ; 
 int CryptGetUserKey (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int CryptSetKeyParam (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int GetLastError () ; 
 int /*<<< orphan*/  KP_PERMISSIONS ; 
 int NTE_BAD_DATA ; 
 int NTE_BAD_FLAGS ; 
 int /*<<< orphan*/  PRIVATEKEYBLOB ; 
 int /*<<< orphan*/  PUBLICKEYBLOB ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  clean_up_base_environment () ; 
 int /*<<< orphan*/  hProv ; 
 int /*<<< orphan*/  init_base_environment (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 

__attribute__((used)) static void test_key_permissions(void)
{
    HCRYPTKEY hKey1, hKey2;
    DWORD dwVal, dwLen;
    BOOL result;

    /* Create keys that are exportable */
    if (!init_base_environment(NULL, CRYPT_EXPORTABLE))
        return;

    result = CryptGetUserKey(hProv, AT_KEYEXCHANGE, &hKey1);
    ok (result, "%08x\n", GetLastError());
    if (!result) return;

    dwVal = 0xdeadbeef;
    dwLen = sizeof(DWORD);
    result = CryptGetKeyParam(hKey1, KP_PERMISSIONS, (BYTE*)&dwVal, &dwLen, 0);
    ok(result, "%08x\n", GetLastError());
    ok(dwVal ==
        (CRYPT_MAC|CRYPT_WRITE|CRYPT_READ|CRYPT_EXPORT|CRYPT_DECRYPT|CRYPT_ENCRYPT) ||
        broken(dwVal == 0xffffffff), /* Win9x/NT4 */
        "expected CRYPT_MAC|CRYPT_WRITE|CRYPT_READ|CRYPT_EXPORT|CRYPT_DECRYPT|CRYPT_ENCRYPT,"
        " got %08x\n", dwVal);

    /* The key exchange key's public key may be exported.. */
    result = CryptExportKey(hKey1, 0, PUBLICKEYBLOB, 0, NULL, &dwLen);
    ok(result, "%08x\n", GetLastError());
    /* and its private key may be too. */
    result = CryptExportKey(hKey1, 0, PRIVATEKEYBLOB, 0, NULL, &dwLen);
    ok(result, "%08x\n", GetLastError());
    /* Turning off the key's export permissions is "allowed".. */
    dwVal &= ~CRYPT_EXPORT;
    result = CryptSetKeyParam(hKey1, KP_PERMISSIONS, (BYTE *)&dwVal, 0);
    ok(result ||
        broken(!result && GetLastError() == NTE_BAD_DATA) || /* W2K */
        broken(!result && GetLastError() == NTE_BAD_FLAGS), /* Win9x/WinME/NT4 */
        "%08x\n", GetLastError());
    /* but it has no effect. */
    dwVal = 0xdeadbeef;
    dwLen = sizeof(DWORD);
    result = CryptGetKeyParam(hKey1, KP_PERMISSIONS, (BYTE*)&dwVal, &dwLen, 0);
    ok(result, "%08x\n", GetLastError());
    ok(dwVal ==
        (CRYPT_MAC|CRYPT_WRITE|CRYPT_READ|CRYPT_EXPORT|CRYPT_DECRYPT|CRYPT_ENCRYPT) ||
        broken(dwVal == 0xffffffff), /* Win9x/NT4 */
        "expected CRYPT_MAC|CRYPT_WRITE|CRYPT_READ|CRYPT_EXPORT|CRYPT_DECRYPT|CRYPT_ENCRYPT,"
        " got %08x\n", dwVal);
    /* Thus, changing the export flag of the key doesn't affect whether the key
     * may be exported.
     */
    result = CryptExportKey(hKey1, 0, PRIVATEKEYBLOB, 0, NULL, &dwLen);
    ok(result, "%08x\n", GetLastError());

    result = CryptGetUserKey(hProv, AT_KEYEXCHANGE, &hKey2);
    ok (result, "%08x\n", GetLastError());

    /* A subsequent get of the same key, into a different handle, also doesn't
     * show that the permissions have been changed.
     */
    dwVal = 0xdeadbeef;
    dwLen = sizeof(DWORD);
    result = CryptGetKeyParam(hKey2, KP_PERMISSIONS, (BYTE*)&dwVal, &dwLen, 0);
    ok(result, "%08x\n", GetLastError());
    ok(dwVal ==
        (CRYPT_MAC|CRYPT_WRITE|CRYPT_READ|CRYPT_EXPORT|CRYPT_DECRYPT|CRYPT_ENCRYPT) ||
        broken(dwVal == 0xffffffff), /* Win9x/NT4 */
        "expected CRYPT_MAC|CRYPT_WRITE|CRYPT_READ|CRYPT_EXPORT|CRYPT_DECRYPT|CRYPT_ENCRYPT,"
        " got %08x\n", dwVal);

    CryptDestroyKey(hKey2);
    CryptDestroyKey(hKey1);

    clean_up_base_environment();
}