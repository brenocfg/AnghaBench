#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * renderSrc; int /*<<< orphan*/ * resource; } ;
struct TYPE_3__ {int /*<<< orphan*/  s; TYPE_2__ picsys; } ;
struct d3d11va_pic_context {TYPE_1__ ctx; int /*<<< orphan*/  va_surface; } ;
typedef  int /*<<< orphan*/  picture_context_t ;

/* Variables and functions */
 int /*<<< orphan*/  AcquireD3D11PictureSys (TYPE_2__*) ; 
 struct d3d11va_pic_context* D3D11VA_PICCONTEXT_FROM_PICCTX (int /*<<< orphan*/ *) ; 
 int D3D11_MAX_SHADER_VIEW ; 
 struct d3d11va_pic_context* malloc (int) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  va_surface_AddRef (int /*<<< orphan*/ ) ; 

__attribute__((used)) static picture_context_t *d3d11va_pic_context_copy(picture_context_t *ctx)
{
    struct d3d11va_pic_context *src_ctx = D3D11VA_PICCONTEXT_FROM_PICCTX(ctx);
    struct d3d11va_pic_context *pic_ctx = malloc(sizeof(*pic_ctx));
    if (unlikely(pic_ctx==NULL))
        return NULL;
    *pic_ctx = *src_ctx;
    va_surface_AddRef(pic_ctx->va_surface);
    for (int i=0;i<D3D11_MAX_SHADER_VIEW; i++)
    {
        pic_ctx->ctx.picsys.resource[i]  = src_ctx->ctx.picsys.resource[i];
        pic_ctx->ctx.picsys.renderSrc[i] = src_ctx->ctx.picsys.renderSrc[i];
    }
    AcquireD3D11PictureSys(&pic_ctx->ctx.picsys);
    return &pic_ctx->ctx.s;
}