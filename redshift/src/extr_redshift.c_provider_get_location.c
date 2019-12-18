#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pollfd {int fd; int /*<<< orphan*/  events; } ;
typedef  int /*<<< orphan*/  location_t ;
typedef  int /*<<< orphan*/  location_state_t ;
struct TYPE_3__ {int (* get_fd ) (int /*<<< orphan*/ *) ;int (* handle ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ;} ;
typedef  TYPE_1__ location_provider_t ;

/* Variables and functions */
 int /*<<< orphan*/  POLLIN ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  fputs (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int poll (struct pollfd*,int,int) ; 
 int /*<<< orphan*/  stderr ; 
 int stub1 (int /*<<< orphan*/ *) ; 
 int stub2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 int systemtime_get_time (double*) ; 

__attribute__((used)) static int
provider_get_location(
	const location_provider_t *provider, location_state_t *state,
	int timeout, location_t *loc)
{
	int available = 0;
	struct pollfd pollfds[1];
	while (!available) {
		int loc_fd = provider->get_fd(state);
		if (loc_fd >= 0) {
			/* Provider is dynamic. */
			/* TODO: This should use a monotonic time source. */
			double now;
			int r = systemtime_get_time(&now);
			if (r < 0) {
				fputs(_("Unable to read system time.\n"),
				      stderr);
				return -1;
			}

			/* Poll on file descriptor until ready. */
			pollfds[0].fd = loc_fd;
			pollfds[0].events = POLLIN;
			r = poll(pollfds, 1, timeout);
			if (r < 0) {
				perror("poll");
				return -1;
			} else if (r == 0) {
				return 0;
			}

			double later;
			r = systemtime_get_time(&later);
			if (r < 0) {
				fputs(_("Unable to read system time.\n"),
				      stderr);
				return -1;
			}

			/* Adjust timeout by elapsed time */
			if (timeout >= 0) {
				timeout -= (later - now) * 1000;
				timeout = timeout < 0 ? 0 : timeout;
			}
		}


		int r = provider->handle(state, loc, &available);
		if (r < 0) return -1;
	}

	return 1;
}