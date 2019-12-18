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
typedef  int /*<<< orphan*/  time_t ;
struct stat {int /*<<< orphan*/  st_mtime; } ;

/* Variables and functions */
 scalar_t__ stat (char const*,struct stat*) ; 

time_t
stat_mtime(const char *path)
{
	struct stat info;

	if (stat(path, &info) < 0)
		return 0;

	return info.st_mtime;
}