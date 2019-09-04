#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct mesh_data {int num_vertices; int num_poly_faces; int num_tri_faces; int* num_tri_per_face; int* indices; int nb_bones; scalar_t__ skin_info; void* vertices; int /*<<< orphan*/  fvf; } ;
struct TYPE_17__ {TYPE_1__* lpVtbl; } ;
struct TYPE_16__ {int /*<<< orphan*/  (* Unlock ) (TYPE_2__*) ;int /*<<< orphan*/  (* GetType ) (TYPE_2__*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* GetChild ) (TYPE_2__*,int,TYPE_2__**) ;int /*<<< orphan*/  (* GetChildren ) (TYPE_2__*,int*) ;int /*<<< orphan*/  (* Lock ) (TYPE_2__*,int*,void const**) ;} ;
typedef  int SIZE_T ;
typedef  TYPE_2__ ID3DXFileData ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  GUID ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  D3DXVECTOR3 ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  D3DFVF_XYZ ; 
 int /*<<< orphan*/  D3D_OK ; 
 int /*<<< orphan*/  DXFILEOBJ_SkinWeights ; 
 int /*<<< orphan*/  DXFILEOBJ_XSkinMeshHeader ; 
 int /*<<< orphan*/  E_FAIL ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 void* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IUnknown_Release (TYPE_2__*) ; 
 scalar_t__ IsEqualGUID (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int PROVIDE_MATERIALS ; 
 int PROVIDE_SKININFO ; 
 int /*<<< orphan*/  TID_D3DRMMeshMaterialList ; 
 int /*<<< orphan*/  TID_D3DRMMeshNormals ; 
 int /*<<< orphan*/  TID_D3DRMMeshTextureCoords ; 
 int /*<<< orphan*/  TID_D3DRMMeshVertexColors ; 
 int /*<<< orphan*/  WARN (char*,...) ; 
 int /*<<< orphan*/  create_dummy_skin (scalar_t__*) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  parse_material_list (TYPE_2__*,struct mesh_data*) ; 
 int /*<<< orphan*/  parse_normals (TYPE_2__*,struct mesh_data*) ; 
 int /*<<< orphan*/  parse_skin_mesh_info (TYPE_2__*,struct mesh_data*,int) ; 
 int /*<<< orphan*/  parse_texture_coords (TYPE_2__*,struct mesh_data*) ; 
 int /*<<< orphan*/  parse_vertex_colors (TYPE_2__*,struct mesh_data*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int*,void const**) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*,int*) ; 
 int /*<<< orphan*/  stub3 (TYPE_2__*,int,TYPE_2__**) ; 
 int /*<<< orphan*/  stub4 (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub5 (TYPE_2__*) ; 

__attribute__((used)) static HRESULT parse_mesh(ID3DXFileData *filedata, struct mesh_data *mesh_data, DWORD provide_flags)
{
    HRESULT hr;
    SIZE_T data_size;
    const BYTE *data, *in_ptr;
    DWORD *index_out_ptr;
    GUID type;
    ID3DXFileData *child = NULL;
    DWORD i;
    SIZE_T nb_children;
    DWORD nb_skin_weights_info = 0;

    /*
     * template Mesh {
     *     DWORD nVertices;
     *     array Vector vertices[nVertices];
     *     DWORD nFaces;
     *     array MeshFace faces[nFaces];
     *     [ ... ]
     * }
     */

    hr = filedata->lpVtbl->Lock(filedata, &data_size, (const void**)&data);
    if (FAILED(hr)) return hr;

    in_ptr = data;
    hr = E_FAIL;

    if (data_size < sizeof(DWORD) * 2) {
        WARN("truncated data (%ld bytes)\n", data_size);
        goto end;
    }
    mesh_data->num_vertices = *(DWORD*)in_ptr;
    if (data_size < sizeof(DWORD) * 2 + mesh_data->num_vertices * sizeof(D3DXVECTOR3)) {
        WARN("truncated data (%ld bytes)\n", data_size);
        goto end;
    }
    in_ptr += sizeof(DWORD) + mesh_data->num_vertices * sizeof(D3DXVECTOR3);

    mesh_data->num_poly_faces = *(DWORD*)in_ptr;
    in_ptr += sizeof(DWORD);

    mesh_data->num_tri_faces = 0;
    for (i = 0; i < mesh_data->num_poly_faces; i++)
    {
        DWORD num_poly_vertices;
        DWORD j;

        if (data_size - (in_ptr - data) < sizeof(DWORD)) {
            WARN("truncated data (%ld bytes)\n", data_size);
            goto end;
        }
        num_poly_vertices = *(DWORD*)in_ptr;
        in_ptr += sizeof(DWORD);
        if (data_size - (in_ptr - data) < num_poly_vertices * sizeof(DWORD)) {
            WARN("truncated data (%ld bytes)\n", data_size);
            goto end;
        }
        if (num_poly_vertices < 3) {
            WARN("face %u has only %u vertices\n", i, num_poly_vertices);
            goto end;
        }
        for (j = 0; j < num_poly_vertices; j++) {
            if (*(DWORD*)in_ptr >= mesh_data->num_vertices) {
                WARN("face %u, index %u: undefined vertex %u (only %u vertices)\n",
                     i, j, *(DWORD*)in_ptr, mesh_data->num_vertices);
                goto end;
            }
            in_ptr += sizeof(DWORD);
        }
        mesh_data->num_tri_faces += num_poly_vertices - 2;
    }

    mesh_data->fvf = D3DFVF_XYZ;

    mesh_data->vertices = HeapAlloc(GetProcessHeap(), 0,
            mesh_data->num_vertices * sizeof(*mesh_data->vertices));
    mesh_data->num_tri_per_face = HeapAlloc(GetProcessHeap(), 0,
            mesh_data->num_poly_faces * sizeof(*mesh_data->num_tri_per_face));
    mesh_data->indices = HeapAlloc(GetProcessHeap(), 0,
            (mesh_data->num_tri_faces + mesh_data->num_poly_faces * 2) * sizeof(*mesh_data->indices));
    if (!mesh_data->vertices || !mesh_data->num_tri_per_face || !mesh_data->indices) {
        hr = E_OUTOFMEMORY;
        goto end;
    }

    in_ptr = data + sizeof(DWORD);
    memcpy(mesh_data->vertices, in_ptr, mesh_data->num_vertices * sizeof(D3DXVECTOR3));
    in_ptr += mesh_data->num_vertices * sizeof(D3DXVECTOR3) + sizeof(DWORD);

    index_out_ptr = mesh_data->indices;
    for (i = 0; i < mesh_data->num_poly_faces; i++)
    {
        DWORD count;

        count = *(DWORD*)in_ptr;
        in_ptr += sizeof(DWORD);
        mesh_data->num_tri_per_face[i] = count - 2;

        while (count--) {
            *index_out_ptr++ = *(DWORD*)in_ptr;
            in_ptr += sizeof(DWORD);
        }
    }

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

        if (IsEqualGUID(&type, &TID_D3DRMMeshNormals)) {
            hr = parse_normals(child, mesh_data);
        } else if (IsEqualGUID(&type, &TID_D3DRMMeshVertexColors)) {
            hr = parse_vertex_colors(child, mesh_data);
        } else if (IsEqualGUID(&type, &TID_D3DRMMeshTextureCoords)) {
            hr = parse_texture_coords(child, mesh_data);
        } else if (IsEqualGUID(&type, &TID_D3DRMMeshMaterialList) &&
                   (provide_flags & PROVIDE_MATERIALS))
        {
            hr = parse_material_list(child, mesh_data);
        } else if (provide_flags & PROVIDE_SKININFO) {
            if (IsEqualGUID(&type, &DXFILEOBJ_XSkinMeshHeader)) {
                if (mesh_data->skin_info) {
                    WARN("Skin mesh header already encountered\n");
                    hr = E_FAIL;
                    goto end;
                }
                hr = parse_skin_mesh_info(child, mesh_data, 0);
                if (FAILED(hr))
                    goto end;
            } else if (IsEqualGUID(&type, &DXFILEOBJ_SkinWeights)) {
                if (!mesh_data->skin_info) {
                    WARN("Skin weights found but skin mesh header not encountered yet\n");
                    hr = E_FAIL;
                    goto end;
                }
                hr = parse_skin_mesh_info(child, mesh_data, nb_skin_weights_info);
                if (FAILED(hr))
                    goto end;
                nb_skin_weights_info++;
            }
        }
        if (FAILED(hr))
            goto end;

        IUnknown_Release(child);
        child = NULL;
    }

    if (mesh_data->skin_info && (nb_skin_weights_info != mesh_data->nb_bones)) {
        WARN("Mismatch between nb skin weights info %u encountered and nb bones %u from skin mesh header\n",
             nb_skin_weights_info, mesh_data->nb_bones);
        hr = E_FAIL;
        goto end;
    }

    if ((provide_flags & PROVIDE_SKININFO) && !mesh_data->skin_info)
    {
        hr = create_dummy_skin(&mesh_data->skin_info);
        if (FAILED(hr))
            goto end;
    }

    hr = D3D_OK;

end:
    if (child)
        IUnknown_Release(child);
    filedata->lpVtbl->Unlock(filedata);
    return hr;
}