#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
typedef  int /*<<< orphan*/  d3d11_handle_t ;
struct TYPE_4__ {int /*<<< orphan*/  d3ddevice; } ;
typedef  TYPE_1__ d3d11_device_t ;
typedef  int /*<<< orphan*/  ID3DBlob ;
typedef  int /*<<< orphan*/  ID3D11PixelShader ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/ * D3D11_CompileShader (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  E_INVALIDARG ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 scalar_t__ ID3D10Blob_GetBufferPointer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ID3D10Blob_GetBufferSize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ID3D10Blob_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ID3D11Device_CreatePixelShader (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int asprintf (char**,int /*<<< orphan*/ ,char*,char const*,char const*,char const*,char const*,char const*,char const*,char const*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  globPixelShaderDefault ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ *,char*) ; 
 int var_InheritInteger (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static HRESULT CompileTargetShader(vlc_object_t *o, d3d11_handle_t *hd3d, bool legacy_shader,
                                   d3d11_device_t *d3d_dev,
                                   const char *psz_sampler,
                                   const char *psz_src_to_linear,
                                   const char *psz_primaries_transform,
                                   const char *psz_linear_to_display,
                                   const char *psz_tone_mapping,
                                   const char *psz_adjust_range, const char *psz_move_planes,
                                   ID3D11PixelShader **output)
{
    char *shader;
    int allocated = asprintf(&shader, globPixelShaderDefault, legacy_shader ? "" : "Array",
                             psz_src_to_linear, psz_linear_to_display,
                             psz_primaries_transform, psz_tone_mapping,
                             psz_adjust_range, psz_move_planes, psz_sampler);
    if (allocated <= 0)
    {
        msg_Err(o, "no room for the Pixel Shader");
        return E_OUTOFMEMORY;
    }
    if (var_InheritInteger(o, "verbose") >= 4)
        msg_Dbg(o, "shader %s", shader);
#ifndef NDEBUG
    else {
    msg_Dbg(o,"psz_src_to_linear %s", psz_src_to_linear);
    msg_Dbg(o,"psz_primaries_transform %s", psz_primaries_transform);
    msg_Dbg(o,"psz_tone_mapping %s", psz_tone_mapping);
    msg_Dbg(o,"psz_linear_to_display %s", psz_linear_to_display);
    msg_Dbg(o,"psz_adjust_range %s", psz_adjust_range);
    msg_Dbg(o,"psz_sampler %s", psz_sampler);
    msg_Dbg(o,"psz_move_planes %s", psz_move_planes);
    }
#endif

    ID3DBlob *pPSBlob = D3D11_CompileShader(o, hd3d, d3d_dev, shader, true);
    free(shader);
    if (!pPSBlob)
        return E_INVALIDARG;

    HRESULT hr = ID3D11Device_CreatePixelShader(d3d_dev->d3ddevice,
                                                (void *)ID3D10Blob_GetBufferPointer(pPSBlob),
                                                ID3D10Blob_GetBufferSize(pPSBlob), NULL, output);

    ID3D10Blob_Release(pPSBlob);
    return hr;
}