#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_31__   TYPE_7__ ;
typedef  struct TYPE_30__   TYPE_6__ ;
typedef  struct TYPE_29__   TYPE_5__ ;
typedef  struct TYPE_28__   TYPE_4__ ;
typedef  struct TYPE_27__   TYPE_3__ ;
typedef  struct TYPE_26__   TYPE_2__ ;
typedef  struct TYPE_25__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_video_context ;
struct TYPE_26__ {int /*<<< orphan*/ * ops; TYPE_3__* sys; } ;
typedef  TYPE_2__ vlc_va_t ;
struct TYPE_25__ {scalar_t__ config_id; scalar_t__ context_id; int /*<<< orphan*/  display; } ;
struct TYPE_27__ {int /*<<< orphan*/ * va_pool; int /*<<< orphan*/ * vctx; TYPE_1__ hw_ctx; int /*<<< orphan*/ * render_targets; } ;
typedef  TYPE_3__ vlc_va_sys_t ;
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_28__ {scalar_t__ type; int /*<<< orphan*/  opaque; } ;
typedef  TYPE_4__ vlc_decoder_device ;
struct TYPE_29__ {scalar_t__ i_chroma; } ;
typedef  TYPE_5__ video_format_t ;
struct va_pool_cfg {TYPE_3__* member_4; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_30__ {TYPE_5__ video; } ;
typedef  TYPE_6__ es_format_t ;
typedef  int /*<<< orphan*/  VASurfaceID ;
typedef  int /*<<< orphan*/  VAProfile ;
typedef  int /*<<< orphan*/  VADisplay ;
struct TYPE_31__ {int /*<<< orphan*/  coded_height; int /*<<< orphan*/  coded_width; } ;
typedef  int /*<<< orphan*/  AVPixFmtDescriptor ;
typedef  TYPE_7__ AVCodecContext ;

/* Variables and functions */
 int GetVaProfile (TYPE_7__*,TYPE_6__ const*,int /*<<< orphan*/ *,int*,unsigned int*) ; 
 int /*<<< orphan*/  VAAPICreateDecoderSurfaces ; 
 int /*<<< orphan*/  VAAPICreateDevice ; 
 int /*<<< orphan*/  VAAPIDestroyDevice ; 
 int /*<<< orphan*/  VAAPISetupAVCodecContext ; 
 int /*<<< orphan*/  VAEntrypointVLD ; 
 scalar_t__ VA_INVALID_ID ; 
 int /*<<< orphan*/  VA_PROGRESSIVE ; 
 scalar_t__ VLC_CODEC_VAAPI_420 ; 
 scalar_t__ VLC_CODEC_VAAPI_420_10BPP ; 
 scalar_t__ VLC_DECODER_DEVICE_VAAPI ; 
 int VLC_EGENERIC ; 
 int VLC_ENOMEM ; 
 int /*<<< orphan*/ * VLC_OBJECT (TYPE_2__*) ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  VLC_UNUSED (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  VLC_VIDEO_CONTEXT_VAAPI ; 
 int /*<<< orphan*/  free (TYPE_3__*) ; 
 TYPE_3__* malloc (int) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msg_Info (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ops ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vaQueryVendorString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  va_pool_Close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * va_pool_Create (TYPE_2__*,struct va_pool_cfg*) ; 
 int va_pool_SetupDecoder (TYPE_2__*,int /*<<< orphan*/ *,TYPE_7__*,TYPE_5__*,unsigned int) ; 
 scalar_t__ vlc_vaapi_CreateConfigChecked (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ vlc_vaapi_CreateContext (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/ * vlc_video_context_Create (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int Create(vlc_va_t *va, AVCodecContext *ctx, const AVPixFmtDescriptor *desc,
                  const es_format_t *fmt_in, vlc_decoder_device *dec_device,
                  video_format_t *fmt_out, vlc_video_context **vtcx_out)
{
    VLC_UNUSED(desc);
    if ( (fmt_out->i_chroma != VLC_CODEC_VAAPI_420 &&
          fmt_out->i_chroma != VLC_CODEC_VAAPI_420_10BPP) || dec_device == NULL ||
        dec_device->type != VLC_DECODER_DEVICE_VAAPI)
        return VLC_EGENERIC;

    vlc_va_sys_t *sys = malloc(sizeof *sys);
    if (unlikely(sys == NULL))
        return VLC_ENOMEM;
    memset(sys, 0, sizeof (*sys));

    vlc_object_t *o = VLC_OBJECT(va);

    int ret = VLC_EGENERIC;

    VADisplay va_dpy = dec_device->opaque;

    VAProfile i_profile;
    unsigned count;
    int i_vlc_chroma;
    if (GetVaProfile(ctx, fmt_in, &i_profile, &i_vlc_chroma, &count) != VLC_SUCCESS)
        goto error;

    /* */
    sys->hw_ctx.display = va_dpy;
    sys->hw_ctx.config_id = VA_INVALID_ID;
    sys->hw_ctx.context_id = VA_INVALID_ID;
    va->sys = sys;

    video_format_t fmt_video = fmt_in->video;
    fmt_video.i_chroma = i_vlc_chroma;

    struct va_pool_cfg pool_cfg = {
        VAAPICreateDevice,
        VAAPIDestroyDevice,
        VAAPICreateDecoderSurfaces,
        VAAPISetupAVCodecContext,
        sys,
    };
    sys->va_pool = va_pool_Create(va, &pool_cfg);
    if (sys->va_pool == NULL)
        goto error;

    int err = va_pool_SetupDecoder(va, sys->va_pool, ctx, &fmt_video, count);
    if (err != VLC_SUCCESS)
        goto error;

    VASurfaceID *render_targets = sys->render_targets;

    sys->hw_ctx.config_id =
        vlc_vaapi_CreateConfigChecked(o, sys->hw_ctx.display, i_profile,
                                      VAEntrypointVLD, i_vlc_chroma);
    if (sys->hw_ctx.config_id == VA_INVALID_ID)
        goto error;

    /* Create a context */
    sys->hw_ctx.context_id =
        vlc_vaapi_CreateContext(o, sys->hw_ctx.display, sys->hw_ctx.config_id,
                                ctx->coded_width, ctx->coded_height, VA_PROGRESSIVE,
                                render_targets, count);
    if (sys->hw_ctx.context_id == VA_INVALID_ID)
        goto error;

    msg_Info(va, "Using %s", vaQueryVendorString(sys->hw_ctx.display));

    sys->vctx = vlc_video_context_Create( dec_device, VLC_VIDEO_CONTEXT_VAAPI, 0, NULL );
    if (sys->vctx == NULL)
        goto error;

    va->ops = &ops;
    *vtcx_out = sys->vctx;
    return VLC_SUCCESS;

error:
    if (sys->va_pool != NULL)
        va_pool_Close(sys->va_pool);
    else
        free(sys);
    return ret;
}