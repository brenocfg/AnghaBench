#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int i_sample_rate; int i_channel_count; } ;
struct TYPE_9__ {int i_width; int i_height; int i_angle; scalar_t__ b_adaptive_playback; scalar_t__ b_tunneled_playback; int /*<<< orphan*/ * p_surface; } ;
union mc_api_args {TYPE_3__ audio; TYPE_1__ video; } ;
struct TYPE_13__ {int /*<<< orphan*/  p_format; int /*<<< orphan*/  p_codec; } ;
typedef  TYPE_5__ mc_api_sys ;
struct TYPE_14__ {scalar_t__ i_cat; int b_direct_rendering; int /*<<< orphan*/  p_obj; int /*<<< orphan*/  psz_mime; scalar_t__ psz_name; TYPE_5__* p_sys; } ;
typedef  TYPE_6__ mc_api ;
struct TYPE_12__ {scalar_t__ (* configure ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* createCodecByName ) (scalar_t__) ;} ;
struct TYPE_10__ {int /*<<< orphan*/  (* setInt32 ) (int /*<<< orphan*/ ,char*,int) ;int /*<<< orphan*/  (* setString ) (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* new ) () ;} ;
struct TYPE_15__ {TYPE_4__ AMediaCodec; TYPE_2__ AMediaFormat; } ;
typedef  int /*<<< orphan*/  ANativeWindow ;

/* Variables and functions */
 scalar_t__ AMEDIA_OK ; 
 int MC_API_ERROR ; 
 scalar_t__ VIDEO_ES ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stub1 (scalar_t__) ; 
 int /*<<< orphan*/  stub10 (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  stub11 (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  stub12 (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ stub13 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 () ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  stub6 (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  stub7 (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  stub8 (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  stub9 (int /*<<< orphan*/ ,char*,int) ; 
 TYPE_7__ syms ; 

__attribute__((used)) static int ConfigureDecoder(mc_api *api, union mc_api_args *p_args)
{
    mc_api_sys *p_sys = api->p_sys;
    ANativeWindow *p_anw = NULL;

    assert(api->psz_mime && api->psz_name);

    p_sys->p_codec = syms.AMediaCodec.createCodecByName(api->psz_name);
    if (!p_sys->p_codec)
    {
        msg_Err(api->p_obj, "AMediaCodec.createCodecByName for %s failed",
                api->psz_name);
        return MC_API_ERROR;
    }

    p_sys->p_format = syms.AMediaFormat.new();
    if (!p_sys->p_format)
    {
        msg_Err(api->p_obj, "AMediaFormat.new failed");
        return MC_API_ERROR;
    }

    syms.AMediaFormat.setInt32(p_sys->p_format, "encoder", 0);
    syms.AMediaFormat.setString(p_sys->p_format, "mime", api->psz_mime);
    /* No limits for input size */
    syms.AMediaFormat.setInt32(p_sys->p_format, "max-input-size", 0);
    if (api->i_cat == VIDEO_ES)
    {
        syms.AMediaFormat.setInt32(p_sys->p_format, "width", p_args->video.i_width);
        syms.AMediaFormat.setInt32(p_sys->p_format, "height", p_args->video.i_height);
        syms.AMediaFormat.setInt32(p_sys->p_format, "rotation-degrees", p_args->video.i_angle);
        if (p_args->video.p_surface)
        {
            p_anw = p_args->video.p_surface;
            if (p_args->video.b_tunneled_playback)
                syms.AMediaFormat.setInt32(p_sys->p_format,
                                           "feature-tunneled-playback", 1);
            if (p_args->video.b_adaptive_playback)
                syms.AMediaFormat.setInt32(p_sys->p_format,
                                           "feature-adaptive-playback", 1);
        }
    }
    else
    {
        syms.AMediaFormat.setInt32(p_sys->p_format, "sample-rate", p_args->audio.i_sample_rate);
        syms.AMediaFormat.setInt32(p_sys->p_format, "channel-count", p_args->audio.i_channel_count);
    }

    if (syms.AMediaCodec.configure(p_sys->p_codec, p_sys->p_format,
                                   p_anw, NULL, 0) != AMEDIA_OK)
    {
        msg_Err(api->p_obj, "AMediaCodec.configure failed");
        return MC_API_ERROR;
    }

    api->b_direct_rendering = !!p_anw;

    return 0;
}