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
struct TYPE_3__ {int saved_stdout; int saved_stdin; int /*<<< orphan*/  saved_stdin_attr; int /*<<< orphan*/  saved_stdout_attr; int /*<<< orphan*/  event; void* sigwinch_event_source; void* master_event_source; void* stdout_event_source; void* stdin_event_source; } ;
typedef  TYPE_1__ PTYForward ;

/* Variables and functions */
 int /*<<< orphan*/  STDIN_FILENO ; 
 int /*<<< orphan*/  STDOUT_FILENO ; 
 int /*<<< orphan*/  TCSANOW ; 
 int /*<<< orphan*/  fd_nonblock (int /*<<< orphan*/ ,int) ; 
 void* sd_event_source_unref (void*) ; 
 int /*<<< orphan*/  sd_event_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcsetattr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pty_forward_disconnect(PTYForward *f) {

        if (f) {
                f->stdin_event_source = sd_event_source_unref(f->stdin_event_source);
                f->stdout_event_source = sd_event_source_unref(f->stdout_event_source);

                f->master_event_source = sd_event_source_unref(f->master_event_source);
                f->sigwinch_event_source = sd_event_source_unref(f->sigwinch_event_source);
                f->event = sd_event_unref(f->event);

                if (f->saved_stdout)
                        tcsetattr(STDOUT_FILENO, TCSANOW, &f->saved_stdout_attr);
                if (f->saved_stdin)
                        tcsetattr(STDIN_FILENO, TCSANOW, &f->saved_stdin_attr);

                f->saved_stdout = f->saved_stdin = false;
        }

        /* STDIN/STDOUT should not be nonblocking normally, so let's unconditionally reset it */
        (void) fd_nonblock(STDIN_FILENO, false);
        (void) fd_nonblock(STDOUT_FILENO, false);
}