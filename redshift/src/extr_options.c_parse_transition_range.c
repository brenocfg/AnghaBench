#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int start; int end; } ;
typedef  TYPE_1__ time_range_t ;

/* Variables and functions */
 int parse_transition_time (char const*,char const**) ; 

__attribute__((used)) static int
parse_transition_range(const char *str, time_range_t *range)
{
	const char *next = NULL;
	int start_time = parse_transition_time(str, &next);
	if (start_time < 0) return -1;

	int end_time;
	if (next[0] == '\0') {
		end_time = start_time;
	} else if (next[0] == '-') {
		next += 1;
		const char *end = NULL;
		end_time = parse_transition_time(next, &end);
		if (end_time < 0 || end[0] != '\0') return -1;
	} else {
		return -1;
	}

	range->start = start_time;
	range->end = end_time;

	return 0;
}