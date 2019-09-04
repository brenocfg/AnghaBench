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
struct TYPE_3__ {void* dSize; void* lpMemory; } ;
typedef  int /*<<< orphan*/  IDirect3DRMObject ;
typedef  int /*<<< orphan*/  IDirect3DRMMeshBuilder3 ;
typedef  int /*<<< orphan*/  IDirect3DRM3 ;
typedef  int /*<<< orphan*/  IDirect3DRM ;
typedef  float HRESULT ;
typedef  int DWORD ;
typedef  float D3DVALUE ;
typedef  TYPE_1__ D3DRMLOADMEMORY ;

/* Variables and functions */
 float D3DRMERR_BADFILE ; 
 float D3DRMERR_BADVALUE ; 
 float D3DRMERR_NOTFOUND ; 
 int /*<<< orphan*/  D3DRMLOAD_FROMMEMORY ; 
 float D3DRM_OK ; 
 float Direct3DRMCreate (int /*<<< orphan*/ **) ; 
 scalar_t__ FAILED (float) ; 
 float IDirect3DRM3_CreateMeshBuilder (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IDirect3DRM3_Release (int /*<<< orphan*/ *) ; 
 int IDirect3DRMMeshBuilder3_GetFaceCount (int /*<<< orphan*/ *) ; 
 float IDirect3DRMMeshBuilder3_GetTextureCoordinates (int /*<<< orphan*/ *,int,float*,float*) ; 
 int IDirect3DRMMeshBuilder3_GetVertexCount (int /*<<< orphan*/ *) ; 
 float IDirect3DRMMeshBuilder3_GetVertices (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *) ; 
 float IDirect3DRMMeshBuilder3_Load (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDirect3DRMMeshBuilder3_Release (int /*<<< orphan*/ *) ; 
 float IDirect3DRMMeshBuilder3_SetTextureCoordinates (int /*<<< orphan*/ *,int,float,float) ; 
 float IDirect3DRM_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IDirect3DRM_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IDirect3DRM3 ; 
 void* data_bad_version ; 
 void* data_no_mesh ; 
 void* data_ok ; 
 int /*<<< orphan*/  ok (int,char*,float) ; 
 void* strlen (void*) ; 
 int /*<<< orphan*/  test_class_name (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  test_object_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  win_skip (char*,float) ; 

__attribute__((used)) static void test_MeshBuilder3(void)
{
    HRESULT hr;
    IDirect3DRM *d3drm;
    IDirect3DRM3 *d3drm3;
    IDirect3DRMMeshBuilder3 *pMeshBuilder3;
    D3DRMLOADMEMORY info;
    int val;
    DWORD val1;
    D3DVALUE valu, valv;

    hr = Direct3DRMCreate(&d3drm);
    ok(hr == D3DRM_OK, "Cannot get IDirect3DRM interface (hr = %x)\n", hr);

    if (FAILED(hr = IDirect3DRM_QueryInterface(d3drm, &IID_IDirect3DRM3, (void **)&d3drm3)))
    {
        win_skip("Cannot get IDirect3DRM3 interface (hr = %x), skipping tests\n", hr);
        IDirect3DRM_Release(d3drm);
        return;
    }

    hr = IDirect3DRM3_CreateMeshBuilder(d3drm3, &pMeshBuilder3);
    ok(hr == D3DRM_OK, "Cannot get IDirect3DRMMeshBuilder3 interface (hr = %x)\n", hr);

    test_class_name((IDirect3DRMObject *)pMeshBuilder3, "Builder");
    test_object_name((IDirect3DRMObject *)pMeshBuilder3);

    info.lpMemory = data_bad_version;
    info.dSize = strlen(data_bad_version);
    hr = IDirect3DRMMeshBuilder3_Load(pMeshBuilder3, &info, NULL, D3DRMLOAD_FROMMEMORY, NULL, NULL);
    ok(hr == D3DRMERR_BADFILE, "Should have returned D3DRMERR_BADFILE (hr = %x)\n", hr);

    info.lpMemory = data_no_mesh;
    info.dSize = strlen(data_no_mesh);
    hr = IDirect3DRMMeshBuilder3_Load(pMeshBuilder3, &info, NULL, D3DRMLOAD_FROMMEMORY, NULL, NULL);
    ok(hr == D3DRMERR_NOTFOUND, "Should have returned D3DRMERR_NOTFOUND (hr = %x)\n", hr);

    info.lpMemory = data_ok;
    info.dSize = strlen(data_ok);
    hr = IDirect3DRMMeshBuilder3_Load(pMeshBuilder3, &info, NULL, D3DRMLOAD_FROMMEMORY, NULL, NULL);
    ok(hr == D3DRM_OK, "Cannot load mesh data (hr = %x)\n", hr);

    val = IDirect3DRMMeshBuilder3_GetVertexCount(pMeshBuilder3);
    ok(val == 4, "Wrong number of vertices %d (must be 4)\n", val);

    val = IDirect3DRMMeshBuilder3_GetFaceCount(pMeshBuilder3);
    ok(val == 3, "Wrong number of faces %d (must be 3)\n", val);

    hr = IDirect3DRMMeshBuilder3_GetVertices(pMeshBuilder3, 0, &val1, NULL);
    ok(hr == D3DRM_OK, "Cannot get vertices information (hr = %x)\n", hr);
    ok(val1 == 4, "Wrong number of vertices %d (must be 4)\n", val1);

    /* Check that Load method generated default texture coordinates (0.0f, 0.0f) for each vertex */
    valu = 1.23f;
    valv = 3.21f;
    hr = IDirect3DRMMeshBuilder3_GetTextureCoordinates(pMeshBuilder3, 0, &valu, &valv);
    ok(hr == D3DRM_OK, "Cannot get texture coordinates (hr = %x)\n", hr);
    ok(valu == 0.0f, "Wrong coordinate %f (must be 0.0)\n", valu);
    ok(valv == 0.0f, "Wrong coordinate %f (must be 0.0)\n", valv);
    valu = 1.23f;
    valv = 3.21f;
    hr = IDirect3DRMMeshBuilder3_GetTextureCoordinates(pMeshBuilder3, 1, &valu, &valv);
    ok(hr == D3DRM_OK, "Cannot get texture coordinates (hr = %x)\n", hr);
    ok(valu == 0.0f, "Wrong coordinate %f (must be 0.0)\n", valu);
    ok(valv == 0.0f, "Wrong coordinate %f (must be 0.0)\n", valv);
    valu = 1.23f;
    valv = 3.21f;
    hr = IDirect3DRMMeshBuilder3_GetTextureCoordinates(pMeshBuilder3, 2, &valu, &valv);
    ok(hr == D3DRM_OK, "Cannot get texture coordinates (hr = %x)\n", hr);
    ok(valu == 0.0f, "Wrong coordinate %f (must be 0.0)\n", valu);
    ok(valv == 0.0f, "Wrong coordinate %f (must be 0.0)\n", valv);
    valu = 1.23f;
    valv = 3.21f;
    hr = IDirect3DRMMeshBuilder3_GetTextureCoordinates(pMeshBuilder3, 3, &valu, &valv);
    ok(hr == D3DRM_OK, "Cannot get texture coordinates (hr = %x)\n", hr);
    ok(valu == 0.0f, "Wrong coordinate %f (must be 0.0)\n", valu);
    ok(valv == 0.0f, "Wrong coordinate %f (must be 0.0)\n", valv);
    hr = IDirect3DRMMeshBuilder3_GetTextureCoordinates(pMeshBuilder3, 4, &valu, &valv);
    ok(hr == D3DRMERR_BADVALUE, "Should fail and return D3DRM_BADVALUE (hr = %x)\n", hr);

    valu = 1.23f;
    valv = 3.21f;
    hr = IDirect3DRMMeshBuilder3_SetTextureCoordinates(pMeshBuilder3, 0, valu, valv);
    ok(hr == D3DRM_OK, "Cannot set texture coordinates (hr = %x)\n", hr);
    hr = IDirect3DRMMeshBuilder3_SetTextureCoordinates(pMeshBuilder3, 4, valu, valv);
    ok(hr == D3DRMERR_BADVALUE, "Should fail and return D3DRM_BADVALUE (hr = %x)\n", hr);

    valu = 0.0f;
    valv = 0.0f;
    hr = IDirect3DRMMeshBuilder3_GetTextureCoordinates(pMeshBuilder3, 0, &valu, &valv);
    ok(hr == D3DRM_OK, "Cannot get texture coordinates (hr = %x)\n", hr);
    ok(valu == 1.23f, "Wrong coordinate %f (must be 1.23)\n", valu);
    ok(valv == 3.21f, "Wrong coordinate %f (must be 3.21)\n", valv);

    IDirect3DRMMeshBuilder3_Release(pMeshBuilder3);
    IDirect3DRM3_Release(d3drm3);
    IDirect3DRM_Release(d3drm);
}