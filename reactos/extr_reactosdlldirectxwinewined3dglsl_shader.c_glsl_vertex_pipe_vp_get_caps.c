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
struct wined3d_vertex_caps {int emulated_flatshading; int vertex_processing_caps; int fvf_caps; int /*<<< orphan*/  raster_caps; int /*<<< orphan*/  max_user_clip_planes; scalar_t__ max_vertex_blend_matrix_index; int /*<<< orphan*/  max_vertex_blend_matrices; int /*<<< orphan*/  max_active_lights; void* ffp_generic_attributes; void* xyzrhw; } ;
struct TYPE_2__ {int /*<<< orphan*/  user_clip_distances; } ;
struct wined3d_gl_info {TYPE_1__ limits; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_ACTIVE_LIGHTS ; 
 int /*<<< orphan*/  MAX_VERTEX_BLENDS ; 
 scalar_t__ MAX_VERTEX_INDEX_BLENDS ; 
 void* TRUE ; 
 int WINED3DFVFCAPS_PSIZE ; 
 int /*<<< orphan*/  WINED3DPRASTERCAPS_FOGRANGE ; 
 int WINED3DVTXPCAPS_DIRECTIONALLIGHTS ; 
 int WINED3DVTXPCAPS_LOCALVIEWER ; 
 int WINED3DVTXPCAPS_MATERIALSOURCE7 ; 
 int WINED3DVTXPCAPS_POSITIONALLIGHTS ; 
 int WINED3DVTXPCAPS_TEXGEN ; 
 int WINED3DVTXPCAPS_TEXGEN_SPHEREMAP ; 
 int WINED3DVTXPCAPS_VERTEXFOG ; 
 int /*<<< orphan*/  needs_legacy_glsl_syntax (struct wined3d_gl_info const*) ; 

__attribute__((used)) static void glsl_vertex_pipe_vp_get_caps(const struct wined3d_gl_info *gl_info, struct wined3d_vertex_caps *caps)
{
    caps->xyzrhw = TRUE;
    caps->emulated_flatshading = !needs_legacy_glsl_syntax(gl_info);
    caps->ffp_generic_attributes = TRUE;
    caps->max_active_lights = MAX_ACTIVE_LIGHTS;
    caps->max_vertex_blend_matrices = MAX_VERTEX_BLENDS;
    caps->max_vertex_blend_matrix_index = MAX_VERTEX_INDEX_BLENDS - 1;
    caps->vertex_processing_caps = WINED3DVTXPCAPS_TEXGEN
            | WINED3DVTXPCAPS_MATERIALSOURCE7
            | WINED3DVTXPCAPS_VERTEXFOG
            | WINED3DVTXPCAPS_DIRECTIONALLIGHTS
            | WINED3DVTXPCAPS_POSITIONALLIGHTS
            | WINED3DVTXPCAPS_LOCALVIEWER
            | WINED3DVTXPCAPS_TEXGEN_SPHEREMAP;
    caps->fvf_caps = WINED3DFVFCAPS_PSIZE | 8; /* 8 texture coordinates. */
    caps->max_user_clip_planes = gl_info->limits.user_clip_distances;
    caps->raster_caps = WINED3DPRASTERCAPS_FOGRANGE;
}