#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_9__ ;
typedef  struct TYPE_22__   TYPE_8__ ;
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {scalar_t__ address; } ;
struct TYPE_19__ {void* is_unique; void* uniqueness_determined; TYPE_2__ header; scalar_t__ has_address; struct TYPE_19__* parent; } ;
typedef  TYPE_5__ tree ;
struct TYPE_20__ {TYPE_4__* item; } ;
typedef  TYPE_6__ traverse_ptr ;
struct TYPE_15__ {int incompat_flags; } ;
struct TYPE_21__ {int /*<<< orphan*/  extent_root; TYPE_1__ superblock; } ;
typedef  TYPE_7__ device_extension ;
typedef  scalar_t__ UINT8 ;
struct TYPE_23__ {int refcount; int flags; } ;
struct TYPE_22__ {scalar_t__ obj_id; int offset; scalar_t__ obj_type; } ;
struct TYPE_17__ {scalar_t__ obj_id; scalar_t__ obj_type; } ;
struct TYPE_18__ {int size; scalar_t__* data; TYPE_3__ key; } ;
typedef  int /*<<< orphan*/  PIRP ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  TYPE_8__ KEY ;
typedef  int /*<<< orphan*/  EXTENT_ITEM_V0 ;
typedef  int /*<<< orphan*/  EXTENT_ITEM2 ;
typedef  TYPE_9__ EXTENT_ITEM ;
typedef  void* BOOL ;

/* Variables and functions */
 int BTRFS_INCOMPAT_FLAGS_SKINNY_METADATA ; 
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ) ; 
 int EXTENT_ITEM_TREE_BLOCK ; 
 void* FALSE ; 
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 void* TRUE ; 
 scalar_t__ TYPE_EXTENT_ITEM ; 
 scalar_t__ TYPE_METADATA_ITEM ; 
 scalar_t__ TYPE_TREE_BLOCK_REF ; 
 int /*<<< orphan*/  find_item (TYPE_7__*,int /*<<< orphan*/ ,TYPE_6__*,TYPE_8__*,void*,int /*<<< orphan*/ ) ; 

BOOL is_tree_unique(device_extension* Vcb, tree* t, PIRP Irp) {
    KEY searchkey;
    traverse_ptr tp;
    NTSTATUS Status;
    BOOL ret = FALSE;
    EXTENT_ITEM* ei;
    UINT8* type;

    if (t->uniqueness_determined)
        return t->is_unique;

    if (t->parent && !is_tree_unique(Vcb, t->parent, Irp))
        goto end;

    if (t->has_address) {
        searchkey.obj_id = t->header.address;
        searchkey.obj_type = Vcb->superblock.incompat_flags & BTRFS_INCOMPAT_FLAGS_SKINNY_METADATA ? TYPE_METADATA_ITEM : TYPE_EXTENT_ITEM;
        searchkey.offset = 0xffffffffffffffff;

        Status = find_item(Vcb, Vcb->extent_root, &tp, &searchkey, FALSE, Irp);
        if (!NT_SUCCESS(Status)) {
            ERR("error - find_item returned %08x\n", Status);
            goto end;
        }

        if (tp.item->key.obj_id != t->header.address || (tp.item->key.obj_type != TYPE_METADATA_ITEM && tp.item->key.obj_type != TYPE_EXTENT_ITEM))
            goto end;

        if (tp.item->key.obj_type == TYPE_EXTENT_ITEM && tp.item->size == sizeof(EXTENT_ITEM_V0))
            goto end;

        if (tp.item->size < sizeof(EXTENT_ITEM))
            goto end;

        ei = (EXTENT_ITEM*)tp.item->data;

        if (ei->refcount > 1)
            goto end;

        if (tp.item->key.obj_type == TYPE_EXTENT_ITEM && ei->flags & EXTENT_ITEM_TREE_BLOCK) {
            EXTENT_ITEM2* ei2;

            if (tp.item->size < sizeof(EXTENT_ITEM) + sizeof(EXTENT_ITEM2))
                goto end;

            ei2 = (EXTENT_ITEM2*)&ei[1];
            type = (UINT8*)&ei2[1];
        } else
            type = (UINT8*)&ei[1];

        if (type >= tp.item->data + tp.item->size || *type != TYPE_TREE_BLOCK_REF)
            goto end;
    }

    ret = TRUE;

end:
    t->is_unique = ret;
    t->uniqueness_determined = TRUE;

    return ret;
}