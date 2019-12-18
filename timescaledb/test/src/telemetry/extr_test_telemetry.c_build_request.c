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
typedef  int /*<<< orphan*/  HttpRequest ;

/* Variables and functions */
 int /*<<< orphan*/  HTTP_CONTENT_LENGTH ; 
 int /*<<< orphan*/  HTTP_GET ; 
 int /*<<< orphan*/  HTTP_HOST ; 
 int /*<<< orphan*/  HTTP_VERSION_10 ; 
 char* TEST_ENDPOINT ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/ * ts_http_request_create (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ts_http_request_set_header (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ts_http_request_set_uri (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ts_http_request_set_version (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static HttpRequest *
build_request(int status)
{
	HttpRequest *req = ts_http_request_create(HTTP_GET);
	char uri[20];

	snprintf(uri, 20, "/status/%d", status);

	ts_http_request_set_uri(req, uri);
	ts_http_request_set_version(req, HTTP_VERSION_10);
	ts_http_request_set_header(req, HTTP_HOST, TEST_ENDPOINT);
	ts_http_request_set_header(req, HTTP_CONTENT_LENGTH, "0");
	return req;
}