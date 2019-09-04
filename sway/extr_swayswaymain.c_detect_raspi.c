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
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int getline (char**,size_t*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strstr (char*,char*) ; 

void detect_raspi(void) {
	bool raspi = false;
	FILE *f = fopen("/sys/firmware/devicetree/base/model", "r");
	if (!f) {
		return;
	}
	char *line = NULL;
	size_t line_size = 0;
	while (getline(&line, &line_size, f) != -1) {
		if (strstr(line, "Raspberry Pi")) {
			raspi = true;
			break;
		}
	}
	fclose(f);
	FILE *g = fopen("/proc/modules", "r");
	if (!g) {
		free(line);
		return;
	}
	bool vc4 = false;
	while (getline(&line, &line_size, g) != -1) {
		if (strstr(line, "vc4")) {
			vc4 = true;
			break;
		}
	}
	free(line);
	fclose(g);
	if (!vc4 && raspi) {
		fprintf(stderr, "\x1B[1;31mWarning: You have a "
				"Raspberry Pi, but the vc4 Module is "
				"not loaded! Set 'dtoverlay=vc4-kms-v3d'"
				"in /boot/config.txt and reboot.\x1B[0m\n");
	}
}