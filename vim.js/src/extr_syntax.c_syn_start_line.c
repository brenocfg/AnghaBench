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
struct TYPE_2__ {scalar_t__ ga_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  check_state_ends () ; 
 scalar_t__ current_col ; 
 int /*<<< orphan*/  current_finished ; 
 int /*<<< orphan*/  current_line_id ; 
 TYPE_1__ current_state ; 
 int next_match_idx ; 
 int /*<<< orphan*/  syn_update_ends (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
syn_start_line()
{
    current_finished = FALSE;
    current_col = 0;

    /*
     * Need to update the end of a start/skip/end that continues from the
     * previous line and regions that have "keepend".
     */
    if (current_state.ga_len > 0)
    {
	syn_update_ends(TRUE);
	check_state_ends();
    }

    next_match_idx = -1;
    ++current_line_id;
}