#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vout_display_t ;
typedef  int /*<<< orphan*/  vout_display_cfg_t ;
typedef  int /*<<< orphan*/  vlc_video_context ;
struct TYPE_4__ {scalar_t__ i_chroma; int /*<<< orphan*/  projection_mode; } ;
typedef  TYPE_1__ video_format_t ;

/* Variables and functions */
 int OpenCommon (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,TYPE_1__*) ; 
 int /*<<< orphan*/  PROJECTION_MODE_RECTANGULAR ; 
 scalar_t__ VLC_CODEC_ANDROID_OPAQUE ; 
 int VLC_EGENERIC ; 

__attribute__((used)) static int Open(vout_display_t *vd, const vout_display_cfg_t *cfg,
                video_format_t *fmtp, vlc_video_context *context)
{
    if (fmtp->i_chroma == VLC_CODEC_ANDROID_OPAQUE)
        return VLC_EGENERIC;

    /* There are two cases:
     * 1. the projection_mode is PROJECTION_MODE_RECTANGULAR
     * 2. gles2 vout failed */
    fmtp->projection_mode = PROJECTION_MODE_RECTANGULAR;

    (void) context;
    return OpenCommon(vd, cfg, fmtp);
}