#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_14__ {scalar_t__ i_sar_num; scalar_t__ i_sar_den; int /*<<< orphan*/  color_range; int /*<<< orphan*/  space; int /*<<< orphan*/  transfer; int /*<<< orphan*/  primaries; int /*<<< orphan*/  i_height; int /*<<< orphan*/  i_width; } ;
struct TYPE_15__ {scalar_t__ i_codec; TYPE_4__ video; } ;
struct TYPE_12__ {scalar_t__ i_sar_num; scalar_t__ i_sar_den; int /*<<< orphan*/  color_range; int /*<<< orphan*/  space; int /*<<< orphan*/  transfer; int /*<<< orphan*/  primaries; int /*<<< orphan*/  i_height; int /*<<< orphan*/  i_width; } ;
struct TYPE_13__ {TYPE_2__ video; int /*<<< orphan*/  i_codec; } ;
struct TYPE_16__ {scalar_t__ i_extra_picture_buffers; TYPE_5__ fmt_in; TYPE_3__ fmt_out; TYPE_7__* p_sys; int /*<<< orphan*/  pf_flush; int /*<<< orphan*/  pf_decode; } ;
typedef  TYPE_6__ decoder_t ;
struct TYPE_11__ {int /*<<< orphan*/  release_picture_callback; int /*<<< orphan*/  alloc_picture_callback; TYPE_6__* cookie; } ;
struct TYPE_18__ {scalar_t__ n_tile_threads; scalar_t__ n_frame_threads; TYPE_1__ allocator; } ;
struct TYPE_17__ {TYPE_9__ s; int /*<<< orphan*/  c; } ;
typedef  TYPE_7__ decoder_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  Decode ; 
 int /*<<< orphan*/  FlushDecoder ; 
 int /*<<< orphan*/  FreePicture ; 
 int /*<<< orphan*/  NewPicture ; 
 scalar_t__ VLC_CLIP (int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ VLC_CODEC_AV1 ; 
 int /*<<< orphan*/  VLC_CODEC_I420 ; 
 int VLC_EGENERIC ; 
 int VLC_ENOMEM ; 
 int VLC_SUCCESS ; 
 scalar_t__ __MAX (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dav1d_default_settings (TYPE_9__*) ; 
 scalar_t__ dav1d_open (int /*<<< orphan*/ *,TYPE_9__*) ; 
 int /*<<< orphan*/  dav1d_version () ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ *,char*) ; 
 void* var_InheritInteger (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  vlc_GetCPUCount () ; 
 TYPE_7__* vlc_obj_malloc (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int OpenDecoder(vlc_object_t *p_this)
{
    decoder_t *dec = (decoder_t *)p_this;

    if (dec->fmt_in.i_codec != VLC_CODEC_AV1)
        return VLC_EGENERIC;

    decoder_sys_t *p_sys = vlc_obj_malloc(p_this, sizeof(*p_sys));
    if (!p_sys)
        return VLC_ENOMEM;

    dav1d_default_settings(&p_sys->s);
    p_sys->s.n_tile_threads = var_InheritInteger(p_this, "dav1d-thread-tiles");
    if (p_sys->s.n_tile_threads == 0)
        p_sys->s.n_tile_threads = VLC_CLIP(vlc_GetCPUCount(), 1, 4);
    p_sys->s.n_frame_threads = var_InheritInteger(p_this, "dav1d-thread-frames");
    if (p_sys->s.n_frame_threads == 0)
        p_sys->s.n_frame_threads = __MAX(1, vlc_GetCPUCount());
    p_sys->s.allocator.cookie = dec;
    p_sys->s.allocator.alloc_picture_callback = NewPicture;
    p_sys->s.allocator.release_picture_callback = FreePicture;

    if (dav1d_open(&p_sys->c, &p_sys->s) < 0)
    {
        msg_Err(p_this, "Could not open the Dav1d decoder");
        return VLC_EGENERIC;
    }

    msg_Dbg(p_this, "Using dav1d version %s with %d/%d frame/tile threads",
            dav1d_version(), p_sys->s.n_frame_threads, p_sys->s.n_tile_threads);

    dec->pf_decode = Decode;
    dec->pf_flush = FlushDecoder;
    dec->i_extra_picture_buffers = (p_sys->s.n_frame_threads - 1);

    dec->fmt_out.video.i_width = dec->fmt_in.video.i_width;
    dec->fmt_out.video.i_height = dec->fmt_in.video.i_height;
    dec->fmt_out.i_codec = VLC_CODEC_I420;
    dec->p_sys = p_sys;

    if (dec->fmt_in.video.i_sar_num > 0 && dec->fmt_in.video.i_sar_den > 0) {
        dec->fmt_out.video.i_sar_num = dec->fmt_in.video.i_sar_num;
        dec->fmt_out.video.i_sar_den = dec->fmt_in.video.i_sar_den;
    }
    dec->fmt_out.video.primaries   = dec->fmt_in.video.primaries;
    dec->fmt_out.video.transfer    = dec->fmt_in.video.transfer;
    dec->fmt_out.video.space       = dec->fmt_in.video.space;
    dec->fmt_out.video.color_range = dec->fmt_in.video.color_range;

    return VLC_SUCCESS;
}