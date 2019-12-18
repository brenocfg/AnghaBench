#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {TYPE_5__* sys; } ;
typedef  TYPE_4__ vout_display_t ;
struct TYPE_17__ {TYPE_6__* p_sub_buffer_bounds; TYPE_3__* p_sub_pic; } ;
typedef  TYPE_5__ vout_display_sys_t ;
typedef  int /*<<< orphan*/  subpicture_t ;
struct TYPE_19__ {scalar_t__ left; unsigned int right; unsigned int bottom; scalar_t__ top; } ;
struct TYPE_18__ {TYPE_7__ bounds; int /*<<< orphan*/ * p_pixels; } ;
typedef  TYPE_6__ buffer_bounds ;
struct TYPE_13__ {unsigned int i_width; unsigned int i_height; } ;
struct TYPE_15__ {TYPE_2__* p; TYPE_1__ format; } ;
struct TYPE_14__ {int /*<<< orphan*/ * p_pixels; } ;
typedef  TYPE_7__ ARect ;

/* Variables and functions */
 int /*<<< orphan*/  SubtitleRegionToBounds (int /*<<< orphan*/ *,TYPE_7__*) ; 
 TYPE_6__* realloc (TYPE_6__*,int) ; 

__attribute__((used)) static void SubtitleGetDirtyBounds(vout_display_t *vd,
                                   subpicture_t *subpicture,
                                   ARect *p_out_bounds)
{
    vout_display_sys_t *sys = vd->sys;
    int i = 0;
    bool b_found = false;

    /* Try to find last bounds set by current locked buffer.
     * Indeed, even if we can lock only one buffer at a time, differents
     * buffers can be locked. This functions will find the last bounds set by
     * the current buffer. */
    if (sys->p_sub_buffer_bounds) {
        for (; sys->p_sub_buffer_bounds[i].p_pixels != NULL; ++i) {
            buffer_bounds *p_bb = &sys->p_sub_buffer_bounds[i];
            if (p_bb->p_pixels == sys->p_sub_pic->p[0].p_pixels) {
                *p_out_bounds = p_bb->bounds;
                b_found = true;
                break;
            }
        }
    }

    if (!b_found
     || p_out_bounds->left < 0
     || p_out_bounds->right < 0
     || (unsigned int) p_out_bounds->right > sys->p_sub_pic->format.i_width
     || p_out_bounds->bottom < 0
     || p_out_bounds->top < 0
     || (unsigned int) p_out_bounds->top > sys->p_sub_pic->format.i_height)
    {
        /* default is full picture */
        p_out_bounds->left = 0;
        p_out_bounds->top = 0;
        p_out_bounds->right = sys->p_sub_pic->format.i_width;
        p_out_bounds->bottom = sys->p_sub_pic->format.i_height;
    }

    /* buffer not found, add it to the array */
    if (!sys->p_sub_buffer_bounds
     || sys->p_sub_buffer_bounds[i].p_pixels == NULL) {
        buffer_bounds *p_bb = realloc(sys->p_sub_buffer_bounds,
                                      (i + 2) * sizeof(buffer_bounds));
        if (p_bb) {
            sys->p_sub_buffer_bounds = p_bb;
            sys->p_sub_buffer_bounds[i].p_pixels = sys->p_sub_pic->p[0].p_pixels;
            sys->p_sub_buffer_bounds[i+1].p_pixels = NULL;
        }
    }

    /* set buffer bounds */
    if (sys->p_sub_buffer_bounds
     && sys->p_sub_buffer_bounds[i].p_pixels != NULL)
        SubtitleRegionToBounds(subpicture, &sys->p_sub_buffer_bounds[i].bounds);
}