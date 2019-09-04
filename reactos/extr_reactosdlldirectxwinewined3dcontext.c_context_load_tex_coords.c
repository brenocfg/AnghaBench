#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ buffer_object; scalar_t__ addr; } ;
struct wined3d_stream_info_element {int stride; TYPE_4__ data; TYPE_3__* format; } ;
struct wined3d_stream_info {unsigned int use_map; struct wined3d_stream_info_element* elements; } ;
struct wined3d_state {unsigned int** texture_states; int load_base_vertex_index; } ;
struct TYPE_14__ {unsigned int texture_coords; unsigned int textures; } ;
struct TYPE_12__ {int /*<<< orphan*/  (* p_glEnableClientState ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* p_glTexCoordPointer ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__) ;} ;
struct TYPE_13__ {TYPE_5__ gl; } ;
struct wined3d_gl_info {TYPE_7__ limits; scalar_t__* supported; TYPE_6__ gl_ops; } ;
struct wined3d_context {unsigned int* tex_unit_map; TYPE_2__* d3d_info; struct wined3d_gl_info* gl_info; } ;
struct TYPE_10__ {int /*<<< orphan*/  gl_vtx_type; int /*<<< orphan*/  gl_vtx_format; } ;
struct TYPE_8__ {unsigned int ffp_blend_stages; } ;
struct TYPE_9__ {TYPE_1__ limits; } ;
typedef  scalar_t__ GLuint ;

/* Variables and functions */
 int /*<<< orphan*/  FIXME (char*,unsigned int) ; 
 int /*<<< orphan*/  GL_ARRAY_BUFFER ; 
 int /*<<< orphan*/  GL_EXTCALL (int /*<<< orphan*/ ) ; 
 scalar_t__ GL_TEXTURE0_ARB ; 
 int /*<<< orphan*/  GL_TEXTURE_COORD_ARRAY ; 
 unsigned int MAX_TEXTURES ; 
 size_t NV_REGISTER_COMBINERS ; 
 int /*<<< orphan*/  TRACE (char*,unsigned int,unsigned int,unsigned int,scalar_t__,scalar_t__) ; 
 unsigned int WINED3D_FFP_TEXCOORD0 ; 
 size_t WINED3D_TSS_TEXCOORD_INDEX ; 
 unsigned int WINED3D_UNMAPPED_STAGE ; 
 int /*<<< orphan*/  checkGLcall (char*) ; 
 int /*<<< orphan*/  glBindBuffer (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  glClientActiveTextureARB (scalar_t__) ; 
 int /*<<< orphan*/  glMultiTexCoord4fARB (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ) ; 

void context_load_tex_coords(const struct wined3d_context *context, const struct wined3d_stream_info *si,
        GLuint *current_bo, const struct wined3d_state *state)
{
    const struct wined3d_gl_info *gl_info = context->gl_info;
    unsigned int mapped_stage = 0;
    unsigned int texture_idx;

    for (texture_idx = 0; texture_idx < context->d3d_info->limits.ffp_blend_stages; ++texture_idx)
    {
        unsigned int coord_idx = state->texture_states[texture_idx][WINED3D_TSS_TEXCOORD_INDEX];

        if ((mapped_stage = context->tex_unit_map[texture_idx]) == WINED3D_UNMAPPED_STAGE)
            continue;

        if (mapped_stage >= gl_info->limits.texture_coords)
        {
            FIXME("Attempted to load unsupported texture coordinate %u.\n", mapped_stage);
            continue;
        }

        if (coord_idx < MAX_TEXTURES && (si->use_map & (1u << (WINED3D_FFP_TEXCOORD0 + coord_idx))))
        {
            const struct wined3d_stream_info_element *e = &si->elements[WINED3D_FFP_TEXCOORD0 + coord_idx];

            TRACE("Setting up texture %u, idx %d, coord_idx %u, data {%#x:%p}.\n",
                    texture_idx, mapped_stage, coord_idx, e->data.buffer_object, e->data.addr);

            if (*current_bo != e->data.buffer_object)
            {
                GL_EXTCALL(glBindBuffer(GL_ARRAY_BUFFER, e->data.buffer_object));
                checkGLcall("glBindBuffer");
                *current_bo = e->data.buffer_object;
            }

            GL_EXTCALL(glClientActiveTextureARB(GL_TEXTURE0_ARB + mapped_stage));
            checkGLcall("glClientActiveTextureARB");

            /* The coords to supply depend completely on the fvf/vertex shader. */
            gl_info->gl_ops.gl.p_glTexCoordPointer(e->format->gl_vtx_format, e->format->gl_vtx_type, e->stride,
                    e->data.addr + state->load_base_vertex_index * e->stride);
            gl_info->gl_ops.gl.p_glEnableClientState(GL_TEXTURE_COORD_ARRAY);
        }
        else
        {
            GL_EXTCALL(glMultiTexCoord4fARB(GL_TEXTURE0_ARB + mapped_stage, 0, 0, 0, 1));
        }
    }
    if (gl_info->supported[NV_REGISTER_COMBINERS])
    {
        /* The number of the mapped stages increases monotonically, so it's fine to use the last used one. */
        for (texture_idx = mapped_stage + 1; texture_idx < gl_info->limits.textures; ++texture_idx)
        {
            GL_EXTCALL(glMultiTexCoord4fARB(GL_TEXTURE0_ARB + texture_idx, 0, 0, 0, 1));
        }
    }

    checkGLcall("loadTexCoords");
}