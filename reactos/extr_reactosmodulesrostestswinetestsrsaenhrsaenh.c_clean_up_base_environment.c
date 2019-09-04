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
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPT_DELETEKEYSET ; 
 int /*<<< orphan*/  CryptAcquireContextA (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ CryptReleaseContext (int /*<<< orphan*/ ,int) ; 
 scalar_t__ ERROR_INVALID_PARAMETER ; 
 scalar_t__ GetLastError () ; 
 scalar_t__ NTE_BAD_FLAGS ; 
 int /*<<< orphan*/  PROV_RSA_FULL ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 scalar_t__ broken (scalar_t__) ; 
 int /*<<< orphan*/  hProv ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  szContainer ; 
 int /*<<< orphan*/  szProvider ; 

__attribute__((used)) static void clean_up_base_environment(void)
{
    BOOL result;

    SetLastError(0xdeadbeef);
    result = CryptReleaseContext(hProv, 1);
    ok(!result || broken(result) /* Win98 */, "Expected failure\n");
    ok(GetLastError()==NTE_BAD_FLAGS, "Expected NTE_BAD_FLAGS, got %08x\n", GetLastError());
        
    /* Just to prove that Win98 also released the CSP */
    SetLastError(0xdeadbeef);
    result = CryptReleaseContext(hProv, 0);
    ok(!result && GetLastError()==ERROR_INVALID_PARAMETER, "%08x\n", GetLastError());

    CryptAcquireContextA(&hProv, szContainer, szProvider, PROV_RSA_FULL, CRYPT_DELETEKEYSET);
}