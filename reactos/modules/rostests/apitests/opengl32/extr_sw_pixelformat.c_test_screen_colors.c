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
struct test_color {int dummy; } ;
typedef  int /*<<< orphan*/  pfd ;
struct TYPE_3__ {int dwFlags; } ;
typedef  TYPE_1__ PIXELFORMATDESCRIPTOR ;
typedef  int /*<<< orphan*/ * HWND ;
typedef  int /*<<< orphan*/  HDC ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CreateWindowA (char*,char*,int /*<<< orphan*/ ,int,int,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int DescribePixelFormat (int /*<<< orphan*/ ,int,int,TYPE_1__*) ; 
 int /*<<< orphan*/  DestroyWindow (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetDC (int /*<<< orphan*/ *) ; 
 int PFD_GENERIC_FORMAT ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WS_OVERLAPPEDWINDOW ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/ * test_depths ; 
 int /*<<< orphan*/  test_format (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct test_color const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_screen_colors(const struct test_color **colors)
{
    int pf, num_pf, ret;
    int i, j;
    HDC hdc;
    HWND hwnd;
    PIXELFORMATDESCRIPTOR pfd;

    hwnd = CreateWindowA("static", "Title", WS_OVERLAPPEDWINDOW, 10, 10, 200, 200, NULL, NULL,
            NULL, NULL);
    if (!hwnd)
    {
        ok(hwnd != NULL, "Failed to create a window.\n");
        return;
    }

    hdc = GetDC( hwnd );
    num_pf = DescribePixelFormat(hdc, 0, 0, NULL);
    ok(num_pf > 0, "DescribePixelFormat failed.\n");

    for (pf = 1; pf <= num_pf; pf++)
    {
        ret = DescribePixelFormat(hdc, pf, sizeof(pfd), &pfd);
        ok(ret == num_pf, "Number of pixel formats changed!\n");

        if (pfd.dwFlags & PFD_GENERIC_FORMAT)
            break;
    }

    ok(pf < num_pf, "No generic pixel format!\n");
    
    /* First the formats compatible with the DC */
    for (i = 0; i < 3; i++)
    {
        /* Single buffered first */
        for (j = 0; j < ARRAY_SIZE(test_depths); j++)
        {
            test_format(hdc, num_pf, pf++, &colors[0][i], test_depths[j], TRUE, FALSE);
        }

        /* Then double buffered */
        for (j = 0; j < ARRAY_SIZE(test_depths); j++)
        {
            test_format(hdc, num_pf, pf++, &colors[0][i], test_depths[j], TRUE, TRUE);
        }
    }
    
    colors++;

    /* Then the rest */
    while (*colors)
    {
        for (i = 0; i < 3; i++)
        {
            for (j = 0; j < ARRAY_SIZE(test_depths); j++)
            {
                test_format(hdc, num_pf, pf++, &colors[0][i], test_depths[j], FALSE, FALSE);
            }
        }
        colors++;
    }

    /* We must have tested all generic formats. */
    ok(pf - 1 == num_pf, "We didn't test all generic formats : tested %u, total %u.\n", pf, num_pf);

    ReleaseDC( hwnd, hdc );
    DestroyWindow( hwnd );
}