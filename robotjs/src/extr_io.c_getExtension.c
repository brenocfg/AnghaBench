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

const char *getExtension(const char *fname, size_t len)
{
	if (fname == NULL || len <= 0) return NULL;

	while (--len > 0 && fname[len] != '.' && fname[len] != '\0')
		;

	return fname + len + 1;
}