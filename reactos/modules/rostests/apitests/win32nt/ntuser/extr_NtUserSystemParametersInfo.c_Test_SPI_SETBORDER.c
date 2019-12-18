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
typedef  int INT ;

/* Variables and functions */
 int GetSystemMetrics (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NtUserSystemParametersInfo (int /*<<< orphan*/ ,int,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SM_CXBORDER ; 
 int /*<<< orphan*/  SPIF_UPDATEINIFILE ; 
 int /*<<< orphan*/  SPI_GETBORDER ; 
 int /*<<< orphan*/  SPI_SETBORDER ; 
 int /*<<< orphan*/  TEST (int) ; 

void
Test_SPI_SETBORDER(void)
{
    INT iOrig, iTemp = 0;

    /* Get original value */
    NtUserSystemParametersInfo(SPI_GETBORDER, 0, &iOrig, 0);

    /* Value 0 */
    NtUserSystemParametersInfo(SPI_SETBORDER, 0, NULL, SPIF_UPDATEINIFILE);
    NtUserSystemParametersInfo(SPI_GETBORDER, 0, &iTemp, 0);
    TEST(iTemp == 1);
    TEST(GetSystemMetrics(SM_CXBORDER) == 1);

    /* Value 1 */
    NtUserSystemParametersInfo(SPI_SETBORDER, 1, NULL, SPIF_UPDATEINIFILE);
    NtUserSystemParametersInfo(SPI_GETBORDER, 0, &iTemp, 0);
    TEST(iTemp == 1);
//  Test_MetricKey(pti, VAL_BORDER, 1);

    /* Value 2 */
    NtUserSystemParametersInfo(SPI_SETBORDER, 2, NULL, SPIF_UPDATEINIFILE);
    NtUserSystemParametersInfo(SPI_GETBORDER, 0, &iTemp, 0);
    TEST(iTemp == 2);
    TEST(GetSystemMetrics(SM_CXBORDER) == 1);

    /* Restore original value */
    NtUserSystemParametersInfo(SPI_SETBORDER, iOrig, NULL, SPIF_UPDATEINIFILE);

}