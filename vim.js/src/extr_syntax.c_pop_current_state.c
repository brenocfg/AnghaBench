#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  si_extmatch; } ;
struct TYPE_3__ {int ga_len; } ;

/* Variables and functions */
 TYPE_2__ CUR_STATE (int) ; 
 TYPE_1__ current_state ; 
 int keepend_level ; 
 int next_match_idx ; 
 int /*<<< orphan*/  unref_extmatch (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pop_current_state()
{
    if (current_state.ga_len)
    {
	unref_extmatch(CUR_STATE(current_state.ga_len - 1).si_extmatch);
	--current_state.ga_len;
    }
    /* after the end of a pattern, try matching a keyword or pattern */
    next_match_idx = -1;

    /* if first state with "keepend" is popped, reset keepend_level */
    if (keepend_level >= current_state.ga_len)
	keepend_level = -1;
}