#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* io_channel ;
typedef  int /*<<< orphan*/  errcode_t ;
struct TYPE_6__ {scalar_t__ refcount; struct TYPE_6__* buffer; int /*<<< orphan*/ * handle; struct TYPE_6__* name; scalar_t__ private_data; } ;
typedef  TYPE_1__* PNT_PRIVATE_DATA ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EXT2_CHECK_MAGIC (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EXT2_ET_MAGIC_IO_CHANNEL ; 
 int /*<<< orphan*/  EXT2_ET_MAGIC_NT_IO_CHANNEL ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 

__attribute__((used)) static errcode_t nt_close(io_channel channel)
{
	PNT_PRIVATE_DATA nt_data = NULL;

	if (channel == NULL)
		return 0;

	EXT2_CHECK_MAGIC(channel, EXT2_ET_MAGIC_IO_CHANNEL);
	nt_data = (PNT_PRIVATE_DATA) channel->private_data;
	EXT2_CHECK_MAGIC(nt_data, EXT2_ET_MAGIC_NT_IO_CHANNEL);

	if (--channel->refcount > 0)
		return 0;

	free(channel->name);
	free(channel);

	if (nt_data != NULL) {
		if (nt_data->handle != NULL)
			CloseHandle(nt_data->handle);
		free(nt_data->buffer);
		free(nt_data);
	}

	return 0;
}