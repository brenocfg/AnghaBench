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
typedef  int /*<<< orphan*/  name ;
struct TYPE_3__ {char* lpMemory; void* dSize; } ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  IDirect3DRMTexture ;
typedef  int /*<<< orphan*/  IDirect3DRMObject ;
typedef  int /*<<< orphan*/  IDirect3DRMMeshBuilder3 ;
typedef  int /*<<< orphan*/  IDirect3DRMMeshBuilder ;
typedef  int /*<<< orphan*/  IDirect3DRMMesh ;
typedef  int /*<<< orphan*/  IDirect3DRMMaterial ;
typedef  int /*<<< orphan*/  IDirect3DRM ;
typedef  int HRESULT ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  D3DVECTOR ;
typedef  float D3DVALUE ;
typedef  TYPE_1__ D3DRMLOADMEMORY ;
typedef  int D3DCOLOR ;

/* Variables and functions */
 int D3DRMERR_BADFILE ; 
 int D3DRMERR_BADVALUE ; 
 int D3DRMERR_NOTFOUND ; 
 int /*<<< orphan*/  D3DRMLOAD_FROMMEMORY ; 
 int D3DRM_OK ; 
 int Direct3DRMCreate (int /*<<< orphan*/ **) ; 
 int E_INVALIDARG ; 
 int IDirect3DRMMaterial_GetEmissive (int /*<<< orphan*/ *,float*,float*,float*) ; 
 float IDirect3DRMMaterial_GetPower (int /*<<< orphan*/ *) ; 
 int IDirect3DRMMaterial_GetSpecular (int /*<<< orphan*/ *,float*,float*,float*) ; 
 int /*<<< orphan*/  IDirect3DRMMaterial_Release (int /*<<< orphan*/ *) ; 
 int IDirect3DRMMeshBuilder3_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IDirect3DRMMeshBuilder3_Release (int /*<<< orphan*/ *) ; 
 int IDirect3DRMMeshBuilder_CreateMesh (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int IDirect3DRMMeshBuilder_GetFaceCount (int /*<<< orphan*/ *) ; 
 int IDirect3DRMMeshBuilder_GetName (int /*<<< orphan*/ *,int*,char*) ; 
 int IDirect3DRMMeshBuilder_GetTextureCoordinates (int /*<<< orphan*/ *,int,float*,float*) ; 
 int IDirect3DRMMeshBuilder_GetVertexCount (int /*<<< orphan*/ *) ; 
 int IDirect3DRMMeshBuilder_GetVertices (int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *,int*,int*) ; 
 int IDirect3DRMMeshBuilder_Load (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int IDirect3DRMMeshBuilder_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IDirect3DRMMeshBuilder_Release (int /*<<< orphan*/ *) ; 
 int IDirect3DRMMeshBuilder_Scale (int /*<<< orphan*/ *,int,int,int) ; 
 int IDirect3DRMMeshBuilder_SetName (int /*<<< orphan*/ *,char*) ; 
 int IDirect3DRMMeshBuilder_SetTextureCoordinates (int /*<<< orphan*/ *,int,float,float) ; 
 int IDirect3DRMMesh_GetGroup (int /*<<< orphan*/ *,int,unsigned int*,unsigned int*,unsigned int*,int*,int /*<<< orphan*/ *) ; 
 int IDirect3DRMMesh_GetGroupColor (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int IDirect3DRMMesh_GetGroupCount (int /*<<< orphan*/ *) ; 
 int IDirect3DRMMesh_GetGroupMaterial (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int IDirect3DRMMesh_GetGroupTexture (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IDirect3DRMMesh_Release (int /*<<< orphan*/ *) ; 
 int IDirect3DRM_CreateMeshBuilder (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IDirect3DRM_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IDirect3DRMMeshBuilder3 ; 
 int /*<<< orphan*/  IID_IDirect3DRMObject ; 
 int /*<<< orphan*/  IID_IDirect3DRMVisual ; 
 int /*<<< orphan*/  IUnknown_Release (int /*<<< orphan*/ *) ; 
 int SUCCEEDED (int) ; 
 int /*<<< orphan*/  check_vector (int /*<<< orphan*/ *,float,float,float,int) ; 
 char* data_bad_version ; 
 char* data_full ; 
 char* data_no_mesh ; 
 char* data_ok ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 void* strlen (char*) ; 
 int /*<<< orphan*/  test_class_name (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  test_object_name (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_MeshBuilder(void)
{
    HRESULT hr;
    IDirect3DRM *d3drm;
    IDirect3DRMMeshBuilder *pMeshBuilder;
    IDirect3DRMMeshBuilder3 *meshbuilder3;
    IDirect3DRMMesh *mesh;
    D3DRMLOADMEMORY info;
    int val;
    DWORD val1, val2, val3;
    D3DVALUE valu, valv;
    D3DVECTOR v[3];
    D3DVECTOR n[4];
    DWORD f[8];
    char name[10];
    DWORD size;
    D3DCOLOR color;
    IUnknown *unk;

    hr = Direct3DRMCreate(&d3drm);
    ok(hr == D3DRM_OK, "Cannot get IDirect3DRM interface (hr = %x)\n", hr);

    hr = IDirect3DRM_CreateMeshBuilder(d3drm, &pMeshBuilder);
    ok(hr == D3DRM_OK, "Cannot get IDirect3DRMMeshBuilder interface (hr = %x)\n", hr);

    hr = IDirect3DRMMeshBuilder_QueryInterface(pMeshBuilder, &IID_IDirect3DRMObject, (void **)&unk);
    ok(SUCCEEDED(hr), "Failed to get IDirect3DRMObject, %#x.\n", hr);
    ok(unk == (IUnknown *)pMeshBuilder, "Unexpected interface pointer.\n");
    IUnknown_Release(unk);

    hr = IDirect3DRMMeshBuilder_QueryInterface(pMeshBuilder, &IID_IDirect3DRMVisual, (void **)&unk);
    ok(SUCCEEDED(hr), "Failed to get IDirect3DRMVisual, %#x.\n", hr);
    ok(unk == (IUnknown *)pMeshBuilder, "Unexpected interface pointer.\n");
    IUnknown_Release(unk);

    hr = IDirect3DRMMeshBuilder_QueryInterface(pMeshBuilder, &IID_IDirect3DRMMeshBuilder3, (void **)&meshbuilder3);
    ok(SUCCEEDED(hr), "Failed to get IDirect3DRMMeshBuilder3, %#x.\n", hr);

    hr = IDirect3DRMMeshBuilder3_QueryInterface(meshbuilder3, &IID_IDirect3DRMObject, (void **)&unk);
    ok(SUCCEEDED(hr), "Failed to get IDirect3DRMObject, %#x.\n", hr);
    ok(unk == (IUnknown *)pMeshBuilder, "Unexpected interface pointer.\n");
    IUnknown_Release(unk);

    hr = IDirect3DRMMeshBuilder3_QueryInterface(meshbuilder3, &IID_IDirect3DRMVisual, (void **)&unk);
    ok(SUCCEEDED(hr), "Failed to get IDirect3DRMVisual, %#x.\n", hr);
    ok(unk == (IUnknown *)pMeshBuilder, "Unexpected interface pointer.\n");
    IUnknown_Release(unk);

    IDirect3DRMMeshBuilder3_Release(meshbuilder3);

    test_class_name((IDirect3DRMObject *)pMeshBuilder, "Builder");
    test_object_name((IDirect3DRMObject *)pMeshBuilder);

    info.lpMemory = data_bad_version;
    info.dSize = strlen(data_bad_version);
    hr = IDirect3DRMMeshBuilder_Load(pMeshBuilder, &info, NULL, D3DRMLOAD_FROMMEMORY, NULL, NULL);
    ok(hr == D3DRMERR_BADFILE, "Should have returned D3DRMERR_BADFILE (hr = %x)\n", hr);

    info.lpMemory = data_no_mesh;
    info.dSize = strlen(data_no_mesh);
    hr = IDirect3DRMMeshBuilder_Load(pMeshBuilder, &info, NULL, D3DRMLOAD_FROMMEMORY, NULL, NULL);
    ok(hr == D3DRMERR_NOTFOUND, "Should have returned D3DRMERR_NOTFOUND (hr = %x)\n", hr);

    info.lpMemory = data_ok;
    info.dSize = strlen(data_ok);
    hr = IDirect3DRMMeshBuilder_Load(pMeshBuilder, &info, NULL, D3DRMLOAD_FROMMEMORY, NULL, NULL);
    ok(hr == D3DRM_OK, "Cannot load mesh data (hr = %x)\n", hr);

    size = sizeof(name);
    hr = IDirect3DRMMeshBuilder_GetName(pMeshBuilder, &size, name);
    ok(hr == D3DRM_OK, "IDirect3DRMMeshBuilder_GetName returned hr = %x\n", hr);
    ok(!strcmp(name, "Object"), "Retrieved name '%s' instead of 'Object'\n", name);
    size = strlen("Object"); /* No space for null character */
    hr = IDirect3DRMMeshBuilder_GetName(pMeshBuilder, &size, name);
    ok(hr == E_INVALIDARG, "IDirect3DRMMeshBuilder_GetName returned hr = %x\n", hr);
    hr = IDirect3DRMMeshBuilder_SetName(pMeshBuilder, NULL);
    ok(hr == D3DRM_OK, "IDirect3DRMMeshBuilder_SetName returned hr = %x\n", hr);
    size = sizeof(name);
    hr = IDirect3DRMMeshBuilder_GetName(pMeshBuilder, &size, name);
    ok(hr == D3DRM_OK, "IDirect3DRMMeshBuilder_GetName returned hr = %x\n", hr);
    ok(size == 0, "Size should be 0 instead of %u\n", size);
    hr = IDirect3DRMMeshBuilder_SetName(pMeshBuilder, "");
    ok(hr == D3DRM_OK, "IDirect3DRMMeshBuilder_SetName returned hr = %x\n", hr);
    size = sizeof(name);
    hr = IDirect3DRMMeshBuilder_GetName(pMeshBuilder, &size, name);
    ok(hr == D3DRM_OK, "IDirect3DRMMeshBuilder_GetName returned hr = %x\n", hr);
    ok(!strcmp(name, ""), "Retrieved name '%s' instead of ''\n", name);

    val = IDirect3DRMMeshBuilder_GetVertexCount(pMeshBuilder);
    ok(val == 4, "Wrong number of vertices %d (must be 4)\n", val);

    val = IDirect3DRMMeshBuilder_GetFaceCount(pMeshBuilder);
    ok(val == 3, "Wrong number of faces %d (must be 3)\n", val);

    hr = IDirect3DRMMeshBuilder_GetVertices(pMeshBuilder, &val1, NULL, &val2, NULL, &val3, NULL);
    ok(hr == D3DRM_OK, "Cannot get vertices information (hr = %x)\n", hr);
    ok(val1 == 4, "Wrong number of vertices %d (must be 4)\n", val1);
    ok(val2 == 4, "Wrong number of normals %d (must be 4)\n", val2);
    ok(val3 == 22, "Wrong number of face data bytes %d (must be 22)\n", val3);

    /* Check that Load method generated default normals */
    hr = IDirect3DRMMeshBuilder_GetVertices(pMeshBuilder, NULL, NULL, &val2, n, NULL, NULL);
    ok(hr == D3DRM_OK, "Cannot get vertices information (hr = %x)\n", hr);
    check_vector(&n[0],  0.577350f, 0.577350f, 0.577350f, 32);
    check_vector(&n[1], -0.229416f, 0.688247f, 0.688247f, 32);
    check_vector(&n[2], -0.229416f, 0.688247f, 0.688247f, 32);
    check_vector(&n[3], -0.577350f, 0.577350f, 0.577350f, 32);

    /* Check that Load method generated default texture coordinates (0.0f, 0.0f) for each vertex */
    valu = 1.23f;
    valv = 3.21f;
    hr = IDirect3DRMMeshBuilder_GetTextureCoordinates(pMeshBuilder, 0, &valu, &valv);
    ok(hr == D3DRM_OK, "Cannot get texture coordinates (hr = %x)\n", hr);
    ok(valu == 0.0f, "Wrong coordinate %f (must be 0.0)\n", valu);
    ok(valv == 0.0f, "Wrong coordinate %f (must be 0.0)\n", valv);
    valu = 1.23f;
    valv = 3.21f;
    hr = IDirect3DRMMeshBuilder_GetTextureCoordinates(pMeshBuilder, 1, &valu, &valv);
    ok(hr == D3DRM_OK, "Cannot get texture coordinates (hr = %x)\n", hr);
    ok(valu == 0.0f, "Wrong coordinate %f (must be 0.0)\n", valu);
    ok(valv == 0.0f, "Wrong coordinate %f (must be 0.0)\n", valv);
    valu = 1.23f;
    valv = 3.21f;
    hr = IDirect3DRMMeshBuilder_GetTextureCoordinates(pMeshBuilder, 2, &valu, &valv);
    ok(hr == D3DRM_OK, "Cannot get texture coordinates (hr = %x)\n", hr);
    ok(valu == 0.0f, "Wrong coordinate %f (must be 0.0)\n", valu);
    ok(valv == 0.0f, "Wrong coordinate %f (must be 0.0)\n", valv);
    valu = 1.23f;
    valv = 3.21f;
    hr = IDirect3DRMMeshBuilder_GetTextureCoordinates(pMeshBuilder, 3, &valu, &valv);
    ok(hr == D3DRM_OK, "Cannot get texture coordinates (hr = %x)\n", hr);
    ok(valu == 0.0f, "Wrong coordinate %f (must be 0.0)\n", valu);
    ok(valv == 0.0f, "Wrong coordinate %f (must be 0.0)\n", valv);
    hr = IDirect3DRMMeshBuilder_GetTextureCoordinates(pMeshBuilder, 4, &valu, &valv);
    ok(hr == D3DRMERR_BADVALUE, "Should fail and return D3DRM_BADVALUE (hr = %x)\n", hr);

    valu = 1.23f;
    valv = 3.21f;
    hr = IDirect3DRMMeshBuilder_SetTextureCoordinates(pMeshBuilder, 0, valu, valv);
    ok(hr == D3DRM_OK, "Cannot set texture coordinates (hr = %x)\n", hr);
    hr = IDirect3DRMMeshBuilder_SetTextureCoordinates(pMeshBuilder, 4, valu, valv);
    ok(hr == D3DRMERR_BADVALUE, "Should fail and return D3DRM_BADVALUE (hr = %x)\n", hr);

    valu = 0.0f;
    valv = 0.0f;
    hr = IDirect3DRMMeshBuilder_GetTextureCoordinates(pMeshBuilder, 0, &valu, &valv);
    ok(hr == D3DRM_OK, "Cannot get texture coordinates (hr = %x)\n", hr);
    ok(valu == 1.23f, "Wrong coordinate %f (must be 1.23)\n", valu);
    ok(valv == 3.21f, "Wrong coordinate %f (must be 3.21)\n", valv);

    IDirect3DRMMeshBuilder_Release(pMeshBuilder);

    hr = IDirect3DRM_CreateMeshBuilder(d3drm, &pMeshBuilder);
    ok(hr == D3DRM_OK, "Cannot get IDirect3DRMMeshBuilder interface (hr = %x)\n", hr);

    /* No group in mesh when mesh builder is not loaded */
    hr = IDirect3DRMMeshBuilder_CreateMesh(pMeshBuilder, &mesh);
    ok(hr == D3DRM_OK, "CreateMesh failed returning hr = %x\n", hr);
    if (hr == D3DRM_OK)
    {
        DWORD nb_groups;

        nb_groups = IDirect3DRMMesh_GetGroupCount(mesh);
        ok(nb_groups == 0, "GetCroupCount returned %u\n", nb_groups);

        IDirect3DRMMesh_Release(mesh);
    }

    info.lpMemory = data_full;
    info.dSize = strlen(data_full);
    hr = IDirect3DRMMeshBuilder_Load(pMeshBuilder, &info, NULL, D3DRMLOAD_FROMMEMORY, NULL, NULL);
    ok(hr == D3DRM_OK, "Cannot load mesh data (hr = %x)\n", hr);

    val = IDirect3DRMMeshBuilder_GetVertexCount(pMeshBuilder);
    ok(val == 3, "Wrong number of vertices %d (must be 3)\n", val);

    val = IDirect3DRMMeshBuilder_GetFaceCount(pMeshBuilder);
    ok(val == 1, "Wrong number of faces %d (must be 1)\n", val);

    /* Check no buffer size and too small buffer size errors */
    val1 = 1; val2 = 3; val3 = 8;
    hr = IDirect3DRMMeshBuilder_GetVertices(pMeshBuilder, &val1, v, &val2, n, &val3, f);
    ok(hr == D3DRMERR_BADVALUE, "IDirect3DRMMeshBuilder_GetVertices returned %#x\n", hr);
    hr = IDirect3DRMMeshBuilder_GetVertices(pMeshBuilder, NULL, v, &val2, n, &val3, f);
    ok(hr == D3DRMERR_BADVALUE, "IDirect3DRMMeshBuilder_GetVertices returned %#x\n", hr);
    val1 = 3; val2 = 1; val3 = 8;
    hr = IDirect3DRMMeshBuilder_GetVertices(pMeshBuilder, &val1, v, &val2, n, &val3, f);
    ok(hr == D3DRMERR_BADVALUE, "IDirect3DRMMeshBuilder_GetVertices returned %#x\n", hr);
    hr = IDirect3DRMMeshBuilder_GetVertices(pMeshBuilder, &val1, v, NULL, n, &val3, f);
    ok(hr == D3DRMERR_BADVALUE, "IDirect3DRMMeshBuilder_GetVertices returned %#x\n", hr);
    val1 = 3; val2 = 3; val3 = 1;
    hr = IDirect3DRMMeshBuilder_GetVertices(pMeshBuilder, &val1, v, &val2, n, &val3, f);
    ok(hr == D3DRMERR_BADVALUE, "IDirect3DRMMeshBuilder_GetVertices returned %#x\n", hr);
    hr = IDirect3DRMMeshBuilder_GetVertices(pMeshBuilder, &val1, v, &val2, n, NULL, f);
    ok(hr == D3DRMERR_BADVALUE, "IDirect3DRMMeshBuilder_GetVertices returned %#x\n", hr);

    val1 = 3; val2 = 3; val3 = 8;
    hr = IDirect3DRMMeshBuilder_GetVertices(pMeshBuilder, &val1, v, &val2, n, &val3, f);
    ok(hr == D3DRM_OK, "Cannot get vertices information (hr = %x)\n", hr);
    ok(val1 == 3, "Wrong number of vertices %d (must be 3)\n", val1);
    ok(val2 == 3, "Wrong number of normals %d (must be 3)\n", val2);
    ok(val3 == 8, "Wrong number of face data bytes %d (must be 8)\n", val3);
    check_vector(&v[0], 0.1f, 0.2f, 0.3f, 32);
    check_vector(&v[1], 0.4f, 0.5f, 0.6f, 32);
    check_vector(&v[2], 0.7f, 0.8f, 0.9f, 32);
    check_vector(&n[0], 1.1f, 1.2f, 1.3f, 32);
    check_vector(&n[1], 1.4f, 1.5f, 1.6f, 32);
    check_vector(&n[2], 1.7f, 1.8f, 1.9f, 32);
    ok(f[0] == 3 , "Wrong component f[0] = %d (expected 3)\n", f[0]);
    ok(f[1] == 0 , "Wrong component f[1] = %d (expected 0)\n", f[1]);
    ok(f[2] == 0 , "Wrong component f[2] = %d (expected 0)\n", f[2]);
    ok(f[3] == 1 , "Wrong component f[3] = %d (expected 1)\n", f[3]);
    ok(f[4] == 1 , "Wrong component f[4] = %d (expected 1)\n", f[4]);
    ok(f[5] == 2 , "Wrong component f[5] = %d (expected 2)\n", f[5]);
    ok(f[6] == 2 , "Wrong component f[6] = %d (expected 2)\n", f[6]);
    ok(f[7] == 0 , "Wrong component f[7] = %d (expected 0)\n", f[7]);

    hr = IDirect3DRMMeshBuilder_CreateMesh(pMeshBuilder, &mesh);
    ok(hr == D3DRM_OK, "CreateMesh failed returning hr = %x\n", hr);
    if (hr == D3DRM_OK)
    {
        DWORD nb_groups;
        unsigned nb_vertices, nb_faces, nb_face_vertices;
        DWORD data_size;
        IDirect3DRMMaterial *material = (IDirect3DRMMaterial *)0xdeadbeef;
        IDirect3DRMTexture *texture = (IDirect3DRMTexture *)0xdeadbeef;
        D3DVALUE values[3];

        nb_groups = IDirect3DRMMesh_GetGroupCount(mesh);
        ok(nb_groups == 1, "GetCroupCount returned %u\n", nb_groups);
        hr = IDirect3DRMMesh_GetGroup(mesh, 1, &nb_vertices, &nb_faces, &nb_face_vertices, &data_size, NULL);
        ok(hr == D3DRMERR_BADVALUE, "GetCroup returned hr = %x\n", hr);
        hr = IDirect3DRMMesh_GetGroup(mesh, 0, &nb_vertices, &nb_faces, &nb_face_vertices, &data_size, NULL);
        ok(hr == D3DRM_OK, "GetCroup failed returning hr = %x\n", hr);
        ok(nb_vertices == 3, "Wrong number of vertices %u (must be 3)\n", nb_vertices);
        ok(nb_faces == 1, "Wrong number of faces %u (must be 1)\n", nb_faces);
        ok(nb_face_vertices == 3, "Wrong number of vertices per face %u (must be 3)\n", nb_face_vertices);
        ok(data_size == 3, "Wrong number of face data bytes %u (must be 3)\n", data_size);
        color = IDirect3DRMMesh_GetGroupColor(mesh, 0);
        ok(color == 0xff00ff00, "Wrong color returned %#x instead of %#x\n", color, 0xff00ff00);
        hr = IDirect3DRMMesh_GetGroupTexture(mesh, 0, &texture);
        ok(hr == D3DRM_OK, "GetCroupTexture failed returning hr = %x\n", hr);
        ok(texture == NULL, "No texture should be present\n");
        hr = IDirect3DRMMesh_GetGroupMaterial(mesh, 0, &material);
        ok(hr == D3DRM_OK, "GetCroupMaterial failed returning hr = %x\n", hr);
        ok(material != NULL, "No material present\n");
        hr = IDirect3DRMMaterial_GetEmissive(material, &values[0], &values[1], &values[2]);
        ok(hr == D3DRM_OK, "Failed to get emissive color, hr %#x.\n", hr);
        ok(values[0] == 0.5f, "Got unexpected red component %.8e.\n", values[0]);
        ok(values[1] == 0.5f, "Got unexpected green component %.8e.\n", values[1]);
        ok(values[2] == 0.5f, "Got unexpected blue component %.8e.\n", values[2]);
        hr = IDirect3DRMMaterial_GetSpecular(material, &values[0], &values[1], &values[2]);
        ok(hr == D3DRM_OK, "Failed to get specular color, hr %#x.\n", hr);
        ok(values[0] == 1.0f, "Got unexpected red component %.8e.\n", values[0]);
        ok(values[1] == 0.0f, "Got unexpected green component %.8e.\n", values[1]);
        ok(values[2] == 0.0f, "Got unexpected blue component %.8e.\n", values[2]);
        values[0] = IDirect3DRMMaterial_GetPower(material);
        ok(values[0] == 30.0f, "Got unexpected power value %.8e.\n", values[0]);
        IDirect3DRMMaterial_Release(material);

        IDirect3DRMMesh_Release(mesh);
    }

    hr = IDirect3DRMMeshBuilder_Scale(pMeshBuilder, 2, 3 ,4);
    ok(hr == D3DRM_OK, "Scale failed returning hr = %x\n", hr);

    hr = IDirect3DRMMeshBuilder_GetVertices(pMeshBuilder, &val1, v, &val2, n, &val3, f);
    ok(hr == D3DRM_OK, "Cannot get vertices information (hr = %x)\n", hr);
    ok(val2 == 3, "Wrong number of normals %d (must be 3)\n", val2);
    ok(val1 == 3, "Wrong number of vertices %d (must be 3)\n", val1);

    check_vector(&v[0], 0.1f * 2, 0.2f * 3, 0.3f * 4, 32);
    check_vector(&v[1], 0.4f * 2, 0.5f * 3, 0.6f * 4, 32);
    check_vector(&v[2], 0.7f * 2, 0.8f * 3, 0.9f * 4, 32);
    /* Normals are not affected by Scale */
    check_vector(&n[0], 1.1f, 1.2f, 1.3f, 32);
    check_vector(&n[1], 1.4f, 1.5f, 1.6f, 32);
    check_vector(&n[2], 1.7f, 1.8f, 1.9f, 32);

    IDirect3DRMMeshBuilder_Release(pMeshBuilder);

    IDirect3DRM_Release(d3drm);
}