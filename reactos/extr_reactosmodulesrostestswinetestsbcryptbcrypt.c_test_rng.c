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
typedef  int /*<<< orphan*/  len ;
typedef  int ULONG ;
typedef  int /*<<< orphan*/  UCHAR ;
typedef  scalar_t__ NTSTATUS ;
typedef  int /*<<< orphan*/ * BCRYPT_ALG_HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  BCRYPT_OBJECT_LENGTH ; 
 int /*<<< orphan*/  BCRYPT_RNG_ALGORITHM ; 
 scalar_t__ BCryptCloseAlgorithmProvider (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ BCryptGenRandom (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 scalar_t__ BCryptGetProperty (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int*,int /*<<< orphan*/ ) ; 
 scalar_t__ BCryptOpenAlgorithmProvider (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MS_PRIMITIVE_PROVIDER ; 
 scalar_t__ STATUS_NOT_SUPPORTED ; 
 scalar_t__ STATUS_SUCCESS ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  test_alg_name (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void test_rng(void)
{
    BCRYPT_ALG_HANDLE alg;
    ULONG size, len;
    UCHAR buf[16];
    NTSTATUS ret;

    alg = NULL;
    ret = BCryptOpenAlgorithmProvider(&alg, BCRYPT_RNG_ALGORITHM, MS_PRIMITIVE_PROVIDER, 0);
    ok(ret == STATUS_SUCCESS, "got %08x\n", ret);
    ok(alg != NULL, "alg not set\n");

    len = size = 0xdeadbeef;
    ret = BCryptGetProperty(alg, BCRYPT_OBJECT_LENGTH, (UCHAR *)&len, sizeof(len), &size, 0);
    ok(ret == STATUS_NOT_SUPPORTED, "got %08x\n", ret);

    test_alg_name(alg, "RNG");

    memset(buf, 0, 16);
    ret = BCryptGenRandom(alg, buf, 8, 0);
    ok(ret == STATUS_SUCCESS, "got %08x\n", ret);
    ok(memcmp(buf, buf + 8, 8), "got zeroes\n");

    ret = BCryptCloseAlgorithmProvider(alg, 0);
    ok(ret == STATUS_SUCCESS, "got %08x\n", ret);
}