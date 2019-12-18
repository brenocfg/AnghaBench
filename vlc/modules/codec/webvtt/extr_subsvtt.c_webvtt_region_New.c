#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {double f_width; double anchor_y; int i_lines_max_scroll; double viewport_anchor_y; int b_scroll_up; int /*<<< orphan*/ * p_child; int /*<<< orphan*/ * p_cssstyle; scalar_t__ viewport_anchor_x; scalar_t__ anchor_x; int /*<<< orphan*/ * p_next; int /*<<< orphan*/ * psz_id; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ webvtt_region_t ;

/* Variables and functions */
 int /*<<< orphan*/  NODE_REGION ; 
 TYPE_1__* malloc (int) ; 

__attribute__((used)) static webvtt_region_t * webvtt_region_New( void )
{
    webvtt_region_t *p_region = malloc(sizeof(*p_region));
    if( p_region )
    {
        p_region->type = NODE_REGION;
        p_region->psz_id = NULL;
        p_region->p_next = NULL;
        p_region->f_width = 1.0; /* 100% */
        p_region->anchor_x = 0;
        p_region->anchor_y = 1.0; /* 100% */
        p_region->i_lines_max_scroll = 3;
        p_region->viewport_anchor_x = 0;
        p_region->viewport_anchor_y = 1.0; /* 100% */
        p_region->b_scroll_up = false;
        p_region->p_cssstyle = NULL;
        p_region->p_child = NULL;
    }
    return p_region;
}