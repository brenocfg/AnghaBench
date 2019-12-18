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
struct video_context_private {int /*<<< orphan*/  vdp; int /*<<< orphan*/ ** pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  vdp_release_x11 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_vdp_video_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void DestroyVDPAUVideoContext(void *private)
{
    struct video_context_private *vctx_priv = private;
    for (unsigned i = 0; vctx_priv->pool[i] != NULL; i++)
        vlc_vdp_video_destroy(vctx_priv->pool[i]);
    vdp_release_x11(vctx_priv->vdp);
}