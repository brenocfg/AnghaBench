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
typedef  int /*<<< orphan*/  vlc_object_t ;
typedef  int /*<<< orphan*/  d3d11_handle_t ;
struct TYPE_3__ {scalar_t__ feature_level; } ;
typedef  TYPE_1__ d3d11_device_t ;
typedef  int /*<<< orphan*/  ID3DBlob ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  D3DCompile (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 scalar_t__ D3D_FEATURE_LEVEL_10_0 ; 
 scalar_t__ D3D_FEATURE_LEVEL_9_3 ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 char* ID3D10Blob_GetBufferPointer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ID3D10Blob_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static ID3DBlob* D3D11_CompileShader(vlc_object_t *obj, const d3d11_handle_t *hd3d,
                                     const d3d11_device_t *d3d_dev,
                                     const char *psz_shader, bool pixel)
{
    ID3DBlob* pShaderBlob = NULL, *pErrBlob;
    const char *target;
    if (pixel)
    {
        if (likely(d3d_dev->feature_level >= D3D_FEATURE_LEVEL_10_0))
            target = "ps_4_0";
        else if (d3d_dev->feature_level >= D3D_FEATURE_LEVEL_9_3)
            target = "ps_4_0_level_9_3";
        else
            target = "ps_4_0_level_9_1";
    }
    else
    {
        if (likely(d3d_dev->feature_level >= D3D_FEATURE_LEVEL_10_0))
            target = "vs_4_0";
        else if (d3d_dev->feature_level >= D3D_FEATURE_LEVEL_9_3)
            target = "vs_4_0_level_9_3";
        else
            target = "vs_4_0_level_9_1";
    }

    HRESULT hr = D3DCompile(psz_shader, strlen(psz_shader),
                            NULL, NULL, NULL, "main", target,
                            0, 0, &pShaderBlob, &pErrBlob);

    if (FAILED(hr)) {
        char *err = pErrBlob ? ID3D10Blob_GetBufferPointer(pErrBlob) : NULL;
        msg_Err(obj, "invalid %s Shader (hr=0x%lX): %s", pixel?"Pixel":"Vertex", hr, err );
        if (pErrBlob)
            ID3D10Blob_Release(pErrBlob);
        return NULL;
    }
    return pShaderBlob;
}