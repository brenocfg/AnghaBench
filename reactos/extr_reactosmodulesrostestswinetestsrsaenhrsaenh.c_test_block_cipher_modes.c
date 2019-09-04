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
typedef  int /*<<< orphan*/  plain ;
typedef  int /*<<< orphan*/  ecb ;
typedef  int /*<<< orphan*/  dwMode ;
typedef  int /*<<< orphan*/  cfb ;
typedef  int /*<<< orphan*/  cbc ;
typedef  int /*<<< orphan*/  HCRYPTKEY ;
typedef  int DWORD ;
typedef  int BYTE ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CALG_RC2 ; 
 int CRYPT_MODE_CBC ; 
 int CRYPT_MODE_CFB ; 
 int CRYPT_MODE_ECB ; 
 int CRYPT_MODE_OFB ; 
 int CryptDecrypt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  CryptDestroyKey (int /*<<< orphan*/ ) ; 
 int CryptEncrypt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*,int) ; 
 int CryptGetKeyParam (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*,int /*<<< orphan*/ ) ; 
 int CryptSetKeyParam (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int ERROR_INTERNAL_ERROR ; 
 int /*<<< orphan*/  ERROR_SUCCESS ; 
 int /*<<< orphan*/  FALSE ; 
 int GetLastError () ; 
 int /*<<< orphan*/  KP_MODE ; 
 int /*<<< orphan*/  KP_SALT ; 
 int NTE_BAD_ALGID ; 
 int /*<<< orphan*/  SetLastError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ broken (int) ; 
 int derive_key (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcmp (int const*,int*,int) ; 
 int /*<<< orphan*/  memcpy (int*,int const*,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void test_block_cipher_modes(void)
{
    static const BYTE plain[23] = { 
        0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 
        0x0c, 0x0d, 0x0e, 0x0f, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16 };
    static const BYTE ecb[24] = {   
        0xc0, 0x9a, 0xe4, 0x2f, 0x0a, 0x47, 0x67, 0x11, 0xf2, 0xb2, 0x5d, 0x5f, 
        0x08, 0xff, 0x49, 0xa4, 0x45, 0x3a, 0x68, 0x14, 0xca, 0x18, 0xe5, 0xf4 };
    static const BYTE cbc[24] = {   
        0xc0, 0x9a, 0xe4, 0x2f, 0x0a, 0x47, 0x67, 0x11, 0x10, 0xf5, 0xda, 0x61,
        0x4e, 0x3d, 0xab, 0xc0, 0x97, 0x85, 0x01, 0x12, 0x97, 0xa4, 0xf7, 0xd3 };
    static const BYTE cfb[24] = {   
        0x29, 0xb5, 0x67, 0x85, 0x0b, 0x1b, 0xec, 0x07, 0x67, 0x2d, 0xa1, 0xa4,
        0x1a, 0x47, 0x24, 0x6a, 0x54, 0xe1, 0xe0, 0x92, 0xf9, 0x0e, 0xf6, 0xeb };
    HCRYPTKEY hKey;
    BOOL result;
    BYTE abData[24];
    DWORD dwMode, dwLen;

    result = derive_key(CALG_RC2, &hKey, 40);
    if (!result) return;

    memcpy(abData, plain, sizeof(plain));

    /* test default chaining mode */
    dwMode = 0xdeadbeef;
    dwLen = sizeof(dwMode);
    result = CryptGetKeyParam(hKey, KP_MODE, (BYTE*)&dwMode, &dwLen, 0);
    ok(result, "%08x\n", GetLastError());
    ok(dwMode == CRYPT_MODE_CBC, "Wrong default chaining mode\n");

    dwMode = CRYPT_MODE_ECB;
    result = CryptSetKeyParam(hKey, KP_MODE, (BYTE*)&dwMode, 0);
    ok(result, "%08x\n", GetLastError());

    result = CryptGetKeyParam(hKey, KP_SALT, NULL, &dwLen, 0);
    ok(result, "%08x\n", GetLastError());
    ok(dwLen == 11 || broken(dwLen == 0 /* Win9x/NT4 */), "unexpected salt length %d\n", dwLen);

    dwLen = 23;
    result = CryptEncrypt(hKey, 0, TRUE, 0, NULL, &dwLen, 24);
    ok(result, "CryptEncrypt failed: %08x\n", GetLastError());
    ok(dwLen == 24, "Unexpected length %d\n", dwLen);

    SetLastError(ERROR_SUCCESS);
    dwLen = 23;
    result = CryptEncrypt(hKey, 0, TRUE, 0, abData, &dwLen, 24);
    ok(result && dwLen == 24 && !memcmp(ecb, abData, sizeof(ecb)), 
       "%08x, dwLen: %d\n", GetLastError(), dwLen);

    result = CryptDecrypt(hKey, 0, TRUE, 0, abData, &dwLen);
    ok(result && dwLen == 23 && !memcmp(plain, abData, sizeof(plain)), 
       "%08x, dwLen: %d\n", GetLastError(), dwLen);

    dwMode = CRYPT_MODE_CBC;
    result = CryptSetKeyParam(hKey, KP_MODE, (BYTE*)&dwMode, 0);
    ok(result, "%08x\n", GetLastError());
    
    dwLen = 23;
    result = CryptEncrypt(hKey, 0, TRUE, 0, NULL, &dwLen, 24);
    ok(result, "CryptEncrypt failed: %08x\n", GetLastError());
    ok(dwLen == 24, "Unexpected length %d\n", dwLen);

    dwLen = 23;
    result = CryptEncrypt(hKey, 0, TRUE, 0, abData, &dwLen, 24);
    ok(result && dwLen == 24 && !memcmp(cbc, abData, sizeof(cbc)), 
       "%08x, dwLen: %d\n", GetLastError(), dwLen);

    result = CryptDecrypt(hKey, 0, TRUE, 0, abData, &dwLen);
    ok(result && dwLen == 23 && !memcmp(plain, abData, sizeof(plain)), 
       "%08x, dwLen: %d\n", GetLastError(), dwLen);

    dwMode = CRYPT_MODE_CFB;
    result = CryptSetKeyParam(hKey, KP_MODE, (BYTE*)&dwMode, 0);
    ok(result, "%08x\n", GetLastError());
    
    dwLen = 16;
    result = CryptEncrypt(hKey, 0, FALSE, 0, abData, &dwLen, 24);
    ok(result && dwLen == 16, "%08x, dwLen: %d\n", GetLastError(), dwLen);

    dwLen = 7;
    result = CryptEncrypt(hKey, 0, TRUE, 0, abData+16, &dwLen, 8);
    ok(result && dwLen == 8 && !memcmp(cfb, abData, sizeof(cfb)), 
       "%08x, dwLen: %d\n", GetLastError(), dwLen);
    
    dwLen = 8;
    result = CryptDecrypt(hKey, 0, FALSE, 0, abData, &dwLen);
    ok(result && dwLen == 8, "%08x, dwLen: %d\n", GetLastError(), dwLen);

    dwLen = 16;
    result = CryptDecrypt(hKey, 0, TRUE, 0, abData+8, &dwLen);
    ok(result && dwLen == 15 && !memcmp(plain, abData, sizeof(plain)), 
       "%08x, dwLen: %d\n", GetLastError(), dwLen);

    dwMode = CRYPT_MODE_OFB;
    result = CryptSetKeyParam(hKey, KP_MODE, (BYTE*)&dwMode, 0);
    if(!result && GetLastError() == ERROR_INTERNAL_ERROR)
    {
        ok(broken(1), "OFB mode not supported\n"); /* Windows 8 */
    }
    else
    {
        ok(result, "%08x\n", GetLastError());

        dwLen = 23;
        result = CryptEncrypt(hKey, 0, TRUE, 0, abData, &dwLen, 24);
        ok(!result && GetLastError() == NTE_BAD_ALGID, "%08x\n", GetLastError());
    }

    CryptDestroyKey(hKey);
}