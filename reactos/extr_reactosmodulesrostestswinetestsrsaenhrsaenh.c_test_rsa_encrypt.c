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
typedef  int /*<<< orphan*/  abData ;
typedef  int /*<<< orphan*/  HCRYPTKEY ;
typedef  int DWORD ;
typedef  char BYTE ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  AT_KEYEXCHANGE ; 
 int /*<<< orphan*/  AT_SIGNATURE ; 
 int CRYPT_DECRYPT ; 
 int CRYPT_ENCRYPT ; 
 int CRYPT_EXPORT ; 
 int CRYPT_MAC ; 
 int /*<<< orphan*/  CRYPT_OAEP ; 
 int CRYPT_READ ; 
 int CRYPT_WRITE ; 
 int CryptDecrypt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,char*,int*) ; 
 int /*<<< orphan*/  CryptDestroyKey (int /*<<< orphan*/ ) ; 
 int CryptEncrypt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,char*,int*,int) ; 
 int CryptExportKey (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 int CryptGetKeyParam (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int*,int /*<<< orphan*/ ) ; 
 int CryptGetUserKey (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int CryptSetKeyParam (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENHANCED_PROV ; 
 int ERROR_MORE_DATA ; 
 int ERROR_NO_TOKEN ; 
 int GetLastError () ; 
 int /*<<< orphan*/  KP_PERMISSIONS ; 
 int /*<<< orphan*/  KP_SALT ; 
 int NTE_BAD_DATA ; 
 int NTE_BAD_FLAGS ; 
 int NTE_BAD_KEY ; 
 int NTE_BAD_KEY_STATE ; 
 int NTE_BAD_LEN ; 
 int NTE_DOUBLE_ENCRYPT ; 
 int NTE_NOT_FOUND ; 
 int /*<<< orphan*/  PRIVATEKEYBLOB ; 
 int /*<<< orphan*/  PUBLICKEYBLOB ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int TRUE ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  hProv ; 
 int /*<<< orphan*/  memcmp (char*,char*,int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  ok (int,char*,int,...) ; 

__attribute__((used)) static void test_rsa_encrypt(void)
{
    HCRYPTKEY hRSAKey;
    BYTE abData[2048] = "Wine rocks!";
    BOOL result;
    DWORD dwVal, dwLen;
    DWORD err;

    /* It is allowed to use the key exchange key for encryption/decryption */
    result = CryptGetUserKey(hProv, AT_KEYEXCHANGE, &hRSAKey);
    ok (result, "%08x\n", GetLastError());
    if (!result) return;

    dwLen = 12;
    result = CryptEncrypt(hRSAKey, 0, TRUE, 0, NULL, &dwLen, (DWORD)sizeof(abData));
    if(!ENHANCED_PROV && !result && GetLastError() == NTE_BAD_KEY)
    {
        CryptDestroyKey(hRSAKey);
        return;
    }
    ok(result, "CryptEncrypt failed: %08x\n", GetLastError());
    ok(dwLen == 128, "Unexpected length %d\n", dwLen);
    /* PKCS1 V1.5 */
    dwLen = 12;
    result = CryptEncrypt(hRSAKey, 0, TRUE, 0, abData, &dwLen, (DWORD)sizeof(abData));
    ok (result, "%08x\n", GetLastError());
    if (!result) return;

    result = CryptDecrypt(hRSAKey, 0, TRUE, 0, abData, &dwLen);
    ok (result && dwLen == 12 && !memcmp(abData, "Wine rocks!", 12), "%08x\n", GetLastError());

    /* OAEP, RFC 8017 PKCS #1 V2.2 */
    /* Test minimal buffer length requirement */
    dwLen = 1;
    SetLastError(0xdeadbeef);
    result = CryptEncrypt(hRSAKey, 0, TRUE, CRYPT_OAEP, abData, &dwLen, 20 * 2 + 2);
    err = GetLastError();
    ok(!result && err == ERROR_MORE_DATA, "%08x\n", err);

    /* Test data length limit */
    dwLen = sizeof(abData) - (20 * 2 + 2) + 1;
    result = CryptEncrypt(hRSAKey, 0, TRUE, CRYPT_OAEP, abData, &dwLen, (DWORD)sizeof(abData));
    err = GetLastError();
    ok(!result && err == NTE_BAD_LEN, "%08x\n", err);

    /* Test malformed data */
    dwLen = 12;
    SetLastError(0xdeadbeef);
    memcpy(abData, "Wine rocks!", dwLen);
    result = CryptDecrypt(hRSAKey, 0, TRUE, CRYPT_OAEP, abData, &dwLen);
    err = GetLastError();
    /* NTE_DOUBLE_ENCRYPT on xp or 2003 */
    ok(!result && (err == NTE_BAD_DATA || broken(err == NTE_DOUBLE_ENCRYPT)), "%08x\n", err);

    /* Test decrypt with insufficient buffer */
    dwLen = 12;
    SetLastError(0xdeadbeef);
    memcpy(abData, "Wine rocks!", 12);
    result = CryptEncrypt(hRSAKey, 0, TRUE, CRYPT_OAEP, abData, &dwLen, (DWORD)sizeof(abData));
    ok(result, "%08x\n", GetLastError());
    dwLen = 11;
    SetLastError(0xdeadbeef);
    result = CryptDecrypt(hRSAKey, 0, TRUE, CRYPT_OAEP, abData, &dwLen);
    err = GetLastError();
    /* broken on xp or 2003 */
    ok((!result && dwLen == 11 && err == NTE_BAD_DATA) || broken(result == TRUE && dwLen == 12 && err == ERROR_NO_TOKEN),
       "%08x %d %08x\n", result, dwLen, err);

    /* Test normal encryption and decryption */
    dwLen = 12;
    memcpy(abData, "Wine rocks!", dwLen);
    result = CryptEncrypt(hRSAKey, 0, TRUE, CRYPT_OAEP, abData, &dwLen, (DWORD)sizeof(abData));
    ok(result, "%08x\n", GetLastError());
    result = CryptDecrypt(hRSAKey, 0, TRUE, CRYPT_OAEP, abData, &dwLen);
    ok(result && dwLen == 12 && !memcmp(abData, "Wine rocks!", 12), "%08x\n", GetLastError());

    dwVal = 0xdeadbeef;
    dwLen = sizeof(DWORD);
    result = CryptGetKeyParam(hRSAKey, KP_PERMISSIONS, (BYTE*)&dwVal, &dwLen, 0);
    ok(result, "%08x\n", GetLastError());
    ok(dwVal ==
        (CRYPT_MAC|CRYPT_WRITE|CRYPT_READ|CRYPT_DECRYPT|CRYPT_ENCRYPT) ||
        broken(dwVal == 0xffffffff), /* Win9x/NT4 */
        "expected CRYPT_MAC|CRYPT_WRITE|CRYPT_READ|CRYPT_DECRYPT|CRYPT_ENCRYPT,"
        " got %08x\n", dwVal);

    /* An RSA key doesn't support salt */
    result = CryptGetKeyParam(hRSAKey, KP_SALT, NULL, &dwLen, 0);
    ok(!result && (GetLastError() == NTE_BAD_KEY || GetLastError() == NTE_NOT_FOUND /* Win7 */),
       "expected NTE_BAD_KEY or NTE_NOT_FOUND, got %08x\n", GetLastError());

    /* The key exchange key's public key may be exported.. */
    result = CryptExportKey(hRSAKey, 0, PUBLICKEYBLOB, 0, NULL, &dwLen);
    ok(result, "%08x\n", GetLastError());
    /* but its private key may not be. */
    SetLastError(0xdeadbeef);
    result = CryptExportKey(hRSAKey, 0, PRIVATEKEYBLOB, 0, NULL, &dwLen);
    ok((!result && GetLastError() == NTE_BAD_KEY_STATE) ||
        broken(result), /* Win9x/NT4 */
        "expected NTE_BAD_KEY_STATE, got %08x\n", GetLastError());
    /* Setting the permissions of the key exchange key isn't allowed, either. */
    dwVal |= CRYPT_EXPORT;
    SetLastError(0xdeadbeef);
    result = CryptSetKeyParam(hRSAKey, KP_PERMISSIONS, (BYTE *)&dwVal, 0);
    ok(!result &&
        (GetLastError() == NTE_BAD_DATA || GetLastError() == NTE_BAD_FLAGS),
        "expected NTE_BAD_DATA or NTE_BAD_FLAGS, got %08x\n", GetLastError());

    CryptDestroyKey(hRSAKey);

    /* It is not allowed to use the signature key for encryption/decryption */
    result = CryptGetUserKey(hProv, AT_SIGNATURE, &hRSAKey);
    ok (result, "%08x\n", GetLastError());
    if (!result) return;

    dwVal = 0xdeadbeef;
    dwLen = sizeof(DWORD);
    result = CryptGetKeyParam(hRSAKey, KP_PERMISSIONS, (BYTE*)&dwVal, &dwLen, 0);
    ok(result, "%08x\n", GetLastError());
    ok(dwVal ==
        (CRYPT_MAC|CRYPT_WRITE|CRYPT_READ|CRYPT_DECRYPT|CRYPT_ENCRYPT) ||
        broken(dwVal == 0xffffffff), /* Win9x/NT4 */
        "expected CRYPT_MAC|CRYPT_WRITE|CRYPT_READ|CRYPT_DECRYPT|CRYPT_ENCRYPT,"
        " got %08x\n", dwVal);

    /* The signature key's public key may also be exported.. */
    result = CryptExportKey(hRSAKey, 0, PUBLICKEYBLOB, 0, NULL, &dwLen);
    ok(result, "%08x\n", GetLastError());
    /* but its private key may not be. */
    SetLastError(0xdeadbeef);
    result = CryptExportKey(hRSAKey, 0, PRIVATEKEYBLOB, 0, NULL, &dwLen);
    ok((!result && GetLastError() == NTE_BAD_KEY_STATE) ||
        broken(result), /* Win9x/NT4 */
        "expected NTE_BAD_KEY_STATE, got %08x\n", GetLastError());
    /* Setting the permissions of the signature key isn't allowed, either. */
    dwVal |= CRYPT_EXPORT;
    SetLastError(0xdeadbeef);
    result = CryptSetKeyParam(hRSAKey, KP_PERMISSIONS, (BYTE *)&dwVal, 0);
    ok(!result &&
        (GetLastError() == NTE_BAD_DATA || GetLastError() == NTE_BAD_FLAGS),
        "expected NTE_BAD_DATA or NTE_BAD_FLAGS, got %08x\n", GetLastError());

    dwLen = 12;
    result = CryptEncrypt(hRSAKey, 0, TRUE, 0, abData, &dwLen, (DWORD)sizeof(abData));
    ok (!result && GetLastError() == NTE_BAD_KEY, "%08x\n", GetLastError());

    CryptDestroyKey(hRSAKey);
}