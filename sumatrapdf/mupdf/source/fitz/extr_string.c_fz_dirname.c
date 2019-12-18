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
 int /*<<< orphan*/  fz_strlcpy (char*,char const*,size_t) ; 
 size_t strlen (char*) ; 

void
fz_dirname(char *dir, const char *path, size_t n)
{
	size_t i;

	if (!path || !path[0])
	{
		fz_strlcpy(dir, ".", n);
		return;
	}

	fz_strlcpy(dir, path, n);

	i = strlen(dir);
	for(; dir[i] == '/'; --i) if (!i) { fz_strlcpy(dir, "/", n); return; }
	for(; dir[i] != '/'; --i) if (!i) { fz_strlcpy(dir, ".", n); return; }
	for(; dir[i] == '/'; --i) if (!i) { fz_strlcpy(dir, "/", n); return; }
	dir[i+1] = 0;
}