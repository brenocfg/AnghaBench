#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  size_t uint16_t ;
struct TYPE_8__ {scalar_t__ offset; TYPE_1__* chunk_item; } ;
typedef  TYPE_2__ btrfs_chunk ;
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_10__ {scalar_t__ offset; } ;
struct TYPE_9__ {scalar_t__ QuadPart; } ;
struct TYPE_7__ {size_t num_stripes; } ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  TYPE_3__ LARGE_INTEGER ;
typedef  int /*<<< orphan*/  IO_STATUS_BLOCK ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  TYPE_4__ CHUNK_ITEM_STRIPE ;

/* Variables and functions */
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NtWriteFile (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 

__attribute__((used)) static NTSTATUS write_data(HANDLE h, uint64_t address, btrfs_chunk* c, void* data, ULONG size) {
    NTSTATUS Status;
    uint16_t i;
    IO_STATUS_BLOCK iosb;
    LARGE_INTEGER off;
    CHUNK_ITEM_STRIPE* cis;

    cis = (CHUNK_ITEM_STRIPE*)&c->chunk_item[1];

    for (i = 0; i < c->chunk_item->num_stripes; i++) {
        off.QuadPart = cis[i].offset + address - c->offset;

        Status = NtWriteFile(h, NULL, NULL, NULL, &iosb, data, size, &off, NULL);
        if (!NT_SUCCESS(Status))
            return Status;
    }

    return STATUS_SUCCESS;
}