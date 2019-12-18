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
typedef  int /*<<< orphan*/  IDirect3DPixelShader9 ;
typedef  int /*<<< orphan*/  IDirect3DDevice9 ;
typedef  int /*<<< orphan*/  ID3DXConstantTable ;
typedef  int /*<<< orphan*/  ID3D10Blob ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  D3DXGetShaderConstantTable (scalar_t__,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  D3D_OK ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 scalar_t__ ID3D10Blob_GetBufferPointer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ID3D10Blob_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDirect3DDevice9_CreatePixelShader (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  ppD3DCompile (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static IDirect3DPixelShader9 *compile_pixel_shader9(IDirect3DDevice9 *device, const char *shader,
        const char *profile, ID3DXConstantTable **constants)
{
    ID3D10Blob *compiled = NULL;
    ID3D10Blob *errors = NULL;
    IDirect3DPixelShader9 *pshader;
    HRESULT hr;

    hr = ppD3DCompile(shader, strlen(shader), NULL, NULL,
            NULL, "test", profile, /* test is the name of the entry point of our shader */
            0, 0, &compiled, &errors);
    ok(hr == D3D_OK, "Pixel shader %s compilation failed: %s\n", shader,
            errors ? (char *)ID3D10Blob_GetBufferPointer(errors) : "");
    if (FAILED(hr)) return NULL;

    hr = D3DXGetShaderConstantTable(ID3D10Blob_GetBufferPointer(compiled), constants);
    ok(hr == D3D_OK, "Could not get constant table from compiled pixel shader\n");

    hr = IDirect3DDevice9_CreatePixelShader(device, ID3D10Blob_GetBufferPointer(compiled), &pshader);
    ok(SUCCEEDED(hr), "IDirect3DDevice9_CreatePixelShader returned: %08x\n", hr);
    ID3D10Blob_Release(compiled);
    return pshader;
}