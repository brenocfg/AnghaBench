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
struct wined3d_shader_desc {scalar_t__ format; int /*<<< orphan*/  byte_code_size; int /*<<< orphan*/  byte_code; } ;
typedef  enum wined3d_shader_type { ____Placeholder_wined3d_shader_type } wined3d_shader_type ;

/* Variables and functions */
 int /*<<< orphan*/  FIXME (char*,scalar_t__) ; 
 scalar_t__ WINED3D_SHADER_BYTE_CODE_FORMAT_SM4 ; 
 int WINED3D_SHADER_TYPE_INVALID ; 
 int wined3d_get_sm4_shader_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum wined3d_shader_type shader_get_shader_type(const struct wined3d_shader_desc *desc)
{
    if (desc->format == WINED3D_SHADER_BYTE_CODE_FORMAT_SM4)
        return wined3d_get_sm4_shader_type(desc->byte_code, desc->byte_code_size);

    FIXME("Could not get shader type for byte code format %#x.\n", desc->format);
    return WINED3D_SHADER_TYPE_INVALID;
}