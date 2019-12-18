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
typedef  int /*<<< orphan*/  sd_event_source ;
typedef  int /*<<< orphan*/  sd_event ;
typedef  int int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 int /*<<< orphan*/  EPOLLIN ; 
 int /*<<< orphan*/ * INT_TO_PTR (char) ; 
 int /*<<< orphan*/  SD_EVENT_ONESHOT ; 
 scalar_t__ SIGRTMIN ; 
 int /*<<< orphan*/  SIG_BLOCK ; 
 int USEC_PER_MSEC ; 
 int /*<<< orphan*/  assert_se (int) ; 
 int do_quit ; 
 int /*<<< orphan*/  exit_handler ; 
 int got_a ; 
 int got_b ; 
 int got_c ; 
 int got_d ; 
 int got_exit ; 
 int got_post ; 
 int got_unref ; 
 int /*<<< orphan*/  io_handler ; 
 scalar_t__ pipe (int*) ; 
 int /*<<< orphan*/  post_handler ; 
 int /*<<< orphan*/  prepare_handler ; 
 int /*<<< orphan*/  safe_close_pair (int*) ; 
 scalar_t__ sd_event_add_exit (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ sd_event_add_io (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ sd_event_add_post (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ sd_event_add_signal (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ sd_event_add_time (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ sd_event_default (int /*<<< orphan*/ **) ; 
 scalar_t__ sd_event_loop (int /*<<< orphan*/ *) ; 
 scalar_t__ sd_event_now (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*) ; 
 int sd_event_run (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ sd_event_set_watchdog (int /*<<< orphan*/ *,int) ; 
 scalar_t__ sd_event_source_get_priority (int /*<<< orphan*/ *,int*) ; 
 scalar_t__ sd_event_source_set_enabled (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ sd_event_source_set_prepare (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ sd_event_source_set_priority (int /*<<< orphan*/ *,int) ; 
 scalar_t__ sd_event_source_set_time (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  sd_event_source_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sd_event_unref (int /*<<< orphan*/ *) ; 
 scalar_t__ sigprocmask_many (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,int) ; 
 int /*<<< orphan*/  time_handler ; 
 int /*<<< orphan*/  unref_handler ; 
 int write (int,char const*,int) ; 

__attribute__((used)) static void test_basic(void) {
        sd_event *e = NULL;
        sd_event_source *w = NULL, *x = NULL, *y = NULL, *z = NULL, *q = NULL, *t = NULL;
        static const char ch = 'x';
        int a[2] = { -1, -1 }, b[2] = { -1, -1}, d[2] = { -1, -1}, k[2] = { -1, -1 };
        uint64_t event_now;
        int64_t priority;

        assert_se(pipe(a) >= 0);
        assert_se(pipe(b) >= 0);
        assert_se(pipe(d) >= 0);
        assert_se(pipe(k) >= 0);

        assert_se(sd_event_default(&e) >= 0);
        assert_se(sd_event_now(e, CLOCK_MONOTONIC, &event_now) > 0);

        assert_se(sd_event_set_watchdog(e, true) >= 0);

        /* Test whether we cleanly can destroy an io event source from its own handler */
        got_unref = false;
        assert_se(sd_event_add_io(e, &t, k[0], EPOLLIN, unref_handler, NULL) >= 0);
        assert_se(write(k[1], &ch, 1) == 1);
        assert_se(sd_event_run(e, (uint64_t) -1) >= 1);
        assert_se(got_unref);

        got_a = false, got_b = false, got_c = false, got_d = 0;

        /* Add a oneshot handler, trigger it, reenable it, and trigger
         * it again. */
        assert_se(sd_event_add_io(e, &w, d[0], EPOLLIN, io_handler, INT_TO_PTR('d')) >= 0);
        assert_se(sd_event_source_set_enabled(w, SD_EVENT_ONESHOT) >= 0);
        assert_se(write(d[1], &ch, 1) >= 0);
        assert_se(sd_event_run(e, (uint64_t) -1) >= 1);
        assert_se(got_d == 1);
        assert_se(write(d[1], &ch, 1) >= 0);
        assert_se(sd_event_run(e, (uint64_t) -1) >= 1);
        assert_se(got_d == 2);

        assert_se(sd_event_add_io(e, &x, a[0], EPOLLIN, io_handler, INT_TO_PTR('a')) >= 0);
        assert_se(sd_event_add_io(e, &y, b[0], EPOLLIN, io_handler, INT_TO_PTR('b')) >= 0);
        assert_se(sd_event_add_time(e, &z, CLOCK_MONOTONIC, 0, 0, time_handler, INT_TO_PTR('c')) >= 0);
        assert_se(sd_event_add_exit(e, &q, exit_handler, INT_TO_PTR('g')) >= 0);

        assert_se(sd_event_source_set_priority(x, 99) >= 0);
        assert_se(sd_event_source_get_priority(x, &priority) >= 0);
        assert_se(priority == 99);
        assert_se(sd_event_source_set_enabled(y, SD_EVENT_ONESHOT) >= 0);
        assert_se(sd_event_source_set_prepare(x, prepare_handler) >= 0);
        assert_se(sd_event_source_set_priority(z, 50) >= 0);
        assert_se(sd_event_source_set_enabled(z, SD_EVENT_ONESHOT) >= 0);
        assert_se(sd_event_source_set_prepare(z, prepare_handler) >= 0);

        /* Test for floating event sources */
        assert_se(sigprocmask_many(SIG_BLOCK, NULL, SIGRTMIN+1, -1) >= 0);
        assert_se(sd_event_add_signal(e, NULL, SIGRTMIN+1, NULL, NULL) >= 0);

        assert_se(write(a[1], &ch, 1) >= 0);
        assert_se(write(b[1], &ch, 1) >= 0);

        assert_se(!got_a && !got_b && !got_c);

        assert_se(sd_event_run(e, (uint64_t) -1) >= 1);

        assert_se(!got_a && got_b && !got_c);

        assert_se(sd_event_run(e, (uint64_t) -1) >= 1);

        assert_se(!got_a && got_b && got_c);

        assert_se(sd_event_run(e, (uint64_t) -1) >= 1);

        assert_se(got_a && got_b && got_c);

        sd_event_source_unref(x);
        sd_event_source_unref(y);

        do_quit = true;
        assert_se(sd_event_add_post(e, NULL, post_handler, NULL) >= 0);
        assert_se(sd_event_now(e, CLOCK_MONOTONIC, &event_now) == 0);
        assert_se(sd_event_source_set_time(z, event_now + 200 * USEC_PER_MSEC) >= 0);
        assert_se(sd_event_source_set_enabled(z, SD_EVENT_ONESHOT) >= 0);

        assert_se(sd_event_loop(e) >= 0);
        assert_se(got_post);
        assert_se(got_exit);

        sd_event_source_unref(z);
        sd_event_source_unref(q);

        sd_event_source_unref(w);

        sd_event_unref(e);

        safe_close_pair(a);
        safe_close_pair(b);
        safe_close_pair(d);
        safe_close_pair(k);
}