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
struct TYPE_3__ {int /*<<< orphan*/  value_len; int /*<<< orphan*/  value; int /*<<< orphan*/  name_len; int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  StringInfo ;
typedef  TYPE_1__ HttpHeader ;

/* Variables and functions */
 int /*<<< orphan*/  COLON ; 
 int /*<<< orphan*/  SPACE ; 
 int /*<<< orphan*/  appendOptionalBinaryStringInfo (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  http_request_serialize_char (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
http_header_serialize(HttpHeader *header, StringInfo buf)
{
	appendOptionalBinaryStringInfo(buf, header->name, header->name_len);
	http_request_serialize_char(COLON, buf);
	http_request_serialize_char(SPACE, buf);
	appendOptionalBinaryStringInfo(buf, header->value, header->value_len);
}