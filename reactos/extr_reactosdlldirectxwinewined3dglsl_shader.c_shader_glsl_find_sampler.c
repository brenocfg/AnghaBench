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
struct wined3d_shader_sampler_map_entry {unsigned int resource_idx; unsigned int sampler_idx; unsigned int bind_idx; } ;
struct wined3d_shader_sampler_map {unsigned int count; struct wined3d_shader_sampler_map_entry* entries; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,unsigned int,unsigned int) ; 

__attribute__((used)) static unsigned int shader_glsl_find_sampler(const struct wined3d_shader_sampler_map *sampler_map,
        unsigned int resource_idx, unsigned int sampler_idx)
{
    struct wined3d_shader_sampler_map_entry *entries = sampler_map->entries;
    unsigned int i;

    for (i = 0; i < sampler_map->count; ++i)
    {
        if (entries[i].resource_idx == resource_idx && entries[i].sampler_idx == sampler_idx)
            return entries[i].bind_idx;
    }

    ERR("No GLSL sampler found for resource %u / sampler %u.\n", resource_idx, sampler_idx);

    return ~0u;
}