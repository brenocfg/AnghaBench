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
typedef  int /*<<< orphan*/  fz_deflate_level ;
typedef  int /*<<< orphan*/  fz_context ;
typedef  int /*<<< orphan*/  fz_buffer ;

/* Variables and functions */
 size_t fz_buffer_storage (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned char**) ; 
 unsigned char* fz_new_deflated_data (int /*<<< orphan*/ *,size_t*,unsigned char*,size_t,int /*<<< orphan*/ ) ; 

unsigned char *fz_new_deflated_data_from_buffer(fz_context *ctx, size_t *compressed_length, fz_buffer *buffer, fz_deflate_level level)
{
	unsigned char *data;
	size_t size = fz_buffer_storage(ctx, buffer, &data);

	if (size == 0 || data == NULL)
	{
		*compressed_length = 0;
		return NULL;
	}

	return fz_new_deflated_data(ctx, compressed_length, data, size, level);
}