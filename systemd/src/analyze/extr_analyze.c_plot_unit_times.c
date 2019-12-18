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
typedef  int /*<<< orphan*/  ts ;
struct unit_times {double activating; double activated; double deactivating; double deactivated; int /*<<< orphan*/  name; int /*<<< orphan*/  time; } ;

/* Variables and functions */
 int FORMAT_TIMESPAN_MAX ; 
 double SCALE_X ; 
 int /*<<< orphan*/  USEC_PER_MSEC ; 
 int /*<<< orphan*/  format_timespan (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svg_bar (char*,double,double,int) ; 
 int /*<<< orphan*/  svg_text (int,double,int,char*,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static int plot_unit_times(struct unit_times *u, double width, int y) {
        char ts[FORMAT_TIMESPAN_MAX];
        bool b;

        if (!u->name)
                return 0;

        svg_bar("activating",   u->activating, u->activated, y);
        svg_bar("active",       u->activated, u->deactivating, y);
        svg_bar("deactivating", u->deactivating, u->deactivated, y);

        /* place the text on the left if we have passed the half of the svg width */
        b = u->activating * SCALE_X < width / 2;
        if (u->time)
                svg_text(b, u->activating, y, "%s (%s)",
                         u->name, format_timespan(ts, sizeof(ts), u->time, USEC_PER_MSEC));
        else
                svg_text(b, u->activating, y, "%s", u->name);

        return 1;
}