#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* io_channel ;
typedef  int /*<<< orphan*/  errcode_t ;
typedef  int ULONG ;
struct TYPE_9__ {scalar_t__ QuadPart; } ;
struct TYPE_8__ {unsigned long buffer_block_number; void* buffer; int block_size; int buffer_size; int /*<<< orphan*/  (* read_error ) (TYPE_1__*,unsigned long,int,void*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  handle; scalar_t__ offset; scalar_t__ private_data; } ;
typedef  void* PVOID ;
typedef  TYPE_1__* PNT_PRIVATE_DATA ;
typedef  TYPE_3__ LARGE_INTEGER ;

/* Variables and functions */
 int /*<<< orphan*/  EXT2_CHECK_MAGIC (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EXT2_ET_MAGIC_IO_CHANNEL ; 
 int /*<<< orphan*/  EXT2_ET_MAGIC_NT_IO_CHANNEL ; 
 int /*<<< orphan*/  _RawRead (int /*<<< orphan*/ ,TYPE_3__,int,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memcpy (void*,void*,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,unsigned long,int,void*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static errcode_t nt_read_blk(io_channel channel, unsigned long block, int count, void *buf)
{
	PVOID read_buffer;
	ULONG read_size;
	ULONG size;
	LARGE_INTEGER offset;
	PNT_PRIVATE_DATA nt_data = NULL;
	errcode_t errcode = 0;

	EXT2_CHECK_MAGIC(channel, EXT2_ET_MAGIC_IO_CHANNEL);
	nt_data = (PNT_PRIVATE_DATA) channel->private_data;
	EXT2_CHECK_MAGIC(nt_data, EXT2_ET_MAGIC_NT_IO_CHANNEL);

	// If it's in the cache, use it!
	if ((count == 1) && (block == nt_data->buffer_block_number) &&
	    (nt_data->buffer_block_number != 0xffffffff)) {
		memcpy(buf, nt_data->buffer, channel->block_size);
		return 0;
	}

	size = (count < 0) ? (ULONG)(-count) : (ULONG)(count * channel->block_size);

	offset.QuadPart = block * channel->block_size + nt_data->offset;

	// If not fit to the block
	if (size <= nt_data->buffer_size) {
		// Update the cache
		nt_data->buffer_block_number = block;
		read_buffer = nt_data->buffer;
		read_size = nt_data->buffer_size;
	} else {
		read_size = size;
		read_buffer = buf;
		assert((read_size % channel->block_size) == 0);
	}

	if (!_RawRead(nt_data->handle, offset, read_size, read_buffer, &errcode)) {
		if (channel->read_error)
			return (channel->read_error)(channel, block, count, buf, size, 0, errcode);
		else
			return errcode;
	}

	if (read_buffer != buf) {
		assert(size <= read_size);
		memcpy(buf, read_buffer, size);
	}

	return 0;
}