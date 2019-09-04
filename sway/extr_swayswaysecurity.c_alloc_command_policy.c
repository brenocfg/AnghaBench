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
struct command_policy {scalar_t__ context; int /*<<< orphan*/  command; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct command_policy*) ; 
 struct command_policy* malloc (int) ; 
 int /*<<< orphan*/  strdup (char const*) ; 

struct command_policy *alloc_command_policy(const char *command) {
	struct command_policy *policy = malloc(sizeof(struct command_policy));
	if (!policy) {
		return NULL;
	}
	policy->command = strdup(command);
	if (!policy->command) {
		free(policy);
		return NULL;
	}
	policy->context = 0;
	return policy;
}