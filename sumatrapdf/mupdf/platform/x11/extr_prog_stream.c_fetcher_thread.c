#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ start_time; scalar_t__ available; scalar_t__ length; scalar_t__ kbps; int /*<<< orphan*/  on_data_arg; int /*<<< orphan*/  (* on_data ) (int /*<<< orphan*/ ,int) ;} ;
typedef  TYPE_1__ prog_state ;
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  Sleep (int) ; 
 scalar_t__ get_current_time () ; 
 int /*<<< orphan*/  lock (TYPE_1__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  unlock (TYPE_1__*) ; 
 int /*<<< orphan*/  usleep (int) ; 

__attribute__((used)) static void fetcher_thread(prog_state *ps)
{
	int complete = 0;

	ps->start_time = get_current_time();

	while (!complete)
	{
		/* Wait a while. */
#ifdef _WIN32
		Sleep(200);
#else
		usleep(200000);
#endif

		lock(ps);

		/* Simulate more data having arrived. */
		if (ps->available < ps->length)
		{
			int64_t av = (get_current_time() - ps->start_time) * ps->kbps;
			if (av > ps->length)
				av = ps->length;
			ps->available = av;
		}
		else
		{
			complete = 1;
		}

		unlock(ps);

		/* Ping callback with new data. */
		if (ps->on_data)
			ps->on_data(ps->on_data_arg, complete);
	}
}