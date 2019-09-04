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
struct vs_compile_args {int const swizzle_map; scalar_t__ clip_enabled; scalar_t__ point_size; scalar_t__ per_vertex_point_size; scalar_t__ flatshading; scalar_t__ next_shader_type; scalar_t__ next_shader_input_count; scalar_t__ fog_src; } ;
typedef  int DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 int FALSE ; 

__attribute__((used)) static inline BOOL vs_args_equal(const struct vs_compile_args *stored, const struct vs_compile_args *new,
        const DWORD use_map)
{
    if((stored->swizzle_map & use_map) != new->swizzle_map) return FALSE;
    if((stored->clip_enabled) != new->clip_enabled) return FALSE;
    if (stored->point_size != new->point_size)
        return FALSE;
    if (stored->per_vertex_point_size != new->per_vertex_point_size)
        return FALSE;
    if (stored->flatshading != new->flatshading)
        return FALSE;
    if (stored->next_shader_type != new->next_shader_type)
        return FALSE;
    if (stored->next_shader_input_count != new->next_shader_input_count)
        return FALSE;
    return stored->fog_src == new->fog_src;
}