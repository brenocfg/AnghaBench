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
struct wined3d_shader_backend_ops {int dummy; } ;
struct wined3d_gl_info {scalar_t__* supported; } ;
struct fragment_pipeline {int dummy; } ;

/* Variables and functions */
 size_t ARB_FRAGMENT_PROGRAM ; 
 size_t ARB_FRAGMENT_SHADER ; 
 size_t ATI_FRAGMENT_SHADER ; 
 size_t NV_REGISTER_COMBINERS ; 
 size_t NV_TEXTURE_SHADER2 ; 
 struct fragment_pipeline const arbfp_fragment_pipeline ; 
 struct fragment_pipeline const atifs_fragment_pipeline ; 
 struct fragment_pipeline const ffp_fragment_pipeline ; 
 struct fragment_pipeline const glsl_fragment_pipe ; 
 struct wined3d_shader_backend_ops const glsl_shader_backend ; 
 struct fragment_pipeline const nvrc_fragment_pipeline ; 
 struct fragment_pipeline const nvts_fragment_pipeline ; 

__attribute__((used)) static const struct fragment_pipeline *select_fragment_implementation(const struct wined3d_gl_info *gl_info,
        const struct wined3d_shader_backend_ops *shader_backend_ops)
{
    if (shader_backend_ops == &glsl_shader_backend && gl_info->supported[ARB_FRAGMENT_SHADER])
        return &glsl_fragment_pipe;
    if (gl_info->supported[ARB_FRAGMENT_PROGRAM])
        return &arbfp_fragment_pipeline;
    if (gl_info->supported[ATI_FRAGMENT_SHADER])
        return &atifs_fragment_pipeline;
    if (gl_info->supported[NV_REGISTER_COMBINERS] && gl_info->supported[NV_TEXTURE_SHADER2])
        return &nvts_fragment_pipeline;
    if (gl_info->supported[NV_REGISTER_COMBINERS])
        return &nvrc_fragment_pipeline;
    return &ffp_fragment_pipeline;
}