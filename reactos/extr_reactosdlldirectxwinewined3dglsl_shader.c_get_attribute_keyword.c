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
struct wined3d_gl_info {int dummy; } ;

/* Variables and functions */
 scalar_t__ needs_legacy_glsl_syntax (struct wined3d_gl_info const*) ; 

__attribute__((used)) static const char *get_attribute_keyword(const struct wined3d_gl_info *gl_info)
{
    return needs_legacy_glsl_syntax(gl_info) ? "attribute" : "in";
}