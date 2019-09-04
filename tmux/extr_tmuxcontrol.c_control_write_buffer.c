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
struct evbuffer {int dummy; } ;
struct client {int /*<<< orphan*/  stdout_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  evbuffer_add (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  evbuffer_add_buffer (int /*<<< orphan*/ ,struct evbuffer*) ; 
 int /*<<< orphan*/  server_client_push_stdout (struct client*) ; 

void
control_write_buffer(struct client *c, struct evbuffer *buffer)
{
	evbuffer_add_buffer(c->stdout_data, buffer);
	evbuffer_add(c->stdout_data, "\n", 1);
	server_client_push_stdout(c);
}