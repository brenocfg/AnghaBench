#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_58__   TYPE_9__ ;
typedef  struct TYPE_57__   TYPE_8__ ;
typedef  struct TYPE_56__   TYPE_7__ ;
typedef  struct TYPE_55__   TYPE_6__ ;
typedef  struct TYPE_54__   TYPE_5__ ;
typedef  struct TYPE_53__   TYPE_4__ ;
typedef  struct TYPE_52__   TYPE_3__ ;
typedef  struct TYPE_51__   TYPE_37__ ;
typedef  struct TYPE_50__   TYPE_2__ ;
typedef  struct TYPE_49__   TYPE_27__ ;
typedef  struct TYPE_48__   TYPE_1__ ;
typedef  struct TYPE_47__   TYPE_18__ ;
typedef  struct TYPE_46__   TYPE_16__ ;
typedef  struct TYPE_45__   TYPE_15__ ;
typedef  struct TYPE_44__   TYPE_14__ ;
typedef  struct TYPE_43__   TYPE_13__ ;
typedef  struct TYPE_42__   TYPE_12__ ;
typedef  struct TYPE_41__   TYPE_11__ ;
typedef  struct TYPE_40__   TYPE_10__ ;

/* Type definitions */
struct TYPE_53__ {scalar_t__ projection_mode; } ;
struct TYPE_57__ {TYPE_4__ source; TYPE_9__* sys; } ;
typedef  TYPE_8__ vout_display_t ;
struct TYPE_47__ {int /*<<< orphan*/  d3dcontext; } ;
struct TYPE_54__ {int /*<<< orphan*/ ** renderSrc; } ;
struct TYPE_42__ {scalar_t__ i_height; scalar_t__ i_width; TYPE_6__* textureFormat; TYPE_5__ picSys; } ;
struct TYPE_56__ {int /*<<< orphan*/ ** renderSrc; int /*<<< orphan*/ * resource; int /*<<< orphan*/ * texture; } ;
struct TYPE_52__ {scalar_t__ luminance_peak; } ;
struct TYPE_48__ {scalar_t__ i_width; scalar_t__ i_height; } ;
struct TYPE_51__ {TYPE_1__ texture_source; } ;
struct TYPE_58__ {int d3dregion_count; TYPE_18__ d3d_dev; TYPE_12__ picQuad; scalar_t__ prepareWait; int /*<<< orphan*/  flatVShader; TYPE_10__** d3dregions; int /*<<< orphan*/  projectionVShader; TYPE_7__ stagingSys; scalar_t__ legacy_shader; TYPE_3__ display; int /*<<< orphan*/  sys; TYPE_37__ area; TYPE_16__* stagingPlanes; } ;
typedef  TYPE_9__ vout_display_sys_t ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  subpicture_t ;
struct TYPE_50__ {scalar_t__ max_luminance; } ;
struct TYPE_49__ {int /*<<< orphan*/  i_chroma; TYPE_2__ mastering; } ;
struct TYPE_40__ {int i_planes; TYPE_27__ format; scalar_t__ p_sys; int /*<<< orphan*/ * p; } ;
typedef  TYPE_10__ picture_t ;
struct TYPE_41__ {int /*<<< orphan*/ ** renderSrc; int /*<<< orphan*/ * texture; int /*<<< orphan*/  slice_index; int /*<<< orphan*/ * resource; } ;
typedef  TYPE_11__ picture_sys_d3d11_t ;
typedef  TYPE_12__ d3d_quad_t ;
struct TYPE_55__ {scalar_t__ formatTexture; } ;
struct TYPE_46__ {int i_pitch; int i_lines; int /*<<< orphan*/ * p_pixels; } ;
struct TYPE_45__ {int back; int /*<<< orphan*/  right; int /*<<< orphan*/  left; int /*<<< orphan*/  bottom; int /*<<< orphan*/  top; } ;
struct TYPE_44__ {int RowPitch; int /*<<< orphan*/ * pData; } ;
struct TYPE_43__ {scalar_t__ Height; scalar_t__ Width; int BindFlags; } ;
typedef  int /*<<< orphan*/  ID3D11ShaderResourceView ;
typedef  int /*<<< orphan*/  ID3D11Asynchronous ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_13__ D3D11_TEXTURE2D_DESC ;
typedef  TYPE_14__ D3D11_MAPPED_SUBRESOURCE ;
typedef  TYPE_15__ D3D11_BOX ;

/* Variables and functions */
 TYPE_11__* ActiveD3D11PictureSys (TYPE_10__*) ; 
 int /*<<< orphan*/  CommonPlacePicture (int /*<<< orphan*/ ,TYPE_37__*,int /*<<< orphan*/ *) ; 
 int D3D11_BIND_SHADER_RESOURCE ; 
 int /*<<< orphan*/  D3D11_MAP_WRITE_DISCARD ; 
 int /*<<< orphan*/  D3D11_RenderQuad (TYPE_18__*,TYPE_12__*,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ ,TYPE_9__*) ; 
 int /*<<< orphan*/  D3D11_UpdateQuadLuminanceScale (TYPE_8__*,TYPE_18__*,TYPE_12__*,float) ; 
 scalar_t__ DXGI_FORMAT_UNKNOWN ; 
 int /*<<< orphan*/  Direct3D11DeleteRegions (int,TYPE_10__**) ; 
 int /*<<< orphan*/  Direct3D11MapSubpicture (TYPE_8__*,int*,TYPE_10__***,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FAILED (int /*<<< orphan*/ ) ; 
 float GetFormatLuminance (int /*<<< orphan*/ ,TYPE_27__*) ; 
 int /*<<< orphan*/  ID3D11DeviceContext_CopySubresourceRegion (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_15__*) ; 
 int /*<<< orphan*/  ID3D11DeviceContext_End (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ ID3D11DeviceContext_GetData (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ID3D11DeviceContext_Map (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_14__*) ; 
 int /*<<< orphan*/  ID3D11DeviceContext_Unmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ID3D11Texture2D_GetDesc (int /*<<< orphan*/ ,TYPE_13__*) ; 
 size_t KNOWN_DXGI_INDEX ; 
 scalar_t__ PROJECTION_MODE_RECTANGULAR ; 
 scalar_t__ S_FALSE ; 
 int /*<<< orphan*/  SelectRenderPlane ; 
 int /*<<< orphan*/  SleepEx (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  UpdateSize (TYPE_8__*) ; 
 int /*<<< orphan*/  VLC_OBJECT (TYPE_8__*) ; 
 int /*<<< orphan*/  __MIN (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  d3d11_device_lock (TYPE_18__*) ; 
 int /*<<< orphan*/  d3d11_device_unlock (TYPE_18__*) ; 
 scalar_t__ is_d3d11_opaque (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_Err (TYPE_8__*,char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  plane_CopyPixels (TYPE_16__*,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void PreparePicture(vout_display_t *vd, picture_t *picture, subpicture_t *subpicture)
{
    vout_display_sys_t *sys = vd->sys;

    if (sys->picQuad.textureFormat->formatTexture == DXGI_FORMAT_UNKNOWN)
    {
        D3D11_MAPPED_SUBRESOURCE mappedResource;
        int i;
        HRESULT hr;

        bool b_mapped = true;
        for (i = 0; i < picture->i_planes; i++) {
            hr = ID3D11DeviceContext_Map(sys->d3d_dev.d3dcontext, sys->stagingSys.resource[i],
                                         0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
            if( unlikely(FAILED(hr)) )
            {
                while (i-- > 0)
                    ID3D11DeviceContext_Unmap(sys->d3d_dev.d3dcontext, sys->stagingSys.resource[i], 0);
                b_mapped = false;
                break;
            }
            sys->stagingPlanes[i].i_pitch = mappedResource.RowPitch;
            sys->stagingPlanes[i].p_pixels = mappedResource.pData;
        }

        if (b_mapped)
        {
            for (i = 0; i < picture->i_planes; i++)
                plane_CopyPixels(&sys->stagingPlanes[i], &picture->p[i]);

            for (i = 0; i < picture->i_planes; i++)
                ID3D11DeviceContext_Unmap(sys->d3d_dev.d3dcontext, sys->stagingSys.resource[i], 0);
        }
    }
    else if (!is_d3d11_opaque(picture->format.i_chroma))
    {
        D3D11_MAPPED_SUBRESOURCE mappedResource;
        HRESULT hr;

        hr = ID3D11DeviceContext_Map(sys->d3d_dev.d3dcontext, sys->stagingSys.resource[0],
                                        0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
        if( unlikely(FAILED(hr)) )
            msg_Err(vd, "Failed to map the %4.4s staging picture. (hr=0x%lX)", (const char*)&picture->format.i_chroma, hr);
        else
        {
            uint8_t *buf = mappedResource.pData;
            for (int i = 0; i < picture->i_planes; i++)
            {
                sys->stagingPlanes[i].i_pitch = mappedResource.RowPitch;
                sys->stagingPlanes[i].p_pixels = buf;

                plane_CopyPixels(&sys->stagingPlanes[i], &picture->p[i]);

                buf += sys->stagingPlanes[i].i_pitch * sys->stagingPlanes[i].i_lines;
            }

            ID3D11DeviceContext_Unmap(sys->d3d_dev.d3dcontext, sys->stagingSys.resource[0], 0);
        }
    }
    else
    {
        picture_sys_d3d11_t *p_sys = ActiveD3D11PictureSys(picture);

        d3d11_device_lock( &sys->d3d_dev );

        if (sys->legacy_shader) {
            D3D11_TEXTURE2D_DESC srcDesc,texDesc;
            ID3D11Texture2D_GetDesc(p_sys->texture[KNOWN_DXGI_INDEX], &srcDesc);
            ID3D11Texture2D_GetDesc(sys->stagingSys.texture[0], &texDesc);
            D3D11_BOX box = {
                .top = 0,
                .bottom = __MIN(srcDesc.Height, texDesc.Height),
                .left = 0,
                .right = __MIN(srcDesc.Width, texDesc.Width),
                .back = 1,
            };
            ID3D11DeviceContext_CopySubresourceRegion(sys->d3d_dev.d3dcontext,
                                                      sys->stagingSys.resource[KNOWN_DXGI_INDEX],
                                                      0, 0, 0, 0,
                                                      p_sys->resource[KNOWN_DXGI_INDEX],
                                                      p_sys->slice_index, &box);
        }
        else
        {
            D3D11_TEXTURE2D_DESC texDesc;
            ID3D11Texture2D_GetDesc(p_sys->texture[0], &texDesc);
            if (texDesc.BindFlags & D3D11_BIND_SHADER_RESOURCE)
            {
                /* for performance reason we don't want to allocate this during
                 * display, do it preferrably when creating the texture */
                assert(p_sys->renderSrc[0]!=NULL);
            }
            if ( sys->picQuad.i_height != texDesc.Height ||
                 sys->picQuad.i_width != texDesc.Width )
            {
                /* the decoder produced different sizes than the vout, we need to
                 * adjust the vertex */
                sys->area.texture_source.i_width  = sys->picQuad.i_height = texDesc.Height;
                sys->area.texture_source.i_height = sys->picQuad.i_width = texDesc.Width;

                CommonPlacePicture(VLC_OBJECT(vd), &sys->area, &sys->sys);
                UpdateSize(vd);
            }
        }
    }

    if (subpicture) {
        int subpicture_region_count    = 0;
        picture_t **subpicture_regions = NULL;
        Direct3D11MapSubpicture(vd, &subpicture_region_count, &subpicture_regions, subpicture);
        Direct3D11DeleteRegions(sys->d3dregion_count, sys->d3dregions);
        sys->d3dregion_count = subpicture_region_count;
        sys->d3dregions      = subpicture_regions;
    }

    if (picture->format.mastering.max_luminance)
    {
        D3D11_UpdateQuadLuminanceScale(vd, &sys->d3d_dev, &sys->picQuad, (float)sys->display.luminance_peak / GetFormatLuminance(VLC_OBJECT(vd), &picture->format));
    }

    /* Render the quad */
    ID3D11ShaderResourceView **renderSrc;
    if (!is_d3d11_opaque(picture->format.i_chroma) || sys->legacy_shader)
        renderSrc = sys->stagingSys.renderSrc;
    else {
        picture_sys_d3d11_t *p_sys = ActiveD3D11PictureSys(picture);
        renderSrc = p_sys->renderSrc;
    }
    D3D11_RenderQuad(&sys->d3d_dev, &sys->picQuad,
                     vd->source.projection_mode == PROJECTION_MODE_RECTANGULAR ? &sys->flatVShader : &sys->projectionVShader,
                     renderSrc, SelectRenderPlane, sys);

    if (subpicture) {
        // draw the additional vertices
        for (int i = 0; i < sys->d3dregion_count; ++i) {
            if (sys->d3dregions[i])
            {
                d3d_quad_t *quad = (d3d_quad_t *) sys->d3dregions[i]->p_sys;
                D3D11_RenderQuad(&sys->d3d_dev, quad, &sys->flatVShader,
                                 quad->picSys.renderSrc, SelectRenderPlane, sys);
            }
        }
    }

    if (sys->prepareWait)
    {
        int maxWait = 10;
        ID3D11DeviceContext_End(sys->d3d_dev.d3dcontext, (ID3D11Asynchronous*)sys->prepareWait);

        while (S_FALSE == ID3D11DeviceContext_GetData(sys->d3d_dev.d3dcontext,
                                                      (ID3D11Asynchronous*)sys->prepareWait, NULL, 0, 0)
               && --maxWait)
            SleepEx(2, TRUE);
    }

    if (is_d3d11_opaque(picture->format.i_chroma) && sys->picQuad.textureFormat->formatTexture != DXGI_FORMAT_UNKNOWN)
        d3d11_device_unlock( &sys->d3d_dev );
}