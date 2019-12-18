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

/* Variables and functions */
 int drop_caches () ; 
 scalar_t__ dropcaches ; 
 int run_process (char*,char**) ; 
 char* script ; 
 int /*<<< orphan*/  sync () ; 
 scalar_t__ synccaches ; 

__attribute__((used)) static int
post_hook(char *phase)
{
	char *argv[3] = { script, phase, (char *)0 };
	int rc;

	if (synccaches)
		sync();

	if (dropcaches) {
		rc = drop_caches();
		if (rc)
			return (rc);
	}

	rc = run_process(script, argv);
	if (rc)
		return (rc);

	return (0);
}