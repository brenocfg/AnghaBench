#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {TYPE_1__* item; } ;
typedef  TYPE_2__ traverse_ptr ;
struct TYPE_15__ {int /*<<< orphan*/  root_root; } ;
typedef  TYPE_3__ device_extension ;
typedef  int /*<<< orphan*/  UINT8 ;
typedef  void* UINT64 ;
typedef  scalar_t__ UINT16 ;
struct TYPE_16__ {void* offset; int /*<<< orphan*/  obj_type; void* obj_id; } ;
struct TYPE_13__ {scalar_t__ size; int /*<<< orphan*/  key; int /*<<< orphan*/  data; } ;
typedef  int /*<<< orphan*/  PIRP ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  TYPE_4__ KEY ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_TAG ; 
 int /*<<< orphan*/  ERR (char*,...) ; 
 int /*<<< orphan*/ * ExAllocatePoolWithTag (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExFreePool (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PagedPool ; 
 int /*<<< orphan*/  RtlCopyMemory (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  STATUS_INSUFFICIENT_RESOURCES ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  TYPE_ROOT_BACKREF ; 
 int /*<<< orphan*/  TYPE_ROOT_REF ; 
 int /*<<< orphan*/  delete_tree_item (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  find_item (TYPE_3__*,int /*<<< orphan*/ ,TYPE_2__*,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  insert_tree_item (TYPE_3__*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  keycmp (int /*<<< orphan*/ ,TYPE_4__) ; 

__attribute__((used)) static NTSTATUS update_root_backref(device_extension* Vcb, UINT64 subvolid, UINT64 parsubvolid, PIRP Irp) {
    KEY searchkey;
    traverse_ptr tp;
    UINT8* data;
    UINT16 datalen;
    NTSTATUS Status;

    searchkey.obj_id = parsubvolid;
    searchkey.obj_type = TYPE_ROOT_REF;
    searchkey.offset = subvolid;

    Status = find_item(Vcb, Vcb->root_root, &tp, &searchkey, FALSE, Irp);
    if (!NT_SUCCESS(Status)) {
        ERR("error - find_item returned %08x\n", Status);
        return Status;
    }

    if (!keycmp(tp.item->key, searchkey) && tp.item->size > 0) {
        datalen = tp.item->size;

        data = ExAllocatePoolWithTag(PagedPool, datalen, ALLOC_TAG);
        if (!data) {
            ERR("out of memory\n");
            return STATUS_INSUFFICIENT_RESOURCES;
        }

        RtlCopyMemory(data, tp.item->data, datalen);
    } else {
        datalen = 0;
        data = NULL;
    }

    searchkey.obj_id = subvolid;
    searchkey.obj_type = TYPE_ROOT_BACKREF;
    searchkey.offset = parsubvolid;

    Status = find_item(Vcb, Vcb->root_root, &tp, &searchkey, FALSE, Irp);
    if (!NT_SUCCESS(Status)) {
        ERR("error - find_item returned %08x\n", Status);

        if (datalen > 0)
            ExFreePool(data);

        return Status;
    }

    if (!keycmp(tp.item->key, searchkey)) {
        Status = delete_tree_item(Vcb, &tp);
        if (!NT_SUCCESS(Status)) {
            ERR("delete_tree_item returned %08x\n", Status);

            if (datalen > 0)
                ExFreePool(data);

            return Status;
        }
    }

    if (datalen > 0) {
        Status = insert_tree_item(Vcb, Vcb->root_root, subvolid, TYPE_ROOT_BACKREF, parsubvolid, data, datalen, NULL, Irp);
        if (!NT_SUCCESS(Status)) {
            ERR("insert_tree_item returned %08x\n", Status);
            ExFreePool(data);
            return Status;
        }
    }

    return STATUS_SUCCESS;
}