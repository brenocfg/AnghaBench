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
struct client {scalar_t__ references; } ;

/* Variables and functions */
 int /*<<< orphan*/  EV_TIMEOUT ; 
 int /*<<< orphan*/  event_once (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct client*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_debug (char*,struct client*,scalar_t__) ; 
 int /*<<< orphan*/  server_client_free ; 

void
server_client_unref(struct client *c)
{
	log_debug("unref client %p (%d references)", c, c->references);

	c->references--;
	if (c->references == 0)
		event_once(-1, EV_TIMEOUT, server_client_free, c, NULL);
}