#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct picture_context_t {struct picture_context_t* (* copy ) (struct picture_context_t*) ;int /*<<< orphan*/  destroy; } ;
struct TYPE_2__ {struct picture_context_t s; int /*<<< orphan*/  va_dpy; int /*<<< orphan*/  surface; } ;
struct vaapi_pic_ctx {TYPE_1__ ctx; int /*<<< orphan*/  picref; } ;

/* Variables and functions */
 struct vaapi_pic_ctx* malloc (int) ; 
 int /*<<< orphan*/  pic_ctx_destroy_cb ; 
 int /*<<< orphan*/  picture_Hold (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct picture_context_t *
pic_ctx_copy_cb(struct picture_context_t *opaque)
{
    struct vaapi_pic_ctx *src_ctx = (struct vaapi_pic_ctx *) opaque;
    struct vaapi_pic_ctx *dst_ctx = malloc(sizeof *dst_ctx);
    if (dst_ctx == NULL)
        return NULL;

    dst_ctx->ctx.s.destroy = pic_ctx_destroy_cb;
    dst_ctx->ctx.s.copy = pic_ctx_copy_cb;
    dst_ctx->ctx.surface = src_ctx->ctx.surface;
    dst_ctx->ctx.va_dpy = src_ctx->ctx.va_dpy;
    dst_ctx->picref = picture_Hold(src_ctx->picref);
    return &dst_ctx->ctx.s;
}