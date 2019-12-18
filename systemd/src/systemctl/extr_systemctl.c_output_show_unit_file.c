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
struct TYPE_4__ {int /*<<< orphan*/  state; int /*<<< orphan*/  path; } ;
typedef  TYPE_1__ UnitFileList ;

/* Variables and functions */
 int /*<<< orphan*/  FNM_NOESCAPE ; 
 char** arg_types ; 
 int /*<<< orphan*/  assert (TYPE_1__ const*) ; 
 int /*<<< orphan*/  basename (int /*<<< orphan*/ ) ; 
 char* strrchr (int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  strv_find (char**,char const*) ; 
 int /*<<< orphan*/  strv_fnmatch_or_empty (char**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strv_isempty (char**) ; 
 char const* unit_file_state_to_string (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool output_show_unit_file(const UnitFileList *u, char **states, char **patterns) {
        assert(u);

        if (!strv_fnmatch_or_empty(patterns, basename(u->path), FNM_NOESCAPE))
                return false;

        if (!strv_isempty(arg_types)) {
                const char *dot;

                dot = strrchr(u->path, '.');
                if (!dot)
                        return false;

                if (!strv_find(arg_types, dot+1))
                        return false;
        }

        if (!strv_isempty(states) &&
            !strv_find(states, unit_file_state_to_string(u->state)))
                return false;

        return true;
}