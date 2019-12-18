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
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_3__ {int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ h264_probe_ctx_t ;
typedef  int /*<<< orphan*/  demux_t ;

/* Variables and functions */
 int GenericOpen (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,char const**,char const**) ; 
 int /*<<< orphan*/  ProbeH264 ; 
 int /*<<< orphan*/  VLC_CODEC_H264 ; 

__attribute__((used)) static int OpenH264( vlc_object_t * p_this )
{
    h264_probe_ctx_t ctx = { 0, 0 };
    const char *rgi_psz_ext[] = { ".h264", ".264", ".bin", ".bit", ".raw", NULL };
    const char *rgi_psz_mime[] = { "video/H264", "video/h264", "video/avc", NULL };

    return GenericOpen( (demux_t*)p_this, "h264", VLC_CODEC_H264, ProbeH264,
                        &ctx, rgi_psz_ext, rgi_psz_mime );
}