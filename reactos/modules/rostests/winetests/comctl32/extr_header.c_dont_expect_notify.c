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
typedef  int /*<<< orphan*/  INT ;

/* Variables and functions */
 int nExpectedNotify ; 
 int /*<<< orphan*/  nUnexpectedNotify ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 
 int /*<<< orphan*/ * unexpectedNotify ; 

__attribute__((used)) static void dont_expect_notify(INT iCode)
{
    ok(nExpectedNotify < 10, "notification count %d\n", nExpectedNotify);
    if (nExpectedNotify < 10)
        unexpectedNotify[nUnexpectedNotify++] = iCode;
}