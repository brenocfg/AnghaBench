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
struct TYPE_4__ {int yMin; int yMax; int xMin; int xMax; } ;
struct TYPE_5__ {int i_character_count; int i_base_line; TYPE_1__ bbox; int /*<<< orphan*/ * p_character; } ;
typedef  TYPE_2__ line_desc_t ;

/* Variables and functions */
 int /*<<< orphan*/  ShiftChar (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void ShiftLine( line_desc_t *p_line, int x, int y )
{
    for( int i=0; i<p_line->i_character_count; i++ )
        ShiftChar( &p_line->p_character[i], x, y );
    p_line->i_base_line += y;
    p_line->bbox.yMin += y;
    p_line->bbox.yMax += y;
    p_line->bbox.xMin += x;
    p_line->bbox.xMax += x;
}