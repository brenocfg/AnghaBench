#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  sector_size; } ;
struct TYPE_6__ {TYPE_1__ superblock; } ;
typedef  TYPE_2__ device_extension ;
typedef  int ULONG ;
struct TYPE_7__ {int /*<<< orphan*/  ClusterSizeInBytes; int /*<<< orphan*/  ChecksumChunkSizeInBytes; scalar_t__ Flags; scalar_t__ Reserved; scalar_t__ ChecksumAlgorithm; } ;
typedef  int /*<<< orphan*/  PFILE_OBJECT ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  TYPE_3__ FSCTL_GET_INTEGRITY_INFORMATION_BUFFER ;

/* Variables and functions */
 int /*<<< orphan*/  STATUS_INVALID_PARAMETER ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  TRACE (char*) ; 

__attribute__((used)) static NTSTATUS get_integrity_information(device_extension* Vcb, PFILE_OBJECT FileObject, void* data, ULONG datalen) {
    FSCTL_GET_INTEGRITY_INFORMATION_BUFFER* fgiib = (FSCTL_GET_INTEGRITY_INFORMATION_BUFFER*)data;

    TRACE("FSCTL_GET_INTEGRITY_INFORMATION\n");

    // STUB

    if (!FileObject)
        return STATUS_INVALID_PARAMETER;

    if (!data || datalen < sizeof(FSCTL_GET_INTEGRITY_INFORMATION_BUFFER))
        return STATUS_INVALID_PARAMETER;

    fgiib->ChecksumAlgorithm = 0;
    fgiib->Reserved = 0;
    fgiib->Flags = 0;
    fgiib->ChecksumChunkSizeInBytes = Vcb->superblock.sector_size;
    fgiib->ClusterSizeInBytes = Vcb->superblock.sector_size;

    return STATUS_SUCCESS;
}