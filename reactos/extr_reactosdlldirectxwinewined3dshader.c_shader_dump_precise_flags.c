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
typedef  int DWORD ;

/* Variables and functions */
 int WINED3DSI_PRECISE_W ; 
 int WINED3DSI_PRECISE_X ; 
 int WINED3DSI_PRECISE_XYZW ; 
 int WINED3DSI_PRECISE_Y ; 
 int WINED3DSI_PRECISE_Z ; 
 int /*<<< orphan*/  shader_addline (struct wined3d_string_buffer*,char*,...) ; 

__attribute__((used)) static void shader_dump_precise_flags(struct wined3d_string_buffer *buffer, DWORD flags)
{
    if (!(flags & WINED3DSI_PRECISE_XYZW))
        return;

    shader_addline(buffer, " [precise");
    if (flags != WINED3DSI_PRECISE_XYZW)
    {
        shader_addline(buffer, "(%s%s%s%s)",
                flags & WINED3DSI_PRECISE_X ? "x" : "",
                flags & WINED3DSI_PRECISE_Y ? "y" : "",
                flags & WINED3DSI_PRECISE_Z ? "z" : "",
                flags & WINED3DSI_PRECISE_W ? "w" : "");
    }
    shader_addline(buffer, "]");
}