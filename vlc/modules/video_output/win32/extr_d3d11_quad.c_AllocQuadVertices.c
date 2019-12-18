#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
typedef  int video_projection_mode_t ;
typedef  int /*<<< orphan*/  d3d_vertex_t ;
struct TYPE_8__ {int vertexCount; int indexCount; int vertexStride; int /*<<< orphan*/ * pIndexBuffer; int /*<<< orphan*/ * pVertexBuffer; } ;
typedef  TYPE_1__ d3d_quad_t ;
struct TYPE_9__ {int /*<<< orphan*/  d3ddevice; } ;
typedef  TYPE_2__ d3d11_device_t ;
typedef  int /*<<< orphan*/  bd ;
typedef  int /*<<< orphan*/  WORD ;
struct TYPE_10__ {int ByteWidth; int /*<<< orphan*/  CPUAccessFlags; int /*<<< orphan*/  BindFlags; int /*<<< orphan*/  Usage; } ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_3__ D3D11_BUFFER_DESC ;

/* Variables and functions */
 int /*<<< orphan*/  D3D11_BIND_INDEX_BUFFER ; 
 int /*<<< orphan*/  D3D11_BIND_VERTEX_BUFFER ; 
 int /*<<< orphan*/  D3D11_CPU_ACCESS_WRITE ; 
 int /*<<< orphan*/  D3D11_USAGE_DYNAMIC ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ID3D11Buffer_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ID3D11Device_CreateBuffer (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
#define  PROJECTION_MODE_CUBEMAP_LAYOUT_STANDARD 130 
#define  PROJECTION_MODE_EQUIRECTANGULAR 129 
#define  PROJECTION_MODE_RECTANGULAR 128 
 int /*<<< orphan*/  SPHERE_SLICES ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_Warn (int /*<<< orphan*/ *,char*,int) ; 
 int nbLatBands ; 
 int nbLonBands ; 

__attribute__((used)) static bool AllocQuadVertices(vlc_object_t *o, d3d11_device_t *d3d_dev, d3d_quad_t *quad, video_projection_mode_t projection)
{
    HRESULT hr;

    switch (projection)
    {
    case PROJECTION_MODE_RECTANGULAR:
        quad->vertexCount = 4;
        quad->indexCount = 2 * 3;
        break;
    case PROJECTION_MODE_EQUIRECTANGULAR:
        quad->vertexCount = (SPHERE_SLICES + 1) * (SPHERE_SLICES + 1);
        quad->indexCount = nbLatBands * nbLonBands * 2 * 3;
        break;
    case PROJECTION_MODE_CUBEMAP_LAYOUT_STANDARD:
        quad->vertexCount = 4 * 6;
        quad->indexCount = 6 * 2 * 3;
        break;
    default:
        msg_Warn(o, "Projection mode %d not handled", projection);
        return false;
    }

    quad->vertexStride = sizeof(d3d_vertex_t);

    D3D11_BUFFER_DESC bd;
    memset(&bd, 0, sizeof(bd));
    bd.Usage = D3D11_USAGE_DYNAMIC;
    bd.ByteWidth = quad->vertexStride * quad->vertexCount;
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

    hr = ID3D11Device_CreateBuffer(d3d_dev->d3ddevice, &bd, NULL, &quad->pVertexBuffer);
    if(FAILED(hr)) {
        msg_Err(o, "Failed to create vertex buffer. (hr=%lX)", hr);
        goto fail;
    }

    /* create the index of the vertices */
    D3D11_BUFFER_DESC quadDesc = {
        .Usage = D3D11_USAGE_DYNAMIC,
        .ByteWidth = sizeof(WORD) * quad->indexCount,
        .BindFlags = D3D11_BIND_INDEX_BUFFER,
        .CPUAccessFlags = D3D11_CPU_ACCESS_WRITE,
    };

    hr = ID3D11Device_CreateBuffer(d3d_dev->d3ddevice, &quadDesc, NULL, &quad->pIndexBuffer);
    if(FAILED(hr)) {
        msg_Err(o, "Could not create the quad indices. (hr=0x%lX)", hr);
        goto fail;
    }

    return true;
fail:
    if (quad->pVertexBuffer)
    {
        ID3D11Buffer_Release(quad->pVertexBuffer);
        quad->pVertexBuffer = NULL;
    }
    if (quad->pVertexBuffer)
    {
        ID3D11Buffer_Release(quad->pIndexBuffer);
        quad->pIndexBuffer = NULL;
    }
    return false;
}