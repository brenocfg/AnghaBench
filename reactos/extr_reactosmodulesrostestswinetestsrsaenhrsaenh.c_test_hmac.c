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
typedef  int /*<<< orphan*/  hmac ;
typedef  int /*<<< orphan*/  abData ;
struct TYPE_2__ {int /*<<< orphan*/  member_4; int /*<<< orphan*/ * member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/ * member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ HMAC_INFO ;
typedef  int /*<<< orphan*/  HCRYPTKEY ;
typedef  int /*<<< orphan*/  HCRYPTHASH ;
typedef  int DWORD ;
typedef  int BYTE ;
typedef  int BOOL ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int /*<<< orphan*/  CALG_HMAC ; 
 int /*<<< orphan*/  CALG_MD5 ; 
 int /*<<< orphan*/  CALG_RC2 ; 
 int CryptCreateHash (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int CryptDestroyHash (int /*<<< orphan*/ ) ; 
 int CryptDestroyKey (int /*<<< orphan*/ ) ; 
 int CryptGetHashParam (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*,int /*<<< orphan*/ ) ; 
 int CryptHashData (int /*<<< orphan*/ ,int*,int,int /*<<< orphan*/ ) ; 
 int CryptSetHashParam (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  HP_HASHVAL ; 
 int /*<<< orphan*/  HP_HMAC_INFO ; 
 scalar_t__ NTE_BAD_KEY ; 
 int /*<<< orphan*/  derive_key (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  hProv ; 
 int /*<<< orphan*/  memcmp (int*,int const*,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void test_hmac(void) {
    HCRYPTKEY hKey;
    HCRYPTHASH hHash;
    BOOL result;
    /* Using CALG_MD2 here fails on Windows 2003, why ? */
    HMAC_INFO hmacInfo = { CALG_MD5, NULL, 0, NULL, 0 };
    DWORD dwLen;
    BYTE abData[256];
    static const BYTE hmac[16] = { 
        0x1a, 0x7d, 0x49, 0xc5, 0x9b, 0x2d, 0x0b, 0x9c, 
        0xcf, 0x10, 0x6b, 0xb6, 0x7d, 0x0f, 0x13, 0x32 };
    int i;

    for (i=0; i < ARRAY_SIZE(abData); i++) abData[i] = (BYTE)i;

    if (!derive_key(CALG_RC2, &hKey, 56)) return;

    result = CryptCreateHash(hProv, CALG_HMAC, hKey, 0, &hHash);
    ok(result, "%08x\n", GetLastError());
    if (!result) return;

    result = CryptSetHashParam(hHash, HP_HMAC_INFO, (BYTE*)&hmacInfo, 0);
    ok(result, "%08x\n", GetLastError());

    result = CryptHashData(hHash, abData, sizeof(abData), 0);
    ok(result, "%08x\n", GetLastError());

    dwLen = ARRAY_SIZE(abData);
    result = CryptGetHashParam(hHash, HP_HASHVAL, abData, &dwLen, 0);
    ok(result, "%08x\n", GetLastError());

    ok(!memcmp(abData, hmac, sizeof(hmac)), "HMAC failed!\n");
    
    result = CryptDestroyHash(hHash);
    ok(result, "%08x\n", GetLastError());
    
    result = CryptDestroyKey(hKey);
    ok(result, "%08x\n", GetLastError());

    /* Provoke errors */
    result = CryptCreateHash(hProv, CALG_HMAC, 0, 0, &hHash);
    ok(!result && GetLastError() == NTE_BAD_KEY, "%08x\n", GetLastError());
}