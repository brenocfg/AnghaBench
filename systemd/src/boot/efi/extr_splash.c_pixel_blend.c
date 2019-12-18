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
typedef  int /*<<< orphan*/  VOID ;
typedef  int UINT32 ;

/* Variables and functions */

__attribute__((used)) static VOID pixel_blend(UINT32 *dst, const UINT32 source) {
        UINT32 alpha, src, src_rb, src_g, dst_rb, dst_g, rb, g;

        alpha = (source & 0xff);

        /* convert src from RGBA to XRGB */
        src = source >> 8;

        /* decompose into RB and G components */
        src_rb = (src & 0xff00ff);
        src_g  = (src & 0x00ff00);

        dst_rb = (*dst & 0xff00ff);
        dst_g  = (*dst & 0x00ff00);

        /* blend */
        rb = ((((src_rb - dst_rb) * alpha + 0x800080) >> 8) + dst_rb) & 0xff00ff;
        g  = ((((src_g  -  dst_g) * alpha + 0x008000) >> 8) +  dst_g) & 0x00ff00;

        *dst = (rb | g);
}