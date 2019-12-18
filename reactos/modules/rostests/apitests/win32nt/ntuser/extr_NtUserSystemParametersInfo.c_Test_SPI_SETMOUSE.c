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
 int NtUserSystemParametersInfo (int /*<<< orphan*/ ,int,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPIF_UPDATEINIFILE ; 
 int /*<<< orphan*/  SPI_GETMOUSE ; 
 int /*<<< orphan*/  SPI_SETMOUSE ; 
 int /*<<< orphan*/  TEST (int) ; 

void
Test_SPI_SETMOUSE(void)
{
    INT aiOrig[3], aiTemp[3];

    /* Get original value */
    NtUserSystemParametersInfo(SPI_GETMOUSE, 0, aiOrig, 0);

    /* Test uiParam value */
    TEST(NtUserSystemParametersInfo(SPI_GETMOUSE, 0, aiTemp, 0) == 1);
    TEST(NtUserSystemParametersInfo(SPI_GETMOUSE, 1, aiTemp, 0) == 1);
    TEST(NtUserSystemParametersInfo(SPI_GETMOUSE, -1, aiTemp, 0) == 1);
    TEST(NtUserSystemParametersInfo(SPI_GETMOUSE, 0xdeadbeef, aiTemp, 0) == 1);

    /* Set modified values */
    aiTemp[0] = aiOrig[0] + 1;
    aiTemp[1] = aiOrig[1] - 1;
    aiTemp[2] = aiOrig[2] + 2;
    NtUserSystemParametersInfo(SPI_SETMOUSE, 2, aiTemp, SPIF_UPDATEINIFILE);
    aiTemp[0] = aiTemp[1] = aiTemp[2] = 0;

    /* Get new values */
    NtUserSystemParametersInfo(SPI_GETMOUSE, 0, aiTemp, 0);

    /* Test modified values */
    TEST(aiTemp[0] == aiOrig[0] + 1);
    TEST(aiTemp[1] == aiOrig[1] - 1);
    TEST(aiTemp[2] == aiOrig[2] + 2);

    // FIXME: Test registry values

    /* Restore original value */
    NtUserSystemParametersInfo(SPI_SETMOUSE, 0, aiOrig, SPIF_UPDATEINIFILE);
}