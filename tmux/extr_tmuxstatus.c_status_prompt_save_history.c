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
typedef  size_t u_int ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fputc (char,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fputs (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  log_debug (char*,char*,...) ; 
 char* status_prompt_find_history_file () ; 
 int /*<<< orphan*/ * status_prompt_hlist ; 
 size_t status_prompt_hsize ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

void
status_prompt_save_history(void)
{
	FILE	*f;
	u_int	 i;
	char	*history_file;

	if ((history_file = status_prompt_find_history_file()) == NULL)
		return;
	log_debug("saving history to %s", history_file);

	f = fopen(history_file, "w");
	if (f == NULL) {
		log_debug("%s: %s", history_file, strerror(errno));
		free(history_file);
		return;
	}
	free(history_file);

	for (i = 0; i < status_prompt_hsize; i++) {
		fputs(status_prompt_hlist[i], f);
		fputc('\n', f);
	}
	fclose(f);

}