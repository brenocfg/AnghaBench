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
struct wined3d_texture {TYPE_1__* sub_resources; } ;
struct wined3d_gl_info {int dummy; } ;
struct TYPE_2__ {scalar_t__ buffer_object; } ;
typedef  scalar_t__ GLuint ;

/* Variables and functions */
 int /*<<< orphan*/  GL_EXTCALL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,scalar_t__,struct wined3d_texture*,unsigned int) ; 
 int /*<<< orphan*/  WINED3D_LOCATION_BUFFER ; 
 int /*<<< orphan*/  checkGLcall (char*) ; 
 int /*<<< orphan*/  glDeleteBuffers (int,scalar_t__*) ; 
 int /*<<< orphan*/  wined3d_texture_invalidate_location (struct wined3d_texture*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wined3d_texture_remove_buffer_object(struct wined3d_texture *texture,
        unsigned int sub_resource_idx, const struct wined3d_gl_info *gl_info)
{
    GLuint *buffer_object = &texture->sub_resources[sub_resource_idx].buffer_object;

    GL_EXTCALL(glDeleteBuffers(1, buffer_object));
    checkGLcall("glDeleteBuffers");

    TRACE("Deleted buffer object %u for texture %p, sub-resource %u.\n",
            *buffer_object, texture, sub_resource_idx);

    wined3d_texture_invalidate_location(texture, sub_resource_idx, WINED3D_LOCATION_BUFFER);
    *buffer_object = 0;
}