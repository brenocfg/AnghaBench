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
struct timeval {int tv_usec; } ;
struct input_ctx {int /*<<< orphan*/  timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  event_add (int /*<<< orphan*/ *,struct timeval*) ; 
 int /*<<< orphan*/  event_del (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
input_start_timer(struct input_ctx *ictx)
{
	struct timeval	tv = { .tv_usec = 100000 };

	event_del(&ictx->timer);
	event_add(&ictx->timer, &tv);
}