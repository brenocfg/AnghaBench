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
struct TYPE_2__ {int usage; } ;
struct wined3d_texture {unsigned int level_count; int /*<<< orphan*/  const target; TYPE_1__ resource; } ;
typedef  int /*<<< orphan*/  const GLenum ;

/* Variables and functions */
#define  GL_TEXTURE_CUBE_MAP_NEGATIVE_X_ARB 133 
#define  GL_TEXTURE_CUBE_MAP_NEGATIVE_Y_ARB 132 
#define  GL_TEXTURE_CUBE_MAP_NEGATIVE_Z_ARB 131 
#define  GL_TEXTURE_CUBE_MAP_POSITIVE_X_ARB 130 
#define  GL_TEXTURE_CUBE_MAP_POSITIVE_Y_ARB 129 
#define  GL_TEXTURE_CUBE_MAP_POSITIVE_Z_ARB 128 
 int WINED3DUSAGE_LEGACY_CUBEMAP ; 

__attribute__((used)) static inline GLenum wined3d_texture_get_sub_resource_target(const struct wined3d_texture *texture,
        unsigned int sub_resource_idx)
{
    static const GLenum cube_targets[] =
    {
        GL_TEXTURE_CUBE_MAP_POSITIVE_X_ARB,
        GL_TEXTURE_CUBE_MAP_NEGATIVE_X_ARB,
        GL_TEXTURE_CUBE_MAP_POSITIVE_Y_ARB,
        GL_TEXTURE_CUBE_MAP_NEGATIVE_Y_ARB,
        GL_TEXTURE_CUBE_MAP_POSITIVE_Z_ARB,
        GL_TEXTURE_CUBE_MAP_NEGATIVE_Z_ARB,
    };

    return texture->resource.usage & WINED3DUSAGE_LEGACY_CUBEMAP
            ? cube_targets[sub_resource_idx / texture->level_count] : texture->target;
}