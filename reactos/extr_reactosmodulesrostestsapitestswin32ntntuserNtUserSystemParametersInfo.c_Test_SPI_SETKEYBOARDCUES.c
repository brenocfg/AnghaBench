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
 int /*<<< orphan*/  SPI_GETKEYBOARDCUES ; 
 int /*<<< orphan*/  SPI_SETKEYBOARDCUES ; 
 int /*<<< orphan*/  Test_UserPref (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UPM_KEYBOARDCUES ; 

void
Test_SPI_SETKEYBOARDCUES(void)
{
    Test_UserPref(SPI_GETKEYBOARDCUES, SPI_SETKEYBOARDCUES, UPM_KEYBOARDCUES);
}