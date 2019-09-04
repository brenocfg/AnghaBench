#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  (* p_glTexParameteri ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ;} ;
struct TYPE_5__ {TYPE_1__ gl; } ;
struct wined3d_gl_info {TYPE_2__ gl_ops; scalar_t__* supported; } ;
struct TYPE_6__ {int /*<<< orphan*/  srgb_decode; void* address_v; void* address_u; int /*<<< orphan*/  mip_filter; void* min_filter; void* mag_filter; } ;
struct gl_texture {unsigned int base_level; TYPE_3__ sampler_desc; } ;
typedef  enum wined3d_texture_filter_type { ____Placeholder_wined3d_texture_filter_type } wined3d_texture_filter_type ;
typedef  int /*<<< orphan*/  GLenum ;

/* Variables and functions */
 size_t EXT_TEXTURE_SRGB_DECODE ; 
 int /*<<< orphan*/  FALSE ; 
 unsigned int GL_CLAMP_TO_EDGE ; 
 unsigned int GL_SKIP_DECODE_EXT ; 
 int /*<<< orphan*/  GL_TEXTURE_BASE_LEVEL ; 
 int /*<<< orphan*/  GL_TEXTURE_MAG_FILTER ; 
 int /*<<< orphan*/  GL_TEXTURE_MIN_FILTER ; 
 int /*<<< orphan*/  GL_TEXTURE_SRGB_DECODE_EXT ; 
 int /*<<< orphan*/  GL_TEXTURE_WRAP_S ; 
 int /*<<< orphan*/  GL_TEXTURE_WRAP_T ; 
 void* WINED3D_TADDRESS_CLAMP ; 
 int /*<<< orphan*/  WINED3D_TEXF_NONE ; 
 void* WINED3D_TEXF_POINT ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  stub5 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  stub6 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int wined3d_gl_mag_filter (int) ; 
 unsigned int wined3d_gl_min_mip_filter (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void apply_texture_blit_state(const struct wined3d_gl_info *gl_info, struct gl_texture *texture,
        GLenum target, unsigned int level, enum wined3d_texture_filter_type filter)
{
    gl_info->gl_ops.gl.p_glTexParameteri(target, GL_TEXTURE_MAG_FILTER, wined3d_gl_mag_filter(filter));
    gl_info->gl_ops.gl.p_glTexParameteri(target, GL_TEXTURE_MIN_FILTER,
            wined3d_gl_min_mip_filter(filter, WINED3D_TEXF_NONE));
    gl_info->gl_ops.gl.p_glTexParameteri(target, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    gl_info->gl_ops.gl.p_glTexParameteri(target, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    if (gl_info->supported[EXT_TEXTURE_SRGB_DECODE])
        gl_info->gl_ops.gl.p_glTexParameteri(target, GL_TEXTURE_SRGB_DECODE_EXT, GL_SKIP_DECODE_EXT);
    gl_info->gl_ops.gl.p_glTexParameteri(target, GL_TEXTURE_BASE_LEVEL, level);

    /* We changed the filtering settings on the texture. Make sure they get
     * reset on subsequent draws. */
    texture->sampler_desc.mag_filter = WINED3D_TEXF_POINT;
    texture->sampler_desc.min_filter = WINED3D_TEXF_POINT;
    texture->sampler_desc.mip_filter = WINED3D_TEXF_NONE;
    texture->sampler_desc.address_u = WINED3D_TADDRESS_CLAMP;
    texture->sampler_desc.address_v = WINED3D_TADDRESS_CLAMP;
    texture->sampler_desc.srgb_decode = FALSE;
    texture->base_level = level;
}