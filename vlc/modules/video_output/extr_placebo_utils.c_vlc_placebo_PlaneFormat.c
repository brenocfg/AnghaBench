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
struct TYPE_3__ {int i_visible_width; int i_visible_height; int /*<<< orphan*/  i_chroma; } ;
typedef  TYPE_1__ video_format_t ;
struct plane_desc {int w_denom; int h_denom; } ;
struct pl_plane_data {int width; int height; } ;
struct fmt_desc {int num_planes; struct plane_desc* planes; } ;

/* Variables and functions */
 int /*<<< orphan*/  FillDesc (int /*<<< orphan*/ ,struct fmt_desc const*,struct pl_plane_data*) ; 
 struct fmt_desc* FindDesc (int /*<<< orphan*/ ) ; 

int vlc_placebo_PlaneFormat(const video_format_t *fmt, struct pl_plane_data data[4])
{
    const struct fmt_desc *desc = FindDesc(fmt->i_chroma);
    if (!desc)
        return 0;

    FillDesc(fmt->i_chroma, desc, data);
    for (int i = 0; i < desc->num_planes; i++) {
        const struct plane_desc *p = &desc->planes[i];
        data[i].width  = (fmt->i_visible_width  + p->w_denom - 1) / p->w_denom;
        data[i].height = (fmt->i_visible_height + p->h_denom - 1) / p->h_denom;
    }

    return desc->num_planes;
}