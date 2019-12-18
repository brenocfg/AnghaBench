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
typedef  int /*<<< orphan*/  fz_context ;
typedef  int /*<<< orphan*/  fz_buffer ;

/* Variables and functions */
 int /*<<< orphan*/  fz_append_data (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void const*,size_t) ; 

__attribute__((used)) static void
buffer_write(fz_context *ctx, void *opaque, const void *data, size_t len)
{
	fz_buffer *buffer = opaque;
	fz_append_data(ctx, buffer, data, len);
}