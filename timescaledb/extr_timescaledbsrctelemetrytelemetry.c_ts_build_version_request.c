#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int len; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__* StringInfo ;
typedef  int /*<<< orphan*/  HttpRequest ;

/* Variables and functions */
 int /*<<< orphan*/  HTTP_CONTENT_LENGTH ; 
 int /*<<< orphan*/  HTTP_CONTENT_TYPE ; 
 int /*<<< orphan*/  HTTP_HOST ; 
 int /*<<< orphan*/  HTTP_POST ; 
 int /*<<< orphan*/  HTTP_VERSION_10 ; 
 char const* TIMESCALE_TYPE ; 
 TYPE_1__* build_version_body () ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/ * ts_http_request_create (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ts_http_request_set_body (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ts_http_request_set_header (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  ts_http_request_set_uri (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  ts_http_request_set_version (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

HttpRequest *
ts_build_version_request(const char *host, const char *path)
{
	char body_len_string[5];
	HttpRequest *req;
	StringInfo jtext = build_version_body();

	snprintf(body_len_string, 5, "%d", jtext->len);

	/* Fill in HTTP request */
	req = ts_http_request_create(HTTP_POST);

	ts_http_request_set_uri(req, path);
	ts_http_request_set_version(req, HTTP_VERSION_10);
	ts_http_request_set_header(req, HTTP_CONTENT_TYPE, TIMESCALE_TYPE);
	ts_http_request_set_header(req, HTTP_CONTENT_LENGTH, body_len_string);
	ts_http_request_set_header(req, HTTP_HOST, host);
	ts_http_request_set_body(req, jtext->data, jtext->len);

	return req;
}