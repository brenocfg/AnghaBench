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
struct conf_server {scalar_t__ valid; int /*<<< orphan*/  info; scalar_t__ weight; scalar_t__ port; int /*<<< orphan*/  addrstr; int /*<<< orphan*/  name; int /*<<< orphan*/  pname; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_VVERB ; 
 int /*<<< orphan*/  log_debug (int /*<<< orphan*/ ,char*,struct conf_server*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  string_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
conf_server_init(struct conf_server *cs)
{
    string_init(&cs->pname);
    string_init(&cs->name);
    string_init(&cs->addrstr);
    cs->port = 0;
    cs->weight = 0;

    memset(&cs->info, 0, sizeof(cs->info));

    cs->valid = 0;

    log_debug(LOG_VVERB, "init conf server %p", cs);
}