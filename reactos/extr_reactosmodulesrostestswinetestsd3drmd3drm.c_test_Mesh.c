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
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  IDirect3DRMObject ;
typedef  int /*<<< orphan*/  IDirect3DRMMesh ;
typedef  int /*<<< orphan*/  IDirect3DRM ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 scalar_t__ D3DRM_OK ; 
 scalar_t__ Direct3DRMCreate (int /*<<< orphan*/ **) ; 
 scalar_t__ IDirect3DRMMesh_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IDirect3DRMMesh_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IDirect3DRM_CreateMesh (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IDirect3DRM_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IDirect3DRMObject ; 
 int /*<<< orphan*/  IID_IDirect3DRMVisual ; 
 int /*<<< orphan*/  IUnknown_Release (int /*<<< orphan*/ *) ; 
 int SUCCEEDED (scalar_t__) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  test_class_name (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  test_object_name (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_Mesh(void)
{
    HRESULT hr;
    IDirect3DRM *d3drm;
    IDirect3DRMMesh *mesh;
    IUnknown *unk;

    hr = Direct3DRMCreate(&d3drm);
    ok(hr == D3DRM_OK, "Cannot get IDirect3DRM interface (hr = %x)\n", hr);

    hr = IDirect3DRM_CreateMesh(d3drm, &mesh);
    ok(hr == D3DRM_OK, "Cannot get IDirect3DRMMesh interface (hr = %x)\n", hr);

    test_class_name((IDirect3DRMObject *)mesh, "Mesh");
    test_object_name((IDirect3DRMObject *)mesh);

    hr = IDirect3DRMMesh_QueryInterface(mesh, &IID_IDirect3DRMObject, (void **)&unk);
    ok(SUCCEEDED(hr), "Failed to get IDirect3DRMObject, %#x.\n", hr);
    IUnknown_Release(unk);

    hr = IDirect3DRMMesh_QueryInterface(mesh, &IID_IDirect3DRMVisual, (void **)&unk);
    ok(SUCCEEDED(hr), "Failed to get IDirect3DRMVisual, %#x.\n", hr);
    IUnknown_Release(unk);

    IDirect3DRMMesh_Release(mesh);

    IDirect3DRM_Release(d3drm);
}