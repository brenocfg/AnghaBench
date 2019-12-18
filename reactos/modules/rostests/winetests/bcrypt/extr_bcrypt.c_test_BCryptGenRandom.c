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
typedef  int /*<<< orphan*/  buffer ;
typedef  int /*<<< orphan*/  UCHAR ;
typedef  scalar_t__ NTSTATUS ;

/* Variables and functions */
 int BCRYPT_RNG_USE_ENTROPY_IN_BUFFER ; 
 int BCRYPT_USE_SYSTEM_PREFERRED_RNG ; 
 scalar_t__ BCryptGenRandom (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 
 scalar_t__ STATUS_INVALID_HANDLE ; 
 scalar_t__ STATUS_INVALID_PARAMETER ; 
 scalar_t__ STATUS_SUCCESS ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void test_BCryptGenRandom(void)
{
    NTSTATUS ret;
    UCHAR buffer[256];

    ret = BCryptGenRandom(NULL, NULL, 0, 0);
    ok(ret == STATUS_INVALID_HANDLE, "Expected STATUS_INVALID_HANDLE, got 0x%x\n", ret);
    ret = BCryptGenRandom(NULL, buffer, 0, 0);
    ok(ret == STATUS_INVALID_HANDLE, "Expected STATUS_INVALID_HANDLE, got 0x%x\n", ret);
    ret = BCryptGenRandom(NULL, buffer, sizeof(buffer), 0);
    ok(ret == STATUS_INVALID_HANDLE, "Expected STATUS_INVALID_HANDLE, got 0x%x\n", ret);
    ret = BCryptGenRandom(NULL, buffer, sizeof(buffer), BCRYPT_USE_SYSTEM_PREFERRED_RNG);
    ok(ret == STATUS_SUCCESS, "Expected success, got 0x%x\n", ret);
    ret = BCryptGenRandom(NULL, buffer, sizeof(buffer),
          BCRYPT_USE_SYSTEM_PREFERRED_RNG|BCRYPT_RNG_USE_ENTROPY_IN_BUFFER);
    ok(ret == STATUS_SUCCESS, "Expected success, got 0x%x\n", ret);
    ret = BCryptGenRandom(NULL, NULL, sizeof(buffer), BCRYPT_USE_SYSTEM_PREFERRED_RNG);
    ok(ret == STATUS_INVALID_PARAMETER, "Expected STATUS_INVALID_PARAMETER, got 0x%x\n", ret);

    /* Zero sized buffer should work too */
    ret = BCryptGenRandom(NULL, buffer, 0, BCRYPT_USE_SYSTEM_PREFERRED_RNG);
    ok(ret == STATUS_SUCCESS, "Expected success, got 0x%x\n", ret);

    /* Test random number generation - It's impossible for a sane RNG to return 8 zeros */
    memset(buffer, 0, 16);
    ret = BCryptGenRandom(NULL, buffer, 8, BCRYPT_USE_SYSTEM_PREFERRED_RNG);
    ok(ret == STATUS_SUCCESS, "Expected success, got 0x%x\n", ret);
    ok(memcmp(buffer, buffer + 8, 8), "Expected a random number, got 0\n");
}