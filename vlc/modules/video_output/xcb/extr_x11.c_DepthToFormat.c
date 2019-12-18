#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  visual_id; } ;
typedef  TYPE_1__ xcb_visualtype_t ;
typedef  int /*<<< orphan*/  xcb_visualid_t ;
typedef  int /*<<< orphan*/  xcb_setup_t ;
struct TYPE_9__ {int /*<<< orphan*/  depth; } ;
typedef  TYPE_2__ xcb_depth_t ;
typedef  int /*<<< orphan*/  video_format_t ;

/* Variables and functions */
 scalar_t__ vlc_xcb_VisualToFormat (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,TYPE_1__ const*,int /*<<< orphan*/ *) ; 
 TYPE_1__* xcb_depth_visuals (TYPE_2__ const*) ; 
 int xcb_depth_visuals_length (TYPE_2__ const*) ; 

__attribute__((used)) static xcb_visualid_t DepthToFormat(const xcb_setup_t *setup,
                                    const xcb_depth_t *depth,
                                    video_format_t *restrict f)
{
    /* Check visual types for the selected depth */
    const xcb_visualtype_t *vt = xcb_depth_visuals(depth);

    for (int i = xcb_depth_visuals_length(depth); i > 0; i--, vt++)
        if (vlc_xcb_VisualToFormat(setup, depth->depth, vt, f))
            return vt->visual_id;

    return 0;
}