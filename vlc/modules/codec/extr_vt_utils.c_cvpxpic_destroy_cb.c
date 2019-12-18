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
struct cvpxpic_ctx {int /*<<< orphan*/  nb_fields; int /*<<< orphan*/  on_released_data; int /*<<< orphan*/  cvpx; int /*<<< orphan*/  (* on_released_cb ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  rc; } ;
typedef  int /*<<< orphan*/  picture_context_t ;

/* Variables and functions */
 int /*<<< orphan*/  CFRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ vlc_atomic_rc_dec (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
cvpxpic_destroy_cb(picture_context_t *opaque)
{
    struct cvpxpic_ctx *ctx = (struct cvpxpic_ctx *)opaque;

    if (vlc_atomic_rc_dec(&ctx->rc))
    {
        CFRelease(ctx->cvpx);
        if (ctx->on_released_cb)
            ctx->on_released_cb(ctx->cvpx, ctx->on_released_data, ctx->nb_fields);
        free(opaque);
    }
}