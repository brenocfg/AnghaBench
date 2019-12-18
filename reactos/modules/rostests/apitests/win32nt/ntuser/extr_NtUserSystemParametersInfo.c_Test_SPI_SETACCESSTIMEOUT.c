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
typedef  int /*<<< orphan*/  atoOrig ;
struct TYPE_3__ {int cbSize; } ;
typedef  TYPE_1__ ACCESSTIMEOUT ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int NtUserSystemParametersInfo (int /*<<< orphan*/ ,int,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPI_GETACCESSTIMEOUT ; 
 int /*<<< orphan*/  SPI_SETACCESSTIMEOUT ; 
 int /*<<< orphan*/  TEST (int) ; 

void
Test_SPI_SETACCESSTIMEOUT(void)
{
    ACCESSTIMEOUT atoOrig, atoTmp;

    /* Get original values */
    atoOrig.cbSize = sizeof(ACCESSTIMEOUT);
    ASSERT(NtUserSystemParametersInfo(SPI_GETACCESSTIMEOUT, 0, &atoOrig, 0) == 1);

    atoTmp.cbSize = sizeof(ACCESSTIMEOUT) - 1;
    TEST(NtUserSystemParametersInfo(SPI_GETACCESSTIMEOUT, 0, &atoTmp, 0) == 0);
    atoTmp.cbSize = sizeof(ACCESSTIMEOUT) + 1;
    TEST(NtUserSystemParametersInfo(SPI_GETACCESSTIMEOUT, 0, &atoTmp, 0) == 0);
    atoTmp.cbSize = sizeof(ACCESSTIMEOUT);
    TEST(NtUserSystemParametersInfo(SPI_GETACCESSTIMEOUT, 0, &atoTmp, 0) == 1);
    atoTmp.cbSize = sizeof(ACCESSTIMEOUT);
    TEST(NtUserSystemParametersInfo(SPI_GETACCESSTIMEOUT, 1, &atoTmp, 0) == 0);
    atoTmp.cbSize = sizeof(ACCESSTIMEOUT);
    TEST(NtUserSystemParametersInfo(SPI_GETACCESSTIMEOUT, -1, &atoTmp, 0) == 0);
    atoTmp.cbSize = sizeof(ACCESSTIMEOUT);
    TEST(NtUserSystemParametersInfo(SPI_GETACCESSTIMEOUT, sizeof(ACCESSTIMEOUT), &atoTmp, 0) == 1);
    atoTmp.cbSize = sizeof(ACCESSTIMEOUT);
    TEST(NtUserSystemParametersInfo(SPI_GETACCESSTIMEOUT, sizeof(ACCESSTIMEOUT)-1, &atoTmp, 0) == 0);
    atoTmp.cbSize = sizeof(ACCESSTIMEOUT);
    TEST(NtUserSystemParametersInfo(SPI_GETACCESSTIMEOUT, sizeof(ACCESSTIMEOUT)+1, &atoTmp, 0) == 0);

    /* Restore original values */
    ASSERT(NtUserSystemParametersInfo(SPI_SETACCESSTIMEOUT, sizeof(atoOrig), &atoOrig, 0) == 1);
}