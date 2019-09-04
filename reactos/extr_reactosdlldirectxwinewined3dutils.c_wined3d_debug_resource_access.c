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
struct debug_buffer {int /*<<< orphan*/  str; } ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  FIXME (char*,int) ; 
 int WINED3D_RESOURCE_ACCESS_CPU ; 
 int WINED3D_RESOURCE_ACCESS_GPU ; 
 int WINED3D_RESOURCE_ACCESS_MAP_R ; 
 int WINED3D_RESOURCE_ACCESS_MAP_W ; 
 int /*<<< orphan*/  debug_append (struct debug_buffer*,char*,char*) ; 
 int /*<<< orphan*/  init_debug_buffer (struct debug_buffer*,char*) ; 
 char const* wine_dbg_sprintf (char*,int /*<<< orphan*/ ) ; 

const char *wined3d_debug_resource_access(DWORD access)
{
    struct debug_buffer buffer;

    init_debug_buffer(&buffer, "0");
#define ACCESS_TO_STR(x) if (access & x) { debug_append(&buffer, #x, " | "); access &= ~x; }
    ACCESS_TO_STR(WINED3D_RESOURCE_ACCESS_GPU);
    ACCESS_TO_STR(WINED3D_RESOURCE_ACCESS_CPU);
    ACCESS_TO_STR(WINED3D_RESOURCE_ACCESS_MAP_R);
    ACCESS_TO_STR(WINED3D_RESOURCE_ACCESS_MAP_W);
#undef ACCESS_TO_STR
    if (access)
        FIXME("Unrecognised access flag(s) %#x.\n", access);

    return wine_dbg_sprintf("%s", buffer.str);
}