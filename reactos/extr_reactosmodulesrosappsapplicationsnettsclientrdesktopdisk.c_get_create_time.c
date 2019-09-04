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
typedef  scalar_t__ time_t ;
struct stat {scalar_t__ st_ctime; int /*<<< orphan*/  st_atime; int /*<<< orphan*/  st_mtime; } ;

/* Variables and functions */
 scalar_t__ MIN (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static time_t
get_create_time(struct stat *st)
{
	time_t ret, ret1;

	ret = MIN(st->st_ctime, st->st_mtime);
	ret1 = MIN(ret, st->st_atime);

	if (ret1 != (time_t) 0)
		return ret1;

	return ret;
}