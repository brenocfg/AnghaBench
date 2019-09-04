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
 int /*<<< orphan*/  SPI_GETMOUSECLICKLOCK ; 
 int /*<<< orphan*/  SPI_SETMOUSECLICKLOCK ; 
 int /*<<< orphan*/  Test_UserPref (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UPM_CLICKLOCK ; 

void
Test_SPI_SETMOUSECLICKLOCK(void)
{
    Test_UserPref(SPI_GETMOUSECLICKLOCK, SPI_SETMOUSECLICKLOCK, UPM_CLICKLOCK);
}