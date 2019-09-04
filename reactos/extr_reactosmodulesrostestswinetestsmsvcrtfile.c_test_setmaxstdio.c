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
 int _setmaxstdio (int) ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 

__attribute__((used)) static void test_setmaxstdio(void)
{
    ok(2048 == _setmaxstdio(2048),"_setmaxstdio returned %d instead of 2048\n",_setmaxstdio(2048));
    ok(-1 == _setmaxstdio(2049),"_setmaxstdio returned %d instead of -1\n",_setmaxstdio(2049));
}