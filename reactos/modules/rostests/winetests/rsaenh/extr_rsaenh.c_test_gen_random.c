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
typedef  int /*<<< orphan*/  rnd2 ;
typedef  int /*<<< orphan*/  rnd1 ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ CryptGenRandom (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 scalar_t__ GetLastError () ; 
 scalar_t__ NTE_FAIL ; 
 int /*<<< orphan*/  hProv ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ok (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static void test_gen_random(void)
{
    BOOL result;
    BYTE rnd1[16], rnd2[16];

    memset(rnd1, 0, sizeof(rnd1));
    memset(rnd2, 0, sizeof(rnd2));

    result = CryptGenRandom(hProv, sizeof(rnd1), rnd1);
    if (!result && GetLastError() == NTE_FAIL) {
        /* rsaenh compiled without OpenSSL */
        return;
    }
    
    ok(result, "%08x\n", GetLastError());

    result = CryptGenRandom(hProv, sizeof(rnd2), rnd2);
    ok(result, "%08x\n", GetLastError());

    ok(memcmp(rnd1, rnd2, sizeof(rnd1)), "CryptGenRandom generates non random data\n");
}