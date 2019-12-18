#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  gboolean ;
struct TYPE_2__ {int /*<<< orphan*/  sync_extra_temp_file; } ;
typedef  int /*<<< orphan*/  GPatternSpec ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ g_pattern_match_string (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/ ** ignore_patterns ; 
 int /*<<< orphan*/ ** office_temp_ignore_patterns ; 
 TYPE_1__* seaf ; 

__attribute__((used)) static gboolean
is_built_in_ignored_file (const char *filename)
{
    GPatternSpec **spec = ignore_patterns;

    while (*spec) {
        if (g_pattern_match_string(*spec, filename))
            return TRUE;
        spec++;
    }

    if (!seaf->sync_extra_temp_file) {
        spec = office_temp_ignore_patterns;
        while (*spec) {
            if (g_pattern_match_string(*spec, filename))
                return TRUE;
            spec++;
        }
    }

    return FALSE;
}