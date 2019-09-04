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
struct wined3d_format {unsigned int red_size; unsigned int red_offset; unsigned int green_size; unsigned int green_offset; unsigned int blue_size; unsigned int blue_offset; } ;
typedef  unsigned int DWORD ;

/* Variables and functions */

__attribute__((used)) static void get_color_masks(const struct wined3d_format *format, DWORD *masks)
{
    masks[0] = ((1u << format->red_size) - 1) << format->red_offset;
    masks[1] = ((1u << format->green_size) - 1) << format->green_offset;
    masks[2] = ((1u << format->blue_size) - 1) << format->blue_offset;
}