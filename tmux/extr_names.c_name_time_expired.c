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
struct window {int /*<<< orphan*/  name_time; } ;
struct timeval {scalar_t__ tv_sec; scalar_t__ tv_usec; } ;

/* Variables and functions */
 scalar_t__ NAME_INTERVAL ; 
 int /*<<< orphan*/  timersub (struct timeval*,int /*<<< orphan*/ *,struct timeval*) ; 

__attribute__((used)) static int
name_time_expired(struct window *w, struct timeval *tv)
{
	struct timeval	offset;

	timersub(tv, &w->name_time, &offset);
	if (offset.tv_sec != 0 || offset.tv_usec > NAME_INTERVAL)
		return (0);
	return (NAME_INTERVAL - offset.tv_usec);
}