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
struct TYPE_6__ {int input; int /*<<< orphan*/  input_event; int /*<<< orphan*/  events; } ;
typedef  TYPE_1__ Uploader ;

/* Variables and functions */
 int EPERM ; 
 int /*<<< orphan*/  EPOLLIN ; 
 int O_CLOEXEC ; 
 int O_NOCTTY ; 
 int O_RDONLY ; 
 int STDIN_FILENO ; 
 scalar_t__ arg_follow ; 
 int /*<<< orphan*/  dispatch_fd_input ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fd_input_callback ; 
 int log_error_errno (int,char*,...) ; 
 int open (char const*,int) ; 
 int sd_event_add_io (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int start_upload (TYPE_1__*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ streq (char const*,char*) ; 

__attribute__((used)) static int open_file_for_upload(Uploader *u, const char *filename) {
        int fd, r = 0;

        if (streq(filename, "-"))
                fd = STDIN_FILENO;
        else {
                fd = open(filename, O_RDONLY|O_CLOEXEC|O_NOCTTY);
                if (fd < 0)
                        return log_error_errno(errno, "Failed to open %s: %m", filename);
        }

        u->input = fd;

        if (arg_follow) {
                r = sd_event_add_io(u->events, &u->input_event,
                                    fd, EPOLLIN, dispatch_fd_input, u);
                if (r < 0) {
                        if (r != -EPERM || arg_follow > 0)
                                return log_error_errno(r, "Failed to register input event: %m");

                        /* Normal files should just be consumed without polling. */
                        r = start_upload(u, fd_input_callback, u);
                }
        }

        return r;
}