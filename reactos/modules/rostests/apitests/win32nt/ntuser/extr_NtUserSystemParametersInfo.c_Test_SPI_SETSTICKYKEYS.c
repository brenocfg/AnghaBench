#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int cbSize; int dwFlags; } ;
typedef  TYPE_1__ STICKYKEYS ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int NtUserSystemParametersInfo (int /*<<< orphan*/ ,int,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPI_GETSTICKYKEYS ; 
 int /*<<< orphan*/  SPI_SETSTICKYKEYS ; 
 int /*<<< orphan*/  TEST (int) ; 

void
Test_SPI_SETSTICKYKEYS(void)
{
    STICKYKEYS skOrig, sk;

    /* Get original values */
    skOrig.cbSize = sizeof(STICKYKEYS);
    ASSERT(NtUserSystemParametersInfo(SPI_GETSTICKYKEYS, 0, &skOrig, 0) == 1);

    sk.cbSize = sizeof(STICKYKEYS)+1;
    TEST(NtUserSystemParametersInfo(SPI_GETSTICKYKEYS, 0, &sk, 0) == 0);

    sk.cbSize = sizeof(STICKYKEYS)-1;
    TEST(NtUserSystemParametersInfo(SPI_GETSTICKYKEYS, 0, &sk, 0) == 0);

    sk.cbSize = sizeof(STICKYKEYS);
    TEST(NtUserSystemParametersInfo(SPI_GETSTICKYKEYS, 1, &sk, 0) == 0);
    TEST(NtUserSystemParametersInfo(SPI_GETSTICKYKEYS, -1, &sk, 0) == 0);
    TEST(NtUserSystemParametersInfo(SPI_GETSTICKYKEYS, sk.cbSize, &sk, 0) == 1);
    TEST(NtUserSystemParametersInfo(SPI_GETSTICKYKEYS, sk.cbSize-1, &sk, 0) == 0);
    TEST(NtUserSystemParametersInfo(SPI_GETSTICKYKEYS, sk.cbSize+1, &sk, 0) == 0);

    sk = skOrig;
    sk.dwFlags = (skOrig.dwFlags ^ 1);
    TEST(NtUserSystemParametersInfo(SPI_SETSTICKYKEYS, sk.cbSize+1, &sk, 0) == 0);
    TEST(NtUserSystemParametersInfo(SPI_SETSTICKYKEYS, sk.cbSize-1, &sk, 0) == 0);
    TEST(NtUserSystemParametersInfo(SPI_SETSTICKYKEYS, sk.cbSize, &sk, 0) == 1);

    sk = skOrig;
    TEST(NtUserSystemParametersInfo(SPI_GETSTICKYKEYS, 0, &sk, 0) == 1);
    TEST(sk.dwFlags == (skOrig.dwFlags ^ 1));

    /* Restore original values */
    skOrig.cbSize = sizeof(STICKYKEYS);
    ASSERT(NtUserSystemParametersInfo(SPI_SETSTICKYKEYS, 0, &skOrig, 0) == 1);

}