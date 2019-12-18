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
typedef  int /*<<< orphan*/  HttpResponseState ;
typedef  int /*<<< orphan*/  HttpRequest ;
typedef  scalar_t__ HttpError ;
typedef  int /*<<< orphan*/  Connection ;

/* Variables and functions */
 int /*<<< orphan*/  AbortCurrentTransaction () ; 
 int /*<<< orphan*/  CommitTransactionCommand () ; 
 scalar_t__ HTTP_ERROR_NONE ; 
 int /*<<< orphan*/  IsTransactionOrTransactionBlock () ; 
 int /*<<< orphan*/  StartTransactionCommand () ; 
 int /*<<< orphan*/  WARNING ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  process_response (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ts_build_version_request (char const*,char const*) ; 
 int /*<<< orphan*/  ts_connection_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ts_http_request_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ts_http_response_state_body_start (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ts_http_response_state_create () ; 
 int /*<<< orphan*/  ts_http_response_state_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ts_http_response_state_status_code (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ts_http_response_state_valid_status (int /*<<< orphan*/ *) ; 
 scalar_t__ ts_http_send_and_recv (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ts_http_strerror (scalar_t__) ; 
 int /*<<< orphan*/ * ts_telemetry_connect (char const*,char const*) ; 
 int /*<<< orphan*/  ts_telemetry_on () ; 

bool
ts_telemetry_main(const char *host, const char *path, const char *service)
{
	HttpError err;
	Connection *conn;
	HttpRequest *req;
	HttpResponseState *rsp;
	bool started = false;

	if (!ts_telemetry_on())
		return true;

	if (!IsTransactionOrTransactionBlock())
	{
		started = true;
		StartTransactionCommand();
	}

	conn = ts_telemetry_connect(host, service);

	if (conn == NULL)
		goto cleanup;

	req = ts_build_version_request(host, path);

	rsp = ts_http_response_state_create();

	err = ts_http_send_and_recv(conn, req, rsp);

	ts_http_request_destroy(req);
	ts_connection_destroy(conn);

	if (err != HTTP_ERROR_NONE)
	{
		elog(WARNING, "telemetry error: %s", ts_http_strerror(err));
		goto cleanup;
	}

	if (!ts_http_response_state_valid_status(rsp))
	{
		elog(WARNING,
			 "telemetry got unexpected HTTP response status: %d",
			 ts_http_response_state_status_code(rsp));
		goto cleanup;
	}

	/*
	 * Do the version-check. Response is the body of a well-formed HTTP
	 * response, since otherwise the previous line will throw an error.
	 */
	process_response(ts_http_response_state_body_start(rsp));

	ts_http_response_state_destroy(rsp);

	if (started)
		CommitTransactionCommand();
	return true;

cleanup:
	if (started)
		AbortCurrentTransaction();
	return false;
}