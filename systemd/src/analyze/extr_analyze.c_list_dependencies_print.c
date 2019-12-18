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
typedef  int /*<<< orphan*/  ts2 ;
typedef  int /*<<< orphan*/  ts ;
struct unit_times {scalar_t__ time; scalar_t__ activating; scalar_t__ activated; } ;
struct boot_times {scalar_t__ userspace_time; } ;

/* Variables and functions */
 int FORMAT_TIMESPAN_MAX ; 
 int /*<<< orphan*/  SPECIAL_GLYPH_TREE_BRANCH ; 
 int /*<<< orphan*/  SPECIAL_GLYPH_TREE_RIGHT ; 
 int /*<<< orphan*/  SPECIAL_GLYPH_TREE_SPACE ; 
 int /*<<< orphan*/  SPECIAL_GLYPH_TREE_VERTICAL ; 
 int /*<<< orphan*/  USEC_PER_MSEC ; 
 char* ansi_highlight_red () ; 
 int /*<<< orphan*/  ansi_normal () ; 
 char* format_timespan (char*,int,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 char* special_glyph (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int list_dependencies_print(
                const char *name,
                unsigned level,
                unsigned branches,
                bool last,
                struct unit_times *times,
                struct boot_times *boot) {

        unsigned i;
        char ts[FORMAT_TIMESPAN_MAX], ts2[FORMAT_TIMESPAN_MAX];

        for (i = level; i != 0; i--)
                printf("%s", special_glyph(branches & (1 << (i-1)) ? SPECIAL_GLYPH_TREE_VERTICAL : SPECIAL_GLYPH_TREE_SPACE));

        printf("%s", special_glyph(last ? SPECIAL_GLYPH_TREE_RIGHT : SPECIAL_GLYPH_TREE_BRANCH));

        if (times) {
                if (times->time > 0)
                        printf("%s%s @%s +%s%s", ansi_highlight_red(), name,
                               format_timespan(ts, sizeof(ts), times->activating - boot->userspace_time, USEC_PER_MSEC),
                               format_timespan(ts2, sizeof(ts2), times->time, USEC_PER_MSEC), ansi_normal());
                else if (times->activated > boot->userspace_time)
                        printf("%s @%s", name, format_timespan(ts, sizeof(ts), times->activated - boot->userspace_time, USEC_PER_MSEC));
                else
                        printf("%s", name);
        } else
                printf("%s", name);
        printf("\n");

        return 0;
}