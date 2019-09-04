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
struct vec4 {float x; float y; float z; float w; } ;
typedef  size_t ULONG ;
struct TYPE_3__ {float peRed; float peGreen; float peBlue; float peFlags; } ;
typedef  TYPE_1__ PALETTEENTRY ;

/* Variables and functions */

__attribute__((used)) static void index_to_rgba(const struct vec4 *index, struct vec4 *rgba, const PALETTEENTRY *palette)
{
    ULONG idx = (ULONG)(index->x * 255.0f + 0.5f);

    rgba->x = palette[idx].peRed / 255.0f;
    rgba->y = palette[idx].peGreen / 255.0f;
    rgba->z = palette[idx].peBlue / 255.0f;
    rgba->w = palette[idx].peFlags / 255.0f; /* peFlags is the alpha component in DX8 and higher */
}