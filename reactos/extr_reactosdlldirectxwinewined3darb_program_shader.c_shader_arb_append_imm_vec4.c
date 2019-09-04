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
 int /*<<< orphan*/  shader_addline (struct wined3d_string_buffer*,char*,char*,char*,char*,char*) ; 
 int /*<<< orphan*/  wined3d_ftoa (float const,char*) ; 

__attribute__((used)) static void shader_arb_append_imm_vec4(struct wined3d_string_buffer *buffer, const float *values)
{
    char str[4][17];

    wined3d_ftoa(values[0], str[0]);
    wined3d_ftoa(values[1], str[1]);
    wined3d_ftoa(values[2], str[2]);
    wined3d_ftoa(values[3], str[3]);
    shader_addline(buffer, "{%s, %s, %s, %s}", str[0], str[1], str[2], str[3]);
}