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
struct color_fixup_desc {scalar_t__ w_sign_fixup; int /*<<< orphan*/  w_source; scalar_t__ z_sign_fixup; int /*<<< orphan*/  z_source; scalar_t__ y_sign_fixup; int /*<<< orphan*/  y_source; scalar_t__ x_sign_fixup; int /*<<< orphan*/  x_source; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  debug_complex_fixup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug_fixup_channel_source (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_complex_fixup (struct color_fixup_desc) ; 
 scalar_t__ is_complex_fixup (struct color_fixup_desc) ; 

void dump_color_fixup_desc(struct color_fixup_desc fixup)
{
    if (is_complex_fixup(fixup))
    {
        TRACE("\tComplex: %s\n", debug_complex_fixup(get_complex_fixup(fixup)));
        return;
    }

    TRACE("\tX: %s%s\n", debug_fixup_channel_source(fixup.x_source), fixup.x_sign_fixup ? ", SIGN_FIXUP" : "");
    TRACE("\tY: %s%s\n", debug_fixup_channel_source(fixup.y_source), fixup.y_sign_fixup ? ", SIGN_FIXUP" : "");
    TRACE("\tZ: %s%s\n", debug_fixup_channel_source(fixup.z_source), fixup.z_sign_fixup ? ", SIGN_FIXUP" : "");
    TRACE("\tW: %s%s\n", debug_fixup_channel_source(fixup.w_source), fixup.w_sign_fixup ? ", SIGN_FIXUP" : "");
}