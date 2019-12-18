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
 int PROMPT_HISTORY ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/ * status_prompt_hlist ; 
 int status_prompt_hsize ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/ * xreallocarray (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  xstrdup (char const*) ; 

__attribute__((used)) static void
status_prompt_add_history(const char *line)
{
	size_t	size;

	if (status_prompt_hsize > 0 &&
	    strcmp(status_prompt_hlist[status_prompt_hsize - 1], line) == 0)
		return;

	if (status_prompt_hsize == PROMPT_HISTORY) {
		free(status_prompt_hlist[0]);

		size = (PROMPT_HISTORY - 1) * sizeof *status_prompt_hlist;
		memmove(&status_prompt_hlist[0], &status_prompt_hlist[1], size);

		status_prompt_hlist[status_prompt_hsize - 1] = xstrdup(line);
		return;
	}

	status_prompt_hlist = xreallocarray(status_prompt_hlist,
	    status_prompt_hsize + 1, sizeof *status_prompt_hlist);
	status_prompt_hlist[status_prompt_hsize++] = xstrdup(line);
}