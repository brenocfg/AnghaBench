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

/* Variables and functions */
 int /*<<< orphan*/  CONNECTION_SSL ; 
 int /*<<< orphan*/  SSL_library_init () ; 
 int /*<<< orphan*/  SSL_load_error_strings () ; 
 int /*<<< orphan*/  ssl_ops ; 
 int /*<<< orphan*/  ts_connection_register (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
_conn_ssl_init(void)
{
	SSL_library_init();
	/* Always returns 1 */
	SSL_load_error_strings();
	ts_connection_register(CONNECTION_SSL, &ssl_ops);
}