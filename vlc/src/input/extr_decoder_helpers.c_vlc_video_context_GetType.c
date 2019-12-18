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
struct TYPE_3__ {int private_type; } ;
typedef  TYPE_1__ vlc_video_context ;
typedef  enum vlc_video_context_type { ____Placeholder_vlc_video_context_type } vlc_video_context_type ;

/* Variables and functions */

enum vlc_video_context_type vlc_video_context_GetType(const vlc_video_context *vctx)
{
    return vctx->private_type;
}