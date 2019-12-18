#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct TYPE_5__ {int i_planes; TYPE_1__* p; } ;
typedef  TYPE_2__ picture_t ;
struct TYPE_4__ {int i_visible_pitch; int i_pitch; int i_visible_lines; int /*<<< orphan*/ * p_pixels; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static void CopyPackedBufferToPicture(picture_t *p_pic, const uint8_t *p_src)
{
    for (int i = 0; i < p_pic->i_planes; ++i)
    {
        uint8_t *p_dst = p_pic->p[i].p_pixels;

        if (p_pic->p[i].i_visible_pitch == p_pic->p[i].i_pitch)
        {
            /* Plane is packed, only one memcpy is needed. */
            uint32_t plane_size = p_pic->p[i].i_pitch * p_pic->p[i].i_visible_lines;
            memcpy(p_dst, p_src, plane_size);
            p_src += plane_size;
            continue;
        }

        for (int i_line = 0; i_line < p_pic->p[i].i_visible_lines; i_line++)
        {
            memcpy(p_dst, p_src, p_pic->p[i].i_visible_pitch);
            p_src += p_pic->p[i].i_visible_pitch;
            p_dst += p_pic->p[i].i_pitch;
        }
    }
}