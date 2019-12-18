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
struct TYPE_2__ {int /*<<< orphan*/  s; int /*<<< orphan*/  picsys; } ;
struct dxva2_pic_context {TYPE_1__ ctx; int /*<<< orphan*/  va_surface; } ;
typedef  int /*<<< orphan*/  picture_context_t ;

/* Variables and functions */
 int /*<<< orphan*/  AcquireD3D9PictureSys (int /*<<< orphan*/ *) ; 
 struct dxva2_pic_context* DXVA2_PICCONTEXT_FROM_PICCTX (int /*<<< orphan*/ *) ; 
 struct dxva2_pic_context* malloc (int) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  va_surface_AddRef (int /*<<< orphan*/ ) ; 

__attribute__((used)) static picture_context_t *dxva2_pic_context_copy(picture_context_t *ctx)
{
    struct dxva2_pic_context *src_ctx = DXVA2_PICCONTEXT_FROM_PICCTX(ctx);
    struct dxva2_pic_context *pic_ctx = malloc(sizeof(*pic_ctx));
    if (unlikely(pic_ctx==NULL))
        return NULL;
    *pic_ctx = *src_ctx;
    va_surface_AddRef(pic_ctx->va_surface);
    AcquireD3D9PictureSys(&pic_ctx->ctx.picsys);
    return &pic_ctx->ctx.s;
}