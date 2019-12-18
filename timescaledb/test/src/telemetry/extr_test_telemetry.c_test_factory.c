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
typedef  int /*<<< orphan*/  Datum ;
typedef  scalar_t__ ConnectionType ;
typedef  int /*<<< orphan*/  Connection ;

/* Variables and functions */
 scalar_t__ CONNECTION_MOCK ; 
 int /*<<< orphan*/  CStringGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CStringGetTextDatum (char*) ; 
 int /*<<< orphan*/  DirectFunctionCall1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ HTTP_ERROR_NONE ; 
 int /*<<< orphan*/ * build_request (int) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  jsonb_in ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_string ; 
 scalar_t__ ts_connection_connect (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * ts_connection_create (scalar_t__) ; 
 int /*<<< orphan*/  ts_connection_destroy (int /*<<< orphan*/ *) ; 
 char* ts_connection_get_and_clear_error (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ts_connection_mock_set_recv_buf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ts_http_request_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ts_http_response_state_body_start (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ts_http_response_state_create () ; 
 int /*<<< orphan*/  ts_http_response_state_destroy (int /*<<< orphan*/ *) ; 
 char const* ts_http_response_state_status_code (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ts_http_response_state_valid_status (int /*<<< orphan*/ *) ; 
 scalar_t__ ts_http_send_and_recv (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char const* ts_http_strerror (scalar_t__) ; 

__attribute__((used)) static Datum
test_factory(ConnectionType type, int status, char *host, int port)
{
	Connection *conn;
	HttpRequest *req;
	HttpResponseState *rsp = NULL;
	HttpError err;
	Datum json;

	conn = ts_connection_create(type);

	if (conn == NULL)
		return CStringGetTextDatum("could not initialize a connection");

	if (ts_connection_connect(conn, host, NULL, port) < 0)
	{
		const char *err_msg = ts_connection_get_and_clear_error(conn);

		ts_connection_destroy(conn);
		elog(ERROR, "connection error: %s", err_msg);
	}

#ifdef TS_DEBUG
	if (type == CONNECTION_MOCK)
		ts_connection_mock_set_recv_buf(conn, test_string, strlen(test_string));
#endif

	req = build_request(status);

	rsp = ts_http_response_state_create();

	err = ts_http_send_and_recv(conn, req, rsp);

	ts_http_request_destroy(req);
	ts_connection_destroy(conn);

	if (err != HTTP_ERROR_NONE)
		elog(ERROR, "%s", ts_http_strerror(err));

	if (!ts_http_response_state_valid_status(rsp))
		elog(ERROR,
			 "endpoint sent back unexpected HTTP status: %d",
			 ts_http_response_state_status_code(rsp));

	json = DirectFunctionCall1(jsonb_in, CStringGetDatum(ts_http_response_state_body_start(rsp)));

	ts_http_response_state_destroy(rsp);

	return json;
}