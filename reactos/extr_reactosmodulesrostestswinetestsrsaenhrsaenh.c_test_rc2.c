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
typedef  int /*<<< orphan*/  rc2_128_encrypted ;
typedef  int /*<<< orphan*/  pszBuffer ;
typedef  int /*<<< orphan*/  pbData ;
typedef  int /*<<< orphan*/  dwMode ;
typedef  int /*<<< orphan*/  dwKeyLen ;
struct TYPE_2__ {unsigned char* pbData; int cbData; } ;
typedef  int* LPBYTE ;
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
 int /*<<< orphan*/  CALG_RC2 ; 
 int CRYPT_CREATE_SALT ; 
 int CRYPT_DECRYPT ; 
 int CRYPT_ENCRYPT ; 
 int CRYPT_MAC ; 
 int CRYPT_MODE_CBC ; 
 int CRYPT_READ ; 
 int CRYPT_WRITE ; 
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
 int ERROR_INVALID_PARAMETER ; 
 int GetLastError () ; 
 int /*<<< orphan*/  HP_HASHVAL ; 
 int /*<<< orphan*/  KP_BLOCKLEN ; 
 int /*<<< orphan*/  KP_EFFECTIVE_KEYLEN ; 
 int /*<<< orphan*/  KP_IV ; 
 int /*<<< orphan*/  KP_KEYLEN ; 
 int /*<<< orphan*/  KP_MODE ; 
 int /*<<< orphan*/  KP_MODE_BITS ; 
 int /*<<< orphan*/  KP_PERMISSIONS ; 
 int /*<<< orphan*/  KP_SALT ; 
 int /*<<< orphan*/  KP_SALT_EX ; 
 int NTE_BAD_ALGID ; 
 int NTE_BAD_DATA ; 
 int NTE_DOUBLE_ENCRYPT ; 
 scalar_t__ STRONG_PROV ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  hProv ; 
 int /*<<< orphan*/  memcmp (unsigned char*,int const*,int) ; 
 int /*<<< orphan*/  memset (unsigned char*,int,int) ; 
 scalar_t__ nt4 ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void test_rc2(void)
{
    static const BYTE rc2_40_encrypted[16] = {
        0xc0, 0x9a, 0xe4, 0x2f, 0x0a, 0x47, 0x67, 0x11,
        0xfb, 0x18, 0x87, 0xce, 0x0c, 0x75, 0x07, 0xb1 };
    static const BYTE rc2_128_encrypted[] = {
        0x82,0x81,0xf7,0xff,0xdd,0xd7,0x88,0x8c,
        0x2a,0x2a,0xc0,0xce,0x4c,0x89,0xb6,0x66 };
    static const BYTE rc2_40def_encrypted[] = {
        0x23,0xc8,0x70,0x13,0x42,0x2e,0xa8,0x98,
        0x5c,0xdf,0x7a,0x9b,0xea,0xdb,0x96,0x1b };
    static const BYTE rc2_40_salt_enh[24] = {
        0xA3, 0xD7, 0x41, 0x87, 0x7A, 0xD0, 0x18, 0xDB,
        0xD4, 0x6A, 0x4F, 0xEE, 0xF3, 0xCA, 0xCD, 0x34,
        0xB3, 0x15, 0x9A, 0x2A, 0x88, 0x5F, 0x43, 0xA5 };
    static const BYTE rc2_40_salt_base[24] = {
        0x8C, 0x4E, 0xA6, 0x00, 0x9B, 0x15, 0xEF, 0x9E,
        0x88, 0x81, 0xD0, 0x65, 0xD6, 0x53, 0x57, 0x08,
        0x0A, 0x77, 0x80, 0xFA, 0x7E, 0x89, 0x14, 0x55 };
    static const BYTE rc2_40_salt_strong[24] = {
        0xB9, 0x33, 0xB6, 0x7A, 0x35, 0xC3, 0x06, 0x88,
        0xBF, 0xD5, 0xCC, 0xAF, 0x14, 0xAE, 0xE2, 0x31,
        0xC6, 0x9A, 0xAA, 0x3F, 0x05, 0x2F, 0x22, 0xDA };
    HCRYPTHASH hHash;
    HCRYPTKEY hKey;
    BOOL result;
    DWORD dwLen, dwKeyLen, dwDataLen, dwMode, dwModeBits, error;
    unsigned char pbData[2000], pbHashValue[16], pszBuffer[256];
    int i;
    
    for (i=0; i<2000; i++) pbData[i] = (unsigned char)i;

    /* MD2 Hashing */
    result = CryptCreateHash(hProv, CALG_MD2, 0, 0, &hHash);
    if (!result) {
        ok(GetLastError()==NTE_BAD_ALGID, "%08x\n", GetLastError());
    } else {
        CRYPT_INTEGER_BLOB salt;

        result = CryptHashData(hHash, pbData, sizeof(pbData), 0);
        ok(result, "%08x\n", GetLastError());

        dwLen = 16;
        result = CryptGetHashParam(hHash, HP_HASHVAL, pbHashValue, &dwLen, 0);
        ok(result, "%08x\n", GetLastError());

        result = CryptDeriveKey(hProv, CALG_RC2, hHash, 40 << 16, &hKey);
        ok(result, "%08x\n", GetLastError());

        dwLen = sizeof(DWORD);
        result = CryptGetKeyParam(hKey, KP_KEYLEN, (BYTE*)&dwKeyLen, &dwLen, 0);
        ok(result, "%08x\n", GetLastError());

        /* test default chaining mode */
        dwMode = 0xdeadbeef;
        dwLen = sizeof(dwMode);
        result = CryptGetKeyParam(hKey, KP_MODE, (BYTE*)&dwMode, &dwLen, 0);
        ok(result, "%08x\n", GetLastError());
        ok(dwMode == CRYPT_MODE_CBC, "Wrong default chaining mode\n");

        dwMode = CRYPT_MODE_CBC;
        result = CryptSetKeyParam(hKey, KP_MODE, (BYTE*)&dwMode, 0);
        ok(result, "%08x\n", GetLastError());

        dwLen = sizeof(DWORD);
        result = CryptGetKeyParam(hKey, KP_MODE_BITS, (BYTE*)&dwModeBits, &dwLen, 0);
        ok(result, "%08x\n", GetLastError());

        dwModeBits = 0xdeadbeef;
        dwLen = sizeof(DWORD);
        result = CryptGetKeyParam(hKey, KP_PERMISSIONS, (BYTE*)&dwModeBits, &dwLen, 0);
        ok(result, "%08x\n", GetLastError());
        ok(dwModeBits ==
            (CRYPT_MAC|CRYPT_WRITE|CRYPT_READ|CRYPT_DECRYPT|CRYPT_ENCRYPT) ||
            broken(dwModeBits == 0xffffffff), /* Win9x/NT4 */
            "expected CRYPT_MAC|CRYPT_WRITE|CRYPT_READ|CRYPT_DECRYPT|CRYPT_ENCRYPT,"
            " got %08x\n", dwModeBits);

        dwLen = sizeof(DWORD);
        result = CryptGetKeyParam(hKey, KP_PERMISSIONS, (BYTE*)&dwModeBits, &dwLen, 0);
        ok(result, "%08x\n", GetLastError());

        dwLen = sizeof(DWORD);
        result = CryptGetKeyParam(hKey, KP_BLOCKLEN, (BYTE*)&dwModeBits, &dwLen, 0);
        ok(result, "%08x\n", GetLastError());
        ok(dwLen == 4, "Expected 4, got %d\n", dwLen);

        dwLen = 0;
        result = CryptGetKeyParam(hKey, KP_IV, NULL, &dwLen, 0);
        ok(result, "%08x\n", GetLastError());
        result = CryptGetKeyParam(hKey, KP_IV, pszBuffer, &dwLen, 0);
        ok(result, "%08x\n", GetLastError());
        ok(dwLen == 8, "Expected 8, got %d\n", dwLen);

        dwLen = 0;
        result = CryptGetKeyParam(hKey, KP_SALT, NULL, &dwLen, 0);
        ok(result, "%08x\n", GetLastError());
        /* The default salt length is always 11... */
        ok(dwLen == 11, "unexpected salt length %d\n", dwLen);
        /* and the default salt is always empty. */
        result = CryptGetKeyParam(hKey, KP_SALT, pszBuffer, &dwLen, 0);
        ok(result, "%08x\n", GetLastError());
        for (i=0; i<dwLen; i++)
            ok(!pszBuffer[i], "unexpected salt value %02x @ %d\n", pszBuffer[i], i);

        dwLen = sizeof(DWORD);
        result = CryptGetKeyParam(hKey, KP_MODE, (BYTE*)&dwMode, &dwLen, 0);
        ok(result, "%08x\n", GetLastError());
        ok(dwMode == CRYPT_MODE_CBC, "Expected CRYPT_MODE_CBC, got %d\n", dwMode);

        result = CryptDestroyHash(hHash);
        ok(result, "%08x\n", GetLastError());

        dwDataLen = 13;
        result = CryptEncrypt(hKey, 0, TRUE, 0, pbData, &dwDataLen, 24);
        ok(result, "%08x\n", GetLastError());

        ok(!memcmp(pbData, rc2_40_encrypted, 16), "RC2 encryption failed!\n");

        dwLen = 0;
        result = CryptGetKeyParam(hKey, KP_IV, NULL, &dwLen, 0);
        ok(result, "%08x\n", GetLastError());
        result = CryptGetKeyParam(hKey, KP_IV, pszBuffer, &dwLen, 0);
        ok(result, "%08x\n", GetLastError());

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
    }

    /* Again, but test setting the effective key len */
    for (i=0; i<2000; i++) pbData[i] = (unsigned char)i;

    result = CryptCreateHash(hProv, CALG_MD2, 0, 0, &hHash);
    if (!result) {
        ok(GetLastError()==NTE_BAD_ALGID, "%08x\n", GetLastError());
    } else {
        result = CryptHashData(hHash, pbData, sizeof(pbData), 0);
        ok(result, "%08x\n", GetLastError());

        dwLen = 16;
        result = CryptGetHashParam(hHash, HP_HASHVAL, pbHashValue, &dwLen, 0);
        ok(result, "%08x\n", GetLastError());

        result = CryptDeriveKey(hProv, CALG_RC2, hHash, 56 << 16, &hKey);
        ok(result, "%08x\n", GetLastError());

        SetLastError(0xdeadbeef);
        result = CryptSetKeyParam(hKey, KP_EFFECTIVE_KEYLEN, NULL, 0);
        ok(!result && GetLastError()==ERROR_INVALID_PARAMETER, "%08x\n", GetLastError());
        dwKeyLen = 0;
        SetLastError(0xdeadbeef);
        result = CryptSetKeyParam(hKey, KP_EFFECTIVE_KEYLEN, (LPBYTE)&dwKeyLen, 0);
        ok(!result && GetLastError()==NTE_BAD_DATA, "%08x\n", GetLastError());
        dwKeyLen = 1025;
        SetLastError(0xdeadbeef);
        result = CryptSetKeyParam(hKey, KP_EFFECTIVE_KEYLEN, (LPBYTE)&dwKeyLen, 0);
        ok(!result, "CryptSetKeyParam failed: %08x\n", GetLastError());

        dwLen = sizeof(dwKeyLen);
        result = CryptGetKeyParam(hKey, KP_KEYLEN, (BYTE *)&dwKeyLen, &dwLen, 0);
        ok(result, "%08x\n", GetLastError());
        ok(dwKeyLen == 56, "%d (%08x)\n", dwKeyLen, GetLastError());
        result = CryptGetKeyParam(hKey, KP_EFFECTIVE_KEYLEN, (BYTE *)&dwKeyLen, &dwLen, 0);
        ok(result, "%08x\n", GetLastError());
        ok(dwKeyLen == 56 || broken(dwKeyLen == 40), "%d (%08x)\n", dwKeyLen, GetLastError());

        dwKeyLen = 128;
        SetLastError(0xdeadbeef);
        result = CryptSetKeyParam(hKey, KP_EFFECTIVE_KEYLEN, (LPBYTE)&dwKeyLen, 0);
        if (!BASE_PROV)
        {
            dwKeyLen = 12345;
            ok(result, "expected success, got error 0x%08X\n", GetLastError());
            result = CryptGetKeyParam(hKey, KP_EFFECTIVE_KEYLEN, (BYTE *)&dwKeyLen, &dwLen, 0);
            ok(result, "%08x\n", GetLastError());
            ok(dwKeyLen == 128, "Expected 128, got %d\n", dwKeyLen);
        }
        else
        {
            ok(!result, "expected error\n");
            ok(GetLastError() == NTE_BAD_DATA, "Expected 0x80009005, got 0x%08X\n", GetLastError());
            result = CryptGetKeyParam(hKey, KP_EFFECTIVE_KEYLEN, (BYTE *)&dwKeyLen, &dwLen, 0);
            ok(result, "%08x\n", GetLastError());
            ok(dwKeyLen == 40, "Expected 40, got %d\n", dwKeyLen);
        }

        dwLen = sizeof(dwKeyLen);
        result = CryptGetKeyParam(hKey, KP_KEYLEN, (BYTE *)&dwKeyLen, &dwLen, 0);
        ok(result, "%08x\n", GetLastError());
        ok(dwKeyLen == 56, "%d (%08x)\n", dwKeyLen, GetLastError());
        result = CryptGetKeyParam(hKey, KP_EFFECTIVE_KEYLEN, (BYTE *)&dwKeyLen, &dwLen, 0);
        ok(result, "%08x\n", GetLastError());
        ok((!BASE_PROV && dwKeyLen == 128) || (BASE_PROV && dwKeyLen == 40),
           "%d (%08x)\n", dwKeyLen, GetLastError());

        result = CryptDestroyHash(hHash);
        ok(result, "%08x\n", GetLastError());

        dwDataLen = 13;
        result = CryptEncrypt(hKey, 0, TRUE, 0, pbData, &dwDataLen, 24);
        ok(result, "%08x\n", GetLastError());
        ok(!memcmp(pbData, !BASE_PROV ? rc2_128_encrypted : rc2_40def_encrypted,
           sizeof(rc2_128_encrypted)), "RC2 encryption failed!\n");

        /* Oddly enough this succeeds, though it should have no effect */
        dwKeyLen = 40;
        result = CryptSetKeyParam(hKey, KP_EFFECTIVE_KEYLEN, (LPBYTE)&dwKeyLen, 0);
        ok(result, "%d\n", GetLastError());

        result = CryptDestroyKey(hKey);
        ok(result, "%08x\n", GetLastError());

        /* Test a 40 bit key with salt */
        result = CryptCreateHash(hProv, CALG_MD5, 0, 0, &hHash);
        ok(result, "%08x\n", GetLastError());

        result = CryptHashData(hHash, pbData, sizeof(pbData), 0);
        ok(result, "%08x\n", GetLastError());

        result = CryptDeriveKey(hProv, CALG_RC2, hHash, (40<<16)|CRYPT_CREATE_SALT, &hKey);
        ok(result, "%08x\n", GetLastError());

        dwDataLen = 16;
        memset(pbData, 0xAF, dwDataLen);
        SetLastError(0xdeadbeef);
        result = CryptEncrypt(hKey, 0, TRUE, 0, pbData, &dwDataLen, 24);
        if(result)
        {
            ok((ENHANCED_PROV && !memcmp(pbData, rc2_40_salt_enh, dwDataLen)) ||
               (STRONG_PROV && !memcmp(pbData, rc2_40_salt_strong, dwDataLen)) ||
               (BASE_PROV && !memcmp(pbData, rc2_40_salt_base, dwDataLen)),
               "RC2 encryption failed!\n");
        }
        else /* <= XP */
        {
            error = GetLastError();
            ok(error == NTE_BAD_DATA || broken(error == NTE_DOUBLE_ENCRYPT),
               "Expected 0x80009005, got 0x%08X\n", error);
        }
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