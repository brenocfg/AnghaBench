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
typedef  scalar_t__ HCRYPTPROV ;
typedef  int /*<<< orphan*/  HCRYPTKEY ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  AT_KEYEXCHANGE ; 
 int /*<<< orphan*/  AT_SIGNATURE ; 
 int /*<<< orphan*/  CALG_AES ; 
 int /*<<< orphan*/  CALG_AES_128 ; 
 int /*<<< orphan*/  CRYPT_NEWKEYSET ; 
 int /*<<< orphan*/  CRYPT_VERIFYCONTEXT ; 
 int CryptAcquireContextA (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CryptDestroyKey (int /*<<< orphan*/ ) ; 
 int CryptGenKey (scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int FALSE ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  GetModuleHandleA (char*) ; 
 scalar_t__ GetProcAddress (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  NTE_BAD_ALGID ; 
 int /*<<< orphan*/  NTE_BAD_FLAGS ; 
 int /*<<< orphan*/  NTE_BAD_KEYSET ; 
 int /*<<< orphan*/  NTE_PROV_TYPE_NOT_DEF ; 
 int /*<<< orphan*/  PROV_RSA_AES ; 
 int TRUE ; 
 scalar_t__ hProv ; 
 int /*<<< orphan*/  ok (int,char*,int,...) ; 
 void* pCryptDuplicateHash ; 
 int /*<<< orphan*/  szContainer ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static BOOL init_aes_environment(void)
{
    HCRYPTKEY hKey;
    BOOL result;

    pCryptDuplicateHash = (void *)GetProcAddress(GetModuleHandleA("advapi32.dll"), "CryptDuplicateHash");

    hProv = (HCRYPTPROV)INVALID_HANDLE_VALUE;

    /* we are using NULL as provider name for RSA_AES provider as the provider
     * names are different in Windows XP and Vista. This differs from what
     * is defined in the SDK on Windows XP.
     * This provider is available on Windows XP, Windows 2003 and Vista.      */

    result = CryptAcquireContextA(&hProv, szContainer, NULL, PROV_RSA_AES, CRYPT_VERIFYCONTEXT);
    if (!result && GetLastError() == NTE_PROV_TYPE_NOT_DEF)
    {
        win_skip("RSA_AES provider not supported\n");
        return FALSE;
    }
    ok(!result && GetLastError()==NTE_BAD_FLAGS, "%d, %08x\n", result, GetLastError());

    if (!CryptAcquireContextA(&hProv, szContainer, NULL, PROV_RSA_AES, 0))
    {
        ok(GetLastError()==NTE_BAD_KEYSET, "%08x\n", GetLastError());
        if (GetLastError()!=NTE_BAD_KEYSET) return FALSE;
        result = CryptAcquireContextA(&hProv, szContainer, NULL, PROV_RSA_AES,
                                     CRYPT_NEWKEYSET);
        ok(result, "%08x\n", GetLastError());
        if (!result) return FALSE;
        result = CryptGenKey(hProv, AT_KEYEXCHANGE, 0, &hKey);
        ok(result, "%08x\n", GetLastError());
        if (result) CryptDestroyKey(hKey);
        result = CryptGenKey(hProv, AT_SIGNATURE, 0, &hKey);
        ok(result, "%08x\n", GetLastError());
        if (result) CryptDestroyKey(hKey);

        /* CALG_AES is not supported, but CALG_AES_128 is */
        result = CryptGenKey(hProv, CALG_AES, 0, &hKey);
        ok(!result && GetLastError() == NTE_BAD_ALGID, "%d %08x\n", result, GetLastError());
        result = CryptGenKey(hProv, CALG_AES, 128 << 16, &hKey);
        ok(!result && GetLastError() == NTE_BAD_ALGID, "%d %08x\n", result, GetLastError());
        result = CryptGenKey(hProv, CALG_AES_128, 0, &hKey);
        ok(result, "%08x\n", GetLastError());
        if (result) CryptDestroyKey(hKey);
    }
    return TRUE;
}