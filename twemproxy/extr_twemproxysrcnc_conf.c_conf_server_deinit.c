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
struct conf_server {scalar_t__ valid; int /*<<< orphan*/  addrstr; int /*<<< orphan*/  name; int /*<<< orphan*/  pname; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_VVERB ; 
 int /*<<< orphan*/  log_debug (int /*<<< orphan*/ ,char*,struct conf_server*) ; 
 int /*<<< orphan*/  string_deinit (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
conf_server_deinit(struct conf_server *cs)
{
    string_deinit(&cs->pname);
    string_deinit(&cs->name);
    string_deinit(&cs->addrstr);
    cs->valid = 0;
    log_debug(LOG_VVERB, "deinit conf server %p", cs);
}