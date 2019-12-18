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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  SWAY_ERROR ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int getline (char**,size_t*,int /*<<< orphan*/ *) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 scalar_t__ strstr (char*,char*) ; 
 int /*<<< orphan*/  sway_log (int /*<<< orphan*/ ,char*) ; 

void detect_proprietary(int allow_unsupported_gpu) {
	FILE *f = fopen("/proc/modules", "r");
	if (!f) {
		return;
	}
	char *line = NULL;
	size_t line_size = 0;
	while (getline(&line, &line_size, f) != -1) {
		if (strncmp(line, "nvidia ", 7) == 0) {
			if (allow_unsupported_gpu) {
				sway_log(SWAY_ERROR,
						"!!! Proprietary Nvidia drivers are in use !!!");
			} else {
				sway_log(SWAY_ERROR,
					"Proprietary Nvidia drivers are NOT supported. "
					"Use Nouveau. To launch sway anyway, launch with "
					"--my-next-gpu-wont-be-nvidia and DO NOT report issues.");
				exit(EXIT_FAILURE);
			}
			break;
		}
		if (strstr(line, "fglrx")) {
			if (allow_unsupported_gpu) {
				sway_log(SWAY_ERROR,
						"!!! Proprietary AMD drivers are in use !!!");
			} else {
				sway_log(SWAY_ERROR, "Proprietary AMD drivers do NOT support "
					"Wayland. Use radeon. To try anyway, launch sway with "
					"--unsupported-gpu and DO NOT report issues.");
				exit(EXIT_FAILURE);
			}
			break;
		}
	}
	free(line);
	fclose(f);
}