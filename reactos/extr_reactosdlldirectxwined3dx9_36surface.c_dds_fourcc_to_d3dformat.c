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
typedef  scalar_t__ const DWORD ;
typedef  scalar_t__ const D3DFORMAT ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (scalar_t__ const*) ; 
#define  D3DFMT_A16B16G16R16F 142 
#define  D3DFMT_A32B32G32R32F 141 
#define  D3DFMT_DXT1 140 
#define  D3DFMT_DXT2 139 
#define  D3DFMT_DXT3 138 
#define  D3DFMT_DXT4 137 
#define  D3DFMT_DXT5 136 
#define  D3DFMT_G16R16F 135 
#define  D3DFMT_G32R32F 134 
#define  D3DFMT_G8R8_G8B8 133 
#define  D3DFMT_R16F 132 
#define  D3DFMT_R32F 131 
#define  D3DFMT_R8G8_B8G8 130 
 scalar_t__ const D3DFMT_UNKNOWN ; 
#define  D3DFMT_UYVY 129 
#define  D3DFMT_YUY2 128 
 int /*<<< orphan*/  WARN (char*,scalar_t__ const) ; 

__attribute__((used)) static D3DFORMAT dds_fourcc_to_d3dformat(DWORD fourcc)
{
    unsigned int i;
    static const DWORD known_fourcc[] = {
        D3DFMT_UYVY,
        D3DFMT_YUY2,
        D3DFMT_R8G8_B8G8,
        D3DFMT_G8R8_G8B8,
        D3DFMT_DXT1,
        D3DFMT_DXT2,
        D3DFMT_DXT3,
        D3DFMT_DXT4,
        D3DFMT_DXT5,
        D3DFMT_R16F,
        D3DFMT_G16R16F,
        D3DFMT_A16B16G16R16F,
        D3DFMT_R32F,
        D3DFMT_G32R32F,
        D3DFMT_A32B32G32R32F,
    };

    for (i = 0; i < ARRAY_SIZE(known_fourcc); i++)
    {
        if (known_fourcc[i] == fourcc)
            return fourcc;
    }

    WARN("Unknown FourCC %#x\n", fourcc);
    return D3DFMT_UNKNOWN;
}