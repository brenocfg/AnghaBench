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
 int /*<<< orphan*/  ok (int,char*,int) ; 
 int pUlFromSzHex (char*) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_UlFromSzHex(void)
{
    if (!pUlFromSzHex)
    {
        win_skip("UlFromSzHex is not available\n");
        return;
    }

    ok(pUlFromSzHex("fF") == 0xffu,
       "UlFromSzHex: expected 0xff, got 0x%x\n", pUlFromSzHex("fF"));

    ok(pUlFromSzHex(" c") == 0, "UlFromSzHex: expected 0x0. got 0x%x\n",
       pUlFromSzHex(" c"));
}