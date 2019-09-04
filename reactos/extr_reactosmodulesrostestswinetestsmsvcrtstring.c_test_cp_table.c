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
 int /*<<< orphan*/  _setmbcp (int) ; 
 int /*<<< orphan*/  ok (int,char*,int,int,int,int) ; 
 int* p_mbctype ; 

__attribute__((used)) static void test_cp_table(int cp, int *result)
{
    int i;
    int count = 0;
    int curr = 0;
    _setmbcp(cp);
    for (i = 0; i < 256; i++)
    {
        if (count == 0)
        {
            curr = result[0];
            count = result[1];
            result += 2;
        }
        ok(p_mbctype[i] == curr, "CP%d: Mismatch in ctype for character %d - %d instead of %d\n", cp, i-1, p_mbctype[i], curr);
        count--;
    }
}