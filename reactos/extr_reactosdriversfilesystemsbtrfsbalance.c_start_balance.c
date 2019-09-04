#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ thread; void* paused; int /*<<< orphan*/  event; int /*<<< orphan*/  status; void* shrinking; void* removing; int /*<<< orphan*/ * opts; } ;
struct TYPE_8__ {scalar_t__ thread; } ;
struct TYPE_10__ {TYPE_2__ balance; scalar_t__ readonly; TYPE_1__ scrub; scalar_t__ locked; } ;
typedef  TYPE_3__ device_extension ;
struct TYPE_11__ {TYPE_6__* opts; } ;
typedef  TYPE_4__ btrfs_start_balance ;
typedef  int /*<<< orphan*/  btrfs_balance_opts ;
typedef  int ULONG ;
typedef  int UINT8 ;
struct TYPE_12__ {int flags; int profiles; scalar_t__ devid; scalar_t__ drange_start; scalar_t__ drange_end; scalar_t__ vrange_start; scalar_t__ vrange_end; scalar_t__ limit_start; scalar_t__ limit_end; scalar_t__ stripes_start; scalar_t__ stripes_end; int convert; void* usage_end; void* usage_start; } ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  KPROCESSOR_MODE ;

/* Variables and functions */
 size_t BALANCE_OPTS_DATA ; 
 size_t BALANCE_OPTS_METADATA ; 
 size_t BALANCE_OPTS_SYSTEM ; 
 int BLOCK_FLAG_DUPLICATE ; 
 int BLOCK_FLAG_RAID0 ; 
 int BLOCK_FLAG_RAID1 ; 
 int BLOCK_FLAG_RAID10 ; 
 int BLOCK_FLAG_RAID5 ; 
 int BLOCK_FLAG_RAID6 ; 
 int BLOCK_FLAG_SINGLE ; 
 int BTRFS_BALANCE_OPTS_CONVERT ; 
 int BTRFS_BALANCE_OPTS_DEVID ; 
 int BTRFS_BALANCE_OPTS_DRANGE ; 
 int BTRFS_BALANCE_OPTS_ENABLED ; 
 int BTRFS_BALANCE_OPTS_LIMIT ; 
 int BTRFS_BALANCE_OPTS_PROFILES ; 
 int BTRFS_BALANCE_OPTS_STRIPES ; 
 int BTRFS_BALANCE_OPTS_USAGE ; 
 int BTRFS_BALANCE_OPTS_VRANGE ; 
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ) ; 
 void* FALSE ; 
 int /*<<< orphan*/  KeInitializeEvent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NotificationEvent ; 
 int /*<<< orphan*/  PsCreateSystemThread (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  RtlConvertLongToLuid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RtlCopyMemory (int /*<<< orphan*/ *,TYPE_6__*,int) ; 
 int /*<<< orphan*/  SE_MANAGE_VOLUME_PRIVILEGE ; 
 int /*<<< orphan*/  STATUS_DEVICE_NOT_READY ; 
 int /*<<< orphan*/  STATUS_INVALID_PARAMETER ; 
 int /*<<< orphan*/  STATUS_MEDIA_WRITE_PROTECTED ; 
 int /*<<< orphan*/  STATUS_PRIVILEGE_NOT_HELD ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  SeSinglePrivilegeCheck (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN (char*) ; 
 int /*<<< orphan*/  balance_thread ; 
 void* max (int,scalar_t__) ; 
 void* min (int,scalar_t__) ; 

NTSTATUS start_balance(device_extension* Vcb, void* data, ULONG length, KPROCESSOR_MODE processor_mode) {
    NTSTATUS Status;
    btrfs_start_balance* bsb = (btrfs_start_balance*)data;
    UINT8 i;

    if (length < sizeof(btrfs_start_balance) || !data)
        return STATUS_INVALID_PARAMETER;

    if (!SeSinglePrivilegeCheck(RtlConvertLongToLuid(SE_MANAGE_VOLUME_PRIVILEGE), processor_mode))
        return STATUS_PRIVILEGE_NOT_HELD;

    if (Vcb->locked) {
        WARN("cannot start balance while locked\n");
        return STATUS_DEVICE_NOT_READY;
    }

    if (Vcb->scrub.thread) {
        WARN("cannot start balance while scrub running\n");
        return STATUS_DEVICE_NOT_READY;
    }

    if (Vcb->balance.thread) {
        WARN("balance already running\n");
        return STATUS_DEVICE_NOT_READY;
    }

    if (Vcb->readonly)
        return STATUS_MEDIA_WRITE_PROTECTED;

    if (!(bsb->opts[BALANCE_OPTS_DATA].flags & BTRFS_BALANCE_OPTS_ENABLED) &&
        !(bsb->opts[BALANCE_OPTS_METADATA].flags & BTRFS_BALANCE_OPTS_ENABLED) &&
        !(bsb->opts[BALANCE_OPTS_SYSTEM].flags & BTRFS_BALANCE_OPTS_ENABLED))
        return STATUS_SUCCESS;

    for (i = 0; i < 3; i++) {
        if (bsb->opts[i].flags & BTRFS_BALANCE_OPTS_ENABLED) {
            if (bsb->opts[i].flags & BTRFS_BALANCE_OPTS_PROFILES) {
                bsb->opts[i].profiles &= BLOCK_FLAG_RAID0 | BLOCK_FLAG_RAID1 | BLOCK_FLAG_DUPLICATE | BLOCK_FLAG_RAID10 |
                                         BLOCK_FLAG_RAID5 | BLOCK_FLAG_RAID6 | BLOCK_FLAG_SINGLE;

                if (bsb->opts[i].profiles == 0)
                    return STATUS_INVALID_PARAMETER;
            }

            if (bsb->opts[i].flags & BTRFS_BALANCE_OPTS_DEVID) {
                if (bsb->opts[i].devid == 0)
                    return STATUS_INVALID_PARAMETER;
            }

            if (bsb->opts[i].flags & BTRFS_BALANCE_OPTS_DRANGE) {
                if (bsb->opts[i].drange_start > bsb->opts[i].drange_end)
                    return STATUS_INVALID_PARAMETER;
            }

            if (bsb->opts[i].flags & BTRFS_BALANCE_OPTS_VRANGE) {
                if (bsb->opts[i].vrange_start > bsb->opts[i].vrange_end)
                    return STATUS_INVALID_PARAMETER;
            }

            if (bsb->opts[i].flags & BTRFS_BALANCE_OPTS_LIMIT) {
                bsb->opts[i].limit_start = max(1, bsb->opts[i].limit_start);
                bsb->opts[i].limit_end = max(1, bsb->opts[i].limit_end);

                if (bsb->opts[i].limit_start > bsb->opts[i].limit_end)
                    return STATUS_INVALID_PARAMETER;
            }

            if (bsb->opts[i].flags & BTRFS_BALANCE_OPTS_STRIPES) {
                bsb->opts[i].stripes_start = max(1, bsb->opts[i].stripes_start);
                bsb->opts[i].stripes_end = max(1, bsb->opts[i].stripes_end);

                if (bsb->opts[i].stripes_start > bsb->opts[i].stripes_end)
                    return STATUS_INVALID_PARAMETER;
            }

            if (bsb->opts[i].flags & BTRFS_BALANCE_OPTS_USAGE) {
                bsb->opts[i].usage_start = min(100, bsb->opts[i].stripes_start);
                bsb->opts[i].usage_end = min(100, bsb->opts[i].stripes_end);

                if (bsb->opts[i].stripes_start > bsb->opts[i].stripes_end)
                    return STATUS_INVALID_PARAMETER;
            }

            if (bsb->opts[i].flags & BTRFS_BALANCE_OPTS_CONVERT) {
                if (bsb->opts[i].convert != BLOCK_FLAG_RAID0 && bsb->opts[i].convert != BLOCK_FLAG_RAID1 &&
                    bsb->opts[i].convert != BLOCK_FLAG_DUPLICATE && bsb->opts[i].convert != BLOCK_FLAG_RAID10 &&
                    bsb->opts[i].convert != BLOCK_FLAG_RAID5 && bsb->opts[i].convert != BLOCK_FLAG_RAID6 &&
                    bsb->opts[i].convert != BLOCK_FLAG_SINGLE)
                    return STATUS_INVALID_PARAMETER;
            }
        }
    }

    RtlCopyMemory(&Vcb->balance.opts[BALANCE_OPTS_DATA], &bsb->opts[BALANCE_OPTS_DATA], sizeof(btrfs_balance_opts));
    RtlCopyMemory(&Vcb->balance.opts[BALANCE_OPTS_METADATA], &bsb->opts[BALANCE_OPTS_METADATA], sizeof(btrfs_balance_opts));
    RtlCopyMemory(&Vcb->balance.opts[BALANCE_OPTS_SYSTEM], &bsb->opts[BALANCE_OPTS_SYSTEM], sizeof(btrfs_balance_opts));

    Vcb->balance.paused = FALSE;
    Vcb->balance.removing = FALSE;
    Vcb->balance.shrinking = FALSE;
    Vcb->balance.status = STATUS_SUCCESS;
    KeInitializeEvent(&Vcb->balance.event, NotificationEvent, !Vcb->balance.paused);

    Status = PsCreateSystemThread(&Vcb->balance.thread, 0, NULL, NULL, NULL, balance_thread, Vcb);
    if (!NT_SUCCESS(Status)) {
        ERR("PsCreateSystemThread returned %08x\n", Status);
        return Status;
    }

    return STATUS_SUCCESS;
}