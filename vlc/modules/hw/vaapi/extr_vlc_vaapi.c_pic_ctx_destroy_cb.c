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
struct vaapi_pic_ctx {int /*<<< orphan*/  picref; } ;
struct picture_context_t {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct picture_context_t*) ; 
 int /*<<< orphan*/  picture_Release (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pic_ctx_destroy_cb(struct picture_context_t *opaque)
{
    struct vaapi_pic_ctx *ctx = (struct vaapi_pic_ctx *) opaque;
    picture_Release(ctx->picref);
    free(opaque);
}