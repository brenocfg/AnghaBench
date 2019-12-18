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
typedef  int /*<<< orphan*/  fz_stream ;
typedef  int /*<<< orphan*/  fz_context ;
typedef  int /*<<< orphan*/  fz_compressed_buffer ;

/* Variables and functions */
 int /*<<< orphan*/ * fz_open_image_decomp_stream_from_buffer (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

fz_stream *
fz_open_compressed_buffer(fz_context *ctx, fz_compressed_buffer *buffer)
{
	return fz_open_image_decomp_stream_from_buffer(ctx, buffer, NULL);
}