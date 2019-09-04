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
struct wined3d_string_buffer {int dummy; } ;
typedef  enum wined3d_data_type { ____Placeholder_wined3d_data_type } wined3d_data_type ;

/* Variables and functions */
 int /*<<< orphan*/  FIXME (char*,int,int) ; 
 int WINED3D_DATA_FLOAT ; 
#define  WINED3D_DATA_INT 131 
#define  WINED3D_DATA_RESOURCE 130 
#define  WINED3D_DATA_SAMPLER 129 
#define  WINED3D_DATA_UINT 128 
 int /*<<< orphan*/  string_buffer_sprintf (struct wined3d_string_buffer*,char*,char const*) ; 

__attribute__((used)) static void shader_glsl_sprintf_cast(struct wined3d_string_buffer *dst_param, const char *src_param,
        enum wined3d_data_type dst_data_type, enum wined3d_data_type src_data_type)
{
    if (dst_data_type == src_data_type)
    {
        string_buffer_sprintf(dst_param, "%s", src_param);
        return;
    }

    if (src_data_type == WINED3D_DATA_FLOAT)
    {
        switch (dst_data_type)
        {
            case WINED3D_DATA_INT:
                string_buffer_sprintf(dst_param, "floatBitsToInt(%s)", src_param);
                return;
            case WINED3D_DATA_RESOURCE:
            case WINED3D_DATA_SAMPLER:
            case WINED3D_DATA_UINT:
                string_buffer_sprintf(dst_param, "floatBitsToUint(%s)", src_param);
                return;
            default:
                break;
        }
    }

    if (src_data_type == WINED3D_DATA_UINT && dst_data_type == WINED3D_DATA_FLOAT)
    {
        string_buffer_sprintf(dst_param, "uintBitsToFloat(%s)", src_param);
        return;
    }

    if (src_data_type == WINED3D_DATA_INT && dst_data_type == WINED3D_DATA_FLOAT)
    {
        string_buffer_sprintf(dst_param, "intBitsToFloat(%s)", src_param);
        return;
    }

    FIXME("Unhandled cast from %#x to %#x.\n", src_data_type, dst_data_type);
    string_buffer_sprintf(dst_param, "%s", src_param);
}