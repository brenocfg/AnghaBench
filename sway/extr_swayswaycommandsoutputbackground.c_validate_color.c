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
 int strlen (char const*) ; 
 int /*<<< orphan*/  strtol (char const*,char**,int) ; 

__attribute__((used)) static bool validate_color(const char *color) {
	if (strlen(color) != 7 || color[0] != '#') {
		return false;
	}

	char *ptr = NULL;
	strtol(&color[1], &ptr, 16);
	return *ptr == '\0';
}