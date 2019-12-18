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
struct TYPE_2__ {scalar_t__ ga_itemsize; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_current_state () ; 
 int /*<<< orphan*/ * current_next_list ; 
 TYPE_1__ current_state ; 
 int keepend_level ; 

__attribute__((used)) static void
invalidate_current_state()
{
    clear_current_state();
    current_state.ga_itemsize = 0;	/* mark current_state invalid */
    current_next_list = NULL;
    keepend_level = -1;
}