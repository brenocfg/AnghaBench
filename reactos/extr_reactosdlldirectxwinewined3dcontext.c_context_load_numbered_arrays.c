#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct wined3d_stream_state {int flags; int frequency; int /*<<< orphan*/  buffer; } ;
struct TYPE_8__ {scalar_t__ buffer_object; int /*<<< orphan*/ * addr; } ;
struct wined3d_stream_info_element {size_t stream_idx; int stride; TYPE_3__* format; TYPE_4__ data; scalar_t__ divisor; } ;
struct wined3d_stream_info {unsigned int use_map; struct wined3d_stream_info_element* elements; } ;
struct wined3d_state {int load_base_vertex_index; struct wined3d_stream_state* streams; struct wined3d_shader** shader; } ;
struct TYPE_5__ {int major; } ;
struct TYPE_6__ {TYPE_1__ shader_version; } ;
struct wined3d_shader {TYPE_2__ reg_maps; } ;
struct wined3d_gl_info {scalar_t__* supported; } ;
struct wined3d_context {int instance_count; unsigned int numbered_array_mask; struct wined3d_gl_info* gl_info; } ;
typedef  int /*<<< orphan*/  ULONG_PTR ;
struct TYPE_7__ {int* flags; int id; int /*<<< orphan*/  gl_normalized; int /*<<< orphan*/  gl_vtx_type; int /*<<< orphan*/  gl_vtx_format; } ;
typedef  int GLushort ;
typedef  scalar_t__ GLuint ;
typedef  int /*<<< orphan*/  const GLubyte ;
typedef  int GLshort ;
typedef  int /*<<< orphan*/  GLhalfNV ;
typedef  int /*<<< orphan*/  GLfloat ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 size_t ARB_INSTANCED_ARRAYS ; 
 size_t ARB_VERTEX_ARRAY_BGRA ; 
 size_t ARB_VERTEX_BUFFER_OBJECT ; 
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  FIXME (char*) ; 
 int /*<<< orphan*/  GL_ARRAY_BUFFER ; 
 int /*<<< orphan*/  GL_EXTCALL (int /*<<< orphan*/ ) ; 
 unsigned int MAX_ATTRIBS ; 
 size_t NV_HALF_FLOAT ; 
 size_t NV_VERTEX_PROGRAM ; 
 int /*<<< orphan*/  TRACE (char*,unsigned int,scalar_t__) ; 
#define  WINED3DFMT_B8G8R8A8_UNORM 144 
 int WINED3DFMT_FLAG_INTEGER ; 
#define  WINED3DFMT_R10G10B10X2_SNORM 143 
#define  WINED3DFMT_R10G10B10X2_UINT 142 
#define  WINED3DFMT_R16G16B16A16_FLOAT 141 
#define  WINED3DFMT_R16G16B16A16_SINT 140 
#define  WINED3DFMT_R16G16B16A16_SNORM 139 
#define  WINED3DFMT_R16G16B16A16_UNORM 138 
#define  WINED3DFMT_R16G16_FLOAT 137 
#define  WINED3DFMT_R16G16_SINT 136 
#define  WINED3DFMT_R16G16_SNORM 135 
#define  WINED3DFMT_R16G16_UNORM 134 
#define  WINED3DFMT_R32G32B32A32_FLOAT 133 
#define  WINED3DFMT_R32G32B32_FLOAT 132 
#define  WINED3DFMT_R32G32_FLOAT 131 
#define  WINED3DFMT_R32_FLOAT 130 
#define  WINED3DFMT_R8G8B8A8_UINT 129 
#define  WINED3DFMT_R8G8B8A8_UNORM 128 
 int WINED3DSTREAMSOURCE_INSTANCEDATA ; 
 unsigned int WINED3D_FFP_DIFFUSE ; 
 size_t WINED3D_GL_RES_TYPE_BUFFER ; 
 size_t WINED3D_SHADER_TYPE_VERTEX ; 
 int /*<<< orphan*/  checkGLcall (char*) ; 
 int /*<<< orphan*/  context_unload_numbered_array (struct wined3d_context*,unsigned int) ; 
 float float_16_to_32 (unsigned short const*) ; 
 int /*<<< orphan*/  glBindBuffer (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  glEnableVertexAttribArray (unsigned int) ; 
 int /*<<< orphan*/  glVertexAttrib1fv (unsigned int,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  glVertexAttrib2f (unsigned int,float,float) ; 
 int /*<<< orphan*/  glVertexAttrib2fv (unsigned int,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  glVertexAttrib2hvNV (unsigned int,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  glVertexAttrib2sv (unsigned int,int const*) ; 
 int /*<<< orphan*/  glVertexAttrib3fv (unsigned int,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  glVertexAttrib4Nsv (unsigned int,int const*) ; 
 int /*<<< orphan*/  glVertexAttrib4Nubv (unsigned int,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  glVertexAttrib4Nusv (unsigned int,int const*) ; 
 int /*<<< orphan*/  glVertexAttrib4f (unsigned int,float,float,float,float) ; 
 int /*<<< orphan*/  glVertexAttrib4fv (unsigned int,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  glVertexAttrib4hvNV (unsigned int,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  glVertexAttrib4sv (unsigned int,int const*) ; 
 int /*<<< orphan*/  glVertexAttrib4ubv (unsigned int,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  glVertexAttribDivisor (unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  glVertexAttribIPointer (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glVertexAttribPointer (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  use_vs (struct wined3d_state const*) ; 
 scalar_t__ wined3d_buffer_load_sysmem (int /*<<< orphan*/ ,struct wined3d_context*) ; 

__attribute__((used)) static void context_load_numbered_arrays(struct wined3d_context *context,
        const struct wined3d_stream_info *stream_info, const struct wined3d_state *state)
{
    const struct wined3d_shader *vs = state->shader[WINED3D_SHADER_TYPE_VERTEX];
    const struct wined3d_gl_info *gl_info = context->gl_info;
    GLuint current_bo;
    unsigned int i;

    /* Default to no instancing. */
    context->instance_count = 0;
    current_bo = gl_info->supported[ARB_VERTEX_BUFFER_OBJECT] ? ~0u : 0;

    for (i = 0; i < MAX_ATTRIBS; ++i)
    {
        const struct wined3d_stream_info_element *element = &stream_info->elements[i];
        const struct wined3d_stream_state *stream;

        if (!(stream_info->use_map & (1u << i)))
        {
            if (context->numbered_array_mask & (1u << i))
                context_unload_numbered_array(context, i);
            if (!use_vs(state) && i == WINED3D_FFP_DIFFUSE)
                GL_EXTCALL(glVertexAttrib4f(i, 1.0f, 1.0f, 1.0f, 1.0f));
            else
                GL_EXTCALL(glVertexAttrib4f(i, 0.0f, 0.0f, 0.0f, 0.0f));
            continue;
        }

        stream = &state->streams[element->stream_idx];

        if ((stream->flags & WINED3DSTREAMSOURCE_INSTANCEDATA) && !context->instance_count)
            context->instance_count = state->streams[0].frequency ? state->streams[0].frequency : 1;

        if (gl_info->supported[ARB_INSTANCED_ARRAYS])
        {
            GL_EXTCALL(glVertexAttribDivisor(i, element->divisor));
        }
        else if (element->divisor)
        {
            /* Unload instanced arrays, they will be loaded using immediate
             * mode instead. */
            if (context->numbered_array_mask & (1u << i))
                context_unload_numbered_array(context, i);
            continue;
        }

        TRACE("Loading array %u [VBO=%u].\n", i, element->data.buffer_object);

        if (element->stride)
        {
            if (current_bo != element->data.buffer_object)
            {
                GL_EXTCALL(glBindBuffer(GL_ARRAY_BUFFER, element->data.buffer_object));
                checkGLcall("glBindBuffer");
                current_bo = element->data.buffer_object;
            }
            /* Use the VBO to find out if a vertex buffer exists, not the vb
             * pointer. vb can point to a user pointer data blob. In that case
             * current_bo will be 0. If there is a vertex buffer but no vbo we
             * won't be load converted attributes anyway. */
            if (vs && vs->reg_maps.shader_version.major >= 4
                    && (element->format->flags[WINED3D_GL_RES_TYPE_BUFFER] & WINED3DFMT_FLAG_INTEGER))
            {
                GL_EXTCALL(glVertexAttribIPointer(i, element->format->gl_vtx_format, element->format->gl_vtx_type,
                        element->stride, element->data.addr + state->load_base_vertex_index * element->stride));
            }
            else
            {
                GL_EXTCALL(glVertexAttribPointer(i, element->format->gl_vtx_format, element->format->gl_vtx_type,
                        element->format->gl_normalized, element->stride,
                        element->data.addr + state->load_base_vertex_index * element->stride));
            }

            if (!(context->numbered_array_mask & (1u << i)))
            {
                GL_EXTCALL(glEnableVertexAttribArray(i));
                context->numbered_array_mask |= (1u << i);
            }
        }
        else
        {
            /* Stride = 0 means always the same values.
             * glVertexAttribPointer() doesn't do that. Instead disable the
             * pointer and set up the attribute statically. But we have to
             * figure out the system memory address. */
            const BYTE *ptr = element->data.addr;
            if (element->data.buffer_object)
                ptr += (ULONG_PTR)wined3d_buffer_load_sysmem(stream->buffer, context);

            if (context->numbered_array_mask & (1u << i))
                context_unload_numbered_array(context, i);

            switch (element->format->id)
            {
                case WINED3DFMT_R32_FLOAT:
                    GL_EXTCALL(glVertexAttrib1fv(i, (const GLfloat *)ptr));
                    break;
                case WINED3DFMT_R32G32_FLOAT:
                    GL_EXTCALL(glVertexAttrib2fv(i, (const GLfloat *)ptr));
                    break;
                case WINED3DFMT_R32G32B32_FLOAT:
                    GL_EXTCALL(glVertexAttrib3fv(i, (const GLfloat *)ptr));
                    break;
                case WINED3DFMT_R32G32B32A32_FLOAT:
                    GL_EXTCALL(glVertexAttrib4fv(i, (const GLfloat *)ptr));
                    break;
                case WINED3DFMT_R8G8B8A8_UINT:
                    GL_EXTCALL(glVertexAttrib4ubv(i, ptr));
                    break;
                case WINED3DFMT_B8G8R8A8_UNORM:
                    if (gl_info->supported[ARB_VERTEX_ARRAY_BGRA])
                    {
                        const DWORD *src = (const DWORD *)ptr;
                        DWORD c = *src & 0xff00ff00u;
                        c |= (*src & 0xff0000u) >> 16;
                        c |= (*src & 0xffu) << 16;
                        GL_EXTCALL(glVertexAttrib4Nubv(i, (GLubyte *)&c));
                        break;
                    }
                    /* else fallthrough */
                case WINED3DFMT_R8G8B8A8_UNORM:
                    GL_EXTCALL(glVertexAttrib4Nubv(i, ptr));
                    break;
                case WINED3DFMT_R16G16_SINT:
                    GL_EXTCALL(glVertexAttrib2sv(i, (const GLshort *)ptr));
                    break;
                case WINED3DFMT_R16G16B16A16_SINT:
                    GL_EXTCALL(glVertexAttrib4sv(i, (const GLshort *)ptr));
                    break;
                case WINED3DFMT_R16G16_SNORM:
                {
                    const GLshort s[4] = {((const GLshort *)ptr)[0], ((const GLshort *)ptr)[1], 0, 1};
                    GL_EXTCALL(glVertexAttrib4Nsv(i, s));
                    break;
                }
                case WINED3DFMT_R16G16_UNORM:
                {
                    const GLushort s[4] = {((const GLushort *)ptr)[0], ((const GLushort *)ptr)[1], 0, 1};
                    GL_EXTCALL(glVertexAttrib4Nusv(i, s));
                    break;
                }
                case WINED3DFMT_R16G16B16A16_SNORM:
                    GL_EXTCALL(glVertexAttrib4Nsv(i, (const GLshort *)ptr));
                    break;
                case WINED3DFMT_R16G16B16A16_UNORM:
                    GL_EXTCALL(glVertexAttrib4Nusv(i, (const GLushort *)ptr));
                    break;
                case WINED3DFMT_R10G10B10X2_UINT:
                    FIXME("Unsure about WINED3DDECLTYPE_UDEC3.\n");
                    /*glVertexAttrib3usvARB(i, (const GLushort *)ptr); Does not exist */
                    break;
                case WINED3DFMT_R10G10B10X2_SNORM:
                    FIXME("Unsure about WINED3DDECLTYPE_DEC3N.\n");
                    /*glVertexAttrib3NusvARB(i, (const GLushort *)ptr); Does not exist */
                    break;
                case WINED3DFMT_R16G16_FLOAT:
                    if (gl_info->supported[NV_HALF_FLOAT] && gl_info->supported[NV_VERTEX_PROGRAM])
                    {
                        /* Not supported by GL_ARB_half_float_vertex. */
                        GL_EXTCALL(glVertexAttrib2hvNV(i, (const GLhalfNV *)ptr));
                    }
                    else
                    {
                        float x = float_16_to_32(((const unsigned short *)ptr) + 0);
                        float y = float_16_to_32(((const unsigned short *)ptr) + 1);
                        GL_EXTCALL(glVertexAttrib2f(i, x, y));
                    }
                    break;
                case WINED3DFMT_R16G16B16A16_FLOAT:
                    if (gl_info->supported[NV_HALF_FLOAT] && gl_info->supported[NV_VERTEX_PROGRAM])
                    {
                        /* Not supported by GL_ARB_half_float_vertex. */
                        GL_EXTCALL(glVertexAttrib4hvNV(i, (const GLhalfNV *)ptr));
                    }
                    else
                    {
                        float x = float_16_to_32(((const unsigned short *)ptr) + 0);
                        float y = float_16_to_32(((const unsigned short *)ptr) + 1);
                        float z = float_16_to_32(((const unsigned short *)ptr) + 2);
                        float w = float_16_to_32(((const unsigned short *)ptr) + 3);
                        GL_EXTCALL(glVertexAttrib4f(i, x, y, z, w));
                    }
                    break;
                default:
                    ERR("Unexpected declaration in stride 0 attributes.\n");
                    break;

            }
        }
    }
    checkGLcall("Loading numbered arrays");
}