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
struct test_color {int dummy; } ;
typedef  int INT ;
typedef  int /*<<< orphan*/ * HDC ;
typedef  int /*<<< orphan*/ * HBITMAP ;

/* Variables and functions */
 int ARRAY_SIZE (int const*) ; 
 int /*<<< orphan*/ * CreateCompatibleDC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SelectObject (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * create_dib_section (int const,void**) ; 
 int /*<<< orphan*/  ok (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  test_bitmap_colors (int /*<<< orphan*/ *,struct test_color const**) ; 
 int /*<<< orphan*/  trace (char*,int const) ; 

__attribute__((used)) static void test_bitmap_formats(const struct test_color ** colors)
{
    HBITMAP oldBmp, dib;
    HDC hdc;
    static const INT bpps [] = {4, 8, 16, 24, 32};
    INT i;
    void* dib_buffer;

    hdc = CreateCompatibleDC(NULL);
    ok (hdc != NULL, "Failed creating a memory DC.\n");

    for (i = 0; i < ARRAY_SIZE(bpps); i++)
    {
        dib = create_dib_section(bpps[i], &dib_buffer);
        ok(dib != NULL, "Failed to create DIB for %u bpp\n", bpps[i]);

        oldBmp = SelectObject(hdc, dib);
        ok (oldBmp != NULL, "Failed to select the DIB\n");

        trace("testing DIB %ubpp\n", bpps[i]);
        /* For mem DC, this is always the depth of the screen which is taken into account */
        test_bitmap_colors(hdc, colors);

        SelectObject(hdc, oldBmp);
        DeleteObject(dib);
    }
}