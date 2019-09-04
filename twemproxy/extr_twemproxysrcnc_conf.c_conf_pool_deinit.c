#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ len; } ;
struct TYPE_3__ {TYPE_2__ name; TYPE_2__ pname; } ;
struct conf_pool {int /*<<< orphan*/  server; TYPE_2__ redis_auth; TYPE_1__ listen; TYPE_2__ name; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_VVERB ; 
 int /*<<< orphan*/  array_deinit (int /*<<< orphan*/ *) ; 
 scalar_t__ array_n (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  array_pop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  conf_server_deinit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_debug (int /*<<< orphan*/ ,char*,struct conf_pool*) ; 
 int /*<<< orphan*/  string_deinit (TYPE_2__*) ; 

__attribute__((used)) static void
conf_pool_deinit(struct conf_pool *cp)
{
    string_deinit(&cp->name);

    string_deinit(&cp->listen.pname);
    string_deinit(&cp->listen.name);

    if (cp->redis_auth.len > 0) {
        string_deinit(&cp->redis_auth);
    }

    while (array_n(&cp->server) != 0) {
        conf_server_deinit(array_pop(&cp->server));
    }
    array_deinit(&cp->server);

    log_debug(LOG_VVERB, "deinit conf pool %p", cp);
}