#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct wined3d_state {TYPE_4__** shader; } ;
struct TYPE_10__ {unsigned int user_clip_distances; scalar_t__ glsl_varyings; } ;
struct wined3d_gl_info {TYPE_5__ limits; } ;
struct TYPE_6__ {unsigned int use_map; scalar_t__ position_transformed; scalar_t__ swizzle_map; } ;
struct wined3d_context {scalar_t__ last_was_rhw; scalar_t__ last_swizzle_map; unsigned int shader_update_mask; scalar_t__ last_was_normal; scalar_t__ last_was_vshader; int /*<<< orphan*/  constant_update_mask; TYPE_1__ stream_info; struct wined3d_gl_info* gl_info; } ;
struct TYPE_7__ {int major; int minor; } ;
struct TYPE_8__ {TYPE_2__ shader_version; } ;
struct TYPE_9__ {TYPE_3__ reg_maps; } ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  STATE_CLIPPLANE (unsigned int) ; 
 unsigned int WINED3D_FFP_NORMAL ; 
 int /*<<< orphan*/  WINED3D_SHADER_CONST_FFP_TEXMATRIX ; 
 int /*<<< orphan*/  WINED3D_SHADER_CONST_VS_CLIP_PLANES ; 
 size_t WINED3D_SHADER_TYPE_PIXEL ; 
 unsigned int WINED3D_SHADER_TYPE_VERTEX ; 
 int /*<<< orphan*/  clipplane (struct wined3d_context*,struct wined3d_state const*,int /*<<< orphan*/ ) ; 
 scalar_t__ needs_legacy_glsl_syntax (struct wined3d_gl_info const*) ; 
 scalar_t__ use_ps (struct wined3d_state const*) ; 
 scalar_t__ use_vs (struct wined3d_state const*) ; 
 scalar_t__ wined3d_max_compat_varyings (struct wined3d_gl_info const*) ; 

__attribute__((used)) static void glsl_vertex_pipe_vdecl(struct wined3d_context *context,
        const struct wined3d_state *state, DWORD state_id)
{
    const struct wined3d_gl_info *gl_info = context->gl_info;
    BOOL normal = !!(context->stream_info.use_map & (1u << WINED3D_FFP_NORMAL));
    const BOOL legacy_clip_planes = needs_legacy_glsl_syntax(gl_info);
    BOOL transformed = context->stream_info.position_transformed;
    BOOL wasrhw = context->last_was_rhw;
    unsigned int i;

    context->last_was_rhw = transformed;

    /* If the vertex declaration contains a transformed position attribute,
     * the draw uses the fixed function vertex pipeline regardless of any
     * vertex shader set by the application. */
    if (transformed != wasrhw
            || context->stream_info.swizzle_map != context->last_swizzle_map)
        context->shader_update_mask |= 1u << WINED3D_SHADER_TYPE_VERTEX;

    context->last_swizzle_map = context->stream_info.swizzle_map;

    if (!use_vs(state))
    {
        if (context->last_was_vshader)
        {
            if (legacy_clip_planes)
                for (i = 0; i < gl_info->limits.user_clip_distances; ++i)
                    clipplane(context, state, STATE_CLIPPLANE(i));
            else
                context->constant_update_mask |= WINED3D_SHADER_CONST_VS_CLIP_PLANES;
        }

        context->constant_update_mask |= WINED3D_SHADER_CONST_FFP_TEXMATRIX;

        /* Because of settings->texcoords, we have to regenerate the vertex
         * shader on a vdecl change if there aren't enough varyings to just
         * always output all the texture coordinates. */
        if (gl_info->limits.glsl_varyings < wined3d_max_compat_varyings(gl_info)
                || normal != context->last_was_normal)
            context->shader_update_mask |= 1u << WINED3D_SHADER_TYPE_VERTEX;

        if (use_ps(state)
                && state->shader[WINED3D_SHADER_TYPE_PIXEL]->reg_maps.shader_version.major == 1
                && state->shader[WINED3D_SHADER_TYPE_PIXEL]->reg_maps.shader_version.minor <= 3)
            context->shader_update_mask |= 1u << WINED3D_SHADER_TYPE_PIXEL;
    }
    else
    {
        if (!context->last_was_vshader)
        {
            /* Vertex shader clipping ignores the view matrix. Update all clip planes. */
            if (legacy_clip_planes)
                for (i = 0; i < gl_info->limits.user_clip_distances; ++i)
                    clipplane(context, state, STATE_CLIPPLANE(i));
            else
                context->constant_update_mask |= WINED3D_SHADER_CONST_VS_CLIP_PLANES;
        }
    }

    context->last_was_vshader = use_vs(state);
    context->last_was_normal = normal;
}