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
typedef  int /*<<< orphan*/  LPWSTR ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  STATUS_INVALID_PARAMETER ; 
 scalar_t__ STATUS_SUCCESS ; 
 int /*<<< orphan*/  STATUS_VARIABLE_NOT_FOUND ; 
 int /*<<< orphan*/  ok (int,char*) ; 
 scalar_t__ pRtlCreateEnvironment (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ pRtlDestroyEnvironment (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  testSetHelper (int /*<<< orphan*/ *,char*,char*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void testSet(void)
{
    LPWSTR              env;
    char                tmp[16];
    int                 i;

    ok(pRtlCreateEnvironment(FALSE, &env) == STATUS_SUCCESS, "Creating environment\n");

    testSetHelper(&env, "cat", "dog", STATUS_SUCCESS, 0);
    testSetHelper(&env, "cat", "horse", STATUS_SUCCESS, 0);
    testSetHelper(&env, "cat", "zz", STATUS_SUCCESS, 0);
    testSetHelper(&env, "cat", NULL, STATUS_SUCCESS, 0);
    testSetHelper(&env, "cat", NULL, STATUS_SUCCESS, STATUS_VARIABLE_NOT_FOUND);
    testSetHelper(&env, "foo", "meouw", STATUS_SUCCESS, 0);
    testSetHelper(&env, "me=too", "also", STATUS_SUCCESS, STATUS_INVALID_PARAMETER);
    testSetHelper(&env, "me", "too=also", STATUS_SUCCESS, 0);
    testSetHelper(&env, "=too", "also", STATUS_SUCCESS, 0);
    testSetHelper(&env, "=", "also", STATUS_SUCCESS, 0);

    for (i = 0; i < 128; i++)
    {
        sprintf(tmp, "zork%03d", i);
        testSetHelper(&env, tmp, "is alive", STATUS_SUCCESS, 0);
    }

    for (i = 0; i < 128; i++)
    {
        sprintf(tmp, "zork%03d", i);
        testSetHelper(&env, tmp, NULL, STATUS_SUCCESS, 0);
    }
    testSetHelper(&env, "fOo", NULL, STATUS_SUCCESS, 0);

    ok(pRtlDestroyEnvironment(env) == STATUS_SUCCESS, "Destroying environment\n");
}