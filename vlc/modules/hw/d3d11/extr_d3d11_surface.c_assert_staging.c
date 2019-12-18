#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_7__ ;
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
struct TYPE_21__ {int /*<<< orphan*/  context; int /*<<< orphan*/ * texture; } ;
typedef  TYPE_2__ picture_sys_d3d11_t ;
struct TYPE_22__ {TYPE_4__* p_sys; } ;
typedef  TYPE_3__ filter_t ;
struct TYPE_23__ {int /*<<< orphan*/ * staging; int /*<<< orphan*/ * procOutTexture; } ;
typedef  TYPE_4__ filter_sys_t ;
struct TYPE_24__ {scalar_t__ formatTexture; int /*<<< orphan*/  name; } ;
typedef  TYPE_5__ d3d_format_t ;
struct TYPE_25__ {int /*<<< orphan*/  d3ddevice; int /*<<< orphan*/  d3dcontext; } ;
typedef  TYPE_6__ d3d11_device_t ;
typedef  int UINT ;
struct TYPE_20__ {int Count; } ;
struct TYPE_26__ {int MipLevels; int ArraySize; scalar_t__ Format; int /*<<< orphan*/  BindFlags; scalar_t__ CPUAccessFlags; int /*<<< orphan*/  Usage; scalar_t__ MiscFlags; TYPE_1__ SampleDesc; } ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  scalar_t__ DXGI_FORMAT ;
typedef  TYPE_7__ D3D11_TEXTURE2D_DESC ;

/* Variables and functions */
 int /*<<< orphan*/  D3D11_BIND_RENDER_TARGET ; 
 scalar_t__ D3D11_CPU_ACCESS_READ ; 
 int D3D11_FORMAT_SUPPORT_SHADER_LOAD ; 
 int D3D11_FORMAT_SUPPORT_VIDEO_PROCESSOR_OUTPUT ; 
 int /*<<< orphan*/  D3D11_USAGE_DEFAULT ; 
 int /*<<< orphan*/  D3D11_USAGE_STAGING ; 
 int /*<<< orphan*/  DxgiFormatToStr (scalar_t__) ; 
 int /*<<< orphan*/  E_FAIL ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 TYPE_5__* FindD3D11Format (TYPE_3__*,TYPE_6__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  ID3D11DeviceContext_GetDevice (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ID3D11Device_CreateTexture2D (int /*<<< orphan*/ ,TYPE_7__*,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ID3D11Device_Release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ID3D11Texture2D_GetDesc (int /*<<< orphan*/ ,TYPE_7__*) ; 
 int /*<<< orphan*/  ID3D11Texture2D_Release (int /*<<< orphan*/ *) ; 
 size_t KNOWN_DXGI_INDEX ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 scalar_t__ SetupProcessor (TYPE_3__*,TYPE_6__*,scalar_t__,scalar_t__) ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  can_map (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_3__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_Err (TYPE_3__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int assert_staging(filter_t *p_filter, picture_sys_d3d11_t *p_sys)
{
    filter_sys_t *sys = p_filter->p_sys;
    HRESULT hr;

    if (sys->staging)
        goto ok;

    D3D11_TEXTURE2D_DESC texDesc;
    ID3D11Texture2D_GetDesc( p_sys->texture[KNOWN_DXGI_INDEX], &texDesc);

    texDesc.MipLevels = 1;
    texDesc.SampleDesc.Count = 1;
    texDesc.MiscFlags = 0;
    texDesc.ArraySize = 1;
    texDesc.Usage = D3D11_USAGE_STAGING;
    texDesc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
    texDesc.BindFlags = 0;

    d3d11_device_t d3d_dev = { .d3dcontext = p_sys->context };
    ID3D11DeviceContext_GetDevice(d3d_dev.d3dcontext, &d3d_dev.d3ddevice);
    sys->staging = NULL;
    hr = ID3D11Device_CreateTexture2D( d3d_dev.d3ddevice, &texDesc, NULL, &sys->staging);
    /* test if mapping the texture works ref #18746 */
    if (SUCCEEDED(hr) && FAILED(hr = can_map(sys, p_sys->context)))
        msg_Dbg(p_filter, "can't map default staging texture (hr=0x%lX)", hr);
#if CAN_PROCESSOR
    if (FAILED(hr)) {
        /* failed with the this format, try a different one */
        UINT supportFlags = D3D11_FORMAT_SUPPORT_SHADER_LOAD | D3D11_FORMAT_SUPPORT_VIDEO_PROCESSOR_OUTPUT;
        const d3d_format_t *new_fmt =
                FindD3D11Format( p_filter, &d3d_dev, 0, false, 0, 0, 0, false, supportFlags );
        if (new_fmt && texDesc.Format != new_fmt->formatTexture)
        {
            DXGI_FORMAT srcFormat = texDesc.Format;
            texDesc.Format = new_fmt->formatTexture;
            hr = ID3D11Device_CreateTexture2D( d3d_dev.d3ddevice, &texDesc, NULL, &sys->staging);
            if (SUCCEEDED(hr))
            {
                texDesc.Usage = D3D11_USAGE_DEFAULT;
                texDesc.CPUAccessFlags = 0;
                texDesc.BindFlags |= D3D11_BIND_RENDER_TARGET;
                hr = ID3D11Device_CreateTexture2D( d3d_dev.d3ddevice, &texDesc, NULL, &sys->procOutTexture);
                if (SUCCEEDED(hr) && SUCCEEDED(hr = can_map(sys, p_sys->context)))
                {
                    d3d11_device_t proc_dev = { .d3ddevice = d3d_dev.d3ddevice, .d3dcontext = p_sys->context };
                    if (SetupProcessor(p_filter, &proc_dev, srcFormat, new_fmt->formatTexture))
                    {
                        ID3D11Texture2D_Release(sys->procOutTexture);
                        ID3D11Texture2D_Release(sys->staging);
                        sys->staging = NULL;
                        hr = E_FAIL;
                    }
                    else
                        msg_Dbg(p_filter, "Using shader+processor format %s", new_fmt->name);
                }
                else
                {
                    msg_Dbg(p_filter, "can't create intermediate texture (hr=0x%lX)", hr);
                    ID3D11Texture2D_Release(sys->staging);
                    sys->staging = NULL;
                }
            }
        }
    }
#endif
    ID3D11Device_Release(d3d_dev.d3ddevice);
    if (FAILED(hr)) {
        msg_Err(p_filter, "Failed to create a %s staging texture to extract surface pixels (hr=0x%lX)", DxgiFormatToStr(texDesc.Format), hr );
        return VLC_EGENERIC;
    }
ok:
    return VLC_SUCCESS;
}