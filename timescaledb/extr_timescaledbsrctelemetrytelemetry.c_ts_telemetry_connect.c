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
typedef  int /*<<< orphan*/  Connection ;

/* Variables and functions */
 int /*<<< orphan*/  CONNECTION_PLAIN ; 
 int /*<<< orphan*/  CONNECTION_SSL ; 
 int /*<<< orphan*/  ERRCODE_FEATURE_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ERRCODE_INTERNAL_ERROR ; 
 int /*<<< orphan*/  WARNING ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errdetail (char*,char const*) ; 
 int /*<<< orphan*/  errmsg (char*,char const*) ; 
 scalar_t__ strcmp (char*,char const*) ; 
 int ts_connection_connect (int /*<<< orphan*/ *,char const*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ts_connection_create (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ts_connection_destroy (int /*<<< orphan*/ *) ; 
 char* ts_connection_get_and_clear_error (int /*<<< orphan*/ *) ; 

Connection *
ts_telemetry_connect(const char *host, const char *service)
{
	Connection *conn = NULL;
	int ret;

	if (strcmp("http", service) == 0)
		conn = ts_connection_create(CONNECTION_PLAIN);
	else if (strcmp("https", service) == 0)
		conn = ts_connection_create(CONNECTION_SSL);
	else
		ereport(WARNING,
				(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
				 errmsg("scheme \"%s\" not supported for telemetry", service)));

	if (conn == NULL)
		return NULL;

	ret = ts_connection_connect(conn, host, service, 0);

	if (ret < 0)
	{
		const char *errstr = ts_connection_get_and_clear_error(conn);

		ts_connection_destroy(conn);
		conn = NULL;

		ereport(WARNING,
				(errcode(ERRCODE_INTERNAL_ERROR),
				 errmsg("telemetry could not connect to \"%s\"", host),
				 errdetail("%s", errstr)));
	}

	return conn;
}