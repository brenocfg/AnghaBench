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
typedef  scalar_t__ uint64_t ;
struct timespec {int tv_nsec; scalar_t__ tv_sec; } ;
struct pollfd {int /*<<< orphan*/  events; int /*<<< orphan*/  fd; } ;
typedef  int /*<<< orphan*/  sd_journal ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 int /*<<< orphan*/  clock_gettime (int /*<<< orphan*/ ,struct timespec*) ; 
 int /*<<< orphan*/  poll (struct pollfd*,int,int) ; 
 int /*<<< orphan*/  sd_journal_get_events (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sd_journal_get_fd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sd_journal_get_timeout (int /*<<< orphan*/ *,scalar_t__*) ; 
 int sd_journal_process (int /*<<< orphan*/ *) ; 

int wait_for_changes(sd_journal *j) {
  uint64_t t;
  int msec;
  struct pollfd pollfd;

  sd_journal_get_timeout(j, &t);
  if (t == (uint64_t) -1)
    msec = -1;
  else {
    struct timespec ts;
    uint64_t n;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    n = (uint64_t) ts.tv_sec * 1000000 + ts.tv_nsec / 1000;
    msec = t > n ? (int) ((t - n + 999) / 1000) : 0;
  }

  pollfd.fd = sd_journal_get_fd(j);
  pollfd.events = sd_journal_get_events(j);
  poll(&pollfd, 1, msec);
  return sd_journal_process(j);
}