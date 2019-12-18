#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  scalar_t__ ssize_t ;
struct TYPE_6__ {scalar_t__ log_message; scalar_t__ log_message_size; int /*<<< orphan*/  log_event_source; } ;
typedef  TYPE_1__ sd_event_source ;
typedef  TYPE_1__ Transfer ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  log_error_errno (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ read (int,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  sd_event_source_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  transfer_send_logs (TYPE_1__*,int) ; 

__attribute__((used)) static int transfer_on_log(sd_event_source *s, int fd, uint32_t revents, void *userdata) {
        Transfer *t = userdata;
        ssize_t l;

        assert(s);
        assert(t);

        l = read(fd, t->log_message + t->log_message_size, sizeof(t->log_message) - t->log_message_size);
        if (l < 0)
                log_error_errno(errno, "Failed to read log message: %m");
        if (l <= 0) {
                /* EOF/read error. We just close the pipe here, and
                 * close the watch, waiting for the SIGCHLD to arrive,
                 * before we do anything else. */
                t->log_event_source = sd_event_source_unref(t->log_event_source);
                return 0;
        }

        t->log_message_size += l;

        transfer_send_logs(t, false);

        return 0;
}