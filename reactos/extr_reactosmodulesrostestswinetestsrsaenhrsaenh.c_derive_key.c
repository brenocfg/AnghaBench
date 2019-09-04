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
typedef  int /*<<< orphan*/  pbData ;
typedef  scalar_t__ HCRYPTKEY ;
typedef  int /*<<< orphan*/  HCRYPTHASH ;
typedef  int DWORD ;
typedef  int BOOL ;
typedef  int /*<<< orphan*/  ALG_ID ;

/* Variables and functions */
 int /*<<< orphan*/  CALG_MD2 ; 
 int CRYPT_EXPORTABLE ; 
 int CryptCreateHash (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int CryptDeriveKey (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__*) ; 
 int /*<<< orphan*/  CryptDestroyHash (int /*<<< orphan*/ ) ; 
 int CryptGetHashParam (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,int*,int /*<<< orphan*/ ) ; 
 int CryptHashData (int /*<<< orphan*/ ,unsigned char*,int,int /*<<< orphan*/ ) ; 
 int FALSE ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  HP_HASHVAL ; 
 scalar_t__ NTE_BAD_ALGID ; 
 int TRUE ; 
 int /*<<< orphan*/  hProv ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 

__attribute__((used)) static BOOL derive_key(ALG_ID aiAlgid, HCRYPTKEY *phKey, DWORD len) 
{
    HCRYPTHASH hHash;
    BOOL result;
    unsigned char pbData[2000];
    int i;

    *phKey = 0;
    for (i=0; i<2000; i++) pbData[i] = (unsigned char)i;
    result = CryptCreateHash(hProv, CALG_MD2, 0, 0, &hHash);
    if (!result) {
        /* rsaenh compiled without OpenSSL */
        ok(GetLastError()==NTE_BAD_ALGID, "%08x\n", GetLastError());
        return FALSE;
    } 
    ok(result, "%08x\n", GetLastError());
    result = CryptHashData(hHash, pbData, sizeof(pbData), 0);
    ok(result, "%08x\n", GetLastError());
    if (!result) return FALSE;
    result = CryptDeriveKey(hProv, aiAlgid, hHash, (len << 16) | CRYPT_EXPORTABLE, phKey);
    ok(result, "%08x\n", GetLastError());
    if (!result) return FALSE;
    len = 2000;
    result = CryptGetHashParam(hHash, HP_HASHVAL, pbData, &len, 0);
    ok(result, "%08x\n", GetLastError());
    CryptDestroyHash(hHash);
    return TRUE;
}