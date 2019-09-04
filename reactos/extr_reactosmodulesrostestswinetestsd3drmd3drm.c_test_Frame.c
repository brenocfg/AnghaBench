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
typedef  scalar_t__ ULONG ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  IDirect3DRMVisualArray ;
typedef  int /*<<< orphan*/  IDirect3DRMVisual ;
typedef  int /*<<< orphan*/  IDirect3DRMObject ;
typedef  int /*<<< orphan*/  IDirect3DRMMeshBuilder ;
typedef  int /*<<< orphan*/  IDirect3DRMLightArray ;
typedef  int /*<<< orphan*/  IDirect3DRMLight ;
typedef  int /*<<< orphan*/  IDirect3DRMFrameArray ;
typedef  int /*<<< orphan*/  IDirect3DRMFrame3 ;
typedef  int /*<<< orphan*/  IDirect3DRMFrame ;
typedef  int /*<<< orphan*/  IDirect3DRM ;
typedef  int HRESULT ;
typedef  int DWORD ;
typedef  int D3DCOLOR ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_REFCOUNT (int /*<<< orphan*/ *,int) ; 
 int D3DRMERR_BADOBJECT ; 
 int D3DRMERR_BADVALUE ; 
 int D3DRMFRAME_PICKENABLE ; 
 int D3DRMFRAME_RENDERENABLE ; 
 int /*<<< orphan*/  D3DRMLIGHT_SPOT ; 
 int D3DRM_OK ; 
 int Direct3DRMCreate (int /*<<< orphan*/ **) ; 
 int IDirect3DRMFrame3_GetTraversalOptions (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  IDirect3DRMFrame3_Release (int /*<<< orphan*/ *) ; 
 int IDirect3DRMFrame3_SetTraversalOptions (int /*<<< orphan*/ *,int) ; 
 int IDirect3DRMFrameArray_GetElement (int /*<<< orphan*/ *,int,int /*<<< orphan*/ **) ; 
 int IDirect3DRMFrameArray_GetSize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDirect3DRMFrameArray_Release (int /*<<< orphan*/ *) ; 
 int IDirect3DRMFrame_AddChild (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int IDirect3DRMFrame_AddLight (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int IDirect3DRMFrame_AddVisual (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int IDirect3DRMFrame_DeleteChild (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int IDirect3DRMFrame_DeleteLight (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int IDirect3DRMFrame_DeleteVisual (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int IDirect3DRMFrame_GetChildren (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int IDirect3DRMFrame_GetLights (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int IDirect3DRMFrame_GetParent (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int IDirect3DRMFrame_GetScene (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int IDirect3DRMFrame_GetSceneBackground (int /*<<< orphan*/ *) ; 
 int IDirect3DRMFrame_GetVisuals (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int IDirect3DRMFrame_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IDirect3DRMFrame_Release (int /*<<< orphan*/ *) ; 
 int IDirect3DRMFrame_SetSceneBackground (int /*<<< orphan*/ *,int) ; 
 int IDirect3DRMFrame_SetSceneBackgroundRGB (int /*<<< orphan*/ *,double,double,double) ; 
 int IDirect3DRMLightArray_GetElement (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int IDirect3DRMLightArray_GetSize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDirect3DRMLightArray_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDirect3DRMLight_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDirect3DRMMeshBuilder_Release (int /*<<< orphan*/ *) ; 
 int IDirect3DRMVisualArray_GetElement (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int IDirect3DRMVisualArray_GetSize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDirect3DRMVisualArray_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDirect3DRMVisual_Release (int /*<<< orphan*/ *) ; 
 int IDirect3DRM_CreateFrame (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int IDirect3DRM_CreateLightRGB (int /*<<< orphan*/ *,int /*<<< orphan*/ ,double,double,double,int /*<<< orphan*/ **) ; 
 int IDirect3DRM_CreateMeshBuilder (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IDirect3DRM_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IDirect3DRMFrame3 ; 
 int SUCCEEDED (int) ; 
 scalar_t__ broken (int) ; 
 int get_refcount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  test_class_name (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  test_object_name (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_Frame(void)
{
    HRESULT hr;
    IDirect3DRM *d3drm;
    IDirect3DRMFrame *pFrameC;
    IDirect3DRMFrame *pFrameP1;
    IDirect3DRMFrame *pFrameP2;
    IDirect3DRMFrame *pFrameTmp;
    IDirect3DRMFrame *scene_frame;
    IDirect3DRMFrameArray *frame_array;
    IDirect3DRMMeshBuilder *mesh_builder;
    IDirect3DRMVisual *visual1;
    IDirect3DRMVisual *visual_tmp;
    IDirect3DRMVisualArray *visual_array;
    IDirect3DRMLight *light1;
    IDirect3DRMLight *light_tmp;
    IDirect3DRMLightArray *light_array;
    IDirect3DRMFrame3 *frame3;
    DWORD count, options;
    ULONG ref, ref2;
    D3DCOLOR color;

    hr = Direct3DRMCreate(&d3drm);
    ok(hr == D3DRM_OK, "Cannot get IDirect3DRM interface (hr = %x)\n", hr);

    ref = get_refcount((IUnknown *)d3drm);
    hr = IDirect3DRM_CreateFrame(d3drm, NULL, &pFrameC);
    ok(hr == D3DRM_OK, "Cannot get IDirect3DRMFrame interface (hr = %x)\n", hr);
    CHECK_REFCOUNT(pFrameC, 1);
    ref2 = get_refcount((IUnknown *)d3drm);
    ok(ref2 > ref, "Expected d3drm object to be referenced.\n");

    test_class_name((IDirect3DRMObject *)pFrameC, "Frame");
    test_object_name((IDirect3DRMObject *)pFrameC);

    hr = IDirect3DRMFrame_GetParent(pFrameC, NULL);
    ok(hr == D3DRMERR_BADVALUE, "Should fail and return D3DRM_BADVALUE (hr = %x)\n", hr);
    pFrameTmp = (void*)0xdeadbeef;
    hr = IDirect3DRMFrame_GetParent(pFrameC, &pFrameTmp);
    ok(hr == D3DRM_OK, "Cannot get parent frame (hr = %x)\n", hr);
    ok(pFrameTmp == NULL, "pFrameTmp = %p\n", pFrameTmp);
    CHECK_REFCOUNT(pFrameC, 1);

    frame_array = NULL;
    hr = IDirect3DRMFrame_GetChildren(pFrameC, &frame_array);
    ok(hr == D3DRM_OK, "Cannot get children (hr = %x)\n", hr);
    ok(!!frame_array, "frame_array = %p\n", frame_array);
    if (frame_array)
    {
        count = IDirect3DRMFrameArray_GetSize(frame_array);
        ok(count == 0, "count = %u\n", count);
        hr = IDirect3DRMFrameArray_GetElement(frame_array, 0, &pFrameTmp);
        ok(hr == D3DRMERR_BADVALUE, "Should have returned D3DRMERR_BADVALUE (hr = %x)\n", hr);
        ok(pFrameTmp == NULL, "pFrameTmp = %p\n", pFrameTmp);
        IDirect3DRMFrameArray_Release(frame_array);
    }

    hr = IDirect3DRM_CreateFrame(d3drm, NULL, &pFrameP1);
    ok(hr == D3DRM_OK, "Cannot get IDirect3DRMFrame interface (hr = %x)\n", hr);

    /* GetParent with NULL pointer */
    hr = IDirect3DRMFrame_GetParent(pFrameP1, NULL);
    ok(hr == D3DRMERR_BADVALUE, "Should have returned D3DRMERR_BADVALUE (hr = %x)\n", hr);
    CHECK_REFCOUNT(pFrameP1, 1);

    /* [Add/Delete]Child with NULL pointer */
    hr = IDirect3DRMFrame_AddChild(pFrameP1, NULL);
    ok(hr == D3DRMERR_BADOBJECT, "Should have returned D3DRMERR_BADOBJECT (hr = %x)\n", hr);
    CHECK_REFCOUNT(pFrameP1, 1);

    hr = IDirect3DRMFrame_DeleteChild(pFrameP1, NULL);
    ok(hr == D3DRMERR_BADOBJECT, "Should have returned D3DRMERR_BADOBJECT (hr = %x)\n", hr);
    CHECK_REFCOUNT(pFrameP1, 1);

    /* Add child to first parent */
    pFrameTmp = (void*)0xdeadbeef;
    hr = IDirect3DRMFrame_GetParent(pFrameP1, &pFrameTmp);
    ok(hr == D3DRM_OK, "Cannot get parent frame (hr = %x)\n", hr);
    ok(pFrameTmp == NULL, "pFrameTmp = %p\n", pFrameTmp);

    hr = IDirect3DRMFrame_AddChild(pFrameP1, pFrameC);
    ok(hr == D3DRM_OK, "Cannot add child frame (hr = %x)\n", hr);
    CHECK_REFCOUNT(pFrameP1, 1);
    CHECK_REFCOUNT(pFrameC, 2);

    hr = IDirect3DRMFrame_GetScene(pFrameC, NULL);
    ok(hr == D3DRMERR_BADVALUE, "Expected hr == D3DRMERR_BADVALUE, got %#x.\n", hr);
    hr = IDirect3DRMFrame_GetScene(pFrameC, &scene_frame);
    ok(SUCCEEDED(hr), "Cannot get scene (hr == %#x).\n", hr);
    ok(scene_frame == pFrameP1, "Expected scene frame == %p, got %p.\n", pFrameP1, scene_frame);
    CHECK_REFCOUNT(pFrameP1, 2);
    IDirect3DRMFrame_Release(scene_frame);
    hr = IDirect3DRMFrame_GetScene(pFrameP1, &scene_frame);
    ok(SUCCEEDED(hr), "Cannot get scene (hr == %#x).\n", hr);
    ok(scene_frame == pFrameP1, "Expected scene frame == %p, got %p.\n", pFrameP1, scene_frame);
    CHECK_REFCOUNT(pFrameP1, 2);
    IDirect3DRMFrame_Release(scene_frame);

    frame_array = NULL;
    hr = IDirect3DRMFrame_GetChildren(pFrameP1, &frame_array);
    ok(hr == D3DRM_OK, "Cannot get children (hr = %x)\n", hr);
    /* In some older version of d3drm, creating IDirect3DRMFrameArray object with GetChildren does not increment refcount of children frames */
    ok((get_refcount((IUnknown*)pFrameC) == 3) || broken(get_refcount((IUnknown*)pFrameC) == 2),
            "Invalid refcount. Expected 3 (or 2) got %d\n", get_refcount((IUnknown*)pFrameC));
    if (frame_array)
    {
        count = IDirect3DRMFrameArray_GetSize(frame_array);
        ok(count == 1, "count = %u\n", count);
        hr = IDirect3DRMFrameArray_GetElement(frame_array, 0, &pFrameTmp);
        ok(hr == D3DRM_OK, "Cannot get element (hr = %x)\n", hr);
        ok(pFrameTmp == pFrameC, "pFrameTmp = %p\n", pFrameTmp);
        ok((get_refcount((IUnknown*)pFrameC) == 4) || broken(get_refcount((IUnknown*)pFrameC) == 3),
                "Invalid refcount. Expected 4 (or 3) got %d\n", get_refcount((IUnknown*)pFrameC));
        IDirect3DRMFrame_Release(pFrameTmp);
        ok((get_refcount((IUnknown*)pFrameC) == 3) || broken(get_refcount((IUnknown*)pFrameC) == 2),
                "Invalid refcount. Expected 3 (or 2) got %d\n", get_refcount((IUnknown*)pFrameC));
        IDirect3DRMFrameArray_Release(frame_array);
        CHECK_REFCOUNT(pFrameC, 2);
    }

    pFrameTmp = (void*)0xdeadbeef;
    hr = IDirect3DRMFrame_GetParent(pFrameC, &pFrameTmp);
    ok(hr == D3DRM_OK, "Cannot get parent frame (hr = %x)\n", hr);
    ok(pFrameTmp == pFrameP1, "pFrameTmp = %p\n", pFrameTmp);
    CHECK_REFCOUNT(pFrameP1, 2);
    IDirect3DRMFrame_Release(pFrameTmp);
    CHECK_REFCOUNT(pFrameP1, 1);

    /* Add child to second parent */
    hr = IDirect3DRM_CreateFrame(d3drm, NULL, &pFrameP2);
    ok(hr == D3DRM_OK, "Cannot get IDirect3DRMFrame interface (hr = %x)\n", hr);

    hr = IDirect3DRMFrame_AddChild(pFrameP2, pFrameC);
    ok(hr == D3DRM_OK, "Cannot add child frame (hr = %x)\n", hr);
    CHECK_REFCOUNT(pFrameC, 2);

    frame_array = NULL;
    hr = IDirect3DRMFrame_GetChildren(pFrameP2, &frame_array);
    ok(hr == D3DRM_OK, "Cannot get children (hr = %x)\n", hr);
    if (frame_array)
    {
        count = IDirect3DRMFrameArray_GetSize(frame_array);
        ok(count == 1, "count = %u\n", count);
        hr = IDirect3DRMFrameArray_GetElement(frame_array, 0, &pFrameTmp);
        ok(hr == D3DRM_OK, "Cannot get element (hr = %x)\n", hr);
        ok(pFrameTmp == pFrameC, "pFrameTmp = %p\n", pFrameTmp);
        IDirect3DRMFrame_Release(pFrameTmp);
        IDirect3DRMFrameArray_Release(frame_array);
    }

    frame_array = NULL;
    hr = IDirect3DRMFrame_GetChildren(pFrameP1, &frame_array);
    ok(hr == D3DRM_OK, "Cannot get children (hr = %x)\n", hr);
    if (frame_array)
    {
        count = IDirect3DRMFrameArray_GetSize(frame_array);
        ok(count == 0, "count = %u\n", count);
        pFrameTmp = (void*)0xdeadbeef;
        hr = IDirect3DRMFrameArray_GetElement(frame_array, 0, &pFrameTmp);
        ok(hr == D3DRMERR_BADVALUE, "Should have returned D3DRMERR_BADVALUE (hr = %x)\n", hr);
        ok(pFrameTmp == NULL, "pFrameTmp = %p\n", pFrameTmp);
        IDirect3DRMFrameArray_Release(frame_array);
    }
    hr = IDirect3DRMFrame_GetScene(pFrameC, &scene_frame);
    ok(SUCCEEDED(hr), "Cannot get scene (hr == %#x).\n", hr);
    ok(scene_frame == pFrameP2, "Expected scene frame == %p, got %p.\n", pFrameP2, scene_frame);
    CHECK_REFCOUNT(pFrameP2, 2);
    IDirect3DRMFrame_Release(scene_frame);
    hr = IDirect3DRMFrame_GetScene(pFrameP2, &scene_frame);
    ok(SUCCEEDED(hr), "Cannot get scene (hr == %#x).\n", hr);
    ok(scene_frame == pFrameP2, "Expected scene frame == %p, got %p.\n", pFrameP2, scene_frame);
    CHECK_REFCOUNT(pFrameP2, 2);
    IDirect3DRMFrame_Release(scene_frame);

    pFrameTmp = (void*)0xdeadbeef;
    hr = IDirect3DRMFrame_GetParent(pFrameC, &pFrameTmp);
    ok(hr == D3DRM_OK, "Cannot get parent frame (hr = %x)\n", hr);
    ok(pFrameTmp == pFrameP2, "pFrameTmp = %p\n", pFrameTmp);
    CHECK_REFCOUNT(pFrameP2, 2);
    CHECK_REFCOUNT(pFrameC, 2);
    IDirect3DRMFrame_Release(pFrameTmp);
    CHECK_REFCOUNT(pFrameP2, 1);

    /* Add child again */
    hr = IDirect3DRMFrame_AddChild(pFrameP2, pFrameC);
    ok(hr == D3DRM_OK, "Cannot add child frame (hr = %x)\n", hr);
    CHECK_REFCOUNT(pFrameC, 2);

    frame_array = NULL;
    hr = IDirect3DRMFrame_GetChildren(pFrameP2, &frame_array);
    ok(hr == D3DRM_OK, "Cannot get children (hr = %x)\n", hr);
    if (frame_array)
    {
        count = IDirect3DRMFrameArray_GetSize(frame_array);
        ok(count == 1, "count = %u\n", count);
        hr = IDirect3DRMFrameArray_GetElement(frame_array, 0, &pFrameTmp);
        ok(hr == D3DRM_OK, "Cannot get element (hr = %x)\n", hr);
        ok(pFrameTmp == pFrameC, "pFrameTmp = %p\n", pFrameTmp);
        IDirect3DRMFrame_Release(pFrameTmp);
        IDirect3DRMFrameArray_Release(frame_array);
    }

    /* Delete child */
    hr = IDirect3DRMFrame_DeleteChild(pFrameP2, pFrameC);
    ok(hr == D3DRM_OK, "Cannot delete child frame (hr = %x)\n", hr);
    CHECK_REFCOUNT(pFrameC, 1);

    frame_array = NULL;
    hr = IDirect3DRMFrame_GetChildren(pFrameP2, &frame_array);
    ok(hr == D3DRM_OK, "Cannot get children (hr = %x)\n", hr);
    if (frame_array)
    {
        count = IDirect3DRMFrameArray_GetSize(frame_array);
        ok(count == 0, "count = %u\n", count);
        pFrameTmp = (void*)0xdeadbeef;
        hr = IDirect3DRMFrameArray_GetElement(frame_array, 0, &pFrameTmp);
        ok(hr == D3DRMERR_BADVALUE, "Should have returned D3DRMERR_BADVALUE (hr = %x)\n", hr);
        ok(pFrameTmp == NULL, "pFrameTmp = %p\n", pFrameTmp);
        IDirect3DRMFrameArray_Release(frame_array);
    }

    pFrameTmp = (void*)0xdeadbeef;
    hr = IDirect3DRMFrame_GetParent(pFrameC, &pFrameTmp);
    ok(hr == D3DRM_OK, "Cannot get parent frame (hr = %x)\n", hr);
    ok(pFrameTmp == NULL, "pFrameTmp = %p\n", pFrameTmp);

    /* Add two children */
    hr = IDirect3DRMFrame_AddChild(pFrameP2, pFrameC);
    ok(hr == D3DRM_OK, "Cannot add child frame (hr = %x)\n", hr);
    CHECK_REFCOUNT(pFrameC, 2);

    hr = IDirect3DRMFrame_AddChild(pFrameP2, pFrameP1);
    ok(hr == D3DRM_OK, "Cannot add child frame (hr = %x)\n", hr);
    CHECK_REFCOUNT(pFrameP1, 2);

    frame_array = NULL;
    hr = IDirect3DRMFrame_GetChildren(pFrameP2, &frame_array);
    ok(hr == D3DRM_OK, "Cannot get children (hr = %x)\n", hr);
    if (frame_array)
    {
        count = IDirect3DRMFrameArray_GetSize(frame_array);
        ok(count == 2, "count = %u\n", count);
        hr = IDirect3DRMFrameArray_GetElement(frame_array, 0, &pFrameTmp);
        ok(hr == D3DRM_OK, "Cannot get element (hr = %x)\n", hr);
        ok(pFrameTmp == pFrameC, "pFrameTmp = %p\n", pFrameTmp);
        IDirect3DRMFrame_Release(pFrameTmp);
        hr = IDirect3DRMFrameArray_GetElement(frame_array, 1, &pFrameTmp);
        ok(hr == D3DRM_OK, "Cannot get element (hr = %x)\n", hr);
        ok(pFrameTmp == pFrameP1, "pFrameTmp = %p\n", pFrameTmp);
        IDirect3DRMFrame_Release(pFrameTmp);
        IDirect3DRMFrameArray_Release(frame_array);
    }

    /* [Add/Delete]Visual with NULL pointer */
    hr = IDirect3DRMFrame_AddVisual(pFrameP1, NULL);
    ok(hr == D3DRMERR_BADOBJECT, "Should have returned D3DRMERR_BADOBJECT (hr = %x)\n", hr);
    CHECK_REFCOUNT(pFrameP1, 2);

    hr = IDirect3DRMFrame_DeleteVisual(pFrameP1, NULL);
    ok(hr == D3DRMERR_BADOBJECT, "Should have returned D3DRMERR_BADOBJECT (hr = %x)\n", hr);
    CHECK_REFCOUNT(pFrameP1, 2);

    /* Create Visual */
    hr = IDirect3DRM_CreateMeshBuilder(d3drm, &mesh_builder);
    ok(hr == D3DRM_OK, "Cannot get IDirect3DRMMeshBuilder interface (hr = %x)\n", hr);
    visual1 = (IDirect3DRMVisual *)mesh_builder;

    /* Add Visual to first parent */
    hr = IDirect3DRMFrame_AddVisual(pFrameP1, visual1);
    ok(hr == D3DRM_OK, "Cannot add visual (hr = %x)\n", hr);
    CHECK_REFCOUNT(pFrameP1, 2);
    CHECK_REFCOUNT(visual1, 2);

    visual_array = NULL;
    hr = IDirect3DRMFrame_GetVisuals(pFrameP1, &visual_array);
    ok(hr == D3DRM_OK, "Cannot get visuals (hr = %x)\n", hr);
    if (visual_array)
    {
        count = IDirect3DRMVisualArray_GetSize(visual_array);
        ok(count == 1, "count = %u\n", count);
        hr = IDirect3DRMVisualArray_GetElement(visual_array, 0, &visual_tmp);
        ok(hr == D3DRM_OK, "Cannot get element (hr = %x)\n", hr);
        ok(visual_tmp == visual1, "visual_tmp = %p\n", visual_tmp);
        IDirect3DRMVisual_Release(visual_tmp);
        IDirect3DRMVisualArray_Release(visual_array);
    }

    /* Delete Visual */
    hr = IDirect3DRMFrame_DeleteVisual(pFrameP1, visual1);
    ok(hr == D3DRM_OK, "Cannot delete visual (hr = %x)\n", hr);
    CHECK_REFCOUNT(pFrameP1, 2);
    IDirect3DRMMeshBuilder_Release(mesh_builder);

    /* [Add/Delete]Light with NULL pointer */
    hr = IDirect3DRMFrame_AddLight(pFrameP1, NULL);
    ok(hr == D3DRMERR_BADOBJECT, "Should have returned D3DRMERR_BADOBJECT (hr = %x)\n", hr);
    CHECK_REFCOUNT(pFrameP1, 2);

    hr = IDirect3DRMFrame_DeleteLight(pFrameP1, NULL);
    ok(hr == D3DRMERR_BADOBJECT, "Should have returned D3DRMERR_BADOBJECT (hr = %x)\n", hr);
    CHECK_REFCOUNT(pFrameP1, 2);

    /* Create Light */
    hr = IDirect3DRM_CreateLightRGB(d3drm, D3DRMLIGHT_SPOT, 0.1, 0.2, 0.3, &light1);
    ok(hr == D3DRM_OK, "Cannot get IDirect3DRMLight interface (hr = %x)\n", hr);

    /* Add Light to first parent */
    hr = IDirect3DRMFrame_AddLight(pFrameP1, light1);
    ok(hr == D3DRM_OK, "Cannot add light (hr = %x)\n", hr);
    CHECK_REFCOUNT(pFrameP1, 2);
    CHECK_REFCOUNT(light1, 2);

    light_array = NULL;
    hr = IDirect3DRMFrame_GetLights(pFrameP1, &light_array);
    ok(hr == D3DRM_OK, "Cannot get lights (hr = %x)\n", hr);
    if (light_array)
    {
        count = IDirect3DRMLightArray_GetSize(light_array);
        ok(count == 1, "count = %u\n", count);
        hr = IDirect3DRMLightArray_GetElement(light_array, 0, &light_tmp);
        ok(hr == D3DRM_OK, "Cannot get element (hr = %x)\n", hr);
        ok(light_tmp == light1, "light_tmp = %p\n", light_tmp);
        IDirect3DRMLight_Release(light_tmp);
        IDirect3DRMLightArray_Release(light_array);
    }

    /* Delete Light */
    hr = IDirect3DRMFrame_DeleteLight(pFrameP1, light1);
    ok(hr == D3DRM_OK, "Cannot delete light (hr = %x)\n", hr);
    CHECK_REFCOUNT(pFrameP1, 2);
    IDirect3DRMLight_Release(light1);

    /* Test SceneBackground on first parent */
    color = IDirect3DRMFrame_GetSceneBackground(pFrameP1);
    ok(color == 0xff000000, "wrong color (%x)\n", color);

    hr = IDirect3DRMFrame_SetSceneBackground(pFrameP1, 0xff180587);
    ok(hr == D3DRM_OK, "Cannot set color (hr = %x)\n", hr);
    color = IDirect3DRMFrame_GetSceneBackground(pFrameP1);
    ok(color == 0xff180587, "wrong color (%x)\n", color);

    hr = IDirect3DRMFrame_SetSceneBackgroundRGB(pFrameP1, 0.5, 0.5, 0.5);
    ok(hr == D3DRM_OK, "Cannot set color (hr = %x)\n", hr);
    color = IDirect3DRMFrame_GetSceneBackground(pFrameP1);
    ok(color == 0xff7f7f7f, "wrong color (%x)\n", color);

    /* Traversal options. */
    hr = IDirect3DRMFrame_QueryInterface(pFrameP2, &IID_IDirect3DRMFrame3, (void **)&frame3);
    ok(SUCCEEDED(hr), "Failed to get IDirect3DRMFrame3 interface, hr %#x.\n", hr);

    hr = IDirect3DRMFrame3_GetTraversalOptions(frame3, NULL);
    ok(hr == D3DRMERR_BADVALUE, "Unexpected hr %#x.\n", hr);

    options = 0;
    hr = IDirect3DRMFrame3_GetTraversalOptions(frame3, &options);
    ok(SUCCEEDED(hr), "Failed to get traversal options, hr %#x.\n", hr);
    ok(options == (D3DRMFRAME_RENDERENABLE | D3DRMFRAME_PICKENABLE), "Unexpected default options %#x.\n", options);

    hr = IDirect3DRMFrame3_SetTraversalOptions(frame3, 0);
    ok(SUCCEEDED(hr), "Unexpected hr %#x.\n", hr);

    hr = IDirect3DRMFrame3_SetTraversalOptions(frame3, 0xf0000000);
    ok(hr == D3DRMERR_BADVALUE, "Unexpected hr %#x.\n", hr);

    hr = IDirect3DRMFrame3_SetTraversalOptions(frame3, 0xf0000000 | D3DRMFRAME_PICKENABLE);
    ok(hr == D3DRMERR_BADVALUE, "Unexpected hr %#x.\n", hr);

    options = 0xf;
    hr = IDirect3DRMFrame3_GetTraversalOptions(frame3, &options);
    ok(SUCCEEDED(hr), "Failed to get traversal options, hr %#x.\n", hr);
    ok(options == 0, "Unexpected traversal options %#x.\n", options);

    hr = IDirect3DRMFrame3_SetTraversalOptions(frame3, D3DRMFRAME_PICKENABLE);
    ok(SUCCEEDED(hr), "Failed to set traversal options, hr %#x.\n", hr);

    options = 0;
    hr = IDirect3DRMFrame3_GetTraversalOptions(frame3, &options);
    ok(SUCCEEDED(hr), "Failed to get traversal options, hr %#x.\n", hr);
    ok(options == D3DRMFRAME_PICKENABLE, "Unexpected traversal options %#x.\n", options);

    IDirect3DRMFrame3_Release(frame3);

    /* Cleanup */
    IDirect3DRMFrame_Release(pFrameP2);
    CHECK_REFCOUNT(pFrameC, 1);
    CHECK_REFCOUNT(pFrameP1, 1);

    IDirect3DRMFrame_Release(pFrameC);
    IDirect3DRMFrame_Release(pFrameP1);

    IDirect3DRM_Release(d3drm);
}