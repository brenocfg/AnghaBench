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
 char* find_icon_in_subdir (char*,char*,char*,char*) ; 

char *find_icon_in_dir(char *name, char *dir, int *min_size, int *max_size) {
	char *icon = find_icon_in_subdir(name, dir, "", "");
	if (icon) {
		*min_size = 1;
		*max_size = 512;
	}
	return icon;

}