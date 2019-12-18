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
struct TYPE_3__ {int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ hevc_probe_ctx_t ;
typedef  int /*<<< orphan*/  demux_t ;

/* Variables and functions */
 int GenericOpen (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,char const**,char const**) ; 
 int /*<<< orphan*/  ProbeHEVC ; 
 int /*<<< orphan*/  VLC_CODEC_HEVC ; 

__attribute__((used)) static int OpenHEVC( vlc_object_t * p_this )
{
    hevc_probe_ctx_t ctx = { 0, 0, 0 };
    const char *rgi_psz_ext[] = { ".h265", ".265", ".hevc", ".bin", ".bit", ".raw", NULL };
    const char *rgi_psz_mime[] = { "video/h265", "video/hevc", "video/HEVC", NULL };

    return GenericOpen( (demux_t*)p_this, "hevc", VLC_CODEC_HEVC, ProbeHEVC,
                        &ctx, rgi_psz_ext, rgi_psz_mime );
}