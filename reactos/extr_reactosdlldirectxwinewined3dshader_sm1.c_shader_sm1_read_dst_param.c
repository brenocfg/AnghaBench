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
struct wined3d_sm1_data {int dummy; } ;
struct wined3d_shader_src_param {int dummy; } ;
struct wined3d_shader_dst_param {int dummy; } ;
typedef  int DWORD ;

/* Variables and functions */
 int WINED3D_SM1_ADDRESS_MODE_RELATIVE ; 
 int /*<<< orphan*/  shader_get_param (struct wined3d_sm1_data*,int const*,int*,int*) ; 
 int /*<<< orphan*/  shader_parse_dst_param (int,struct wined3d_shader_src_param*,struct wined3d_shader_dst_param*) ; 
 int /*<<< orphan*/  shader_parse_src_param (int,int /*<<< orphan*/ *,struct wined3d_shader_src_param*) ; 

__attribute__((used)) static void shader_sm1_read_dst_param(struct wined3d_sm1_data *priv, const DWORD **ptr,
        struct wined3d_shader_dst_param *dst_param, struct wined3d_shader_src_param *dst_rel_addr)
{
    DWORD token, addr_token;

    *ptr += shader_get_param(priv, *ptr, &token, &addr_token);
    if (token & WINED3D_SM1_ADDRESS_MODE_RELATIVE)
    {
        shader_parse_src_param(addr_token, NULL, dst_rel_addr);
        shader_parse_dst_param(token, dst_rel_addr, dst_param);
    }
    else
    {
        shader_parse_dst_param(token, NULL, dst_param);
    }
}