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
typedef  enum wined3d_shader_type { ____Placeholder_wined3d_shader_type } wined3d_shader_type ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  FIXME (char*,int) ; 
 int /*<<< orphan*/  WARN (char*,long) ; 
 int WINED3D_SHADER_TYPE_COMPUTE ; 
 int WINED3D_SHADER_TYPE_DOMAIN ; 
 int WINED3D_SHADER_TYPE_GEOMETRY ; 
 int WINED3D_SHADER_TYPE_HULL ; 
 int WINED3D_SHADER_TYPE_INVALID ; 
 int WINED3D_SHADER_TYPE_PIXEL ; 
 int WINED3D_SHADER_TYPE_VERTEX ; 
#define  WINED3D_SM4_GS 133 
#define  WINED3D_SM4_PS 132 
#define  WINED3D_SM4_VS 131 
#define  WINED3D_SM5_CS 130 
#define  WINED3D_SM5_DS 129 
#define  WINED3D_SM5_HS 128 

enum wined3d_shader_type wined3d_get_sm4_shader_type(const DWORD *byte_code, size_t byte_code_size)
{
    DWORD shader_type;

    if (byte_code_size / sizeof(*byte_code) < 1)
    {
        WARN("Invalid byte code size %lu.\n", (long)byte_code_size);
        return WINED3D_SHADER_TYPE_INVALID;
    }

    shader_type = byte_code[0] >> 16;
    switch (shader_type)
    {
        case WINED3D_SM4_PS:
            return WINED3D_SHADER_TYPE_PIXEL;
            break;
        case WINED3D_SM4_VS:
            return WINED3D_SHADER_TYPE_VERTEX;
            break;
        case WINED3D_SM4_GS:
            return WINED3D_SHADER_TYPE_GEOMETRY;
            break;
        case WINED3D_SM5_HS:
            return WINED3D_SHADER_TYPE_HULL;
            break;
        case WINED3D_SM5_DS:
            return WINED3D_SHADER_TYPE_DOMAIN;
            break;
        case WINED3D_SM5_CS:
            return WINED3D_SHADER_TYPE_COMPUTE;
            break;
        default:
            FIXME("Unrecognised shader type %#x.\n", shader_type);
            return WINED3D_SHADER_TYPE_INVALID;
    }
}