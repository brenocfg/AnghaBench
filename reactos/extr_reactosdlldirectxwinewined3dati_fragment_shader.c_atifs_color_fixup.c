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
struct color_fixup_desc {int dummy; } ;
typedef  int /*<<< orphan*/  GLuint ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*) ; 
 int GL_2X_BIT_ATI ; 
 int GL_ALPHA ; 
 int GL_BIAS_BIT_ATI ; 
 int GL_BLUE_BIT_ATI ; 
 int GL_GREEN_BIT_ATI ; 
 int /*<<< orphan*/  GL_MOV_ATI ; 
 int GL_NONE ; 
 int /*<<< orphan*/  GL_ONE ; 
 int GL_RED_BIT_ATI ; 
 int /*<<< orphan*/  color_fixup_rg ; 
 int /*<<< orphan*/  color_fixup_rgba ; 
 int /*<<< orphan*/  color_fixup_rgl ; 
 scalar_t__ is_same_fixup (struct color_fixup_desc,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wrap_op1 (struct wined3d_gl_info const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void atifs_color_fixup(const struct wined3d_gl_info *gl_info, struct color_fixup_desc fixup, GLuint reg)
{
    if(is_same_fixup(fixup, color_fixup_rg))
    {
        wrap_op1(gl_info, GL_MOV_ATI, reg, GL_RED_BIT_ATI | GL_GREEN_BIT_ATI, GL_NONE,
                reg, GL_NONE, GL_2X_BIT_ATI | GL_BIAS_BIT_ATI);
        wrap_op1(gl_info, GL_MOV_ATI, reg, GL_BLUE_BIT_ATI, GL_NONE,
                GL_ONE, GL_NONE, GL_NONE);
        wrap_op1(gl_info, GL_MOV_ATI, reg, GL_ALPHA, GL_NONE,
                GL_ONE, GL_NONE, GL_NONE);
    }
    else if(is_same_fixup(fixup, color_fixup_rgl))
    {
        wrap_op1(gl_info, GL_MOV_ATI, reg, GL_RED_BIT_ATI | GL_GREEN_BIT_ATI, GL_NONE,
                reg, GL_NONE, GL_2X_BIT_ATI | GL_BIAS_BIT_ATI);
    }
    else if (is_same_fixup(fixup, color_fixup_rgba))
    {
        wrap_op1(gl_info, GL_MOV_ATI, reg, GL_NONE, GL_NONE,
                reg, GL_NONE, GL_2X_BIT_ATI | GL_BIAS_BIT_ATI);
        wrap_op1(gl_info, GL_MOV_ATI, reg, GL_ALPHA, GL_NONE,
                reg, GL_NONE, GL_2X_BIT_ATI | GL_BIAS_BIT_ATI);
    }
    else
    {
        /* Should not happen - atifs_color_fixup_supported refuses other fixups. */
        ERR("Unsupported color fixup.\n");
    }
}