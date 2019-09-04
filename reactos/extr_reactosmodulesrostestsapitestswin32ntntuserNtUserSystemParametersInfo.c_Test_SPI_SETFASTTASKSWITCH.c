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
 int NtUserSystemParametersInfo (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPI_SETFASTTASKSWITCH ; 
 int /*<<< orphan*/  TEST (int) ; 

void
Test_SPI_SETFASTTASKSWITCH(void)
{
    char buf[10];
    TEST(NtUserSystemParametersInfo(SPI_SETFASTTASKSWITCH, 0, 0, 0) == 1);
    TEST(NtUserSystemParametersInfo(SPI_SETFASTTASKSWITCH, 0, buf, 0) == 1);


}