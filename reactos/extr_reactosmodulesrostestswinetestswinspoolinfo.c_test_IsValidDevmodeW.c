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
typedef  int /*<<< orphan*/  DEVMODEW ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 scalar_t__ pIsValidDevmodeW (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_IsValidDevmodeW(void)
{
    BOOL br;

    if (!pIsValidDevmodeW)
    {
        win_skip("IsValidDevmodeW not implemented.\n");
        return;
    }

    br = pIsValidDevmodeW(NULL, 0);
    ok(br == FALSE, "Got %d\n", br);

    br = pIsValidDevmodeW(NULL, 1);
    ok(br == FALSE, "Got %d\n", br);

    br = pIsValidDevmodeW(NULL, sizeof(DEVMODEW));
    ok(br == FALSE, "Got %d\n", br);
}