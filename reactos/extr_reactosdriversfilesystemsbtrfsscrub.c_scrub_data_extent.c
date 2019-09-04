#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {size_t sector_size; } ;
struct TYPE_6__ {TYPE_1__ superblock; } ;
typedef  TYPE_2__ device_extension ;
typedef  int /*<<< orphan*/  chunk ;
typedef  size_t ULONG ;
typedef  scalar_t__ UINT64 ;
typedef  int /*<<< orphan*/  UINT32 ;
typedef  int /*<<< orphan*/  RTL_BITMAP ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 size_t RtlFindFirstRunClear (int /*<<< orphan*/ *,size_t*) ; 
 size_t RtlFindNextForwardRunClear (int /*<<< orphan*/ *,size_t,size_t*) ; 
 size_t SCRUB_UNIT ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 scalar_t__ UInt32x32To64 (size_t,size_t) ; 
 int /*<<< orphan*/  scrub_extent (TYPE_2__*,int /*<<< orphan*/ *,size_t,scalar_t__,size_t,int /*<<< orphan*/ *) ; 

__attribute__((used)) static NTSTATUS scrub_data_extent(device_extension* Vcb, chunk* c, UINT64 offset, ULONG type, UINT32* csum, RTL_BITMAP* bmp) {
    NTSTATUS Status;
    ULONG runlength, index;

    runlength = RtlFindFirstRunClear(bmp, &index);

    while (runlength != 0) {
        do {
            ULONG rl;

            if (runlength * Vcb->superblock.sector_size > SCRUB_UNIT)
                rl = SCRUB_UNIT / Vcb->superblock.sector_size;
            else
                rl = runlength;

            Status = scrub_extent(Vcb, c, type, offset + UInt32x32To64(index, Vcb->superblock.sector_size), rl * Vcb->superblock.sector_size, &csum[index]);
            if (!NT_SUCCESS(Status)) {
                ERR("scrub_data_extent_dup returned %08x\n", Status);
                return Status;
            }

            runlength -= rl;
            index += rl;
        } while (runlength > 0);

        runlength = RtlFindNextForwardRunClear(bmp, index, &index);
    }

    return STATUS_SUCCESS;
}