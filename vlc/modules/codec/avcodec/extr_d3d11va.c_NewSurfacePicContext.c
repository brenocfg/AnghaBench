#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {TYPE_5__* sys; } ;
typedef  TYPE_4__ vlc_va_t ;
struct TYPE_9__ {int /*<<< orphan*/  d3dcontext; } ;
struct TYPE_13__ {TYPE_1__ d3d_dev; int /*<<< orphan*/ ** renderSrc; int /*<<< orphan*/ ** hw_surface; } ;
typedef  TYPE_5__ vlc_va_sys_t ;
typedef  int /*<<< orphan*/  vlc_va_surface_t ;
struct TYPE_11__ {int /*<<< orphan*/  s; } ;
struct d3d11va_pic_context {TYPE_3__ ctx; int /*<<< orphan*/ * va_surface; } ;
typedef  int /*<<< orphan*/  picture_context_t ;
struct TYPE_10__ {int ArraySlice; } ;
struct TYPE_14__ {TYPE_2__ Texture2D; } ;
typedef  int /*<<< orphan*/  ID3D11VideoDecoderOutputView ;
typedef  int /*<<< orphan*/  ID3D11ShaderResourceView ;
typedef  int /*<<< orphan*/  ID3D11Resource ;
typedef  TYPE_6__ D3D11_VIDEO_DECODER_OUTPUT_VIEW_DESC ;

/* Variables and functions */
 struct d3d11va_pic_context* CreatePicContext (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ **) ; 
 int D3D11_MAX_SHADER_VIEW ; 
 int /*<<< orphan*/  ID3D11Resource_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ID3D11VideoDecoderOutputView_GetDesc (int /*<<< orphan*/ *,TYPE_6__*) ; 
 int /*<<< orphan*/  ID3D11VideoDecoderOutputView_GetResource (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 size_t va_surface_GetIndex (int /*<<< orphan*/ *) ; 

__attribute__((used)) static picture_context_t* NewSurfacePicContext(vlc_va_t *va, vlc_va_surface_t *va_surface)
{
    vlc_va_sys_t *sys = va->sys;
    ID3D11VideoDecoderOutputView *surface = sys->hw_surface[va_surface_GetIndex(va_surface)];
    ID3D11ShaderResourceView *resourceView[D3D11_MAX_SHADER_VIEW];
    ID3D11Resource *p_resource;
    ID3D11VideoDecoderOutputView_GetResource(surface, &p_resource);

    D3D11_VIDEO_DECODER_OUTPUT_VIEW_DESC viewDesc;
    ID3D11VideoDecoderOutputView_GetDesc(surface, &viewDesc);

    for (int i=0; i<D3D11_MAX_SHADER_VIEW; i++)
        resourceView[i] = sys->renderSrc[viewDesc.Texture2D.ArraySlice*D3D11_MAX_SHADER_VIEW + i];

    struct d3d11va_pic_context *pic_ctx = CreatePicContext(
                                                  p_resource,
                                                  sys->d3d_dev.d3dcontext,
                                                  viewDesc.Texture2D.ArraySlice,
                                                  resourceView);
    ID3D11Resource_Release(p_resource);
    if (unlikely(pic_ctx==NULL))
        return NULL;
    pic_ctx->va_surface = va_surface;
    return &pic_ctx->ctx.s;
}