#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct mesh_data {int num_poly_faces; int num_materials; int /*<<< orphan*/ * materials; void* material_indices; } ;
struct TYPE_13__ {TYPE_1__* lpVtbl; } ;
struct TYPE_12__ {int /*<<< orphan*/  (* Unlock ) (TYPE_2__*) ;int /*<<< orphan*/  (* GetType ) (TYPE_2__*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* GetChild ) (TYPE_2__*,int,TYPE_2__**) ;int /*<<< orphan*/  (* GetChildren ) (TYPE_2__*,int*) ;int /*<<< orphan*/  (* Lock ) (TYPE_2__*,int*,void const**) ;} ;
typedef  int SIZE_T ;
typedef  TYPE_2__ ID3DXFileData ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  GUID ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  D3D_OK ; 
 int /*<<< orphan*/  E_FAIL ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 void* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IUnknown_Release (TYPE_2__*) ; 
 scalar_t__ IsEqualGUID (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TID_D3DRMMaterial ; 
 int /*<<< orphan*/  WARN (char*,...) ; 
 int /*<<< orphan*/  destroy_materials (struct mesh_data*) ; 
 int /*<<< orphan*/  memcpy (void*,int const*,int) ; 
 int /*<<< orphan*/  parse_material (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int*,void const**) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*,int*) ; 
 int /*<<< orphan*/  stub3 (TYPE_2__*,int,TYPE_2__**) ; 
 int /*<<< orphan*/  stub4 (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub5 (TYPE_2__*) ; 

__attribute__((used)) static HRESULT parse_material_list(ID3DXFileData *filedata, struct mesh_data *mesh)
{
    HRESULT hr;
    SIZE_T data_size;
    const DWORD *data, *in_ptr;
    GUID type;
    ID3DXFileData *child = NULL;
    DWORD num_materials;
    DWORD i;
    SIZE_T nb_children;

    destroy_materials(mesh);

    hr = filedata->lpVtbl->Lock(filedata, &data_size, (const void**)&data);
    if (FAILED(hr)) return hr;

    /* template MeshMaterialList {
     *     DWORD nMaterials;
     *     DWORD nFaceIndexes;
     *     array DWORD faceIndexes[nFaceIndexes];
     *     [ Material ]
     * }
     */

    in_ptr = data;
    hr = E_FAIL;

    if (data_size < sizeof(DWORD)) {
        WARN("truncated data (%ld bytes)\n", data_size);
        goto end;
    }
    num_materials = *in_ptr++;
    if (!num_materials) {
        hr = D3D_OK;
        goto end;
    }

    if (data_size < 2 * sizeof(DWORD)) {
        WARN("truncated data (%ld bytes)\n", data_size);
        goto end;
    }
    if (*in_ptr++ != mesh->num_poly_faces) {
        WARN("number of material face indices (%u) doesn't match number of faces (%u)\n",
             *(in_ptr - 1), mesh->num_poly_faces);
        goto end;
    }
    if (data_size < 2 * sizeof(DWORD) + mesh->num_poly_faces * sizeof(DWORD)) {
        WARN("truncated data (%ld bytes)\n", data_size);
        goto end;
    }
    for (i = 0; i < mesh->num_poly_faces; i++) {
        if (*in_ptr++ >= num_materials) {
            WARN("face %u: reference to undefined material %u (only %u materials)\n",
                 i, *(in_ptr - 1), num_materials);
            goto end;
        }
    }

    mesh->materials = HeapAlloc(GetProcessHeap(), 0, num_materials * sizeof(*mesh->materials));
    mesh->material_indices = HeapAlloc(GetProcessHeap(), 0, mesh->num_poly_faces * sizeof(*mesh->material_indices));
    if (!mesh->materials || !mesh->material_indices) {
        hr = E_OUTOFMEMORY;
        goto end;
    }
    memcpy(mesh->material_indices, data + 2, mesh->num_poly_faces * sizeof(DWORD));

    hr = filedata->lpVtbl->GetChildren(filedata, &nb_children);
    if (FAILED(hr))
        goto end;

    for (i = 0; i < nb_children; i++)
    {
        hr = filedata->lpVtbl->GetChild(filedata, i, &child);
        if (FAILED(hr))
            goto end;
        hr = child->lpVtbl->GetType(child, &type);
        if (FAILED(hr))
            goto end;

        if (IsEqualGUID(&type, &TID_D3DRMMaterial)) {
            if (mesh->num_materials >= num_materials) {
                WARN("more materials defined than declared\n");
                hr = E_FAIL;
                goto end;
            }
            hr = parse_material(child, &mesh->materials[mesh->num_materials++]);
            if (FAILED(hr))
                goto end;
        }

        IUnknown_Release(child);
        child = NULL;
    }
    if (num_materials != mesh->num_materials) {
        WARN("only %u of %u materials defined\n", num_materials, mesh->num_materials);
        hr = E_FAIL;
    }

end:
    if (child)
        IUnknown_Release(child);
    filedata->lpVtbl->Unlock(filedata);
    return hr;
}