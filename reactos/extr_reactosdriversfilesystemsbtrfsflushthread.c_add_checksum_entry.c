#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_20__ {TYPE_3__* item; } ;
typedef  TYPE_4__ traverse_ptr ;
struct TYPE_17__ {int sector_size; } ;
struct TYPE_21__ {int /*<<< orphan*/  checksum_root; TYPE_1__ superblock; } ;
typedef  TYPE_5__ device_extension ;
typedef  scalar_t__ ULONG ;
typedef  int UINT64 ;
typedef  scalar_t__ UINT32 ;
typedef  int UINT16 ;
struct TYPE_22__ {int offset; void* obj_type; void* obj_id; } ;
struct TYPE_18__ {int offset; } ;
struct TYPE_19__ {int size; scalar_t__* data; TYPE_2__ key; } ;
typedef  int /*<<< orphan*/  RTL_BITMAP ;
typedef  int /*<<< orphan*/  PIRP ;
typedef  scalar_t__ NTSTATUS ;
typedef  TYPE_6__ KEY ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_TAG ; 
 int /*<<< orphan*/  ERR (char*,...) ; 
 void* EXTENT_CSUM_ID ; 
 scalar_t__* ExAllocatePoolWithTag (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExFreePool (scalar_t__*) ; 
 int /*<<< orphan*/  FALSE ; 
 int MAX_CSUM_SIZE ; 
 int /*<<< orphan*/  NT_SUCCESS (scalar_t__) ; 
 int /*<<< orphan*/  PagedPool ; 
 int /*<<< orphan*/  RtlClearBits (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  RtlCopyMemory (scalar_t__*,scalar_t__*,int) ; 
 scalar_t__ RtlFindFirstRunClear (int /*<<< orphan*/ *,scalar_t__*) ; 
 scalar_t__ RtlFindNextForwardRunClear (int /*<<< orphan*/ *,scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  RtlInitializeBitMap (int /*<<< orphan*/ *,scalar_t__*,scalar_t__) ; 
 int /*<<< orphan*/  RtlSetAllBits (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RtlSetBits (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 scalar_t__ STATUS_NOT_FOUND ; 
 int /*<<< orphan*/  TRACE (char*,int,...) ; 
 void* TYPE_EXTENT_CSUM ; 
 int UInt32x32To64 (scalar_t__,int) ; 
 scalar_t__ delete_tree_item (TYPE_5__*,TYPE_4__*) ; 
 scalar_t__ find_item (TYPE_5__*,int /*<<< orphan*/ ,TYPE_4__*,TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ find_next_item (TYPE_5__*,TYPE_4__*,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ insert_tree_item (TYPE_5__*,int /*<<< orphan*/ ,void*,void*,int,scalar_t__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ min (int,int) ; 

void add_checksum_entry(device_extension* Vcb, UINT64 address, ULONG length, UINT32* csum, PIRP Irp) {
    KEY searchkey;
    traverse_ptr tp, next_tp;
    NTSTATUS Status;
    UINT64 startaddr, endaddr;
    ULONG len;
    UINT32* checksums;
    RTL_BITMAP bmp;
    ULONG* bmparr;
    ULONG runlength, index;

    searchkey.obj_id = EXTENT_CSUM_ID;
    searchkey.obj_type = TYPE_EXTENT_CSUM;
    searchkey.offset = address;

    // FIXME - create checksum_root if it doesn't exist at all

    Status = find_item(Vcb, Vcb->checksum_root, &tp, &searchkey, FALSE, Irp);
    if (Status == STATUS_NOT_FOUND) { // tree is completely empty
        if (csum) { // not deleted
            ULONG length2 = length;
            UINT64 off = address;
            UINT32* data = csum;

            do {
                UINT16 il = (UINT16)min(length2, MAX_CSUM_SIZE / sizeof(UINT32));

                checksums = ExAllocatePoolWithTag(PagedPool, il * sizeof(UINT32), ALLOC_TAG);
                if (!checksums) {
                    ERR("out of memory\n");
                    return;
                }

                RtlCopyMemory(checksums, data, il * sizeof(UINT32));

                Status = insert_tree_item(Vcb, Vcb->checksum_root, EXTENT_CSUM_ID, TYPE_EXTENT_CSUM, off, checksums,
                                          il * sizeof(UINT32), NULL, Irp);
                if (!NT_SUCCESS(Status)) {
                    ERR("insert_tree_item returned %08x\n", Status);
                    ExFreePool(checksums);
                    return;
                }

                length2 -= il;

                if (length2 > 0) {
                    off += il * Vcb->superblock.sector_size;
                    data += il;
                }
            } while (length2 > 0);
        }
    } else if (!NT_SUCCESS(Status)) {
        ERR("find_item returned %08x\n", Status);
        return;
    } else {
        UINT32 tplen;

        // FIXME - check entry is TYPE_EXTENT_CSUM?

        if (tp.item->key.offset < address && tp.item->key.offset + (tp.item->size * Vcb->superblock.sector_size / sizeof(UINT32)) >= address)
            startaddr = tp.item->key.offset;
        else
            startaddr = address;

        searchkey.obj_id = EXTENT_CSUM_ID;
        searchkey.obj_type = TYPE_EXTENT_CSUM;
        searchkey.offset = address + (length * Vcb->superblock.sector_size);

        Status = find_item(Vcb, Vcb->checksum_root, &tp, &searchkey, FALSE, Irp);
        if (!NT_SUCCESS(Status)) {
            ERR("find_item returned %08x\n", Status);
            return;
        }

        tplen = tp.item->size / sizeof(UINT32);

        if (tp.item->key.offset + (tplen * Vcb->superblock.sector_size) >= address + (length * Vcb->superblock.sector_size))
            endaddr = tp.item->key.offset + (tplen * Vcb->superblock.sector_size);
        else
            endaddr = address + (length * Vcb->superblock.sector_size);

        TRACE("cs starts at %llx (%x sectors)\n", address, length);
        TRACE("startaddr = %llx\n", startaddr);
        TRACE("endaddr = %llx\n", endaddr);

        len = (ULONG)((endaddr - startaddr) / Vcb->superblock.sector_size);

        checksums = ExAllocatePoolWithTag(PagedPool, sizeof(UINT32) * len, ALLOC_TAG);
        if (!checksums) {
            ERR("out of memory\n");
            return;
        }

        bmparr = ExAllocatePoolWithTag(PagedPool, sizeof(ULONG) * ((len/8)+1), ALLOC_TAG);
        if (!bmparr) {
            ERR("out of memory\n");
            ExFreePool(checksums);
            return;
        }

        RtlInitializeBitMap(&bmp, bmparr, len);
        RtlSetAllBits(&bmp);

        searchkey.obj_id = EXTENT_CSUM_ID;
        searchkey.obj_type = TYPE_EXTENT_CSUM;
        searchkey.offset = address;

        Status = find_item(Vcb, Vcb->checksum_root, &tp, &searchkey, FALSE, Irp);
        if (!NT_SUCCESS(Status)) {
            ERR("find_item returned %08x\n", Status);
            ExFreePool(checksums);
            ExFreePool(bmparr);
            return;
        }

        // set bit = free space, cleared bit = allocated sector

        while (tp.item->key.offset < endaddr) {
            if (tp.item->key.offset >= startaddr) {
                if (tp.item->size > 0) {
                    ULONG itemlen = (ULONG)min((len - (tp.item->key.offset - startaddr) / Vcb->superblock.sector_size) * sizeof(UINT32), tp.item->size);

                    RtlCopyMemory(&checksums[(tp.item->key.offset - startaddr) / Vcb->superblock.sector_size], tp.item->data, itemlen);
                    RtlClearBits(&bmp, (ULONG)((tp.item->key.offset - startaddr) / Vcb->superblock.sector_size), itemlen / sizeof(UINT32));
                }

                Status = delete_tree_item(Vcb, &tp);
                if (!NT_SUCCESS(Status)) {
                    ERR("delete_tree_item returned %08x\n", Status);
                    ExFreePool(checksums);
                    ExFreePool(bmparr);
                    return;
                }
            }

            if (find_next_item(Vcb, &tp, &next_tp, FALSE, Irp)) {
                tp = next_tp;
            } else
                break;
        }

        if (!csum) { // deleted
            RtlSetBits(&bmp, (ULONG)((address - startaddr) / Vcb->superblock.sector_size), length);
        } else {
            RtlCopyMemory(&checksums[(address - startaddr) / Vcb->superblock.sector_size], csum, length * sizeof(UINT32));
            RtlClearBits(&bmp, (ULONG)((address - startaddr) / Vcb->superblock.sector_size), length);
        }

        runlength = RtlFindFirstRunClear(&bmp, &index);

        while (runlength != 0) {
            do {
                UINT16 rl;
                UINT64 off;
                UINT32* data;

                if (runlength * sizeof(UINT32) > MAX_CSUM_SIZE)
                    rl = MAX_CSUM_SIZE / sizeof(UINT32);
                else
                    rl = (UINT16)runlength;

                data = ExAllocatePoolWithTag(PagedPool, sizeof(UINT32) * rl, ALLOC_TAG);
                if (!data) {
                    ERR("out of memory\n");
                    ExFreePool(bmparr);
                    ExFreePool(checksums);
                    return;
                }

                RtlCopyMemory(data, &checksums[index], sizeof(UINT32) * rl);

                off = startaddr + UInt32x32To64(index, Vcb->superblock.sector_size);

                Status = insert_tree_item(Vcb, Vcb->checksum_root, EXTENT_CSUM_ID, TYPE_EXTENT_CSUM, off, data, sizeof(UINT32) * rl, NULL, Irp);
                if (!NT_SUCCESS(Status)) {
                    ERR("insert_tree_item returned %08x\n", Status);
                    ExFreePool(data);
                    ExFreePool(bmparr);
                    ExFreePool(checksums);
                    return;
                }

                runlength -= rl;
                index += rl;
            } while (runlength > 0);

            runlength = RtlFindNextForwardRunClear(&bmp, index, &index);
        }

        ExFreePool(bmparr);
        ExFreePool(checksums);
    }
}