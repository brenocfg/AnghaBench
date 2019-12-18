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
struct stat {int /*<<< orphan*/  st_mtime; int /*<<< orphan*/  st_ctime; int /*<<< orphan*/  st_atime; } ;

/* Variables and functions */
#define  ST_ATIME 130 
#define  ST_CTIME 129 
#define  ST_MTIME 128 
 int stat (char const*,struct stat*) ; 

__attribute__((used)) static int
get_file_time(const char *pfile, int what, time_t *ptr)
{
	struct stat stat_buf;

	if (pfile == NULL || ptr == NULL) {
		return (-1);
	}

	if (stat(pfile, &stat_buf) == -1) {
		return (-1);
	}

	switch (what) {
		case ST_ATIME:
			*ptr = stat_buf.st_atime;
			return (0);
		case ST_CTIME:
			*ptr = stat_buf.st_ctime;
			return (0);
		case ST_MTIME:
			*ptr = stat_buf.st_mtime;
			return (0);
		default:
			return (-1);
	}
}