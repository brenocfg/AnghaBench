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
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPT_DELETEKEYSET ; 
 int /*<<< orphan*/  CryptAcquireContextA (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CryptReleaseContext (int /*<<< orphan*/ ,int) ; 
 scalar_t__ GetLastError () ; 
 scalar_t__ NTE_BAD_FLAGS ; 
 int /*<<< orphan*/  PROV_RSA_AES ; 
 int /*<<< orphan*/  hProv ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  szContainer ; 

__attribute__((used)) static void clean_up_aes_environment(void)
{
    BOOL result;

    result = CryptReleaseContext(hProv, 1);
    ok(!result && GetLastError()==NTE_BAD_FLAGS, "%08x\n", GetLastError());

    CryptAcquireContextA(&hProv, szContainer, NULL, PROV_RSA_AES, CRYPT_DELETEKEYSET);
}