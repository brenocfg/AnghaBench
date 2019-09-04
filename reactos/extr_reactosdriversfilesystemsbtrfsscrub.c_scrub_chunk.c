#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_32__   TYPE_9__ ;
typedef  struct TYPE_31__   TYPE_8__ ;
typedef  struct TYPE_30__   TYPE_7__ ;
typedef  struct TYPE_29__   TYPE_6__ ;
typedef  struct TYPE_28__   TYPE_5__ ;
typedef  struct TYPE_27__   TYPE_4__ ;
typedef  struct TYPE_26__   TYPE_3__ ;
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_1__ ;

/* Type definitions */
struct TYPE_28__ {TYPE_4__* item; } ;
typedef  TYPE_5__ traverse_ptr ;
struct TYPE_25__ {int node_size; int sector_size; } ;
struct TYPE_29__ {int /*<<< orphan*/  tree_lock; TYPE_2__ superblock; int /*<<< orphan*/  checksum_root; int /*<<< orphan*/  extent_root; } ;
typedef  TYPE_6__ device_extension ;
struct TYPE_30__ {int offset; TYPE_1__* chunk_item; } ;
typedef  TYPE_7__ chunk ;
typedef  int ULONG ;
typedef  int UINT64 ;
typedef  int UINT32 ;
struct TYPE_32__ {int flags; } ;
struct TYPE_31__ {int obj_id; int offset; scalar_t__ obj_type; } ;
struct TYPE_26__ {int obj_id; scalar_t__ obj_type; int offset; } ;
struct TYPE_27__ {int size; TYPE_3__ key; scalar_t__ data; } ;
struct TYPE_24__ {int type; int size; } ;
typedef  int /*<<< orphan*/  RTL_BITMAP ;
typedef  scalar_t__ NTSTATUS ;
typedef  TYPE_8__ KEY ;
typedef  TYPE_9__ EXTENT_ITEM ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_TAG ; 
 int BLOCK_FLAG_DUPLICATE ; 
 int BLOCK_FLAG_RAID0 ; 
 int BLOCK_FLAG_RAID1 ; 
 int BLOCK_FLAG_RAID10 ; 
 int BLOCK_FLAG_RAID5 ; 
 int BLOCK_FLAG_RAID6 ; 
 int /*<<< orphan*/  ERR (char*,...) ; 
 int EXTENT_CSUM_ID ; 
 int EXTENT_ITEM_TREE_BLOCK ; 
 int /*<<< orphan*/  ExAcquireResourceSharedLite (int /*<<< orphan*/ *,scalar_t__) ; 
 int* ExAllocatePoolWithTag (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExFreePool (int*) ; 
 int /*<<< orphan*/  ExReleaseResourceLite (int /*<<< orphan*/ *) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  NT_SUCCESS (scalar_t__) ; 
 int /*<<< orphan*/  PagedPool ; 
 int /*<<< orphan*/  RtlClearBits (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  RtlCopyMemory (int*,scalar_t__,int) ; 
 int /*<<< orphan*/  RtlInitializeBitMap (int /*<<< orphan*/ *,int*,int) ; 
 int /*<<< orphan*/  RtlSetAllBits (int /*<<< orphan*/ *) ; 
 scalar_t__ STATUS_INSUFFICIENT_RESOURCES ; 
 scalar_t__ STATUS_INTERNAL_ERROR ; 
 scalar_t__ STATUS_NOT_FOUND ; 
 scalar_t__ STATUS_SUCCESS ; 
 int /*<<< orphan*/  TRACE (char*,int) ; 
 scalar_t__ TRUE ; 
 scalar_t__ TYPE_EXTENT_CSUM ; 
 scalar_t__ TYPE_EXTENT_ITEM ; 
 scalar_t__ TYPE_METADATA_ITEM ; 
 scalar_t__ find_item (TYPE_6__*,int /*<<< orphan*/ ,TYPE_5__*,TYPE_8__*,scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ find_next_item (TYPE_6__*,TYPE_5__*,TYPE_5__*,scalar_t__,int /*<<< orphan*/ *) ; 
 int max (int,int) ; 
 int min (int,int) ; 
 scalar_t__ scrub_chunk_raid56 (TYPE_6__*,TYPE_7__*,int*,scalar_t__*) ; 
 scalar_t__ scrub_data_extent (TYPE_6__*,TYPE_7__*,int,int,int*,int /*<<< orphan*/ *) ; 
 scalar_t__ scrub_extent (TYPE_6__*,TYPE_7__*,int,int,int,int /*<<< orphan*/ *) ; 
 scalar_t__ sector_align (int,int) ; 

__attribute__((used)) static NTSTATUS scrub_chunk(device_extension* Vcb, chunk* c, UINT64* offset, BOOL* changed) {
    NTSTATUS Status;
    KEY searchkey;
    traverse_ptr tp;
    BOOL b = FALSE, tree_run = FALSE;
    ULONG type, num_extents = 0;
    UINT64 total_data = 0, tree_run_start, tree_run_end;

    TRACE("chunk %llx\n", c->offset);

    ExAcquireResourceSharedLite(&Vcb->tree_lock, TRUE);

    if (c->chunk_item->type & BLOCK_FLAG_DUPLICATE)
        type = BLOCK_FLAG_DUPLICATE;
    else if (c->chunk_item->type & BLOCK_FLAG_RAID0)
        type = BLOCK_FLAG_RAID0;
    else if (c->chunk_item->type & BLOCK_FLAG_RAID1)
        type = BLOCK_FLAG_DUPLICATE;
    else if (c->chunk_item->type & BLOCK_FLAG_RAID10)
        type = BLOCK_FLAG_RAID10;
    else if (c->chunk_item->type & BLOCK_FLAG_RAID5) {
        Status = scrub_chunk_raid56(Vcb, c, offset, changed);
        goto end;
    } else if (c->chunk_item->type & BLOCK_FLAG_RAID6) {
        Status = scrub_chunk_raid56(Vcb, c, offset, changed);
        goto end;
    } else // SINGLE
        type = BLOCK_FLAG_DUPLICATE;

    searchkey.obj_id = *offset;
    searchkey.obj_type = TYPE_METADATA_ITEM;
    searchkey.offset = 0xffffffffffffffff;

    Status = find_item(Vcb, Vcb->extent_root, &tp, &searchkey, FALSE, NULL);
    if (!NT_SUCCESS(Status)) {
        ERR("error - find_item returned %08x\n", Status);
        goto end;
    }

    do {
        traverse_ptr next_tp;

        if (tp.item->key.obj_id >= c->offset + c->chunk_item->size)
            break;

        if (tp.item->key.obj_id >= *offset && (tp.item->key.obj_type == TYPE_EXTENT_ITEM || tp.item->key.obj_type == TYPE_METADATA_ITEM)) {
            UINT64 size = tp.item->key.obj_type == TYPE_METADATA_ITEM ? Vcb->superblock.node_size : tp.item->key.offset;
            BOOL is_tree;
            UINT32* csum = NULL;
            RTL_BITMAP bmp;
            ULONG* bmparr = NULL;

            TRACE("%llx\n", tp.item->key.obj_id);

            is_tree = FALSE;

            if (tp.item->key.obj_type == TYPE_METADATA_ITEM)
                is_tree = TRUE;
            else {
                EXTENT_ITEM* ei = (EXTENT_ITEM*)tp.item->data;

                if (tp.item->size < sizeof(EXTENT_ITEM)) {
                    ERR("(%llx,%x,%llx) was %u bytes, expected at least %u\n", tp.item->key.obj_id, tp.item->key.obj_type, tp.item->key.offset, tp.item->size, sizeof(EXTENT_ITEM));
                    Status = STATUS_INTERNAL_ERROR;
                    goto end;
                }

                if (ei->flags & EXTENT_ITEM_TREE_BLOCK)
                    is_tree = TRUE;
            }

            if (size < Vcb->superblock.sector_size) {
                ERR("extent %llx has size less than sector_size (%llx < %x)\n", tp.item->key.obj_id, Vcb->superblock.sector_size);
                Status = STATUS_INTERNAL_ERROR;
                goto end;
            }

            // load csum
            if (!is_tree) {
                traverse_ptr tp2;

                csum = ExAllocatePoolWithTag(PagedPool, (ULONG)(sizeof(UINT32) * size / Vcb->superblock.sector_size), ALLOC_TAG);
                if (!csum) {
                    ERR("out of memory\n");
                    Status = STATUS_INSUFFICIENT_RESOURCES;
                    goto end;
                }

                bmparr = ExAllocatePoolWithTag(PagedPool, (ULONG)(sector_align(((size / Vcb->superblock.sector_size) >> 3) + 1, sizeof(ULONG))), ALLOC_TAG);
                if (!bmparr) {
                    ERR("out of memory\n");
                    ExFreePool(csum);
                    Status = STATUS_INSUFFICIENT_RESOURCES;
                    goto end;
                }

                RtlInitializeBitMap(&bmp, bmparr, (ULONG)(size / Vcb->superblock.sector_size));
                RtlSetAllBits(&bmp); // 1 = no csum, 0 = csum

                searchkey.obj_id = EXTENT_CSUM_ID;
                searchkey.obj_type = TYPE_EXTENT_CSUM;
                searchkey.offset = tp.item->key.obj_id;

                Status = find_item(Vcb, Vcb->checksum_root, &tp2, &searchkey, FALSE, NULL);
                if (!NT_SUCCESS(Status) && Status != STATUS_NOT_FOUND) {
                    ERR("find_item returned %08x\n", Status);
                    ExFreePool(csum);
                    ExFreePool(bmparr);
                    goto end;
                }

                if (Status != STATUS_NOT_FOUND) {
                    do {
                        traverse_ptr next_tp2;

                        if (tp2.item->key.obj_type == TYPE_EXTENT_CSUM) {
                            if (tp2.item->key.offset >= tp.item->key.obj_id + size)
                                break;
                            else if (tp2.item->size >= sizeof(UINT32) && tp2.item->key.offset + (tp2.item->size * Vcb->superblock.sector_size / sizeof(UINT32)) >= tp.item->key.obj_id) {
                                UINT64 cs = max(tp.item->key.obj_id, tp2.item->key.offset);
                                UINT64 ce = min(tp.item->key.obj_id + size, tp2.item->key.offset + (tp2.item->size * Vcb->superblock.sector_size / sizeof(UINT32)));

                                RtlCopyMemory(csum + ((cs - tp.item->key.obj_id) / Vcb->superblock.sector_size),
                                              tp2.item->data + ((cs - tp2.item->key.offset) * sizeof(UINT32) / Vcb->superblock.sector_size),
                                              (ULONG)((ce - cs) * sizeof(UINT32) / Vcb->superblock.sector_size));

                                RtlClearBits(&bmp, (ULONG)((cs - tp.item->key.obj_id) / Vcb->superblock.sector_size), (ULONG)((ce - cs) / Vcb->superblock.sector_size));

                                if (ce == tp.item->key.obj_id + size)
                                    break;
                            }
                        }

                        if (find_next_item(Vcb, &tp2, &next_tp2, FALSE, NULL))
                            tp2 = next_tp2;
                        else
                            break;
                    } while (TRUE);
                }
            }

            if (tree_run) {
                if (!is_tree || tp.item->key.obj_id > tree_run_end) {
                    Status = scrub_extent(Vcb, c, type, tree_run_start, (UINT32)(tree_run_end - tree_run_start), NULL);
                    if (!NT_SUCCESS(Status)) {
                        ERR("scrub_extent returned %08x\n", Status);
                        goto end;
                    }

                    if (!is_tree)
                        tree_run = FALSE;
                    else {
                        tree_run_start = tp.item->key.obj_id;
                        tree_run_end = tp.item->key.obj_id + Vcb->superblock.node_size;
                    }
                } else
                    tree_run_end = tp.item->key.obj_id + Vcb->superblock.node_size;
            } else if (is_tree) {
                tree_run = TRUE;
                tree_run_start = tp.item->key.obj_id;
                tree_run_end = tp.item->key.obj_id + Vcb->superblock.node_size;
            }

            if (!is_tree) {
                Status = scrub_data_extent(Vcb, c, tp.item->key.obj_id, type, csum, &bmp);
                if (!NT_SUCCESS(Status)) {
                    ERR("scrub_data_extent returned %08x\n", Status);
                    ExFreePool(csum);
                    ExFreePool(bmparr);
                    goto end;
                }

                ExFreePool(csum);
                ExFreePool(bmparr);
            }

            *offset = tp.item->key.obj_id + size;
            *changed = TRUE;

            total_data += size;
            num_extents++;

            // only do so much at a time
            if (num_extents >= 64 || total_data >= 0x8000000) // 128 MB
                break;
        }

        b = find_next_item(Vcb, &tp, &next_tp, FALSE, NULL);

        if (b)
            tp = next_tp;
    } while (b);

    if (tree_run) {
        Status = scrub_extent(Vcb, c, type, tree_run_start, (UINT32)(tree_run_end - tree_run_start), NULL);
        if (!NT_SUCCESS(Status)) {
            ERR("scrub_extent returned %08x\n", Status);
            goto end;
        }
    }

    Status = STATUS_SUCCESS;

end:
    ExReleaseResourceLite(&Vcb->tree_lock);

    return Status;
}