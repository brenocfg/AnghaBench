#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ yMax; scalar_t__ xMin; } ;
struct TYPE_6__ {TYPE_1__ bbox; } ;
typedef  TYPE_2__ line_desc_t ;

/* Variables and functions */
 int /*<<< orphan*/  ShiftLine (TYPE_2__*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void MoveLineTo( line_desc_t *p_line, int x, int y )
{
    ShiftLine( p_line, x - p_line->bbox.xMin,
                       y - p_line->bbox.yMax );
}