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
typedef  int USHORT ;

/* Variables and functions */
 int /*<<< orphan*/  ok (int,char*,int,int,int) ; 
 int /*<<< orphan*/  pSwapPword (int*,int) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_SwapPword(void)
{
    USHORT shorts[3];

    if (!pSwapPword)
    {
        win_skip("SwapPword is not available\n");
        return;
    }

    shorts[0] = 0xff01;
    shorts[1] = 0x10ff;
    shorts[2] = 0x2001;
    pSwapPword(shorts, 2);
    ok((shorts[0] == 0x01ff && shorts[1] == 0xff10 && shorts[2] == 0x2001),
       "Expected {0x01ff,0xff10,0x2001}, got {0x%04x,0x%04x,0x%04x}\n",
       shorts[0], shorts[1], shorts[2]);
}