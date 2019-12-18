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
struct d3d11_pic_context {int /*<<< orphan*/  s; int /*<<< orphan*/  picsys; } ;
typedef  int /*<<< orphan*/  picture_context_t ;

/* Variables and functions */
 int /*<<< orphan*/  AcquireD3D11PictureSys (int /*<<< orphan*/ *) ; 
 struct d3d11_pic_context* D3D11_PICCONTEXT_FROM_PICCTX (int /*<<< orphan*/ *) ; 
 struct d3d11_pic_context* calloc (int,int) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

picture_context_t *d3d11_pic_context_copy(picture_context_t *ctx)
{
    struct d3d11_pic_context *pic_ctx = calloc(1, sizeof(*pic_ctx));
    if (unlikely(pic_ctx==NULL))
        return NULL;
    *pic_ctx = *D3D11_PICCONTEXT_FROM_PICCTX(ctx);
    AcquireD3D11PictureSys(&pic_ctx->picsys);
    return &pic_ctx->s;
}