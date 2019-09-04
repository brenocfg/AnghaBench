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
struct wined3d_vec4 {float x; float y; float z; float w; } ;
struct wined3d_gl_info {int dummy; } ;
typedef  int GLint ;
typedef  float GLfloat ;

/* Variables and functions */
 int /*<<< orphan*/  GL_EXTCALL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glUniform4fv (int,int,float*) ; 

__attribute__((used)) static inline void apply_clamped_constant(const struct wined3d_gl_info *gl_info,
        GLint location, const struct wined3d_vec4 *data)
{
    GLfloat clamped_constant[4];

    if (location == -1) return;

    clamped_constant[0] = data->x < -1.0f ? -1.0f : data->x > 1.0f ? 1.0f : data->x;
    clamped_constant[1] = data->y < -1.0f ? -1.0f : data->y > 1.0f ? 1.0f : data->y;
    clamped_constant[2] = data->z < -1.0f ? -1.0f : data->z > 1.0f ? 1.0f : data->z;
    clamped_constant[3] = data->w < -1.0f ? -1.0f : data->w > 1.0f ? 1.0f : data->w;

    GL_EXTCALL(glUniform4fv(location, 1, clamped_constant));
}