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
 int /*<<< orphan*/ * future ; 
 int future_count ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int nelem (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  save_mark () ; 

__attribute__((used)) static void push_future(void)
{
	if (future_count + 1 >= (int)nelem(future))
	{
		memmove(future, future + 1, sizeof *future * (nelem(future) - 1));
		future[future_count] = save_mark();
	}
	else
	{
		future[future_count++] = save_mark();
	}
}