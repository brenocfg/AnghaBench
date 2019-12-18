#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_9__ ;
typedef  struct TYPE_26__   TYPE_8__ ;
typedef  struct TYPE_25__   TYPE_7__ ;
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;
typedef  struct TYPE_18__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_23__ {unsigned int plane_count; int pixel_size; TYPE_4__* p; } ;
typedef  TYPE_5__ vlc_chroma_description_t ;
struct TYPE_24__ {int i_height; int i_width; int i_visible_height; int i_visible_width; int /*<<< orphan*/  i_chroma; } ;
typedef  TYPE_6__ video_format_t ;
typedef  int /*<<< orphan*/  texDesc ;
struct TYPE_25__ {int i_lines; int i_visible_lines; int i_pitch; int i_visible_pitch; int i_pixel_pitch; } ;
typedef  TYPE_7__ plane_t ;
struct TYPE_26__ {scalar_t__ formatTexture; scalar_t__* resourceFormat; } ;
typedef  TYPE_8__ d3d_format_t ;
struct TYPE_27__ {int /*<<< orphan*/  d3ddevice; } ;
typedef  TYPE_9__ d3d11_device_t ;
struct TYPE_21__ {int num; int den; } ;
struct TYPE_20__ {int num; int den; } ;
struct TYPE_22__ {TYPE_3__ w; TYPE_2__ h; } ;
struct TYPE_19__ {int Count; } ;
struct TYPE_18__ {int MipLevels; unsigned int ArraySize; scalar_t__ Format; int Height; int Width; scalar_t__ CPUAccessFlags; int /*<<< orphan*/  Usage; int /*<<< orphan*/  BindFlags; scalar_t__ MiscFlags; TYPE_1__ SampleDesc; } ;
typedef  int /*<<< orphan*/  ID3D11Texture2D ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_10__ D3D11_TEXTURE2D_DESC ;

/* Variables and functions */
 int /*<<< orphan*/  D3D11_BIND_DECODER ; 
 int /*<<< orphan*/  D3D11_BIND_SHADER_RESOURCE ; 
 scalar_t__ D3D11_CPU_ACCESS_WRITE ; 
 unsigned int D3D11_MAX_SHADER_VIEW ; 
 int /*<<< orphan*/  D3D11_USAGE_DEFAULT ; 
 int /*<<< orphan*/  D3D11_USAGE_DYNAMIC ; 
 scalar_t__ DXGI_FORMAT_UNKNOWN ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ID3D11Device_CreateTexture2D (int /*<<< orphan*/ ,TYPE_10__*,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ID3D11Texture2D_AddRef (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ID3D11Texture2D_Release (int /*<<< orphan*/ *) ; 
 int PICTURE_PLANE_MAX ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  ZeroMemory (TYPE_10__*,int) ; 
 unsigned int __MAX (int,unsigned int) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ is_d3d11_opaque (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ *,char*,unsigned int,int /*<<< orphan*/ ) ; 
 TYPE_5__* vlc_fourcc_GetChromaDescription (int /*<<< orphan*/ ) ; 

int AllocateTextures( vlc_object_t *obj, d3d11_device_t *d3d_dev,
                      const d3d_format_t *cfg, const video_format_t *fmt,
                      unsigned pool_size, ID3D11Texture2D *textures[],
                      plane_t out_planes[] )
{
    plane_t planes[PICTURE_PLANE_MAX];
    unsigned plane, plane_count;
    HRESULT hr;
    ID3D11Texture2D *slicedTexture = NULL;
    D3D11_TEXTURE2D_DESC texDesc;
    ZeroMemory(&texDesc, sizeof(texDesc));
    texDesc.MipLevels = 1;
    texDesc.SampleDesc.Count = 1;
    texDesc.MiscFlags = 0; //D3D11_RESOURCE_MISC_SHARED;
    texDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
    if (is_d3d11_opaque(fmt->i_chroma)) {
        texDesc.BindFlags |= D3D11_BIND_DECODER;
        texDesc.Usage = D3D11_USAGE_DEFAULT;
        texDesc.CPUAccessFlags = 0;
    } else {
        texDesc.Usage = D3D11_USAGE_DYNAMIC;
        texDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    }
    texDesc.ArraySize = pool_size;

    const vlc_chroma_description_t *p_chroma_desc = vlc_fourcc_GetChromaDescription( fmt->i_chroma );
    if( !p_chroma_desc )
        return VLC_EGENERIC;

    if (cfg->formatTexture == DXGI_FORMAT_UNKNOWN) {
        if (p_chroma_desc->plane_count == 0)
        {
            msg_Dbg(obj, "failed to get the pixel format planes for %4.4s", (char *)&fmt->i_chroma);
            return VLC_EGENERIC;
        }
        assert(p_chroma_desc->plane_count <= D3D11_MAX_SHADER_VIEW);
        plane_count = p_chroma_desc->plane_count;

        texDesc.Format = cfg->resourceFormat[0];
        assert(cfg->resourceFormat[1] == cfg->resourceFormat[0]);
        assert(cfg->resourceFormat[2] == cfg->resourceFormat[0]);

    } else {
        plane_count = __MAX(1, p_chroma_desc->plane_count);
        texDesc.Format = cfg->formatTexture;
        texDesc.Height = fmt->i_height;
        texDesc.Width = fmt->i_width;

        hr = ID3D11Device_CreateTexture2D( d3d_dev->d3ddevice, &texDesc, NULL, &slicedTexture );
        if (FAILED(hr)) {
            msg_Err(obj, "CreateTexture2D failed for the %d pool. (hr=0x%lX)", pool_size, hr);
            goto error;
        }
    }
    for( unsigned i = 0; i < p_chroma_desc->plane_count; i++ )
    {
        plane_t *p = &planes[i];

        p->i_lines         = fmt->i_height * p_chroma_desc->p[i].h.num / p_chroma_desc->p[i].h.den;
        p->i_visible_lines = fmt->i_visible_height * p_chroma_desc->p[i].h.num / p_chroma_desc->p[i].h.den;
        p->i_pitch         = fmt->i_width * p_chroma_desc->p[i].w.num / p_chroma_desc->p[i].w.den * p_chroma_desc->pixel_size;
        p->i_visible_pitch = fmt->i_visible_width * p_chroma_desc->p[i].w.num / p_chroma_desc->p[i].w.den * p_chroma_desc->pixel_size;
        p->i_pixel_pitch   = p_chroma_desc->pixel_size;
    }

    for (unsigned picture_count = 0; picture_count < pool_size; picture_count++) {
        for (plane = 0; plane < plane_count; plane++)
        {
            if (slicedTexture) {
                textures[picture_count * D3D11_MAX_SHADER_VIEW + plane] = slicedTexture;
                ID3D11Texture2D_AddRef(slicedTexture);
            } else {
                texDesc.Height = planes[plane].i_lines;
                texDesc.Width  = planes[plane].i_pitch;
                hr = ID3D11Device_CreateTexture2D( d3d_dev->d3ddevice, &texDesc, NULL, &textures[picture_count * D3D11_MAX_SHADER_VIEW + plane] );
                if (FAILED(hr)) {
                    msg_Err(obj, "CreateTexture2D failed for the %d pool. (hr=0x%lX)", pool_size, hr);
                    goto error;
                }
            }
        }
        if (out_planes)
            for (plane = 0; plane < p_chroma_desc->plane_count; plane++)
            {
                out_planes[plane] = planes[plane];
            }
        for (; plane < D3D11_MAX_SHADER_VIEW; plane++) {
            if (!cfg->resourceFormat[plane])
                textures[picture_count * D3D11_MAX_SHADER_VIEW + plane] = NULL;
            else
            {
                textures[picture_count * D3D11_MAX_SHADER_VIEW + plane] = textures[picture_count * D3D11_MAX_SHADER_VIEW];
                ID3D11Texture2D_AddRef(textures[picture_count * D3D11_MAX_SHADER_VIEW + plane]);
            }
        }
    }

    if (slicedTexture)
        ID3D11Texture2D_Release(slicedTexture);
    return VLC_SUCCESS;
error:
    if (slicedTexture)
        ID3D11Texture2D_Release(slicedTexture);
    return VLC_EGENERIC;
}