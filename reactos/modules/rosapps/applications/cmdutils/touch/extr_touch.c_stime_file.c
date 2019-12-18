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
struct stat {int /*<<< orphan*/  st_mtime; int /*<<< orphan*/  st_atime; } ;

/* Variables and functions */
 int /*<<< orphan*/  err (int,char*,char*) ; 
 scalar_t__ stat (char*,struct stat*) ; 

void
stime_file(char *fname, time_t *tvp)
{
	struct stat sb;

	if (stat(fname, &sb))
		err(1, "%s", fname);
	tvp[0] = sb.st_atime;
	tvp[1] = sb.st_mtime;
}