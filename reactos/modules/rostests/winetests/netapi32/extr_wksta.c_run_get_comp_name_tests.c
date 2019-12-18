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
typedef  int /*<<< orphan*/ * LPWSTR ;

/* Variables and functions */
 scalar_t__ NERR_Success ; 
 int /*<<< orphan*/  computer_name ; 
 int /*<<< orphan*/  lstrcmpW (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*) ; 
 int /*<<< orphan*/  pNetApiBufferFree (int /*<<< orphan*/ *) ; 
 scalar_t__ pNetpGetComputerName (int /*<<< orphan*/ **) ; 

__attribute__((used)) static void run_get_comp_name_tests(void)
{
    LPWSTR ws = NULL;

    ok(pNetpGetComputerName(&ws) == NERR_Success, "Computer name is retrieved\n");
    ok(!lstrcmpW(computer_name, ws), "This is really computer name\n");
    pNetApiBufferFree(ws);
}