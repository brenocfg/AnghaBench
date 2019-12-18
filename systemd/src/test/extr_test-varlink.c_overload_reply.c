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
typedef  int /*<<< orphan*/  VarlinkReplyFlags ;
typedef  int /*<<< orphan*/  Varlink ;
typedef  int /*<<< orphan*/  JsonVariant ;

/* Variables and functions */
 int /*<<< orphan*/  VARLINK_ERROR_DISCONNECTED ; 
 int /*<<< orphan*/  assert_se (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_event_exit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  streq (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strna (char const*) ; 
 int /*<<< orphan*/  varlink_get_event (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int overload_reply(Varlink *link, JsonVariant *parameters, const char *error_id, VarlinkReplyFlags flags, void *userdata) {

        /* This method call reply should always be called with a disconnection, since the method call should
         * be talking to an overloaded server */

        log_debug("Over reply triggered with error: %s", strna(error_id));
        assert_se(streq(error_id, VARLINK_ERROR_DISCONNECTED));
        sd_event_exit(varlink_get_event(link), 0);

        return 0;
}