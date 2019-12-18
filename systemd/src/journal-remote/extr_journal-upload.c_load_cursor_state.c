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
struct TYPE_3__ {int /*<<< orphan*/  last_cursor; int /*<<< orphan*/  state_file; } ;
typedef  TYPE_1__ Uploader ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  log_debug (char*,int /*<<< orphan*/ ) ; 
 int log_error_errno (int,char*,int /*<<< orphan*/ ) ; 
 int parse_env_file (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int load_cursor_state(Uploader *u) {
        int r;

        if (!u->state_file)
                return 0;

        r = parse_env_file(NULL, u->state_file, "LAST_CURSOR", &u->last_cursor);
        if (r == -ENOENT)
                log_debug("State file %s is not present.", u->state_file);
        else if (r < 0)
                return log_error_errno(r, "Failed to read state file %s: %m",
                                       u->state_file);
        else
                log_debug("Last cursor was %s", u->last_cursor);

        return 0;
}