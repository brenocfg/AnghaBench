#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct struct_io_channel {int dummy; } ;
typedef  TYPE_1__* io_channel ;
typedef  scalar_t__ errcode_t ;
struct TYPE_8__ {int refcount; int buffer_block_number; struct TYPE_8__* buffer; int /*<<< orphan*/ * handle; struct TYPE_8__* name; int /*<<< orphan*/  read_only; int /*<<< orphan*/  size; int /*<<< orphan*/  offset; struct TYPE_8__* private_data; void* buffer_size; int /*<<< orphan*/  magic; void* block_size; int /*<<< orphan*/  manager; } ;
typedef  TYPE_1__* PNT_PRIVATE_DATA ;
typedef  int /*<<< orphan*/  NT_PRIVATE_DATA ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  BooleanFlagOn (int,int /*<<< orphan*/ ) ; 
 scalar_t__ EIO ; 
 scalar_t__ ENOMEM ; 
 scalar_t__ EXT2_ET_BAD_DEVICE_NAME ; 
 int /*<<< orphan*/  EXT2_ET_MAGIC_IO_CHANNEL ; 
 int /*<<< orphan*/  EXT2_ET_MAGIC_NT_IO_CHANNEL ; 
 int /*<<< orphan*/  EXT2_FLAG_RW ; 
 void* EXT2_MIN_BLOCK_SIZE ; 
 int /*<<< orphan*/  _CloseDisk (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _Ext2OpenDevice (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  _UnlockDrive (int /*<<< orphan*/ *) ; 
 TYPE_1__* calloc (int,int) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 TYPE_1__* malloc (void*) ; 
 int /*<<< orphan*/  nt_io_manager () ; 
 int /*<<< orphan*/  strcpy (TYPE_1__*,char const*) ; 
 int strlen (char const*) ; 

__attribute__((used)) static errcode_t nt_open(const char *name, int flags, io_channel *channel)
{
	io_channel io = NULL;
	PNT_PRIVATE_DATA nt_data = NULL;
	errcode_t errcode = 0;

	if (name == NULL)
		return EXT2_ET_BAD_DEVICE_NAME;

	// Allocate buffers
	io = (io_channel) calloc(1, sizeof(struct struct_io_channel));
	if (io == NULL) {
		errcode = ENOMEM;
		goto out;
	}

	io->name = calloc(strlen(name) + 1, 1);
	if (io->name == NULL) {
		errcode = ENOMEM;
		goto out;
	}

	nt_data = (PNT_PRIVATE_DATA) calloc(1, sizeof(NT_PRIVATE_DATA));
	if (nt_data == NULL) {
		errcode = ENOMEM;
		goto out;
	}

	nt_data->buffer = malloc(EXT2_MIN_BLOCK_SIZE);
	if (nt_data->buffer == NULL) {
		errcode = ENOMEM;
		goto out;
	}

	// Initialize data
	io->magic = EXT2_ET_MAGIC_IO_CHANNEL;
	io->manager = nt_io_manager();
	strcpy(io->name, name);
	io->block_size = EXT2_MIN_BLOCK_SIZE;
	io->refcount = 1;

	nt_data->magic = EXT2_ET_MAGIC_NT_IO_CHANNEL;
	nt_data->buffer_block_number = 0xffffffff;
	nt_data->buffer_size = EXT2_MIN_BLOCK_SIZE;
	io->private_data = nt_data;

	// Open the device
	if (!_Ext2OpenDevice(name, (BOOLEAN)!BooleanFlagOn(flags, EXT2_FLAG_RW), &nt_data->handle,
		&nt_data->offset, &nt_data->size, &nt_data->read_only, &errcode)) {
		if (!errcode)
			errcode = EIO;
		goto out;
	}

	// Done
	*channel = io;

out:
	if (errcode) {
		if (io != NULL) {
			free(io->name);
			free(io);
		}

		if (nt_data != NULL) {
			if (nt_data->handle != NULL) {
				_UnlockDrive(nt_data->handle);
				_CloseDisk(nt_data->handle);
			}
			free(nt_data->buffer);
			free(nt_data);
		}
	}

	return errcode;
}