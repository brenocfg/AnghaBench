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
typedef  int /*<<< orphan*/  COMMTIMEOUTS ;

/* Variables and functions */
 int /*<<< orphan*/  ReadIntervalTimeout ; 
 int /*<<< orphan*/  ReadTotalTimeoutConstant ; 
 int /*<<< orphan*/  ReadTotalTimeoutMultiplier ; 
 int /*<<< orphan*/  WriteTotalTimeoutConstant ; 
 int /*<<< orphan*/  WriteTotalTimeoutMultiplier ; 
 int /*<<< orphan*/  check_timeouts_member (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void check_timeouts(const char *function, const TEST *ptest, int initial_value, const COMMTIMEOUTS *ptimeouts1, const COMMTIMEOUTS *ptimeouts2)
{
	check_timeouts_member(ReadIntervalTimeout);
	check_timeouts_member(ReadTotalTimeoutMultiplier);
	check_timeouts_member(ReadTotalTimeoutConstant);
	check_timeouts_member(WriteTotalTimeoutMultiplier);
	check_timeouts_member(WriteTotalTimeoutConstant);
}