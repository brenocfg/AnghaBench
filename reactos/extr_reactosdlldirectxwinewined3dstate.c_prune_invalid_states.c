#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct wined3d_gl_info {int dummy; } ;
struct TYPE_2__ {int ffp_vertex_blend_matrices; scalar_t__ ffp_blend_stages; } ;
struct wined3d_d3d_info {TYPE_1__ limits; } ;
struct StateEntry {void* apply; scalar_t__ representative; } ;

/* Variables and functions */
 scalar_t__ MAX_TEXTURES ; 
 unsigned int STATE_TEXTURESTAGE (scalar_t__,int /*<<< orphan*/ ) ; 
 unsigned int STATE_TRANSFORM (scalar_t__) ; 
 int /*<<< orphan*/  WINED3D_HIGHEST_TEXTURE_STATE ; 
 scalar_t__ WINED3D_TS_TEXTURE0 ; 
 scalar_t__ WINED3D_TS_WORLD_MATRIX (int) ; 
 void* state_undefined ; 

__attribute__((used)) static void prune_invalid_states(struct StateEntry *state_table, const struct wined3d_gl_info *gl_info,
        const struct wined3d_d3d_info *d3d_info)
{
    unsigned int start, last, i;

    start = STATE_TEXTURESTAGE(d3d_info->limits.ffp_blend_stages, 0);
    last = STATE_TEXTURESTAGE(MAX_TEXTURES - 1, WINED3D_HIGHEST_TEXTURE_STATE);
    for (i = start; i <= last; ++i)
    {
        state_table[i].representative = 0;
        state_table[i].apply = state_undefined;
    }

    start = STATE_TRANSFORM(WINED3D_TS_TEXTURE0 + d3d_info->limits.ffp_blend_stages);
    last = STATE_TRANSFORM(WINED3D_TS_TEXTURE0 + MAX_TEXTURES - 1);
    for (i = start; i <= last; ++i)
    {
        state_table[i].representative = 0;
        state_table[i].apply = state_undefined;
    }

    start = STATE_TRANSFORM(WINED3D_TS_WORLD_MATRIX(d3d_info->limits.ffp_vertex_blend_matrices));
    last = STATE_TRANSFORM(WINED3D_TS_WORLD_MATRIX(255));
    for (i = start; i <= last; ++i)
    {
        state_table[i].representative = 0;
        state_table[i].apply = state_undefined;
    }
}