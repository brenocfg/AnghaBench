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
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  BuildCommDCBA (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  check_dcb (char*,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  check_result (char*,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void test_BuildCommDCBA(const char *string, const TEST *ptest, int initial_value, const DCB *pexpected_dcb)
{
	BOOL result;
	DCB dcb;

	/* set initial conditions */
	memset(&dcb, initial_value, sizeof(DCB));
	SetLastError(0xdeadbeef);

	result = BuildCommDCBA(string, &dcb);

	/* check results */
	check_result("BuildCommDCBA", ptest, initial_value, result);
	check_dcb("BuildCommDCBA", ptest, initial_value, &dcb, pexpected_dcb);
}