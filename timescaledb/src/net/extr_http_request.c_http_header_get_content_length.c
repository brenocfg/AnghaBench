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
struct TYPE_3__ {int /*<<< orphan*/  value; int /*<<< orphan*/  name_len; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ HttpHeader ;

/* Variables and functions */
 int /*<<< orphan*/  HTTP_CONTENT_LENGTH ; 
 int /*<<< orphan*/  sscanf (int /*<<< orphan*/ ,char*,int*) ; 
 int /*<<< orphan*/  strncmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
http_header_get_content_length(HttpHeader *header)
{
	int content_length = -1;

	if (!strncmp(header->name, HTTP_CONTENT_LENGTH, header->name_len))
		sscanf(header->value, "%d", &content_length);
	return content_length;
}