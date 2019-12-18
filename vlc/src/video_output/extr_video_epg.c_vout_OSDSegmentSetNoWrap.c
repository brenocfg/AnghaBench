#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* style; struct TYPE_5__* p_next; } ;
typedef  TYPE_2__ text_segment_t ;
struct TYPE_4__ {int /*<<< orphan*/  i_features; int /*<<< orphan*/  e_wrapinfo; } ;

/* Variables and functions */
 int /*<<< orphan*/  STYLE_HAS_WRAP_INFO ; 
 int /*<<< orphan*/  STYLE_WRAP_NONE ; 

__attribute__((used)) static void vout_OSDSegmentSetNoWrap(text_segment_t *p_segment)
{
    for( ; p_segment; p_segment = p_segment->p_next )
    {
        p_segment->style->e_wrapinfo = STYLE_WRAP_NONE;
        p_segment->style->i_features |= STYLE_HAS_WRAP_INFO;
    }
}