#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_4__ {int i_pitch; int i_visible_lines; int /*<<< orphan*/  i_visible_pitch; int /*<<< orphan*/ * p_pixels; } ;
typedef  TYPE_1__ plane_t ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void Plane_VFlip(plane_t *restrict dst, const plane_t *restrict src)
{
    const uint8_t *src_pixels = src->p_pixels;
    uint8_t *restrict dst_pixels = dst->p_pixels;

    dst_pixels += dst->i_pitch * dst->i_visible_lines;
    for (int y = 0; y < dst->i_visible_lines; y++) {
        dst_pixels -= dst->i_pitch;
        memcpy(dst_pixels, src_pixels, dst->i_visible_pitch);
        src_pixels += src->i_pitch;
    }
}