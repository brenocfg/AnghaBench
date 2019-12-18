#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned int surface_count; scalar_t__ video_context; scalar_t__ decoder; } ;
struct TYPE_5__ {int /*<<< orphan*/  hd3d; int /*<<< orphan*/  d3d_dev; TYPE_1__ hw; scalar_t__ d3ddec; scalar_t__* renderSrc; scalar_t__* hw_surface; } ;
typedef  TYPE_2__ vlc_va_sys_t ;
typedef  int /*<<< orphan*/  ID3D11Resource ;

/* Variables and functions */
 int /*<<< orphan*/  D3D11_Destroy (int /*<<< orphan*/ *) ; 
 int D3D11_MAX_SHADER_VIEW ; 
 int /*<<< orphan*/  D3D11_ReleaseDevice (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ID3D11Resource_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ID3D11ShaderResourceView_Release (scalar_t__) ; 
 int /*<<< orphan*/  ID3D11VideoContext_Release (scalar_t__) ; 
 int /*<<< orphan*/  ID3D11VideoDecoderOutputView_GetResource (scalar_t__,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ID3D11VideoDecoderOutputView_Release (scalar_t__) ; 
 int /*<<< orphan*/  ID3D11VideoDecoder_Release (scalar_t__) ; 
 int /*<<< orphan*/  ID3D11VideoDevice_Release (scalar_t__) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 

__attribute__((used)) static void DxDestroySurfaces(void *opaque)
{
    vlc_va_sys_t *sys = opaque;
    if (sys->hw_surface[0]) {
        ID3D11Resource *p_texture;
        ID3D11VideoDecoderOutputView_GetResource( sys->hw_surface[0], &p_texture );
        ID3D11Resource_Release(p_texture);
        ID3D11Resource_Release(p_texture);
        for (unsigned i = 0; i < sys->hw.surface_count; i++)
        {
            ID3D11VideoDecoderOutputView_Release( sys->hw_surface[i] );
            for (int j = 0; j < D3D11_MAX_SHADER_VIEW; j++)
            {
                if (sys->renderSrc[i*D3D11_MAX_SHADER_VIEW + j])
                    ID3D11ShaderResourceView_Release(sys->renderSrc[i*D3D11_MAX_SHADER_VIEW + j]);
            }
        }
    }
    if (sys->hw.decoder)
        ID3D11VideoDecoder_Release(sys->hw.decoder);

    if (sys->d3ddec)
        ID3D11VideoDevice_Release(sys->d3ddec);
    if (sys->hw.video_context)
        ID3D11VideoContext_Release(sys->hw.video_context);
    D3D11_ReleaseDevice( &sys->d3d_dev );

    D3D11_Destroy( &sys->hd3d );

    free(sys);
}