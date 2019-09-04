#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int size; } ;
struct dds_header {int miplevels; int caps2; int depth; TYPE_3__ pixel_format; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
typedef  int UINT ;
struct TYPE_4__ {int Depth; int MipLevels; int /*<<< orphan*/  ImageFileFormat; int /*<<< orphan*/  Height; int /*<<< orphan*/  Width; int /*<<< orphan*/  Format; int /*<<< orphan*/  ResourceType; } ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int DWORD ;
typedef  TYPE_1__ D3DXIMAGE_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  D3DFMT_UNKNOWN ; 
 int /*<<< orphan*/  D3DRTYPE_CUBETEXTURE ; 
 int /*<<< orphan*/  D3DRTYPE_TEXTURE ; 
 int /*<<< orphan*/  D3DRTYPE_VOLUMETEXTURE ; 
 int /*<<< orphan*/  D3DXERR_INVALIDDATA ; 
 int /*<<< orphan*/  D3DXIFF_DDS ; 
 int /*<<< orphan*/  D3D_OK ; 
 int DDS_CAPS2_CUBEMAP ; 
 int DDS_CAPS2_CUBEMAP_NEGATIVEZ ; 
 int DDS_CAPS2_CUBEMAP_POSITIVEX ; 
 int DDS_CAPS2_VOLUME ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN (char*,int,int) ; 
 int calculate_dds_file_size (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  dds_pixel_format_to_d3dformat (TYPE_3__*) ; 

__attribute__((used)) static HRESULT get_image_info_from_dds(const void *buffer, UINT length, D3DXIMAGE_INFO *info)
{
    UINT faces = 1;
    UINT expected_length;
    const struct dds_header *header = buffer;

    if (length < sizeof(*header) || !info)
        return D3DXERR_INVALIDDATA;

    if (header->pixel_format.size != sizeof(header->pixel_format))
        return D3DXERR_INVALIDDATA;

    info->Width = header->width;
    info->Height = header->height;
    info->Depth = 1;
    info->MipLevels = header->miplevels ? header->miplevels : 1;

    info->Format = dds_pixel_format_to_d3dformat(&header->pixel_format);
    if (info->Format == D3DFMT_UNKNOWN)
        return D3DXERR_INVALIDDATA;

    TRACE("Pixel format is %#x\n", info->Format);

    if (header->caps2 & DDS_CAPS2_VOLUME)
    {
        info->Depth = header->depth;
        info->ResourceType = D3DRTYPE_VOLUMETEXTURE;
    }
    else if (header->caps2 & DDS_CAPS2_CUBEMAP)
    {
        DWORD face;
        faces = 0;
        for (face = DDS_CAPS2_CUBEMAP_POSITIVEX; face <= DDS_CAPS2_CUBEMAP_NEGATIVEZ; face <<= 1)
        {
            if (header->caps2 & face)
                faces++;
        }
        info->ResourceType = D3DRTYPE_CUBETEXTURE;
    }
    else
    {
        info->ResourceType = D3DRTYPE_TEXTURE;
    }

    expected_length = calculate_dds_file_size(info->Format, info->Width, info->Height, info->Depth,
        info->MipLevels, faces);
    if (length < expected_length)
    {
        WARN("File is too short %u, expected at least %u bytes\n", length, expected_length);
        return D3DXERR_INVALIDDATA;
    }

    info->ImageFileFormat = D3DXIFF_DDS;
    return D3D_OK;
}