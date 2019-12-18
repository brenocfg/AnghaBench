#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ dev_t ;
typedef  int /*<<< orphan*/  Unit ;
struct TYPE_8__ {int /*<<< orphan*/  pipe_fd; int /*<<< orphan*/  expire_tokens; int /*<<< orphan*/  tokens; scalar_t__ dev_id; scalar_t__ result; scalar_t__ deserialized_state; } ;
typedef  TYPE_1__ FDSet ;
typedef  scalar_t__ AutomountState ;
typedef  scalar_t__ AutomountResult ;
typedef  TYPE_1__ Automount ;

/* Variables and functions */
 TYPE_1__* AUTOMOUNT (int /*<<< orphan*/ *) ; 
 scalar_t__ AUTOMOUNT_SUCCESS ; 
 int /*<<< orphan*/  UINT_TO_PTR (unsigned int) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 scalar_t__ automount_result_from_string (char const*) ; 
 scalar_t__ automount_state_from_string (char const*) ; 
 int /*<<< orphan*/  fdset_contains (TYPE_1__*,int) ; 
 int /*<<< orphan*/  fdset_remove (TYPE_1__*,int) ; 
 int /*<<< orphan*/  log_oom () ; 
 int /*<<< orphan*/  log_unit_debug (int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/  log_unit_error_errno (int /*<<< orphan*/ *,int,char*) ; 
 scalar_t__ safe_atoi (char const*,int*) ; 
 scalar_t__ safe_atolu (char const*,unsigned long*) ; 
 scalar_t__ safe_atou (char const*,unsigned int*) ; 
 int /*<<< orphan*/  safe_close (int /*<<< orphan*/ ) ; 
 int set_ensure_allocated (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int set_put (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ streq (char const*,char*) ; 

__attribute__((used)) static int automount_deserialize_item(Unit *u, const char *key, const char *value, FDSet *fds) {
        Automount *a = AUTOMOUNT(u);
        int r;

        assert(a);
        assert(fds);

        if (streq(key, "state")) {
                AutomountState state;

                state = automount_state_from_string(value);
                if (state < 0)
                        log_unit_debug(u, "Failed to parse state value: %s", value);
                else
                        a->deserialized_state = state;
        } else if (streq(key, "result")) {
                AutomountResult f;

                f = automount_result_from_string(value);
                if (f < 0)
                        log_unit_debug(u, "Failed to parse result value: %s", value);
                else if (f != AUTOMOUNT_SUCCESS)
                        a->result = f;

        } else if (streq(key, "dev-id")) {
                unsigned long d;

                if (safe_atolu(value, &d) < 0)
                        log_unit_debug(u, "Failed to parse dev-id value: %s", value);
                else
                        a->dev_id = (dev_t) d;

        } else if (streq(key, "token")) {
                unsigned token;

                if (safe_atou(value, &token) < 0)
                        log_unit_debug(u, "Failed to parse token value: %s", value);
                else {
                        r = set_ensure_allocated(&a->tokens, NULL);
                        if (r < 0) {
                                log_oom();
                                return 0;
                        }

                        r = set_put(a->tokens, UINT_TO_PTR(token));
                        if (r < 0)
                                log_unit_error_errno(u, r, "Failed to add token to set: %m");
                }
        } else if (streq(key, "expire-token")) {
                unsigned token;

                if (safe_atou(value, &token) < 0)
                        log_unit_debug(u, "Failed to parse token value: %s", value);
                else {
                        r = set_ensure_allocated(&a->expire_tokens, NULL);
                        if (r < 0) {
                                log_oom();
                                return 0;
                        }

                        r = set_put(a->expire_tokens, UINT_TO_PTR(token));
                        if (r < 0)
                                log_unit_error_errno(u, r, "Failed to add expire token to set: %m");
                }
        } else if (streq(key, "pipe-fd")) {
                int fd;

                if (safe_atoi(value, &fd) < 0 || fd < 0 || !fdset_contains(fds, fd))
                        log_unit_debug(u, "Failed to parse pipe-fd value: %s", value);
                else {
                        safe_close(a->pipe_fd);
                        a->pipe_fd = fdset_remove(fds, fd);
                }
        } else
                log_unit_debug(u, "Unknown serialization key: %s", key);

        return 0;
}