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
struct picture_context_t {int dummy; } ;
struct cvpxpic_ctx {int /*<<< orphan*/  rc; } ;
typedef  struct picture_context_t picture_context_t ;

/* Variables and functions */
 int /*<<< orphan*/  vlc_atomic_rc_inc (int /*<<< orphan*/ *) ; 

__attribute__((used)) static picture_context_t *
cvpxpic_copy_cb(struct picture_context_t *opaque)
{
    struct cvpxpic_ctx *ctx = (struct cvpxpic_ctx *)opaque;
    vlc_atomic_rc_inc(&ctx->rc);
    return opaque;
}