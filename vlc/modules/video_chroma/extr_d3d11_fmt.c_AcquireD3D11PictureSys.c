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
struct TYPE_3__ {scalar_t__ processorOutput; scalar_t__ processorInput; scalar_t__ context; scalar_t__* texture; scalar_t__* renderSrc; } ;
typedef  TYPE_1__ picture_sys_d3d11_t ;

/* Variables and functions */
 int D3D11_MAX_SHADER_VIEW ; 
 int /*<<< orphan*/  ID3D11DeviceContext_AddRef (scalar_t__) ; 
 int /*<<< orphan*/  ID3D11ShaderResourceView_AddRef (scalar_t__) ; 
 int /*<<< orphan*/  ID3D11Texture2D_AddRef (scalar_t__) ; 
 int /*<<< orphan*/  ID3D11VideoProcessorInputView_AddRef (scalar_t__) ; 
 int /*<<< orphan*/  ID3D11VideoProcessorOutputView_AddRef (scalar_t__) ; 

void AcquireD3D11PictureSys(picture_sys_d3d11_t *p_sys)
{
    for (int i=0; i<D3D11_MAX_SHADER_VIEW; i++) {
        if (p_sys->renderSrc[i])
            ID3D11ShaderResourceView_AddRef(p_sys->renderSrc[i]);
        if (p_sys->texture[i])
            ID3D11Texture2D_AddRef(p_sys->texture[i]);
    }
    if (p_sys->context)
        ID3D11DeviceContext_AddRef(p_sys->context);
    if (p_sys->processorInput)
        ID3D11VideoProcessorInputView_AddRef(p_sys->processorInput);
    if (p_sys->processorOutput)
        ID3D11VideoProcessorOutputView_AddRef(p_sys->processorOutput);
}