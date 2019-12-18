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
typedef  scalar_t__ ULONG ;

/* Variables and functions */
 int /*<<< orphan*/  ok (int,char*) ; 
 scalar_t__ pFBadRowSet (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_FBadRowSet(void)
{
    ULONG ulRet;

    if (!pFBadRowSet)
    {
        win_skip("FBadRowSet is not available\n");
        return;
    }

    ulRet = pFBadRowSet(NULL);
    ok(ulRet != 0, "FBadRow(null): Expected non-zero, got 0\n");

    /* FIXME */
}