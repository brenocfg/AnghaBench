#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct vpx_image {TYPE_2__* user_priv; } ;
struct TYPE_4__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ decoder_t ;
struct TYPE_5__ {int /*<<< orphan*/  ctx; } ;
typedef  TYPE_2__ decoder_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  vpx_codec_destroy (int /*<<< orphan*/ *) ; 
 struct vpx_image* vpx_codec_get_frame (int /*<<< orphan*/ *,void const**) ; 

__attribute__((used)) static void CloseDecoder(vlc_object_t *p_this)
{
    decoder_t *dec = (decoder_t *)p_this;
    decoder_sys_t *sys = dec->p_sys;

    /* Free our PTS */
    const void *iter = NULL;
    for (;;) {
        struct vpx_image *img = vpx_codec_get_frame(&sys->ctx, &iter);
        if (!img)
            break;
        free(img->user_priv);
    }

    vpx_codec_destroy(&sys->ctx);

    free(sys);
}