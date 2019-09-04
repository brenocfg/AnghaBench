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
typedef  int /*<<< orphan*/  test_string ;
typedef  int /*<<< orphan*/  data ;
typedef  int /*<<< orphan*/  HCRYPTPROV ;
typedef  int /*<<< orphan*/  HCRYPTKEY ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  AT_KEYEXCHANGE ; 
 int /*<<< orphan*/  CALG_RSA_KEYX ; 
 int /*<<< orphan*/  CRYPT_DELETEKEYSET ; 
 int /*<<< orphan*/  CRYPT_EXPORTABLE ; 
 int /*<<< orphan*/  CRYPT_NEWKEYSET ; 
 int CryptAcquireContextA (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int CryptDecrypt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  CryptDestroyKey (int /*<<< orphan*/ ) ; 
 int CryptEncrypt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*,int) ; 
 int CryptExportKey (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 int CryptGenKey (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int CryptGetUserKey (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int CryptImportKey (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CryptReleaseContext (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/ * HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ NTE_BAD_KEY ; 
 scalar_t__ NTE_PERM ; 
 int /*<<< orphan*/  PRIVATEKEYBLOB ; 
 int /*<<< orphan*/  PROV_RSA_FULL ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  szContainer ; 

__attribute__((used)) static void test_rsa_round_trip(void)
{
    static const char test_string[] = "Well this is a fine how-do-you-do.";
    HCRYPTPROV prov;
    HCRYPTKEY signKey, keyExchangeKey;
    BOOL result;
    BYTE data[256], *exportedKey;
    DWORD dataLen, keyLen;

    CryptAcquireContextA(&prov, szContainer, NULL, PROV_RSA_FULL,
     CRYPT_DELETEKEYSET);

    /* Generate a new key... */
    result = CryptAcquireContextA(&prov, szContainer, NULL, PROV_RSA_FULL,
     CRYPT_NEWKEYSET);
    ok(result, "CryptAcquireContextA failed: %08x\n", GetLastError());
    result = CryptGenKey(prov, CALG_RSA_KEYX, CRYPT_EXPORTABLE, &signKey);
    ok(result, "CryptGenKey with CALG_RSA_KEYX failed with error %08x\n", GetLastError());
    result = CryptGetUserKey(prov, AT_KEYEXCHANGE, &keyExchangeKey);
    ok(result, "CryptGetUserKey failed: %08x\n", GetLastError());
    /* encrypt some data with it... */
    memcpy(data, test_string, strlen(test_string) + 1);
    dataLen = strlen(test_string) + 1;
    result = CryptEncrypt(keyExchangeKey, 0, TRUE, 0, data, &dataLen,
                          sizeof(data));
    ok(result || broken(GetLastError() == NTE_BAD_KEY /* Win9x/2000 */) ||
       broken(GetLastError() == NTE_PERM /* NT4 */),
       "CryptEncrypt failed: %08x\n", GetLastError());
    /* export the key... */
    result = CryptExportKey(keyExchangeKey, 0, PRIVATEKEYBLOB, 0, NULL,
                            &keyLen);
    ok(result, "CryptExportKey failed: %08x\n", GetLastError());
    exportedKey = HeapAlloc(GetProcessHeap(), 0, keyLen);
    result = CryptExportKey(keyExchangeKey, 0, PRIVATEKEYBLOB, 0, exportedKey,
                            &keyLen);
    ok(result, "CryptExportKey failed: %08x\n", GetLastError());
    /* destroy the key... */
    CryptDestroyKey(keyExchangeKey);
    CryptDestroyKey(signKey);
    /* import the key again... */
    result = CryptImportKey(prov, exportedKey, keyLen, 0, 0, &keyExchangeKey);
    ok(result, "CryptImportKey failed: %08x\n", GetLastError());
    HeapFree(GetProcessHeap(), 0, exportedKey);
    /* and decrypt the data encrypted with the original key with the imported
     * key.
     */
    result = CryptDecrypt(keyExchangeKey, 0, TRUE, 0, data, &dataLen);
    ok(result || broken(GetLastError() == NTE_BAD_KEY /* Win9x/2000 */) ||
       broken(GetLastError() == NTE_PERM /* NT4 */),
       "CryptDecrypt failed: %08x\n", GetLastError());
    if (result)
    {
        ok(dataLen == sizeof(test_string), "unexpected size %d\n", dataLen);
        ok(!memcmp(data, test_string, sizeof(test_string)), "unexpected value\n");
    }
    CryptDestroyKey(keyExchangeKey);
    CryptReleaseContext(prov, 0);

    CryptAcquireContextA(&prov, szContainer, NULL, PROV_RSA_FULL,
     CRYPT_DELETEKEYSET);
}