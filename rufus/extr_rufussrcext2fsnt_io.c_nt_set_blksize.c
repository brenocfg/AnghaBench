#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* io_channel ;
typedef  int /*<<< orphan*/  errcode_t ;
struct TYPE_5__ {int block_size; int buffer_block_number; int buffer_size; int /*<<< orphan*/ * buffer; scalar_t__ private_data; } ;
typedef  TYPE_1__* PNT_PRIVATE_DATA ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  EXT2_CHECK_MAGIC (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EXT2_ET_MAGIC_IO_CHANNEL ; 
 int /*<<< orphan*/  EXT2_ET_MAGIC_NT_IO_CHANNEL ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * malloc (int) ; 

__attribute__((used)) static errcode_t nt_set_blksize(io_channel channel, int blksize)
{
	PNT_PRIVATE_DATA nt_data = NULL;

	EXT2_CHECK_MAGIC(channel, EXT2_ET_MAGIC_IO_CHANNEL);
	nt_data = (PNT_PRIVATE_DATA) channel->private_data;
	EXT2_CHECK_MAGIC(nt_data, EXT2_ET_MAGIC_NT_IO_CHANNEL);

	if (channel->block_size != blksize) {
		channel->block_size = blksize;

		free(nt_data->buffer);
		nt_data->buffer_block_number = 0xffffffff;
		nt_data->buffer_size = channel->block_size;
		assert((nt_data->buffer_size % 512) == 0);

		nt_data->buffer = malloc(nt_data->buffer_size);
		if (nt_data->buffer == NULL)
			return ENOMEM;
	}

	return 0;
}