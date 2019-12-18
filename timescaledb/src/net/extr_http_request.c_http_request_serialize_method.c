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
struct TYPE_3__ {int /*<<< orphan*/  method; } ;
typedef  int /*<<< orphan*/  StringInfo ;
typedef  TYPE_1__ HttpRequest ;

/* Variables and functions */
 char* METHOD_STRING (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  appendStringInfoString (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static void
http_request_serialize_method(HttpRequest *req, StringInfo buf)
{
	const char *method = METHOD_STRING(req->method);

	appendStringInfoString(buf, method);
}