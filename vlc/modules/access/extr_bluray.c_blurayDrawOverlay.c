#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_9__ ;
typedef  struct TYPE_27__   TYPE_8__ ;
typedef  struct TYPE_26__   TYPE_7__ ;
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;
typedef  struct TYPE_19__   TYPE_12__ ;
typedef  struct TYPE_18__   TYPE_11__ ;
typedef  struct TYPE_17__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  video_format_t ;
struct TYPE_22__ {scalar_t__ i_width; scalar_t__ i_height; TYPE_2__* p_palette; } ;
struct TYPE_26__ {scalar_t__ i_x; scalar_t__ i_y; TYPE_3__ fmt; TYPE_1__* p_picture; struct TYPE_26__* p_next; } ;
typedef  TYPE_7__ subpicture_region_t ;
struct TYPE_27__ {int i_pitch; int /*<<< orphan*/ * p_pixels; } ;
typedef  TYPE_8__ plane_t ;
struct TYPE_28__ {TYPE_10__* p_sys; } ;
typedef  TYPE_9__ demux_t ;
struct TYPE_25__ {TYPE_5__** p_overlays; } ;
struct TYPE_17__ {TYPE_6__ bdj; } ;
typedef  TYPE_10__ demux_sys_t ;
struct TYPE_24__ {int /*<<< orphan*/  lock; TYPE_7__* p_regions; } ;
struct TYPE_23__ {int /*<<< orphan*/  T; int /*<<< orphan*/  Cr; int /*<<< orphan*/  Cb; int /*<<< orphan*/  Y; } ;
struct TYPE_21__ {int i_entries; int /*<<< orphan*/ ** palette; } ;
struct TYPE_20__ {TYPE_8__* p; } ;
struct TYPE_19__ {size_t plane; scalar_t__ x; scalar_t__ y; scalar_t__ w; scalar_t__ h; TYPE_4__* palette; TYPE_11__* img; } ;
struct TYPE_18__ {int len; int /*<<< orphan*/  color; } ;
typedef  TYPE_11__ BD_PG_RLE_ELEM ;
typedef  TYPE_12__ BD_OVERLAY ;

/* Variables and functions */
 int /*<<< orphan*/  VLC_CODEC_YUVP ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  subpicture_region_Delete (TYPE_7__*) ; 
 TYPE_7__* subpicture_region_New (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  video_format_Init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  video_format_Setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,scalar_t__,int,int) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void blurayDrawOverlay(demux_t *p_demux, const BD_OVERLAY* const ov)
{
    demux_sys_t *p_sys = p_demux->p_sys;

    /*
     * Compute a subpicture_region_t.
     * It will be copied and sent to the vout later.
     */
    vlc_mutex_lock(&p_sys->bdj.p_overlays[ov->plane]->lock);

    /* Find a region to update */
    subpicture_region_t **pp_reg = &p_sys->bdj.p_overlays[ov->plane]->p_regions;
    subpicture_region_t *p_reg = p_sys->bdj.p_overlays[ov->plane]->p_regions;
    subpicture_region_t *p_last = NULL;
    while (p_reg != NULL) {
        p_last = p_reg;
        if (p_reg->i_x == ov->x && p_reg->i_y == ov->y &&
                p_reg->fmt.i_width == ov->w && p_reg->fmt.i_height == ov->h)
            break;
        pp_reg = &p_reg->p_next;
        p_reg = p_reg->p_next;
    }

    if (!ov->img) {
        if (p_reg) {
            /* drop region */
            *pp_reg = p_reg->p_next;
            subpicture_region_Delete(p_reg);
        }
        vlc_mutex_unlock(&p_sys->bdj.p_overlays[ov->plane]->lock);
        return;
    }

    /* If there is no region to update, create a new one. */
    if (!p_reg) {
        video_format_t fmt;
        video_format_Init(&fmt, 0);
        video_format_Setup(&fmt, VLC_CODEC_YUVP, ov->w, ov->h, ov->w, ov->h, 1, 1);

        p_reg = subpicture_region_New(&fmt);
        if (p_reg) {
            p_reg->i_x = ov->x;
            p_reg->i_y = ov->y;
            /* Append it to our list. */
            if (p_last != NULL)
                p_last->p_next = p_reg;
            else /* If we don't have a last region, then our list empty */
                p_sys->bdj.p_overlays[ov->plane]->p_regions = p_reg;
        }
    }

    /* Now we can update the region, regardless it's an update or an insert */
    const BD_PG_RLE_ELEM *img = ov->img;
    for (int y = 0; y < ov->h; y++)
        for (int x = 0; x < ov->w;) {
            plane_t *p = &p_reg->p_picture->p[0];
            memset(&p->p_pixels[y * p->i_pitch + x], img->color, img->len);
            x += img->len;
            img++;
        }

    if (ov->palette) {
        p_reg->fmt.p_palette->i_entries = 256;
        for (int i = 0; i < 256; ++i) {
            p_reg->fmt.p_palette->palette[i][0] = ov->palette[i].Y;
            p_reg->fmt.p_palette->palette[i][1] = ov->palette[i].Cb;
            p_reg->fmt.p_palette->palette[i][2] = ov->palette[i].Cr;
            p_reg->fmt.p_palette->palette[i][3] = ov->palette[i].T;
        }
    }

    vlc_mutex_unlock(&p_sys->bdj.p_overlays[ov->plane]->lock);
    /*
     * /!\ The region is now stored in our internal list, but not in the subpicture /!\
     */
}