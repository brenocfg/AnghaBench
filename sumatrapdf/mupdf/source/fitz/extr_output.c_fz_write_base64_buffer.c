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
typedef  int /*<<< orphan*/  fz_output ;
typedef  int /*<<< orphan*/  fz_context ;
typedef  int /*<<< orphan*/  fz_buffer ;

/* Variables and functions */
 size_t fz_buffer_storage (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned char**) ; 
 int /*<<< orphan*/  fz_write_base64 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned char*,size_t,int) ; 

void
fz_write_base64_buffer(fz_context *ctx, fz_output *out, fz_buffer *buf, int newline)
{
	unsigned char *data;
	size_t size = fz_buffer_storage(ctx, buf, &data);
	fz_write_base64(ctx, out, data, size, newline);
}