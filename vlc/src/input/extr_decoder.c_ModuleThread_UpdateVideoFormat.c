#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vout_thread_t ;
struct TYPE_10__ {TYPE_4__* mouse_opaque; int /*<<< orphan*/  mouse_event; int /*<<< orphan*/ * fmt; int /*<<< orphan*/  clock; int /*<<< orphan*/ * vout; } ;
typedef  TYPE_3__ vout_configuration_t ;
typedef  int /*<<< orphan*/  vlc_video_context ;
struct decoder_owner {int vout_thread_started; int /*<<< orphan*/  p_resource; int /*<<< orphan*/  p_clock; int /*<<< orphan*/ * out_pool; int /*<<< orphan*/ * vctx; } ;
typedef  enum vlc_vout_order { ____Placeholder_vlc_vout_order } vlc_vout_order ;
struct TYPE_9__ {int /*<<< orphan*/  video; } ;
struct TYPE_8__ {int i_codec; } ;
struct TYPE_11__ {TYPE_2__ fmt_out; scalar_t__ i_extra_picture_buffers; TYPE_1__ fmt_in; } ;
typedef  TYPE_4__ decoder_t ;

/* Variables and functions */
 int CreateVoutIfNeeded (struct decoder_owner*,int /*<<< orphan*/ **,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MouseEvent ; 
#define  VLC_CODEC_AV1 135 
#define  VLC_CODEC_DIRAC 134 
#define  VLC_CODEC_H264 133 
#define  VLC_CODEC_HEVC 132 
#define  VLC_CODEC_VP5 131 
#define  VLC_CODEC_VP6 130 
#define  VLC_CODEC_VP6F 129 
#define  VLC_CODEC_VP8 128 
 struct decoder_owner* dec_get_owner (TYPE_4__*) ; 
 int /*<<< orphan*/  decoder_Notify (struct decoder_owner*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int input_resource_StartVout (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  on_vout_started ; 
 int /*<<< orphan*/ * picture_pool_NewFromFormat (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/ * vlc_video_context_Hold (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_video_context_Release (int /*<<< orphan*/ *) ; 
 int vout_ChangeSource (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ModuleThread_UpdateVideoFormat( decoder_t *p_dec, vlc_video_context *vctx )
{
    struct decoder_owner *p_owner = dec_get_owner( p_dec );

    enum vlc_vout_order vout_order;
    vout_thread_t *p_vout = NULL;
    int created_vout = CreateVoutIfNeeded(p_owner, &p_vout, &vout_order, NULL);
    if (created_vout == -1)
        return -1; // error
    if (created_vout == 0)
    {
        // video context didn't change
        if (vctx != NULL && p_owner->vctx == vctx)
            return 0;
    }
    if (p_owner->vctx)
        vlc_video_context_Release(p_owner->vctx);
    p_owner->vctx = vctx ? vlc_video_context_Hold(vctx) : NULL;

    // configure the new vout

    if ( p_owner->out_pool == NULL )
    {
        unsigned dpb_size;
        switch( p_dec->fmt_in.i_codec )
        {
        case VLC_CODEC_HEVC:
        case VLC_CODEC_H264:
        case VLC_CODEC_DIRAC: /* FIXME valid ? */
            dpb_size = 18;
            break;
        case VLC_CODEC_AV1:
            dpb_size = 10;
            break;
        case VLC_CODEC_VP5:
        case VLC_CODEC_VP6:
        case VLC_CODEC_VP6F:
        case VLC_CODEC_VP8:
            dpb_size = 3;
            break;
        default:
            dpb_size = 2;
            break;
        }

        p_owner->out_pool = picture_pool_NewFromFormat( &p_dec->fmt_out.video,
                            dpb_size + p_dec->i_extra_picture_buffers + 1 );
        if (p_owner->out_pool == NULL)
            return -1;
    }
    int res;
    if (p_owner->vout_thread_started)
    {
        res = vout_ChangeSource(p_vout, &p_dec->fmt_out.video);
        if (res == 0)
            // the display/thread is started and can handle the new source format
            return 0;
    }

    vout_configuration_t cfg = {
        .vout = p_vout, .clock = p_owner->p_clock, .fmt = &p_dec->fmt_out.video,
        .mouse_event = MouseEvent, .mouse_opaque = p_dec,
    };
    res = input_resource_StartVout( p_owner->p_resource, vctx, &cfg);
    if (res == 0)
    {
        p_owner->vout_thread_started = true;
        decoder_Notify(p_owner, on_vout_started, p_vout, vout_order);
    }
    return res;
}