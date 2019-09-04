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
struct wined3d_shader_frontend {int dummy; } ;
typedef  enum wined3d_shader_byte_code_format { ____Placeholder_wined3d_shader_byte_code_format } wined3d_shader_byte_code_format ;

/* Variables and functions */
 int /*<<< orphan*/  WARN (char*,int) ; 
#define  WINED3D_SHADER_BYTE_CODE_FORMAT_SM1 129 
#define  WINED3D_SHADER_BYTE_CODE_FORMAT_SM4 128 
 struct wined3d_shader_frontend const sm1_shader_frontend ; 
 struct wined3d_shader_frontend const sm4_shader_frontend ; 

__attribute__((used)) static const struct wined3d_shader_frontend *shader_select_frontend(enum wined3d_shader_byte_code_format format)
{
    switch (format)
    {
        case WINED3D_SHADER_BYTE_CODE_FORMAT_SM1:
            return &sm1_shader_frontend;

        case WINED3D_SHADER_BYTE_CODE_FORMAT_SM4:
            return &sm4_shader_frontend;

        default:
            WARN("Invalid byte code format %#x specified.\n", format);
            return NULL;
    }
}