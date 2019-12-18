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
typedef  int /*<<< orphan*/  Unit ;

/* Variables and functions */
 int /*<<< orphan*/  unit_log_failure (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  unit_log_success (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void unit_log_result(Unit *u, bool success, const char *result) {
        if (success)
                unit_log_success(u);
        else
                unit_log_failure(u, result);
}