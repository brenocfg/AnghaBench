#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int64_t ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_2__ {int /*<<< orphan*/  len; } ;
typedef  TYPE_1__ fz_buffer ;

/* Variables and functions */

__attribute__((used)) static int64_t
buffer_tell(fz_context *ctx, void *opaque)
{
	fz_buffer *buffer = opaque;
	return (int64_t)buffer->len;
}