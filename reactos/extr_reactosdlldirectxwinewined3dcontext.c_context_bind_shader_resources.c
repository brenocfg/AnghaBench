#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct wined3d_state {struct wined3d_sampler*** sampler; struct wined3d_shader_resource_view*** shader_resource_view; struct wined3d_shader** shader; } ;
struct wined3d_shader_sampler_map_entry {unsigned int bind_idx; size_t resource_idx; size_t sampler_idx; } ;
struct wined3d_shader_resource_view {int dummy; } ;
struct TYPE_3__ {unsigned int count; struct wined3d_shader_sampler_map_entry* entries; } ;
struct TYPE_4__ {TYPE_1__ sampler_map; int /*<<< orphan*/  shader_version; } ;
struct wined3d_shader {TYPE_2__ reg_maps; } ;
struct wined3d_sampler {int dummy; } ;
struct wined3d_device {struct wined3d_sampler* null_sampler; struct wined3d_sampler* default_sampler; } ;
struct wined3d_context {struct wined3d_device* device; } ;
typedef  enum wined3d_shader_type { ____Placeholder_wined3d_shader_type } wined3d_shader_type ;
typedef  unsigned int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  FIXME (char*,struct wined3d_shader const*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  WARN (char*,int,size_t) ; 
 size_t WINED3D_SAMPLER_DEFAULT ; 
 unsigned int* context_get_tex_unit_mapping (struct wined3d_context*,int /*<<< orphan*/ *,unsigned int*,unsigned int*) ; 
 unsigned int min (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  wined3d_shader_resource_view_bind (struct wined3d_shader_resource_view*,unsigned int,struct wined3d_sampler*,struct wined3d_context*) ; 

__attribute__((used)) static void context_bind_shader_resources(struct wined3d_context *context,
        const struct wined3d_state *state, enum wined3d_shader_type shader_type)
{
    unsigned int bind_idx, shader_sampler_count, base, count, i;
    const struct wined3d_device *device = context->device;
    struct wined3d_shader_sampler_map_entry *entry;
    struct wined3d_shader_resource_view *view;
    const struct wined3d_shader *shader;
    struct wined3d_sampler *sampler;
    const DWORD *tex_unit_map;

    if (!(shader = state->shader[shader_type]))
        return;

    tex_unit_map = context_get_tex_unit_mapping(context,
            &shader->reg_maps.shader_version, &base, &count);

    shader_sampler_count = shader->reg_maps.sampler_map.count;
    if (shader_sampler_count > count)
        FIXME("Shader %p needs %u samplers, but only %u are supported.\n",
                shader, shader_sampler_count, count);
    count = min(shader_sampler_count, count);

    for (i = 0; i < count; ++i)
    {
        entry = &shader->reg_maps.sampler_map.entries[i];
        bind_idx = base + entry->bind_idx;
        if (tex_unit_map)
            bind_idx = tex_unit_map[bind_idx];

        if (!(view = state->shader_resource_view[shader_type][entry->resource_idx]))
        {
            WARN("No resource view bound at index %u, %u.\n", shader_type, entry->resource_idx);
            continue;
        }

        if (entry->sampler_idx == WINED3D_SAMPLER_DEFAULT)
            sampler = device->default_sampler;
        else if (!(sampler = state->sampler[shader_type][entry->sampler_idx]))
            sampler = device->null_sampler;
        wined3d_shader_resource_view_bind(view, bind_idx, sampler, context);
    }
}