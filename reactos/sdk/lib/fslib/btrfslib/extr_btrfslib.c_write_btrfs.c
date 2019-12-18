#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  btrfs_root ;
struct TYPE_7__ {int /*<<< orphan*/  dev_id; } ;
struct TYPE_6__ {TYPE_4__ dev_item; } ;
typedef  TYPE_1__ btrfs_dev ;
typedef  int /*<<< orphan*/  btrfs_chunk ;
typedef  int /*<<< orphan*/  ULONG ;
typedef  int /*<<< orphan*/  PUNICODE_STRING ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  LIST_ENTRY ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int /*<<< orphan*/  DEV_ITEM ;
typedef  int /*<<< orphan*/  BTRFS_UUID ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int BLOCK_FLAG_DATA ; 
 int BLOCK_FLAG_DUPLICATE ; 
 int BLOCK_FLAG_METADATA ; 
 int BLOCK_FLAG_SYSTEM ; 
 int BTRFS_INCOMPAT_FLAGS_MIXED_GROUPS ; 
 int BTRFS_INCOMPAT_FLAGS_SKINNY_METADATA ; 
 int /*<<< orphan*/  BTRFS_ROOT_CHECKSUM ; 
 int /*<<< orphan*/  BTRFS_ROOT_CHUNK ; 
 int /*<<< orphan*/  BTRFS_ROOT_DATA_RELOC ; 
 int /*<<< orphan*/  BTRFS_ROOT_DEVTREE ; 
 int /*<<< orphan*/  BTRFS_ROOT_EXTENT ; 
 int /*<<< orphan*/  BTRFS_ROOT_FSTREE ; 
 int /*<<< orphan*/  BTRFS_ROOT_ROOT ; 
 int /*<<< orphan*/  InitializeListHead (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NtGetTickCount () ; 
 int /*<<< orphan*/  STATUS_INTERNAL_ERROR ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  TYPE_DEV_ITEM ; 
 int /*<<< orphan*/  add_block_group_items (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * add_chunk (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_item (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*,int) ; 
 int /*<<< orphan*/ * add_root (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assign_addresses (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  clear_first_megabyte (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_chunks (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_roots (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_uuid (int /*<<< orphan*/ *,...) ; 
 int /*<<< orphan*/  init_device (TYPE_1__*,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  init_fs_tree (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ is_ssd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_default_subvol (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  srand (unsigned int) ; 
 scalar_t__ time (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_roots (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_superblocks (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static NTSTATUS write_btrfs(HANDLE h, uint64_t size, PUNICODE_STRING label, uint32_t sector_size, uint32_t node_size, uint64_t incompat_flags) {
    NTSTATUS Status;
    LIST_ENTRY roots, chunks;
    btrfs_root *root_root, *chunk_root, *extent_root, *dev_root, *fs_root, *reloc_root;
    btrfs_chunk *sys_chunk, *metadata_chunk;
    btrfs_dev dev;
    BTRFS_UUID fsuuid, chunkuuid;
    BOOL ssd;
    uint64_t metadata_flags;
#ifdef __REACTOS__
    ULONG seed;
#endif

#ifndef __REACTOS__
    srand((unsigned int)time(0));
    get_uuid(&fsuuid);
    get_uuid(&chunkuuid);
#else
    seed = NtGetTickCount();
    get_uuid(&fsuuid, &seed);
    get_uuid(&chunkuuid, &seed);
#endif

    InitializeListHead(&roots);
    InitializeListHead(&chunks);

    root_root = add_root(&roots, BTRFS_ROOT_ROOT);
    chunk_root = add_root(&roots, BTRFS_ROOT_CHUNK);
    extent_root = add_root(&roots, BTRFS_ROOT_EXTENT);
    dev_root = add_root(&roots, BTRFS_ROOT_DEVTREE);
    add_root(&roots, BTRFS_ROOT_CHECKSUM);
    fs_root = add_root(&roots, BTRFS_ROOT_FSTREE);
    reloc_root = add_root(&roots, BTRFS_ROOT_DATA_RELOC);

#ifndef __REACTOS__
    init_device(&dev, 1, size, &fsuuid, sector_size);
#else
    init_device(&dev, 1, size, &fsuuid, sector_size, &seed);
#endif

    ssd = is_ssd(h);

    sys_chunk = add_chunk(&chunks, BLOCK_FLAG_SYSTEM | (ssd ? 0 : BLOCK_FLAG_DUPLICATE), chunk_root, &dev, dev_root, &chunkuuid, sector_size);
    if (!sys_chunk)
        return STATUS_INTERNAL_ERROR;

    metadata_flags = BLOCK_FLAG_METADATA;

    if (!ssd && !(incompat_flags & BTRFS_INCOMPAT_FLAGS_MIXED_GROUPS))
        metadata_flags |= BLOCK_FLAG_DUPLICATE;

    if (incompat_flags & BTRFS_INCOMPAT_FLAGS_MIXED_GROUPS)
        metadata_flags |= BLOCK_FLAG_DATA;

    metadata_chunk = add_chunk(&chunks, metadata_flags, chunk_root, &dev, dev_root, &chunkuuid, sector_size);
    if (!metadata_chunk)
        return STATUS_INTERNAL_ERROR;

    add_item(chunk_root, 1, TYPE_DEV_ITEM, dev.dev_item.dev_id, &dev.dev_item, sizeof(DEV_ITEM));

    set_default_subvol(root_root, node_size);

    init_fs_tree(fs_root, node_size);
    init_fs_tree(reloc_root, node_size);

    assign_addresses(&roots, sys_chunk, metadata_chunk, node_size, root_root, extent_root, incompat_flags & BTRFS_INCOMPAT_FLAGS_SKINNY_METADATA);

    add_block_group_items(&chunks, extent_root);

    Status = write_roots(h, &roots, node_size, &fsuuid, &chunkuuid);
    if (!NT_SUCCESS(Status))
        return Status;

    Status = clear_first_megabyte(h);
    if (!NT_SUCCESS(Status))
        return Status;

    Status = write_superblocks(h, &dev, chunk_root, root_root, extent_root, sys_chunk, node_size, &fsuuid, sector_size, label, incompat_flags);
    if (!NT_SUCCESS(Status))
        return Status;

    free_roots(&roots);
    free_chunks(&chunks);

    return STATUS_SUCCESS;
}