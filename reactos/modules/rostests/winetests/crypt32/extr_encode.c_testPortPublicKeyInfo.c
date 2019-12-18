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
typedef  int /*<<< orphan*/ * PCERT_PUBLIC_KEY_INFO ;
typedef  int /*<<< orphan*/  HCRYPTPROV ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPT_DELETEKEYSET ; 
 int /*<<< orphan*/  CRYPT_NEWKEYSET ; 
 int /*<<< orphan*/  CryptAcquireContextA (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CryptReleaseContext (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MS_DEF_PROV_A ; 
 int /*<<< orphan*/  PROV_RSA_FULL ; 
 int /*<<< orphan*/  cspName ; 
 int /*<<< orphan*/  ok (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  testExportPublicKey (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  testImportPublicKey (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void testPortPublicKeyInfo(void)
{
    HCRYPTPROV csp;
    BOOL ret;
    PCERT_PUBLIC_KEY_INFO info = NULL;

    /* Just in case a previous run failed, delete this thing */
    CryptAcquireContextA(&csp, cspName, MS_DEF_PROV_A, PROV_RSA_FULL,
     CRYPT_DELETEKEYSET);
    ret = CryptAcquireContextA(&csp, cspName, MS_DEF_PROV_A, PROV_RSA_FULL,
     CRYPT_NEWKEYSET);
    ok(ret,"CryptAcquireContextA failed\n");

    testExportPublicKey(csp, &info);
    testImportPublicKey(csp, info);

    HeapFree(GetProcessHeap(), 0, info);
    CryptReleaseContext(csp, 0);
    ret = CryptAcquireContextA(&csp, cspName, MS_DEF_PROV_A, PROV_RSA_FULL,
     CRYPT_DELETEKEYSET);
    ok(ret,"CryptAcquireContextA failed\n");
}