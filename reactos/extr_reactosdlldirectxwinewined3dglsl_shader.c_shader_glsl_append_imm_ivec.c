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
struct wined3d_string_buffer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,unsigned int) ; 
 int /*<<< orphan*/  shader_addline (struct wined3d_string_buffer*,char*,...) ; 

__attribute__((used)) static void shader_glsl_append_imm_ivec(struct wined3d_string_buffer *buffer,
        const int *values, unsigned int size)
{
    int i;

    if (!size || size > 4)
    {
        ERR("Invalid vector size %u.\n", size);
        return;
    }

    if (size > 1)
        shader_addline(buffer, "ivec%u(", size);

    for (i = 0; i < size; ++i)
        shader_addline(buffer, i ? ", %#x" : "%#x", values[i]);

    if (size > 1)
        shader_addline(buffer, ")");
}