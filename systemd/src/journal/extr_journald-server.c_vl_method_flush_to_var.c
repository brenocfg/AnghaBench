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
typedef  int /*<<< orphan*/  VarlinkMethodFlags ;
typedef  int /*<<< orphan*/  Varlink ;
typedef  int /*<<< orphan*/  Server ;
typedef  int /*<<< orphan*/  JsonVariant ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 scalar_t__ json_variant_elements (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_info (char*) ; 
 int /*<<< orphan*/  server_full_flush (int /*<<< orphan*/ *) ; 
 int varlink_error_invalid_parameter (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int varlink_reply (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vl_method_flush_to_var(Varlink *link, JsonVariant *parameters, VarlinkMethodFlags flags, void *userdata) {
        Server *s = userdata;

        assert(link);
        assert(s);

        if (json_variant_elements(parameters) > 0)
                return varlink_error_invalid_parameter(link, parameters);

        log_info("Received client request to flush runtime journal.");
        server_full_flush(s);

        return varlink_reply(link, NULL);
}