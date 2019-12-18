#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char* verb; int sense; } ;
typedef  TYPE_1__ VerbSense ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  workshop_frame_sensitivities (TYPE_1__*) ; 

void workshop_sensitivity(int num, char *table)
{
	/* build up a verb table */
	VerbSense *vs;
	int i;
	char *s;
	if ((num < 1) || (num > 500)) {
		return;
	}

	vs = (VerbSense *)malloc((num+1)*sizeof(VerbSense));

	/* Point to the individual names (destroys the table string, but
	 * that's okay -- this is more efficient than duplicating strings) */
	s = table;
	for (i = 0; i < num; i++) {
		while (*s == ' ') {
			s++;
		}
		vs[i].verb = s;
		while (*s && (*s != ' ') && (*s != '\001')) {
			s++;
		}
		if (*s == 0) {
			vs[i].verb = NULL;
			break;
		}
		if (*s == '\001') {
			*s = 0;
			s++;
		}
		*s = 0;
		s++;
		while (*s == ' ') {
			s++;
		}
		if (*s == '1') {
			vs[i].sense = 1;
		} else {
			vs[i].sense = 0;
		}
		s++;
	}
	vs[i].verb = NULL;

	workshop_frame_sensitivities(vs);

	free(vs);
}