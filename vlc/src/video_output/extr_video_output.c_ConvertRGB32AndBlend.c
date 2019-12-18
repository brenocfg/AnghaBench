#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_10__ ;

/* Type definitions */
struct TYPE_15__ {TYPE_1__* p; } ;
typedef  TYPE_2__ vout_thread_t ;
typedef  int /*<<< orphan*/  vlc_blender_t ;
typedef  int /*<<< orphan*/  subpicture_t ;
typedef  int /*<<< orphan*/  picture_t ;
typedef  int /*<<< orphan*/  filter_chain_t ;
struct TYPE_17__ {int /*<<< orphan*/  i_chroma; } ;
struct TYPE_16__ {TYPE_4__ video; } ;
typedef  TYPE_3__ es_format_t ;
struct TYPE_14__ {TYPE_10__* spu_blend; } ;
struct TYPE_13__ {TYPE_3__ fmt_out; } ;

/* Variables and functions */
 int /*<<< orphan*/  VLC_CODEC_RGB32 ; 
 int /*<<< orphan*/  VLC_OBJECT (TYPE_2__*) ; 
 int /*<<< orphan*/  assert (TYPE_10__*) ; 
 int /*<<< orphan*/  filter_DeleteBlend (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * filter_NewBlend (int /*<<< orphan*/ ,TYPE_4__*) ; 
 scalar_t__ filter_chain_AppendConverter (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  filter_chain_Delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * filter_chain_NewVideo (TYPE_2__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  filter_chain_Reset (int /*<<< orphan*/ *,TYPE_3__*,TYPE_3__*) ; 
 int /*<<< orphan*/ * filter_chain_VideoFilter (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ picture_BlendSubpicture (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  picture_Hold (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  picture_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  video_format_FixRgb (TYPE_4__*) ; 

__attribute__((used)) static picture_t *ConvertRGB32AndBlend(vout_thread_t *vout, picture_t *pic,
                                     subpicture_t *subpic)
{
    /* This function will convert the pic to RGB32 and blend the subpic to it.
     * The returned pic can't be used to display since the chroma will be
     * different than the "vout display" one, but it can be used for snapshots.
     * */

    assert(vout->p->spu_blend);

    filter_chain_t *filterc = filter_chain_NewVideo(vout, false, NULL);
    if (!filterc)
        return NULL;

    es_format_t src = vout->p->spu_blend->fmt_out;
    es_format_t dst = src;
    dst.video.i_chroma = VLC_CODEC_RGB32;
    video_format_FixRgb(&dst.video);

    filter_chain_Reset(filterc, &src, &dst);

    if (filter_chain_AppendConverter(filterc, &dst) != 0)
    {
        filter_chain_Delete(filterc);
        return NULL;
    }

    picture_Hold(pic);
    pic = filter_chain_VideoFilter(filterc, pic);
    filter_chain_Delete(filterc);

    if (pic)
    {
        vlc_blender_t *swblend = filter_NewBlend(VLC_OBJECT(vout), &dst.video);
        if (swblend)
        {
            bool success = picture_BlendSubpicture(pic, swblend, subpic) > 0;
            filter_DeleteBlend(swblend);
            if (success)
                return pic;
        }
        picture_Release(pic);
    }
    return NULL;
}