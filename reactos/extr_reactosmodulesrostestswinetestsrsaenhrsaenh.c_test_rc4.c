#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pszBuffer ;
typedef  int /*<<< orphan*/  pbData ;
struct TYPE_2__ {unsigned char* pbData; int cbData; } ;
typedef  int /*<<< orphan*/  HCRYPTKEY ;
typedef  int /*<<< orphan*/  HCRYPTHASH ;
typedef  int DWORD ;
typedef  TYPE_1__ CRYPT_INTEGER_BLOB ;
typedef  int BYTE ;
typedef  int BOOL ;

/* Variables and functions */
 scalar_t__ BASE_PROV ; 
 int /*<<< orphan*/  CALG_MD2 ; 
 int /*<<< orphan*/  CALG_MD5 ; 
 int /*<<< orphan*/  CALG_RC4 ; 
 int CRYPT_CREATE_SALT ; 
 int CRYPT_MODE_CBC ; 
 int CryptCreateHash (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int CryptDecrypt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,int*) ; 
 int CryptDeriveKey (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int CryptDestroyHash (int /*<<< orphan*/ ) ; 
 int CryptDestroyKey (int /*<<< orphan*/ ) ; 
 int CryptEncrypt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,int*,int) ; 
 int CryptGetHashParam (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,int*,int /*<<< orphan*/ ) ; 
 int CryptGetKeyParam (int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int CryptHashData (int /*<<< orphan*/ ,unsigned char*,int,int /*<<< orphan*/ ) ; 
 int CryptSetKeyParam (int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 scalar_t__ ENHANCED_PROV ; 
 int GetLastError () ; 
 int /*<<< orphan*/  HP_HASHVAL ; 
 int /*<<< orphan*/  KP_BLOCKLEN ; 
 int /*<<< orphan*/  KP_IV ; 
 int /*<<< orphan*/  KP_KEYLEN ; 
 int /*<<< orphan*/  KP_MODE ; 
 int /*<<< orphan*/  KP_SALT ; 
 int /*<<< orphan*/  KP_SALT_EX ; 
 int NTE_BAD_ALGID ; 
 scalar_t__ STRONG_PROV ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  hProv ; 
 int /*<<< orphan*/  memcmp (unsigned char*,int const*,int) ; 
 int /*<<< orphan*/  memset (unsigned char*,int,int) ; 
 scalar_t__ nt4 ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void test_rc4(void)
{
    static const BYTE rc4[16] = { 
        0x17, 0x0c, 0x44, 0x8e, 0xae, 0x90, 0xcd, 0xb0, 
        0x7f, 0x87, 0xf5, 0x7a, 0xec, 0xb2, 0x2e, 0x35 };    
    static const BYTE rc4_40_salt[16] = {
        0x41, 0xE6, 0x33, 0xC9, 0x50, 0xA1, 0xBF, 0x88,
        0x12, 0x4D, 0xD3, 0xE3, 0x47, 0x88, 0x6D, 0xA5 };
    static const BYTE rc4_40_salt_base[16] = {
        0x2F, 0xAC, 0xEA, 0xEA, 0xFF, 0x68, 0x7E, 0x77,
        0xF4, 0xB9, 0x48, 0x7C, 0x4E, 0x79, 0xA6, 0xB5 };
    BOOL result;
    HCRYPTHASH hHash;
    HCRYPTKEY hKey;
    DWORD dwDataLen = 5, dwKeyLen, dwLen = sizeof(DWORD), dwMode;
    unsigned char pbData[2000];
    unsigned char pszBuffer[256];
    int i;

    for (i=0; i<2000; i++) pbData[i] = (unsigned char)i;

    /* MD2 Hashing */
    result = CryptCreateHash(hProv, CALG_MD2, 0, 0, &hHash);
    if (!result) {
        /* rsaenh compiled without OpenSSL */
        ok(GetLastError() == NTE_BAD_ALGID, "%08x\n", GetLastError());
    } else {
        CRYPT_INTEGER_BLOB salt;

        result = CryptHashData(hHash, pbData, sizeof(pbData), 0);
           ok(result, "%08x\n", GetLastError());

        dwLen = 16;
        result = CryptGetHashParam(hHash, HP_HASHVAL, pszBuffer, &dwLen, 0);
        ok(result, "%08x\n", GetLastError());

        result = CryptDeriveKey(hProv, CALG_RC4, hHash, 56 << 16, &hKey);
        ok(result, "%08x\n", GetLastError());

        dwLen = sizeof(DWORD);
        result = CryptGetKeyParam(hKey, KP_KEYLEN, (BYTE*)&dwKeyLen, &dwLen, 0);
        ok(result, "%08x\n", GetLastError());
        ok(dwKeyLen == 56, "Expected 56, got %d\n", dwKeyLen);

        dwLen = sizeof(DWORD);
        result = CryptGetKeyParam(hKey, KP_BLOCKLEN, (BYTE*)&dwKeyLen, &dwLen, 0);
        ok(result, "%08x\n", GetLastError());
        ok(dwKeyLen == 0, "Expected 0, got %d\n", dwKeyLen);

        dwLen = 0;
        result = CryptGetKeyParam(hKey, KP_IV, NULL, &dwLen, 0);
        ok(result, "%08x\n", GetLastError());
        result = CryptGetKeyParam(hKey, KP_IV, pszBuffer, &dwLen, 0);

        dwLen = 0;
        result = CryptGetKeyParam(hKey, KP_SALT, NULL, &dwLen, 0);
        ok(result, "%08x\n", GetLastError());
        result = CryptGetKeyParam(hKey, KP_SALT, pszBuffer, &dwLen, 0);
        ok(result, "%08x\n", GetLastError());

        dwLen = sizeof(DWORD);
        result = CryptGetKeyParam(hKey, KP_MODE, (BYTE*)&dwMode, &dwLen, 0);
        ok(result, "%08x\n", GetLastError());
        ok(dwMode == 0 || broken(dwMode == CRYPT_MODE_CBC) /* <= 2000 */,
           "Expected 0, got %d\n", dwMode);

        result = CryptDestroyHash(hHash);
        ok(result, "%08x\n", GetLastError());

        dwDataLen = 16;
        result = CryptEncrypt(hKey, 0, TRUE, 0, NULL, &dwDataLen, 24);
        ok(result, "%08x\n", GetLastError());
        dwDataLen = 16;
        result = CryptEncrypt(hKey, 0, TRUE, 0, pbData, &dwDataLen, 24);
        ok(result, "%08x\n", GetLastError());

        ok(!memcmp(pbData, rc4, dwDataLen), "RC4 encryption failed!\n");

        result = CryptDecrypt(hKey, 0, TRUE, 0, pbData, &dwDataLen);
        ok(result, "%08x\n", GetLastError());

        /* Setting the salt value will not reset the salt length in base or strong providers */
        result = CryptSetKeyParam(hKey, KP_SALT, pbData, 0);
        ok(result, "setting salt failed: %08x\n", GetLastError());
        dwLen = 0;
        result = CryptGetKeyParam(hKey, KP_SALT, NULL, &dwLen, 0);
        ok(result, "%08x\n", GetLastError());
        if (BASE_PROV || STRONG_PROV)
            ok(dwLen == 11, "expected salt length 11, got %d\n", dwLen);
        else
            ok(dwLen == 0 || broken(nt4 && dwLen == 11), "expected salt length 0, got %d\n", dwLen);
        /* What sizes salt can I set? */
        salt.pbData = pbData;
        for (i=0; i<24; i++)
        {
            salt.cbData = i;
            result = CryptSetKeyParam(hKey, KP_SALT_EX, (BYTE *)&salt, 0);
            ok(result, "setting salt failed for size %d: %08x\n", i, GetLastError());
            /* The returned salt length is the same as the set salt length */
            result = CryptGetKeyParam(hKey, KP_SALT, NULL, &dwLen, 0);
            ok(result, "%08x\n", GetLastError());
            ok(dwLen == i, "size %d: unexpected salt length %d\n", i, dwLen);
        }
        salt.cbData = 25;
        SetLastError(0xdeadbeef);
        result = CryptSetKeyParam(hKey, KP_SALT_EX, (BYTE *)&salt, 0);
        ok(!result ||
           broken(result), /* Win9x, WinMe, NT4, W2K */
           "%08x\n", GetLastError());

        result = CryptDestroyKey(hKey);
        ok(result, "%08x\n", GetLastError());

        /* Test a 40 bit key with salt */
        result = CryptCreateHash(hProv, CALG_MD5, 0, 0, &hHash);
        ok(result, "%08x\n", GetLastError());

        result = CryptHashData(hHash, pbData, sizeof(pbData), 0);
        ok(result, "%08x\n", GetLastError());

        result = CryptDeriveKey(hProv, CALG_RC4, hHash, (40<<16)|CRYPT_CREATE_SALT, &hKey);
        ok(result, "%08x\n", GetLastError());
        dwDataLen = 16;
        memset(pbData, 0xAF, dwDataLen);
        SetLastError(0xdeadbeef);
        result = CryptEncrypt(hKey, 0, TRUE, 0, pbData, &dwDataLen, 24);
        ok(result, "%08x\n", GetLastError());
        ok((ENHANCED_PROV && !memcmp(pbData, rc4_40_salt, dwDataLen)) ||
           (!ENHANCED_PROV && !memcmp(pbData, rc4_40_salt_base, dwDataLen)),
           "RC4 encryption failed!\n");

        dwLen = sizeof(DWORD);
        dwKeyLen = 12345;
        result = CryptGetKeyParam(hKey, KP_KEYLEN, (BYTE*)&dwKeyLen, &dwLen, 0);
        ok(result, "%08x\n", GetLastError());
        ok(dwKeyLen == 40, "Expected 40, got %d\n", dwKeyLen);

        dwLen = sizeof(pszBuffer);
        memset(pszBuffer, 0xAF, dwLen);
        result = CryptGetKeyParam(hKey, KP_SALT, pszBuffer, &dwLen, 0);
        ok(result, "%08x\n", GetLastError());
        if (!ENHANCED_PROV)
            ok(dwLen == 11, "Expected 11, got %d\n", dwLen);
        else
            ok(dwLen == 0, "Expected 0, got %d\n", dwLen);

        result = CryptDestroyKey(hKey);
        ok(result, "%08x\n", GetLastError());

        result = CryptDestroyHash(hHash);
        ok(result, "%08x\n", GetLastError());
    }
}