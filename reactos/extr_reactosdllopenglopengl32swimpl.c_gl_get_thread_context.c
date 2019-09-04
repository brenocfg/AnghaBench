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
struct sw_context {int /*<<< orphan*/ * gl_ctx; } ;
typedef  int /*<<< orphan*/  GLcontext ;

/* Variables and functions */
 scalar_t__ IntGetCurrentDHGLRC () ; 

GLcontext* gl_get_thread_context(void)
{
    struct sw_context* sw_ctx = (struct sw_context*)IntGetCurrentDHGLRC();
    return sw_ctx->gl_ctx;
}