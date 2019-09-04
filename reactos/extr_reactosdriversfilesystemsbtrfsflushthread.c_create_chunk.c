#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_34__   TYPE_8__ ;
typedef  struct TYPE_33__   TYPE_7__ ;
typedef  struct TYPE_32__   TYPE_6__ ;
typedef  struct TYPE_31__   TYPE_5__ ;
typedef  struct TYPE_30__   TYPE_4__ ;
typedef  struct TYPE_29__   TYPE_3__ ;
typedef  struct TYPE_28__   TYPE_2__ ;
typedef  struct TYPE_27__   TYPE_21__ ;
typedef  struct TYPE_26__   TYPE_1__ ;
typedef  struct TYPE_25__   TYPE_14__ ;
typedef  struct TYPE_24__   TYPE_12__ ;

/* Type definitions */
struct TYPE_31__ {TYPE_14__* dev_root; TYPE_14__* chunk_root; TYPE_14__* extent_root; } ;
typedef  TYPE_5__ device_extension ;
struct TYPE_32__ {int size; int offset; int /*<<< orphan*/  created; TYPE_12__** devices; TYPE_21__* chunk_item; int /*<<< orphan*/  used; } ;
typedef  TYPE_6__ chunk ;
typedef  size_t UINT16 ;
struct TYPE_34__ {int offset; } ;
struct TYPE_33__ {int chunk_tree; int flags; int objid; int address; size_t length; int /*<<< orphan*/  chunktree_uuid; int /*<<< orphan*/  chunktree; int /*<<< orphan*/  used; } ;
struct TYPE_30__ {int dev_id; } ;
struct TYPE_29__ {TYPE_2__* tree; } ;
struct TYPE_26__ {int /*<<< orphan*/  chunk_tree_uuid; } ;
struct TYPE_28__ {TYPE_1__ header; } ;
struct TYPE_27__ {int type; int size; size_t num_stripes; size_t sub_stripes; } ;
struct TYPE_25__ {TYPE_3__ treeholder; int /*<<< orphan*/  id; } ;
struct TYPE_24__ {TYPE_4__ devitem; } ;
typedef  int /*<<< orphan*/  PIRP ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  TYPE_7__ DEV_EXTENT ;
typedef  TYPE_8__ CHUNK_ITEM_STRIPE ;
typedef  TYPE_7__ CHUNK_ITEM ;
typedef  TYPE_7__ BLOCK_GROUP_ITEM ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_TAG ; 
 int BLOCK_FLAG_RAID0 ; 
 int BLOCK_FLAG_RAID10 ; 
 int BLOCK_FLAG_RAID5 ; 
 int BLOCK_FLAG_RAID6 ; 
 int BLOCK_FLAG_SYSTEM ; 
 int /*<<< orphan*/  ERR (char*,...) ; 
 TYPE_7__* ExAllocatePoolWithTag (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExFreePool (TYPE_7__*) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PagedPool ; 
 int /*<<< orphan*/  RtlCopyMemory (TYPE_7__*,TYPE_21__*,int) ; 
 int /*<<< orphan*/  STATUS_INSUFFICIENT_RESOURCES ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  TYPE_BLOCK_GROUP_ITEM ; 
 int /*<<< orphan*/  TYPE_CHUNK_ITEM ; 
 int /*<<< orphan*/  TYPE_DEV_EXTENT ; 
 int /*<<< orphan*/  add_to_bootstrap (TYPE_5__*,int,int /*<<< orphan*/ ,int,TYPE_7__*,int) ; 
 int /*<<< orphan*/  insert_tree_item (TYPE_5__*,TYPE_14__*,int,int /*<<< orphan*/ ,int,TYPE_7__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_dev_item (TYPE_5__*,TYPE_12__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static NTSTATUS create_chunk(device_extension* Vcb, chunk* c, PIRP Irp) {
    CHUNK_ITEM* ci;
    CHUNK_ITEM_STRIPE* cis;
    BLOCK_GROUP_ITEM* bgi;
    UINT16 i, factor;
    NTSTATUS Status;

    ci = ExAllocatePoolWithTag(PagedPool, c->size, ALLOC_TAG);
    if (!ci) {
        ERR("out of memory\n");
        return STATUS_INSUFFICIENT_RESOURCES;
    }

    RtlCopyMemory(ci, c->chunk_item, c->size);

    Status = insert_tree_item(Vcb, Vcb->chunk_root, 0x100, TYPE_CHUNK_ITEM, c->offset, ci, c->size, NULL, Irp);
    if (!NT_SUCCESS(Status)) {
        ERR("insert_tree_item failed\n");
        ExFreePool(ci);
        return Status;
    }

    if (c->chunk_item->type & BLOCK_FLAG_SYSTEM) {
        Status = add_to_bootstrap(Vcb, 0x100, TYPE_CHUNK_ITEM, c->offset, ci, c->size);
        if (!NT_SUCCESS(Status)) {
            ERR("add_to_bootstrap returned %08x\n", Status);
            return Status;
        }
    }

    // add BLOCK_GROUP_ITEM to tree 2

    bgi = ExAllocatePoolWithTag(PagedPool, sizeof(BLOCK_GROUP_ITEM), ALLOC_TAG);
    if (!bgi) {
        ERR("out of memory\n");
        return STATUS_INSUFFICIENT_RESOURCES;
    }

    bgi->used = c->used;
    bgi->chunk_tree = 0x100;
    bgi->flags = c->chunk_item->type;

    Status = insert_tree_item(Vcb, Vcb->extent_root, c->offset, TYPE_BLOCK_GROUP_ITEM, c->chunk_item->size, bgi, sizeof(BLOCK_GROUP_ITEM), NULL, Irp);
    if (!NT_SUCCESS(Status)) {
        ERR("insert_tree_item failed\n");
        ExFreePool(bgi);
        return Status;
    }

    if (c->chunk_item->type & BLOCK_FLAG_RAID0)
        factor = c->chunk_item->num_stripes;
    else if (c->chunk_item->type & BLOCK_FLAG_RAID10)
        factor = c->chunk_item->num_stripes / c->chunk_item->sub_stripes;
    else if (c->chunk_item->type & BLOCK_FLAG_RAID5)
        factor = c->chunk_item->num_stripes - 1;
    else if (c->chunk_item->type & BLOCK_FLAG_RAID6)
        factor = c->chunk_item->num_stripes - 2;
    else // SINGLE, DUPLICATE, RAID1
        factor = 1;

    // add DEV_EXTENTs to tree 4

    cis = (CHUNK_ITEM_STRIPE*)&c->chunk_item[1];

    for (i = 0; i < c->chunk_item->num_stripes; i++) {
        DEV_EXTENT* de;

        de = ExAllocatePoolWithTag(PagedPool, sizeof(DEV_EXTENT), ALLOC_TAG);
        if (!de) {
            ERR("out of memory\n");
            return STATUS_INSUFFICIENT_RESOURCES;
        }

        de->chunktree = Vcb->chunk_root->id;
        de->objid = 0x100;
        de->address = c->offset;
        de->length = c->chunk_item->size / factor;
        de->chunktree_uuid = Vcb->chunk_root->treeholder.tree->header.chunk_tree_uuid;

        Status = insert_tree_item(Vcb, Vcb->dev_root, c->devices[i]->devitem.dev_id, TYPE_DEV_EXTENT, cis[i].offset, de, sizeof(DEV_EXTENT), NULL, Irp);
        if (!NT_SUCCESS(Status)) {
            ERR("insert_tree_item returned %08x\n", Status);
            ExFreePool(de);
            return Status;
        }

        // FIXME - no point in calling this twice for the same device
        Status = update_dev_item(Vcb, c->devices[i], Irp);
        if (!NT_SUCCESS(Status)) {
            ERR("update_dev_item returned %08x\n", Status);
            return Status;
        }
    }

    c->created = FALSE;

    return STATUS_SUCCESS;
}