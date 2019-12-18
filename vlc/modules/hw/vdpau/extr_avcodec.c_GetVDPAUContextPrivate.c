#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_video_context ;
struct video_context_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VLC_VIDEO_CONTEXT_VDPAU ; 
 scalar_t__ vlc_video_context_GetPrivate (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct video_context_private *GetVDPAUContextPrivate(vlc_video_context *vctx)
{
    return (struct video_context_private *)
        vlc_video_context_GetPrivate( vctx, VLC_VIDEO_CONTEXT_VDPAU );
}