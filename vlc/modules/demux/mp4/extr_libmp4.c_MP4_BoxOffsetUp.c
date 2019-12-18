#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_3__ {struct TYPE_3__* p_next; struct TYPE_3__* p_first; int /*<<< orphan*/  i_pos; } ;
typedef  TYPE_1__ MP4_Box_t ;

/* Variables and functions */

__attribute__((used)) static void MP4_BoxOffsetUp( MP4_Box_t *p_box, uint64_t i_offset )
{
    while(p_box)
    {
        p_box->i_pos += i_offset;
        MP4_BoxOffsetUp( p_box->p_first, i_offset );
        p_box = p_box->p_next;
    }
}