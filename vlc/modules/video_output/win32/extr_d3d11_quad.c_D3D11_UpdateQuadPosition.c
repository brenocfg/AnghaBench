#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
typedef  int /*<<< orphan*/  video_orientation_t ;
typedef  int /*<<< orphan*/  d3d_vertex_t ;
struct TYPE_10__ {int projection; int /*<<< orphan*/ * pVertexBuffer; scalar_t__ pIndexBuffer; } ;
typedef  TYPE_1__ d3d_quad_t ;
struct TYPE_11__ {int /*<<< orphan*/  d3dcontext; } ;
typedef  TYPE_2__ d3d11_device_t ;
struct TYPE_12__ {int /*<<< orphan*/ * pData; } ;
typedef  int /*<<< orphan*/  RECT ;
typedef  int /*<<< orphan*/  ID3D11Resource ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_3__ D3D11_MAPPED_SUBRESOURCE ;

/* Variables and functions */
 int /*<<< orphan*/  D3D11_MAP_WRITE_DISCARD ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ID3D11DeviceContext_Map (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  ID3D11DeviceContext_Unmap (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
#define  PROJECTION_MODE_CUBEMAP_LAYOUT_STANDARD 130 
#define  PROJECTION_MODE_EQUIRECTANGULAR 129 
#define  PROJECTION_MODE_RECTANGULAR 128 
 int /*<<< orphan*/  SetupQuadCube (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetupQuadFlat (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetupQuadSphere (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_Warn (int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

bool D3D11_UpdateQuadPosition( vlc_object_t *o, d3d11_device_t *d3d_dev, d3d_quad_t *quad,
                                const RECT *output, video_orientation_t orientation )
{
    bool result = true;
    HRESULT hr;
    D3D11_MAPPED_SUBRESOURCE mappedResource;
    d3d_vertex_t *dst_data;

    if (unlikely(quad->pVertexBuffer == NULL))
        return false;

    /* create the vertices */
    hr = ID3D11DeviceContext_Map(d3d_dev->d3dcontext, (ID3D11Resource *)quad->pVertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
    if (FAILED(hr)) {
        msg_Err(o, "Failed to lock the vertex buffer (hr=0x%lX)", hr);
        return false;
    }
    dst_data = mappedResource.pData;

    /* create the vertex indices */
    hr = ID3D11DeviceContext_Map(d3d_dev->d3dcontext, (ID3D11Resource *)quad->pIndexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
    if (FAILED(hr)) {
        msg_Err(o, "Failed to lock the index buffer (hr=0x%lX)", hr);
        ID3D11DeviceContext_Unmap(d3d_dev->d3dcontext, (ID3D11Resource *)quad->pVertexBuffer, 0);
        return false;
    }

    switch (quad->projection)
    {
    case PROJECTION_MODE_RECTANGULAR:
        SetupQuadFlat(dst_data, output, quad, mappedResource.pData, orientation);
        break;
    case PROJECTION_MODE_EQUIRECTANGULAR:
        SetupQuadSphere(dst_data, output, quad, mappedResource.pData);
        break;
    case PROJECTION_MODE_CUBEMAP_LAYOUT_STANDARD:
        SetupQuadCube(dst_data, output, quad, mappedResource.pData);
        break;
    default:
        msg_Warn(o, "Projection mode %d not handled", quad->projection);
        result = false;
    }

    ID3D11DeviceContext_Unmap(d3d_dev->d3dcontext, (ID3D11Resource *)quad->pIndexBuffer, 0);
    ID3D11DeviceContext_Unmap(d3d_dev->d3dcontext, (ID3D11Resource *)quad->pVertexBuffer, 0);

    return result;
}