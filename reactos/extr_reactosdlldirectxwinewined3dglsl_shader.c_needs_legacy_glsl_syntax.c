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
struct wined3d_gl_info {scalar_t__ glsl_version; } ;
typedef  int BOOL ;

/* Variables and functions */
 scalar_t__ MAKEDWORD_VERSION (int,int) ; 

__attribute__((used)) static BOOL needs_legacy_glsl_syntax(const struct wined3d_gl_info *gl_info)
{
    return gl_info->glsl_version < MAKEDWORD_VERSION(1, 30);
}