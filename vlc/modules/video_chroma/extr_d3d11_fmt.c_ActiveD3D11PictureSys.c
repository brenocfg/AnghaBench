#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct d3d11_pic_context {int /*<<< orphan*/  picsys; } ;
struct TYPE_3__ {int /*<<< orphan*/ * context; int /*<<< orphan*/ * p_sys; } ;
typedef  TYPE_1__ picture_t ;
typedef  int /*<<< orphan*/  picture_sys_d3d11_t ;

/* Variables and functions */
 struct d3d11_pic_context* D3D11_PICCONTEXT_FROM_PICCTX (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

picture_sys_d3d11_t *ActiveD3D11PictureSys(picture_t *pic)
{
    if (unlikely(pic->context == NULL))
        return pic->p_sys;

    struct d3d11_pic_context *pic_ctx = D3D11_PICCONTEXT_FROM_PICCTX(pic->context);
    return &pic_ctx->picsys;
}