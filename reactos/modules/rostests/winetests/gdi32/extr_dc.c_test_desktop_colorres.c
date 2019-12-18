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
typedef  int /*<<< orphan*/  HDC ;

/* Variables and functions */
 int /*<<< orphan*/  BITSPIXEL ; 
 int /*<<< orphan*/  COLORRES ; 
 int /*<<< orphan*/  GetDC (int /*<<< orphan*/ *) ; 
 int GetDeviceCaps (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void test_desktop_colorres(void)
{
    HDC hdc = GetDC(NULL);
    int bitspixel, colorres;

    bitspixel = GetDeviceCaps(hdc, BITSPIXEL);
    ok(bitspixel != 0, "Expected to get valid BITSPIXEL capability value\n");

    colorres = GetDeviceCaps(hdc, COLORRES);
    ok(colorres != 0 ||
       broken(colorres == 0), /* Win9x */
       "Expected to get valid COLORRES capability value\n");

    if (colorres)
    {
        switch (bitspixel)
        {
        case 8:
            ok(colorres == 18,
               "Expected COLORRES to be 18, got %d\n", colorres);
            break;
        case 16:
            ok(colorres == 16,
               "Expected COLORRES to be 16, got %d\n", colorres);
            break;
        case 24:
        case 32:
            ok(colorres == 24,
               "Expected COLORRES to be 24, got %d\n", bitspixel);
            break;
        default:
            ok(0, "Got unknown BITSPIXEL %d with COLORRES %d\n", bitspixel, colorres);
            break;
        }
    }

    ReleaseDC(NULL, hdc);
}