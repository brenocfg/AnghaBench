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
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  event; int /*<<< orphan*/  job_list; } ;
struct TYPE_8__ {TYPE_1__ calcthreads; } ;
typedef  TYPE_2__ device_extension ;
struct TYPE_9__ {int refcount; int /*<<< orphan*/  list_entry; int /*<<< orphan*/  event; scalar_t__ done; scalar_t__ pos; int /*<<< orphan*/ * csum; int /*<<< orphan*/  sectors; int /*<<< orphan*/ * data; } ;
typedef  TYPE_3__ calc_job ;
typedef  int /*<<< orphan*/  UINT8 ;
typedef  int /*<<< orphan*/  UINT32 ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_TAG ; 
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  ExAcquireResourceExclusiveLite (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_3__* ExAllocatePoolWithTag (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExReleaseResourceLite (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  InsertTailList (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KeClearEvent (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KeInitializeEvent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KeSetEvent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NonPagedPool ; 
 int /*<<< orphan*/  NotificationEvent ; 
 int /*<<< orphan*/  STATUS_INSUFFICIENT_RESOURCES ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  TRUE ; 

NTSTATUS add_calc_job(device_extension* Vcb, UINT8* data, UINT32 sectors, UINT32* csum, calc_job** pcj) {
    calc_job* cj;

    cj = ExAllocatePoolWithTag(NonPagedPool, sizeof(calc_job), ALLOC_TAG);
    if (!cj) {
        ERR("out of memory\n");
        return STATUS_INSUFFICIENT_RESOURCES;
    }

    cj->data = data;
    cj->sectors = sectors;
    cj->csum = csum;
    cj->pos = 0;
    cj->done = 0;
    cj->refcount = 1;
    KeInitializeEvent(&cj->event, NotificationEvent, FALSE);

    ExAcquireResourceExclusiveLite(&Vcb->calcthreads.lock, TRUE);

    InsertTailList(&Vcb->calcthreads.job_list, &cj->list_entry);

    KeSetEvent(&Vcb->calcthreads.event, 0, FALSE);
    KeClearEvent(&Vcb->calcthreads.event);

    ExReleaseResourceLite(&Vcb->calcthreads.lock);

    *pcj = cj;

    return STATUS_SUCCESS;
}