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
typedef  int /*<<< orphan*/  HCRYPTPROV ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPT_DELETEKEYSET ; 
 int /*<<< orphan*/  CRYPT_NEWKEYSET ; 
 int /*<<< orphan*/  PROV_RSA_FULL ; 
 scalar_t__ pCryptAcquireContextA (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pCryptReleaseContext (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  szBadKeySet ; 
 int /*<<< orphan*/  szKeySet ; 
 int /*<<< orphan*/ * szRsaBaseProv ; 

__attribute__((used)) static void init_environment(void)
{
	HCRYPTPROV hProv;
	
	/* Ensure that container "wine_test_keyset" does exist */
	if (!pCryptAcquireContextA(&hProv, szKeySet, szRsaBaseProv, PROV_RSA_FULL, 0))
	{
		pCryptAcquireContextA(&hProv, szKeySet, szRsaBaseProv, PROV_RSA_FULL, CRYPT_NEWKEYSET);
	}
	pCryptReleaseContext(hProv, 0);

	/* Ensure that container "wine_test_keyset" does exist in default PROV_RSA_FULL type provider */
	if (!pCryptAcquireContextA(&hProv, szKeySet, NULL, PROV_RSA_FULL, 0))
	{
		pCryptAcquireContextA(&hProv, szKeySet, NULL, PROV_RSA_FULL, CRYPT_NEWKEYSET);
	}
	pCryptReleaseContext(hProv, 0);

	/* Ensure that container "wine_test_bad_keyset" does not exist. */
	if (pCryptAcquireContextA(&hProv, szBadKeySet, szRsaBaseProv, PROV_RSA_FULL, 0))
	{
		pCryptReleaseContext(hProv, 0);
		pCryptAcquireContextA(&hProv, szBadKeySet, szRsaBaseProv, PROV_RSA_FULL, CRYPT_DELETEKEYSET);
	}
}