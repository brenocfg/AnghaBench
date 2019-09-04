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
typedef  int /*<<< orphan*/ * PROC ;
typedef  int /*<<< orphan*/  LPCSTR ;

/* Variables and functions */
 int /*<<< orphan*/  WARN (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _mesa_ColorSubTableEXT ; 
 int /*<<< orphan*/  _mesa_ColorTableEXT ; 
 int /*<<< orphan*/  _mesa_GetColorTableEXT ; 
 int /*<<< orphan*/  _mesa_GetColorTableParameterfvEXT ; 
 int /*<<< orphan*/  _mesa_GetColorTableParameterivEXT ; 
 int /*<<< orphan*/  _swimpl_AddSwapHintRectWIN ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

PROC sw_GetProcAddress(LPCSTR name)
{
    /* GL_EXT_paletted_texture */
    if (strcmp(name, "glColorTableEXT") == 0)
        return (PROC)_mesa_ColorTableEXT;
    if (strcmp(name, "glColorSubTableEXT") == 0)
        return (PROC)_mesa_ColorSubTableEXT;
    if (strcmp(name, "glColorGetTableEXT") == 0)
        return (PROC)_mesa_GetColorTableEXT;
    if (strcmp(name, "glGetColorTableParameterivEXT") == 0)
        return (PROC)_mesa_GetColorTableParameterivEXT;
    if (strcmp(name, "glGetColorTableParameterfvEXT") == 0)
        return (PROC)_mesa_GetColorTableParameterfvEXT;
    if (strcmp(name, "glAddSwapHintRectWIN") == 0)
        return (PROC)_swimpl_AddSwapHintRectWIN;

    WARN("Asking for proc address %s, returning NULL.\n", name);
    return NULL;
}