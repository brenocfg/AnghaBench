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
struct TYPE_5__ {TYPE_1__ bbox; int /*<<< orphan*/  p_outline; int /*<<< orphan*/  p_shadow; int /*<<< orphan*/  p_glyph; } ;
typedef  TYPE_2__ line_character_t ;

/* Variables and functions */
 int /*<<< orphan*/  ShiftGlyph (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void ShiftChar( line_character_t *c, int x, int y )
{
    ShiftGlyph( c->p_glyph, x, y );
    ShiftGlyph( c->p_shadow, x, y );
    ShiftGlyph( c->p_outline, x, y );
    c->bbox.yMin += y;
    c->bbox.yMax += y;
    c->bbox.xMin += x;
    c->bbox.xMax += x;
}