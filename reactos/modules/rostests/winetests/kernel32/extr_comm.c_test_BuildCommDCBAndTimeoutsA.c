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
typedef  int /*<<< orphan*/  TEST ;
typedef  int /*<<< orphan*/  DCB ;
typedef  int /*<<< orphan*/  COMMTIMEOUTS ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  BuildCommDCBAndTimeoutsA (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  check_dcb (char*,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  check_result (char*,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_timeouts (char*,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void test_BuildCommDCBAndTimeoutsA(const char *string, const TEST *ptest, int initial_value, const DCB *pexpected_dcb, const COMMTIMEOUTS *pexpected_timeouts)
{
	BOOL result;
	DCB dcb;
	COMMTIMEOUTS timeouts;

	/* set initial conditions */
	memset(&dcb, initial_value, sizeof(DCB));
	memset(&timeouts, initial_value, sizeof(COMMTIMEOUTS));
	SetLastError(0xdeadbeef);

	result = BuildCommDCBAndTimeoutsA(string, &dcb, &timeouts);

	/* check results */
	check_result("BuildCommDCBAndTimeoutsA", ptest, initial_value, result);
	check_dcb("BuildCommDCBAndTimeoutsA", ptest, initial_value, &dcb, pexpected_dcb);
	check_timeouts("BuildCommDCBAndTimeoutsA", ptest, initial_value, &timeouts, pexpected_timeouts);
}