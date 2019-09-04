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
struct wined3d_string_buffer {int dummy; } ;
struct TYPE_7__ {int major; } ;
struct TYPE_10__ {TYPE_2__ shader_version; } ;
struct wined3d_shader {struct arb_pshader_private* backend_data; TYPE_5__ reg_maps; int /*<<< orphan*/  input_signature; struct wined3d_device* device; } ;
struct wined3d_gl_info {int dummy; } ;
struct wined3d_device {struct shader_arb_priv* shader_priv; TYPE_1__* adapter; } ;
struct TYPE_8__ {scalar_t__ ffp_blend_stages; } ;
struct wined3d_d3d_info {TYPE_3__ limits; int /*<<< orphan*/  vs_clipping; } ;
struct shader_arb_priv {int dummy; } ;
struct arb_pshader_private {int clamp_consts; unsigned int input_signature_idx; unsigned int clipplane_emulation; size_t num_gl_shaders; size_t shader_array_size; struct arb_ps_compiled_shader* gl_shaders; } ;
struct TYPE_9__ {int /*<<< orphan*/  tex_types; } ;
struct arb_ps_compile_args {TYPE_4__ super; } ;
struct arb_ps_compiled_shader {int /*<<< orphan*/  prgId; struct arb_ps_compile_args args; } ;
typedef  size_t UINT ;
struct TYPE_6__ {struct wined3d_d3d_info d3d_info; struct wined3d_gl_info gl_info; } ;
typedef  int /*<<< orphan*/  GLuint ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 struct arb_ps_compiled_shader* HeapReAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct arb_ps_compiled_shader*,int) ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 unsigned int find_input_signature (struct shader_arb_priv*,int /*<<< orphan*/ *) ; 
 void* heap_alloc_zero (int) ; 
 int max (int,int) ; 
 int /*<<< orphan*/  memcmp (struct arb_ps_compile_args*,struct arb_ps_compile_args const*,int) ; 
 int /*<<< orphan*/  pixelshader_update_resource_types (struct wined3d_shader*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shader_arb_generate_pshader (struct wined3d_shader*,struct wined3d_gl_info const*,struct wined3d_string_buffer*,struct arb_ps_compile_args const*,struct arb_ps_compiled_shader*) ; 
 unsigned int shader_find_free_input_register (TYPE_5__*,scalar_t__) ; 
 int /*<<< orphan*/  string_buffer_free (struct wined3d_string_buffer*) ; 
 int /*<<< orphan*/  string_buffer_init (struct wined3d_string_buffer*) ; 

__attribute__((used)) static struct arb_ps_compiled_shader *find_arb_pshader(struct wined3d_shader *shader,
        const struct arb_ps_compile_args *args)
{
    struct wined3d_device *device = shader->device;
    const struct wined3d_gl_info *gl_info = &device->adapter->gl_info;
    const struct wined3d_d3d_info *d3d_info = &device->adapter->d3d_info;
    UINT i;
    DWORD new_size;
    struct arb_ps_compiled_shader *new_array;
    struct wined3d_string_buffer buffer;
    struct arb_pshader_private *shader_data;
    GLuint ret;

    if (!shader->backend_data)
    {
        struct shader_arb_priv *priv = device->shader_priv;

        shader->backend_data = heap_alloc_zero(sizeof(*shader_data));
        shader_data = shader->backend_data;
        shader_data->clamp_consts = shader->reg_maps.shader_version.major == 1;

        if (shader->reg_maps.shader_version.major < 3)
            shader_data->input_signature_idx = ~0U;
        else
            shader_data->input_signature_idx = find_input_signature(priv, &shader->input_signature);

        TRACE("Shader got assigned input signature index %u\n", shader_data->input_signature_idx);

        if (!d3d_info->vs_clipping)
            shader_data->clipplane_emulation = shader_find_free_input_register(&shader->reg_maps,
                    d3d_info->limits.ffp_blend_stages - 1);
        else
            shader_data->clipplane_emulation = ~0U;
    }
    shader_data = shader->backend_data;

    /* Usually we have very few GL shaders for each d3d shader(just 1 or maybe 2),
     * so a linear search is more performant than a hashmap or a binary search
     * (cache coherency etc)
     */
    for (i = 0; i < shader_data->num_gl_shaders; ++i)
    {
        if (!memcmp(&shader_data->gl_shaders[i].args, args, sizeof(*args)))
            return &shader_data->gl_shaders[i];
    }

    TRACE("No matching GL shader found, compiling a new shader\n");
    if(shader_data->shader_array_size == shader_data->num_gl_shaders) {
        if (shader_data->num_gl_shaders)
        {
            new_size = shader_data->shader_array_size + max(1, shader_data->shader_array_size / 2);
            new_array = HeapReAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, shader_data->gl_shaders,
                                    new_size * sizeof(*shader_data->gl_shaders));
        }
        else
        {
            new_array = heap_alloc_zero(sizeof(*shader_data->gl_shaders));
            new_size = 1;
        }

        if(!new_array) {
            ERR("Out of memory\n");
            return 0;
        }
        shader_data->gl_shaders = new_array;
        shader_data->shader_array_size = new_size;
    }

    shader_data->gl_shaders[shader_data->num_gl_shaders].args = *args;

    pixelshader_update_resource_types(shader, args->super.tex_types);

    if (!string_buffer_init(&buffer))
    {
        ERR("Failed to initialize shader buffer.\n");
        return 0;
    }

    ret = shader_arb_generate_pshader(shader, gl_info, &buffer, args,
            &shader_data->gl_shaders[shader_data->num_gl_shaders]);
    string_buffer_free(&buffer);
    shader_data->gl_shaders[shader_data->num_gl_shaders].prgId = ret;

    return &shader_data->gl_shaders[shader_data->num_gl_shaders++];
}