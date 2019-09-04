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
typedef  int DWORD ;

/* Variables and functions */

__attribute__((used)) static inline unsigned int fixup_d3dcolor(DWORD *dst_color)
{
    DWORD src_color = *dst_color;

    /* Color conversion like in draw_primitive_immediate_mode(). Watch out for
     * endianness. If we want this to work on big-endian machines as well we
     * have to consider more things.
     *
     * 0xff000000: Alpha mask
     * 0x00ff0000: Blue mask
     * 0x0000ff00: Green mask
     * 0x000000ff: Red mask
     */
    *dst_color = 0;
    *dst_color |= (src_color & 0xff00ff00u);         /* Alpha Green */
    *dst_color |= (src_color & 0x00ff0000u) >> 16;   /* Red */
    *dst_color |= (src_color & 0x000000ffu) << 16;   /* Blue */

    return sizeof(*dst_color);
}