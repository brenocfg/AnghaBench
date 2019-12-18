#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_4__ {scalar_t__ data; } ;
typedef  TYPE_1__ fz_buffer ;

/* Variables and functions */
 int /*<<< orphan*/  fz_terminate_buffer (int /*<<< orphan*/ *,TYPE_1__*) ; 

const char *
fz_string_from_buffer(fz_context *ctx, fz_buffer *buf)
{
	if (!buf)
		return "";
	fz_terminate_buffer(ctx, buf);
	return (const char *)buf->data;
}