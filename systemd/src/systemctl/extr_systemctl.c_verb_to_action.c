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
typedef  enum action { ____Placeholder_action } action ;
struct TYPE_2__ {int /*<<< orphan*/  verb; } ;

/* Variables and functions */
 int _ACTION_INVALID ; 
 int _ACTION_MAX ; 
 TYPE_1__* action_table ; 
 scalar_t__ streq_ptr (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static enum action verb_to_action(const char *verb) {
        enum action i;

        for (i = 0; i < _ACTION_MAX; i++)
                if (streq_ptr(action_table[i].verb, verb))
                        return i;

        return _ACTION_INVALID;
}