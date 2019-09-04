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

/* Variables and functions */
 int /*<<< orphan*/  ok (int,char*,unsigned int) ; 
 unsigned int pUFromSz (char*) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_UFromSz(void)
{
    if (!pUFromSz)
    {
        win_skip("UFromSz is not available\n");
        return;
    }

    ok(pUFromSz("105679") == 105679u,
       "UFromSz: expected 105679, got %d\n", pUFromSz("105679"));

    ok(pUFromSz(" 4") == 0, "UFromSz: expected 0. got %d\n",
       pUFromSz(" 4"));
}