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
typedef  int /*<<< orphan*/  ngx_event_t ;

/* Variables and functions */
 int /*<<< orphan*/  ngx_http_lua_socket_keepalive_close_handler (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ngx_http_lua_socket_keepalive_rev_handler(ngx_event_t *ev)
{
    (void) ngx_http_lua_socket_keepalive_close_handler(ev);
}