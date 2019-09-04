#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_9__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {TYPE_2__* item; } ;
typedef  TYPE_3__ traverse_ptr ;
struct TYPE_14__ {int incompat_flags; scalar_t__ node_size; } ;
struct TYPE_17__ {int /*<<< orphan*/  extent_root; TYPE_1__ superblock; } ;
typedef  TYPE_4__ device_extension ;
typedef  int ULONG ;
typedef  scalar_t__ UINT8 ;
typedef  int UINT64 ;
typedef  int UINT32 ;
struct TYPE_21__ {scalar_t__ obj_id; scalar_t__ obj_type; scalar_t__ offset; } ;
struct TYPE_20__ {int flags; int refcount; } ;
struct TYPE_19__ {int obj_id; scalar_t__ obj_type; int offset; } ;
struct TYPE_18__ {int offset; } ;
struct TYPE_15__ {int size; TYPE_9__ key; scalar_t__ data; } ;
typedef  TYPE_5__ SHARED_BLOCK_REF ;
typedef  int /*<<< orphan*/  PIRP ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  TYPE_6__ KEY ;
typedef  int /*<<< orphan*/  EXTENT_ITEM2 ;
typedef  TYPE_7__ EXTENT_ITEM ;

/* Variables and functions */
 int BTRFS_INCOMPAT_FLAGS_SKINNY_METADATA ; 
 int /*<<< orphan*/  ERR (char*,int,...) ; 
 int EXTENT_ITEM_TREE_BLOCK ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,int) ; 
 scalar_t__ TYPE_EXTENT_ITEM ; 
 scalar_t__ TYPE_METADATA_ITEM ; 
 scalar_t__ TYPE_SHARED_BLOCK_REF ; 
 int /*<<< orphan*/  find_item (TYPE_4__*,int /*<<< orphan*/ ,TYPE_3__*,TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int get_extent_data_len (scalar_t__) ; 
 int get_extent_data_refcount (scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  keycmp (TYPE_6__,TYPE_9__) ; 

UINT64 find_extent_shared_tree_refcount(device_extension* Vcb, UINT64 address, UINT64 parent, PIRP Irp) {
    NTSTATUS Status;
    KEY searchkey;
    traverse_ptr tp;
    UINT64 inline_rc;
    EXTENT_ITEM* ei;
    UINT32 len;
    UINT8* ptr;

    searchkey.obj_id = address;
    searchkey.obj_type = Vcb->superblock.incompat_flags & BTRFS_INCOMPAT_FLAGS_SKINNY_METADATA ? TYPE_METADATA_ITEM : TYPE_EXTENT_ITEM;
    searchkey.offset = 0xffffffffffffffff;

    Status = find_item(Vcb, Vcb->extent_root, &tp, &searchkey, FALSE, Irp);
    if (!NT_SUCCESS(Status)) {
        ERR("error - find_item returned %08x\n", Status);
        return 0;
    }

    if (tp.item->key.obj_id != searchkey.obj_id || (tp.item->key.obj_type != TYPE_EXTENT_ITEM && tp.item->key.obj_type != TYPE_METADATA_ITEM)) {
        TRACE("could not find address %llx in extent tree\n", address);
        return 0;
    }

    if (tp.item->key.obj_type == TYPE_EXTENT_ITEM && tp.item->key.offset != Vcb->superblock.node_size) {
        ERR("extent %llx had size %llx, not %llx as expected\n", address, tp.item->key.offset, Vcb->superblock.node_size);
        return 0;
    }

    if (tp.item->size < sizeof(EXTENT_ITEM)) {
        ERR("(%llx,%x,%llx): size was %u, expected at least %u\n", tp.item->key.obj_id, tp.item->key.obj_type, tp.item->key.offset, tp.item->size, sizeof(EXTENT_ITEM));
        return 0;
    }

    ei = (EXTENT_ITEM*)tp.item->data;
    inline_rc = 0;

    len = tp.item->size - sizeof(EXTENT_ITEM);
    ptr = (UINT8*)&ei[1];

    if (searchkey.obj_type == TYPE_EXTENT_ITEM && ei->flags & EXTENT_ITEM_TREE_BLOCK) {
        if (tp.item->size < sizeof(EXTENT_ITEM) + sizeof(EXTENT_ITEM2)) {
            ERR("(%llx,%x,%llx): size was %u, expected at least %u\n", tp.item->key.obj_id, tp.item->key.obj_type, tp.item->key.offset,
                                                                       tp.item->size, sizeof(EXTENT_ITEM) + sizeof(EXTENT_ITEM2));
            return 0;
        }

        len -= sizeof(EXTENT_ITEM2);
        ptr += sizeof(EXTENT_ITEM2);
    }

    while (len > 0) {
        UINT8 secttype = *ptr;
        ULONG sectlen = get_extent_data_len(secttype);
        UINT64 sectcount = get_extent_data_refcount(secttype, ptr + sizeof(UINT8));

        len--;

        if (sectlen > len) {
            ERR("(%llx,%x,%llx): %x bytes left, expecting at least %x\n", tp.item->key.obj_id, tp.item->key.obj_type, tp.item->key.offset, len, sectlen);
            return 0;
        }

        if (sectlen == 0) {
            ERR("(%llx,%x,%llx): unrecognized extent type %x\n", tp.item->key.obj_id, tp.item->key.obj_type, tp.item->key.offset, secttype);
            return 0;
        }

        if (secttype == TYPE_SHARED_BLOCK_REF) {
            SHARED_BLOCK_REF* sectsbr = (SHARED_BLOCK_REF*)(ptr + sizeof(UINT8));

            if (sectsbr->offset == parent)
                return 1;
        }

        len -= sectlen;
        ptr += sizeof(UINT8) + sectlen;
        inline_rc += sectcount;
    }

    // FIXME - what if old?

    if (inline_rc == ei->refcount)
        return 0;

    searchkey.obj_id = address;
    searchkey.obj_type = TYPE_SHARED_BLOCK_REF;
    searchkey.offset = parent;

    Status = find_item(Vcb, Vcb->extent_root, &tp, &searchkey, FALSE, Irp);
    if (!NT_SUCCESS(Status)) {
        ERR("error - find_item returned %08x\n", Status);
        return 0;
    }

    if (!keycmp(searchkey, tp.item->key))
        return 1;

    return 0;
}