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
struct args_value {char const* value; } ;

/* Variables and functions */
 struct args_value* TAILQ_NEXT (struct args_value*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  entry ; 

const char *
args_next_value(struct args_value **value)
{
	if (*value == NULL)
		return (NULL);
	*value = TAILQ_NEXT(*value, entry);
	if (*value == NULL)
		return (NULL);
	return ((*value)->value);
}