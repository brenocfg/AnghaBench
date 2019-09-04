#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ddraw {int d3dversion; int /*<<< orphan*/  IDirectDraw7_iface; } ;
struct TYPE_4__ {int /*<<< orphan*/ * lpVtbl; } ;
struct d3d_vertex_buffer {int ref; int version; int Caps; int fvf; int size; int /*<<< orphan*/  wined3d_declaration; int /*<<< orphan*/  wined3d_buffer; struct ddraw* ddraw; TYPE_1__ IDirect3DVertexBuffer7_iface; } ;
struct TYPE_5__ {int dwSize; int dwCaps; int dwFVF; int dwNumVertices; } ;
typedef  scalar_t__ HRESULT ;
typedef  TYPE_2__ D3DVERTEXBUFFERDESC ;

/* Variables and functions */
 scalar_t__ D3D_OK ; 
 scalar_t__ DDERR_INVALIDPARAMS ; 
 scalar_t__ DDERR_OUTOFMEMORY ; 
 int /*<<< orphan*/  ERR (char*,int) ; 
 scalar_t__ FAILED (scalar_t__) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IDirectDraw7_AddRef (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 int /*<<< orphan*/  WARN (char*,scalar_t__) ; 
 scalar_t__ WINED3DERR_INVALIDCALL ; 
 int /*<<< orphan*/  d3d_vertex_buffer7_vtbl ; 
 scalar_t__ d3d_vertex_buffer_create_wined3d_buffer (struct d3d_vertex_buffer*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ddraw_find_decl (struct ddraw*,int) ; 
 int get_flexible_vertex_size (int) ; 
 struct d3d_vertex_buffer* heap_alloc_zero (int) ; 
 int /*<<< orphan*/  heap_free (struct d3d_vertex_buffer*) ; 
 int /*<<< orphan*/  wined3d_buffer_decref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wined3d_mutex_lock () ; 
 int /*<<< orphan*/  wined3d_mutex_unlock () ; 
 int /*<<< orphan*/  wined3d_vertex_declaration_incref (int /*<<< orphan*/ ) ; 

HRESULT d3d_vertex_buffer_create(struct d3d_vertex_buffer **vertex_buf,
        struct ddraw *ddraw, D3DVERTEXBUFFERDESC *desc)
{
    struct d3d_vertex_buffer *buffer;
    HRESULT hr = D3D_OK;

    TRACE("Vertex buffer description:\n");
    TRACE("    dwSize %u\n", desc->dwSize);
    TRACE("    dwCaps %#x\n", desc->dwCaps);
    TRACE("    FVF %#x\n", desc->dwFVF);
    TRACE("    dwNumVertices %u\n", desc->dwNumVertices);

    if (!(buffer = heap_alloc_zero(sizeof(*buffer))))
        return DDERR_OUTOFMEMORY;

    buffer->IDirect3DVertexBuffer7_iface.lpVtbl = &d3d_vertex_buffer7_vtbl;
    buffer->ref = 1;
    buffer->version = ddraw->d3dversion;
    if (buffer->version == 7)
        IDirectDraw7_AddRef(&ddraw->IDirectDraw7_iface);
    buffer->ddraw = ddraw;
    buffer->Caps = desc->dwCaps;
    buffer->fvf = desc->dwFVF;
    buffer->size = get_flexible_vertex_size(desc->dwFVF) * desc->dwNumVertices;

    wined3d_mutex_lock();

    if (FAILED(hr = d3d_vertex_buffer_create_wined3d_buffer(buffer, FALSE, &buffer->wined3d_buffer)))
    {
        WARN("Failed to create wined3d vertex buffer, hr %#x.\n", hr);
        if (hr == WINED3DERR_INVALIDCALL)
            hr = DDERR_INVALIDPARAMS;
        goto end;
    }

    if (!(buffer->wined3d_declaration = ddraw_find_decl(ddraw, desc->dwFVF)))
    {
        ERR("Failed to find vertex declaration for fvf %#x.\n", desc->dwFVF);
        wined3d_buffer_decref(buffer->wined3d_buffer);
        hr = DDERR_INVALIDPARAMS;
        goto end;
    }
    wined3d_vertex_declaration_incref(buffer->wined3d_declaration);

end:
    wined3d_mutex_unlock();
    if (hr == D3D_OK)
        *vertex_buf = buffer;
    else
        heap_free(buffer);

    return hr;
}