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
struct TYPE_4__ {int /*<<< orphan*/  rc; } ;
typedef  TYPE_1__ vlc_video_context ;

/* Variables and functions */
 int /*<<< orphan*/  vlc_atomic_rc_inc (int /*<<< orphan*/ *) ; 

vlc_video_context *vlc_video_context_Hold(vlc_video_context *vctx)
{
    vlc_atomic_rc_inc( &vctx->rc );
    return vctx;
}