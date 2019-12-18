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
typedef  int /*<<< orphan*/ * LPSTR ;
typedef  int DWORD ;

/* Variables and functions */
 int CRYPT_DELETE_DEFAULT ; 
 int CRYPT_MACHINE_DEFAULT ; 
 scalar_t__ ERROR_ACCESS_DENIED ; 
 scalar_t__ ERROR_INVALID_PARAMETER ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  LMEM_ZEROINIT ; 
 int /*<<< orphan*/ * LocalAlloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  LocalFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * MS_DEF_PROV_A ; 
 int /*<<< orphan*/  PROV_RSA_FULL ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 scalar_t__ broken (int) ; 
 scalar_t__ lstrlenA (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__,...) ; 
 int pCryptGetDefaultProviderA (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int*) ; 
 int pCryptSetProviderExA (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  skip (char*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int strlen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_set_provider_ex(void)
{
	DWORD result;
	DWORD notNull = 5;
        LPSTR curProvName = NULL;
        DWORD curlen;
	
	/* results */
	LPSTR pszProvName = NULL;
	DWORD cbProvName;
	
	if(!pCryptGetDefaultProviderA || !pCryptSetProviderExA)
	{
	    win_skip("CryptGetDefaultProviderA and/or CryptSetProviderExA are not available\n");
	    return;
	}

        /* store the current one */
        pCryptGetDefaultProviderA(PROV_RSA_FULL, NULL, CRYPT_MACHINE_DEFAULT, NULL, &curlen);
        if (!(curProvName = LocalAlloc(LMEM_ZEROINIT, curlen)))
            return;
        result = pCryptGetDefaultProviderA(PROV_RSA_FULL, NULL, CRYPT_MACHINE_DEFAULT, curProvName, &curlen);
        ok(result, "%d\n", GetLastError());

	/* check pdwReserved for NULL */
	result = pCryptSetProviderExA(MS_DEF_PROV_A, PROV_RSA_FULL, &notNull, CRYPT_MACHINE_DEFAULT);
	ok(!result && GetLastError()==ERROR_INVALID_PARAMETER, "expected %i, got %d\n",
		ERROR_INVALID_PARAMETER, GetLastError());

	/* remove the default provider and then set it to MS_DEF_PROV/PROV_RSA_FULL */
        SetLastError(0xdeadbeef);
	result = pCryptSetProviderExA(MS_DEF_PROV_A, PROV_RSA_FULL, NULL, CRYPT_MACHINE_DEFAULT | CRYPT_DELETE_DEFAULT);
	if (!result)
	{
                ok( GetLastError() == ERROR_ACCESS_DENIED || broken(GetLastError() == ERROR_INVALID_PARAMETER),
                    "wrong error %u\n", GetLastError() );
		skip("Not enough rights to remove the default provider\n");
                LocalFree(curProvName);
		return;
	}

	result = pCryptSetProviderExA(MS_DEF_PROV_A, PROV_RSA_FULL, NULL, CRYPT_MACHINE_DEFAULT);
	ok(result, "%d\n", GetLastError());
	
	/* call CryptGetDefaultProvider to see if they match */
	result = pCryptGetDefaultProviderA(PROV_RSA_FULL, NULL, CRYPT_MACHINE_DEFAULT, NULL, &cbProvName);
	ok(result, "%d\n", GetLastError());
	if (!(pszProvName = LocalAlloc(LMEM_ZEROINIT, cbProvName)))
		goto reset;

	result = pCryptGetDefaultProviderA(PROV_RSA_FULL, NULL, CRYPT_MACHINE_DEFAULT, pszProvName, &cbProvName);
	ok(result && !strcmp(MS_DEF_PROV_A, pszProvName), "expected %s, got %s\n", MS_DEF_PROV_A, pszProvName);
	ok(result && cbProvName==(strlen(MS_DEF_PROV_A) + 1), "expected %i, got %d\n", (lstrlenA(MS_DEF_PROV_A) + 1), cbProvName);

	LocalFree(pszProvName);

reset:
        /* Set the provider back to its original */
        result = pCryptSetProviderExA(curProvName, PROV_RSA_FULL, NULL, CRYPT_MACHINE_DEFAULT);
        ok(result, "%d\n", GetLastError());
        LocalFree(curProvName);
}