#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_3__* sys; } ;
typedef  TYPE_2__ vlc_va_t ;
struct TYPE_7__ {int /*<<< orphan*/ * hw_surface; } ;
typedef  TYPE_3__ vlc_va_sys_t ;
typedef  int /*<<< orphan*/  vlc_va_surface_t ;
struct TYPE_5__ {int /*<<< orphan*/  s; } ;
struct dxva2_pic_context {TYPE_1__ ctx; int /*<<< orphan*/ * va_surface; } ;
typedef  int /*<<< orphan*/  picture_context_t ;

/* Variables and functions */
 struct dxva2_pic_context* CreatePicContext (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 size_t va_surface_GetIndex (int /*<<< orphan*/ *) ; 

__attribute__((used)) static picture_context_t* NewSurfacePicContext(vlc_va_t *va, vlc_va_surface_t *va_surface)
{
    vlc_va_sys_t *sys = va->sys;
    struct dxva2_pic_context *pic_ctx = CreatePicContext(sys->hw_surface[va_surface_GetIndex(va_surface)]);
    if (unlikely(pic_ctx==NULL))
        return NULL;
    pic_ctx->va_surface = va_surface;
    return &pic_ctx->ctx.s;
}