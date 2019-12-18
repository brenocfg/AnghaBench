#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_9__ ;
typedef  struct TYPE_24__   TYPE_8__ ;
typedef  struct TYPE_23__   TYPE_7__ ;
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_20__ {int /*<<< orphan*/  i_chroma; } ;
struct TYPE_21__ {TYPE_4__ video; } ;
struct TYPE_18__ {int /*<<< orphan*/  i_chroma; } ;
struct TYPE_19__ {TYPE_2__ video; } ;
struct TYPE_22__ {TYPE_5__ fmt_out; TYPE_3__ fmt_in; } ;
typedef  TYPE_6__ vlc_blender_t ;
struct TYPE_23__ {int i_alpha; TYPE_8__* p_region; scalar_t__ b_absolute; int /*<<< orphan*/  b_fade; } ;
typedef  TYPE_7__ subpicture_t ;
struct TYPE_24__ {scalar_t__ i_align; int i_alpha; scalar_t__ p_picture; int /*<<< orphan*/  i_y; int /*<<< orphan*/  i_x; int /*<<< orphan*/  fmt; struct TYPE_24__* p_next; } ;
typedef  TYPE_8__ subpicture_region_t ;
struct TYPE_17__ {int /*<<< orphan*/  i_height; int /*<<< orphan*/  i_width; } ;
struct TYPE_25__ {TYPE_1__ format; } ;
typedef  TYPE_9__ picture_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ filter_Blend (TYPE_6__*,TYPE_9__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int) ; 
 scalar_t__ filter_ConfigureBlend (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msg_Err (TYPE_6__*,char*,char*,char*) ; 

unsigned picture_BlendSubpicture(picture_t *dst,
                                 vlc_blender_t *blend, subpicture_t *src)
{
    unsigned done = 0;

    assert(src && !src->b_fade && src->b_absolute);

    for (subpicture_region_t *r = src->p_region; r != NULL; r = r->p_next) {
        assert(r->p_picture && r->i_align == 0);
        if (filter_ConfigureBlend(blend, dst->format.i_width,
                                  dst->format.i_height,  &r->fmt)
         || filter_Blend(blend, dst, r->i_x, r->i_y, r->p_picture,
                         src->i_alpha * r->i_alpha / 255))
            msg_Err(blend, "blending %4.4s to %4.4s failed",
                    (char *)&blend->fmt_in.video.i_chroma,
                    (char *)&blend->fmt_out.video.i_chroma );
        else
            done++;
    }
    return done;
}