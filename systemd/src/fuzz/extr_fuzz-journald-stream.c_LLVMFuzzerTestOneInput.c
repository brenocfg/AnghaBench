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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  scalar_t__ ssize_t ;
struct TYPE_5__ {scalar_t__ n_stdout_streams; int /*<<< orphan*/  event; } ;
typedef  int /*<<< orphan*/  StdoutStream ;
typedef  TYPE_1__ Server ;

/* Variables and functions */
 int /*<<< orphan*/  AF_UNIX ; 
 int /*<<< orphan*/  LOG_CRIT ; 
 int /*<<< orphan*/  SIOCINQ ; 
 int SOCK_CLOEXEC ; 
 int SOCK_NONBLOCK ; 
 int SOCK_STREAM ; 
 int /*<<< orphan*/  assert_se (int) ; 
 int /*<<< orphan*/  dummy_server_init (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getenv (char*) ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  log_set_max_level (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  safe_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_event_run (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  server_done (TYPE_1__*) ; 
 scalar_t__ socketpair (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stdout_stream_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ stdout_stream_install (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * stream_fds ; 
 scalar_t__ write (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,size_t) ; 

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
        Server s;
        StdoutStream *stream;
        int v;

        if (size == 0 || size > 65536)
                return 0;

        if (!getenv("SYSTEMD_LOG_LEVEL"))
                log_set_max_level(LOG_CRIT);

        assert_se(socketpair(AF_UNIX, SOCK_STREAM|SOCK_CLOEXEC|SOCK_NONBLOCK, 0, stream_fds) >= 0);
        dummy_server_init(&s, NULL, 0);
        assert_se(stdout_stream_install(&s, stream_fds[0], &stream) >= 0);
        assert_se(write(stream_fds[1], data, size) == (ssize_t) size);
        while (ioctl(stream_fds[0], SIOCINQ, &v) == 0 && v)
                sd_event_run(s.event, (uint64_t) -1);
        if (s.n_stdout_streams)
                stdout_stream_destroy(stream);
        server_done(&s);
        stream_fds[1] = safe_close(stream_fds[1]);

        return 0;
}