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
typedef  int BOOL ;

/* Variables and functions */
 int FALSE ; 
#define  PNG_COLOR_TYPE_GRAY 132 
#define  PNG_COLOR_TYPE_GRAY_ALPHA 131 
#define  PNG_COLOR_TYPE_PALETTE 130 
#define  PNG_COLOR_TYPE_RGB 129 
#define  PNG_COLOR_TYPE_RGB_ALPHA 128 
 int /*<<< orphan*/  ok (int /*<<< orphan*/ ,char*,int,int) ; 

__attribute__((used)) static BOOL is_valid_png_type_depth(int color_type, int bit_depth, BOOL plte)
{
    switch (color_type)
    {
    case PNG_COLOR_TYPE_GRAY:
        return bit_depth == 1 || bit_depth == 2 || bit_depth == 4 || bit_depth == 8 || bit_depth == 16;

    case PNG_COLOR_TYPE_RGB:
        return bit_depth == 8 || bit_depth == 16;

    case PNG_COLOR_TYPE_PALETTE:
        return (bit_depth == 1 || bit_depth == 2 || bit_depth == 4 || bit_depth == 8) && plte;

    case PNG_COLOR_TYPE_GRAY_ALPHA:
        return bit_depth == 8 || bit_depth == 16;

    case PNG_COLOR_TYPE_RGB_ALPHA:
        return bit_depth == 8 || bit_depth == 16;

    default:
        ok(0, "unknown PNG type %d, depth %d\n", color_type, bit_depth);
        return FALSE;
    }
}