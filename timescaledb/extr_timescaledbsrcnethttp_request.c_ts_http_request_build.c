#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
struct TYPE_20__ {struct TYPE_20__* next; } ;
struct TYPE_19__ {int body_len; TYPE_3__* headers; } ;
struct TYPE_18__ {size_t len; char const* data; } ;
typedef  TYPE_1__ StringInfoData ;
typedef  TYPE_2__ HttpRequest ;
typedef  TYPE_3__ HttpHeader ;

/* Variables and functions */
 int /*<<< orphan*/  CARRIAGE ; 
 int /*<<< orphan*/  NEW_LINE ; 
 int /*<<< orphan*/  SPACE ; 
 int http_header_get_content_length (TYPE_3__*) ; 
 int /*<<< orphan*/  http_header_serialize (TYPE_3__*,TYPE_1__*) ; 
 int /*<<< orphan*/  http_request_serialize_body (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  http_request_serialize_char (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  http_request_serialize_method (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  http_request_serialize_uri (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  http_request_serialize_version (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  initStringInfo (TYPE_1__*) ; 

const char *
ts_http_request_build(HttpRequest *req, size_t *buf_size)
{
	/* serialize into this buf, which is allocated on caller's memory context */
	StringInfoData buf;
	HttpHeader *cur_header;
	int content_length = 0;
	bool verified_content_length = false;

	initStringInfo(&buf);

	http_request_serialize_method(req, &buf);
	http_request_serialize_char(SPACE, &buf);

	http_request_serialize_uri(req, &buf);
	http_request_serialize_char(SPACE, &buf);

	http_request_serialize_version(req, &buf);
	http_request_serialize_char(CARRIAGE, &buf);
	http_request_serialize_char(NEW_LINE, &buf);

	cur_header = req->headers;

	while (cur_header != NULL)
	{
		content_length = http_header_get_content_length(cur_header);
		if (content_length != -1)
		{
			/* make sure it's equal to body_len */
			if (content_length != req->body_len)
			{
				return NULL;
			}
			else
				verified_content_length = true;
		}
		http_header_serialize(cur_header, &buf);
		http_request_serialize_char(CARRIAGE, &buf);
		http_request_serialize_char(NEW_LINE, &buf);

		cur_header = cur_header->next;
	}
	http_request_serialize_char(CARRIAGE, &buf);
	http_request_serialize_char(NEW_LINE, &buf);

	if (!verified_content_length)
	{
		/* Then there was no header field for Content-Length */
		if (req->body_len != 0)
		{
			return NULL;
		}
	}

	http_request_serialize_body(req, &buf);
	/* Now everything lives in buf.data */
	if (buf_size != NULL)
		*buf_size = buf.len;
	return buf.data;
}