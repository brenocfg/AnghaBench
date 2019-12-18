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
typedef  int /*<<< orphan*/  vlc_gl_t ;
typedef  int /*<<< orphan*/  GLubyte ;

/* Variables and functions */
 void* glXGetProcAddressARB (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void *GetSymbol(vlc_gl_t *gl, const char *procname)
{
    (void) gl;
    return glXGetProcAddressARB ((const GLubyte *)procname);
}