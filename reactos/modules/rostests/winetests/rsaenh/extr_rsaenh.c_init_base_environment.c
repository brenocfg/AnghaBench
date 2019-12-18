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
typedef  int /*<<< orphan*/  DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  AT_KEYEXCHANGE ; 
 int /*<<< orphan*/  AT_SIGNATURE ; 
 int /*<<< orphan*/  CRYPT_NEWKEYSET ; 
 int /*<<< orphan*/  CRYPT_VERIFYCONTEXT ; 
 int CryptAcquireContextA (scalar_t__*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CryptDestroyKey (int /*<<< orphan*/ ) ; 
 int CryptGenKey (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int FALSE ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  GetModuleHandleA (char*) ; 
 scalar_t__ GetProcAddress (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  NTE_BAD_FLAGS ; 
 int /*<<< orphan*/  NTE_BAD_KEYSET ; 
 int /*<<< orphan*/  NTE_KEYSET_NOT_DEF ; 
 int /*<<< orphan*/  NTE_TEMPORARY_PROFILE ; 
 int /*<<< orphan*/  PROV_RSA_FULL ; 
 int TRUE ; 
 scalar_t__ broken (int) ; 
 scalar_t__ hProv ; 
 int /*<<< orphan*/  ok (int,char*,int,...) ; 
 void* pCryptDuplicateHash ; 
 int /*<<< orphan*/  szContainer ; 
 char const* szProvider ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static BOOL init_base_environment(const char *provider, DWORD dwKeyFlags)
{
    HCRYPTKEY hKey;
    BOOL result;

    if (provider) szProvider = provider;
        
    pCryptDuplicateHash = (void *)GetProcAddress(GetModuleHandleA("advapi32.dll"), "CryptDuplicateHash");
        
    hProv = (HCRYPTPROV)INVALID_HANDLE_VALUE;

    result = CryptAcquireContextA(&hProv, szContainer, szProvider, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT);
    ok(!result && (GetLastError()==NTE_BAD_FLAGS ||
       broken(GetLastError() == NTE_KEYSET_NOT_DEF /* Win9x/NT4 */)),
       "%d, %08x\n", result, GetLastError());
    
    if (!CryptAcquireContextA(&hProv, szContainer, szProvider, PROV_RSA_FULL, 0))
    {
        ok(GetLastError()==NTE_BAD_KEYSET ||
           broken(GetLastError() == NTE_TEMPORARY_PROFILE /* some Win7 setups */) ||
           broken(GetLastError() == NTE_KEYSET_NOT_DEF /* Win9x/NT4 */),
           "%08x\n", GetLastError());
        if (GetLastError()!=NTE_BAD_KEYSET)
        {
            win_skip("RSA full provider not available\n");
            return FALSE;
        }
        result = CryptAcquireContextA(&hProv, szContainer, szProvider, PROV_RSA_FULL,
                                     CRYPT_NEWKEYSET);
        ok(result, "%08x\n", GetLastError());
        if (!result)
        {
            win_skip("Couldn't create crypto provider\n");
            return FALSE;
        }
        result = CryptGenKey(hProv, AT_KEYEXCHANGE, dwKeyFlags, &hKey);
        ok(result, "%08x\n", GetLastError());
        if (result) CryptDestroyKey(hKey);
        result = CryptGenKey(hProv, AT_SIGNATURE, dwKeyFlags, &hKey);
        ok(result, "%08x\n", GetLastError());
        if (result) CryptDestroyKey(hKey);
    }
    return TRUE;
}