#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_46__   TYPE_7__ ;
typedef  struct TYPE_45__   TYPE_6__ ;
typedef  struct TYPE_44__   TYPE_5__ ;
typedef  struct TYPE_43__   TYPE_4__ ;
typedef  struct TYPE_42__   TYPE_3__ ;
typedef  struct TYPE_41__   TYPE_2__ ;
typedef  struct TYPE_40__   TYPE_1__ ;

/* Type definitions */
typedef  int UINT32 ;
struct TYPE_46__ {int /*<<< orphan*/  DeviceExtension; } ;
struct TYPE_42__ {int FsControlCode; int /*<<< orphan*/  InputBufferLength; int /*<<< orphan*/  OutputBufferLength; int /*<<< orphan*/  Type3InputBuffer; } ;
struct TYPE_43__ {TYPE_3__ FileSystemControl; } ;
struct TYPE_45__ {TYPE_4__ Parameters; int /*<<< orphan*/  FileObject; } ;
struct TYPE_41__ {int /*<<< orphan*/  SystemBuffer; } ;
struct TYPE_40__ {int /*<<< orphan*/  Information; } ;
struct TYPE_44__ {TYPE_2__ AssociatedIrp; int /*<<< orphan*/  RequestorMode; TYPE_1__ IoStatus; int /*<<< orphan*/  UserBuffer; } ;
typedef  TYPE_5__* PIRP ;
typedef  TYPE_6__* PIO_STACK_LOCATION ;
typedef  TYPE_7__* PDEVICE_OBJECT ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
#define  FSCTL_ALLOW_EXTENDED_DASD_IO 222 
#define  FSCTL_BTRFS_ADD_DEVICE 221 
#define  FSCTL_BTRFS_CREATE_SNAPSHOT 220 
#define  FSCTL_BTRFS_CREATE_SUBVOL 219 
#define  FSCTL_BTRFS_FIND_SUBVOL 218 
#define  FSCTL_BTRFS_GET_DEVICES 217 
#define  FSCTL_BTRFS_GET_FILE_IDS 216 
#define  FSCTL_BTRFS_GET_INODE_INFO 215 
#define  FSCTL_BTRFS_GET_USAGE 214 
#define  FSCTL_BTRFS_GET_UUID 213 
#define  FSCTL_BTRFS_GET_XATTRS 212 
#define  FSCTL_BTRFS_MKNOD 211 
#define  FSCTL_BTRFS_PAUSE_BALANCE 210 
#define  FSCTL_BTRFS_PAUSE_SCRUB 209 
#define  FSCTL_BTRFS_QUERY_BALANCE 208 
#define  FSCTL_BTRFS_QUERY_SCRUB 207 
#define  FSCTL_BTRFS_READ_SEND_BUFFER 206 
#define  FSCTL_BTRFS_RECEIVED_SUBVOL 205 
#define  FSCTL_BTRFS_REMOVE_DEVICE 204 
#define  FSCTL_BTRFS_RESERVE_SUBVOL 203 
#define  FSCTL_BTRFS_RESET_STATS 202 
#define  FSCTL_BTRFS_RESIZE 201 
#define  FSCTL_BTRFS_RESUME_BALANCE 200 
#define  FSCTL_BTRFS_RESUME_SCRUB 199 
#define  FSCTL_BTRFS_SEND_SUBVOL 198 
#define  FSCTL_BTRFS_SET_INODE_INFO 197 
#define  FSCTL_BTRFS_SET_XATTR 196 
#define  FSCTL_BTRFS_START_BALANCE 195 
#define  FSCTL_BTRFS_START_SCRUB 194 
#define  FSCTL_BTRFS_STOP_BALANCE 193 
#define  FSCTL_BTRFS_STOP_SCRUB 192 
#define  FSCTL_CREATE_OR_GET_OBJECT_ID 191 
#define  FSCTL_CREATE_USN_JOURNAL 190 
#define  FSCTL_DELETE_OBJECT_ID 189 
#define  FSCTL_DELETE_REPARSE_POINT 188 
#define  FSCTL_DELETE_USN_JOURNAL 187 
#define  FSCTL_DISMOUNT_VOLUME 186 
#define  FSCTL_DUPLICATE_EXTENTS_TO_FILE 185 
#define  FSCTL_ENABLE_UPGRADE 184 
#define  FSCTL_ENCRYPTION_FSCTL_IO 183 
#define  FSCTL_ENUM_USN_DATA 182 
#define  FSCTL_EXTEND_VOLUME 181 
#define  FSCTL_FILESYSTEM_GET_STATISTICS 180 
#define  FSCTL_FILE_PREFETCH 179 
#define  FSCTL_FIND_FILES_BY_SID 178 
#define  FSCTL_GET_COMPRESSION 177 
#define  FSCTL_GET_INTEGRITY_INFORMATION 176 
#define  FSCTL_GET_NTFS_FILE_RECORD 175 
#define  FSCTL_GET_NTFS_VOLUME_DATA 174 
#define  FSCTL_GET_OBJECT_ID 173 
#define  FSCTL_GET_REPARSE_POINT 172 
#define  FSCTL_GET_RETRIEVAL_POINTERS 171 
#define  FSCTL_GET_VOLUME_BITMAP 170 
#define  FSCTL_INVALIDATE_VOLUMES 169 
#define  FSCTL_IS_PATHNAME_VALID 168 
#define  FSCTL_IS_VOLUME_DIRTY 167 
#define  FSCTL_IS_VOLUME_MOUNTED 166 
#define  FSCTL_LOCK_VOLUME 165 
#define  FSCTL_MARK_HANDLE 164 
#define  FSCTL_MARK_VOLUME_DIRTY 163 
#define  FSCTL_MOVE_FILE 162 
#define  FSCTL_OPBATCH_ACK_CLOSE_PENDING 161 
#define  FSCTL_OPLOCK_BREAK_ACKNOWLEDGE 160 
#define  FSCTL_OPLOCK_BREAK_ACK_NO_2 159 
#define  FSCTL_OPLOCK_BREAK_NOTIFY 158 
#define  FSCTL_QUERY_ALLOCATED_RANGES 157 
#define  FSCTL_QUERY_FAT_BPB 156 
#define  FSCTL_QUERY_RETRIEVAL_POINTERS 155 
#define  FSCTL_QUERY_USN_JOURNAL 154 
#define  FSCTL_QUERY_VOLUME_CONTAINER_STATE 153 
#define  FSCTL_READ_FILE_USN_DATA 152 
#define  FSCTL_READ_FROM_PLEX 151 
#define  FSCTL_READ_RAW_ENCRYPTED 150 
#define  FSCTL_READ_USN_JOURNAL 149 
#define  FSCTL_RECALL_FILE 148 
#define  FSCTL_REQUEST_BATCH_OPLOCK 147 
#define  FSCTL_REQUEST_FILTER_OPLOCK 146 
#define  FSCTL_REQUEST_OPLOCK 145 
#define  FSCTL_REQUEST_OPLOCK_LEVEL_1 144 
#define  FSCTL_REQUEST_OPLOCK_LEVEL_2 143 
#define  FSCTL_SECURITY_ID_CHECK 142 
#define  FSCTL_SET_BOOTLOADER_ACCESSED 141 
#define  FSCTL_SET_COMPRESSION 140 
#define  FSCTL_SET_ENCRYPTION 139 
#define  FSCTL_SET_INTEGRITY_INFORMATION 138 
#define  FSCTL_SET_OBJECT_ID 137 
#define  FSCTL_SET_OBJECT_ID_EXTENDED 136 
#define  FSCTL_SET_REPARSE_POINT 135 
#define  FSCTL_SET_SPARSE 134 
#define  FSCTL_SET_ZERO_DATA 133 
#define  FSCTL_SIS_COPYFILE 132 
#define  FSCTL_SIS_LINK_FILES 131 
#define  FSCTL_UNLOCK_VOLUME 130 
#define  FSCTL_WRITE_RAW_ENCRYPTED 129 
#define  FSCTL_WRITE_USN_CLOSE_RECORD 128 
 TYPE_6__* IoGetCurrentIrpStackLocation (TYPE_5__*) ; 
 int /*<<< orphan*/  NormalPagePriority ; 
 int /*<<< orphan*/  STATUS_INVALID_DEVICE_REQUEST ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  WARN (char*,...) ; 
 int /*<<< orphan*/  add_device (int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  allow_extended_dasd_io (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_snapshot (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/  create_subvol (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/  delete_reparse_point (TYPE_7__*,TYPE_5__*) ; 
 int /*<<< orphan*/  dismount_volume (int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/  duplicate_extents (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/  find_subvol (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/  fs_get_statistics (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fsctl_get_xattrs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fsctl_set_xattr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/  get_compression (TYPE_5__*) ; 
 int /*<<< orphan*/  get_devices (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_file_ids (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_inode_info (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_integrity_information (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_object_id (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_reparse_point (TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_usage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/  invalidate_volumes (TYPE_5__*) ; 
 int /*<<< orphan*/  is_volume_dirty (int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/  is_volume_mounted (int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/  lock_volume (int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/  map_user_buffer (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mknod (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/  pause_balance (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pause_scrub (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  query_balance (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  query_ranges (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  query_scrub (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  query_uuid (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_send_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  recvd_subvol (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remove_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reserve_subvol (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/  reset_stats (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resize_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/  resume_balance (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resume_scrub (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_subvol (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/  set_compression (TYPE_5__*) ; 
 int /*<<< orphan*/  set_inode_info (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/  set_integrity_information (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_reparse_point (TYPE_7__*,TYPE_5__*) ; 
 int /*<<< orphan*/  set_sparse (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/  set_zero_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/  start_balance (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  start_scrub (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stop_balance (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stop_scrub (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlock_volume (int /*<<< orphan*/ ,TYPE_5__*) ; 

NTSTATUS fsctl_request(PDEVICE_OBJECT DeviceObject, PIRP* Pirp, UINT32 type) {
    PIRP Irp = *Pirp;
    PIO_STACK_LOCATION IrpSp = IoGetCurrentIrpStackLocation(Irp);
    NTSTATUS Status;

    switch (type) {
#if (NTDDI_VERSION >= NTDDI_WIN7)
        case FSCTL_REQUEST_OPLOCK:
            WARN("STUB: FSCTL_REQUEST_OPLOCK\n");
            Status = STATUS_INVALID_DEVICE_REQUEST;
            break;
#endif

        case FSCTL_REQUEST_OPLOCK_LEVEL_1:
            WARN("STUB: FSCTL_REQUEST_OPLOCK_LEVEL_1\n");
            Status = STATUS_INVALID_DEVICE_REQUEST;
            break;

        case FSCTL_REQUEST_OPLOCK_LEVEL_2:
            WARN("STUB: FSCTL_REQUEST_OPLOCK_LEVEL_2\n");
            Status = STATUS_INVALID_DEVICE_REQUEST;
            break;

        case FSCTL_REQUEST_BATCH_OPLOCK:
            WARN("STUB: FSCTL_REQUEST_BATCH_OPLOCK\n");
            Status = STATUS_INVALID_DEVICE_REQUEST;
            break;

        case FSCTL_OPLOCK_BREAK_ACKNOWLEDGE:
            WARN("STUB: FSCTL_OPLOCK_BREAK_ACKNOWLEDGE\n");
            Status = STATUS_INVALID_DEVICE_REQUEST;
            break;

        case FSCTL_OPLOCK_BREAK_ACK_NO_2:
            WARN("STUB: FSCTL_OPLOCK_BREAK_ACK_NO_2\n");
            Status = STATUS_INVALID_DEVICE_REQUEST;
            break;

        case FSCTL_OPBATCH_ACK_CLOSE_PENDING:
            WARN("STUB: FSCTL_OPBATCH_ACK_CLOSE_PENDING\n");
            Status = STATUS_INVALID_DEVICE_REQUEST;
            break;

        case FSCTL_OPLOCK_BREAK_NOTIFY:
            WARN("STUB: FSCTL_OPLOCK_BREAK_NOTIFY\n");
            Status = STATUS_INVALID_DEVICE_REQUEST;
            break;

        case FSCTL_REQUEST_FILTER_OPLOCK:
            WARN("STUB: FSCTL_REQUEST_FILTER_OPLOCK\n");
            Status = STATUS_INVALID_DEVICE_REQUEST;
            break;

        case FSCTL_LOCK_VOLUME:
            Status = lock_volume(DeviceObject->DeviceExtension, Irp);
            break;

        case FSCTL_UNLOCK_VOLUME:
            Status = unlock_volume(DeviceObject->DeviceExtension, Irp);
            break;

        case FSCTL_DISMOUNT_VOLUME:
            Status = dismount_volume(DeviceObject->DeviceExtension, Irp);
            break;

        case FSCTL_IS_VOLUME_MOUNTED:
            Status = is_volume_mounted(DeviceObject->DeviceExtension, Irp);
            break;

        case FSCTL_IS_PATHNAME_VALID:
            WARN("STUB: FSCTL_IS_PATHNAME_VALID\n");
            Status = STATUS_INVALID_DEVICE_REQUEST;
            break;

        case FSCTL_MARK_VOLUME_DIRTY:
            WARN("STUB: FSCTL_MARK_VOLUME_DIRTY\n");
            Status = STATUS_INVALID_DEVICE_REQUEST;
            break;

        case FSCTL_QUERY_RETRIEVAL_POINTERS:
            WARN("STUB: FSCTL_QUERY_RETRIEVAL_POINTERS\n");
            Status = STATUS_INVALID_DEVICE_REQUEST;
            break;

        case FSCTL_GET_COMPRESSION:
            Status = get_compression(Irp);
            break;

        case FSCTL_SET_COMPRESSION:
            Status = set_compression(Irp);
            break;

        case FSCTL_SET_BOOTLOADER_ACCESSED:
            WARN("STUB: FSCTL_SET_BOOTLOADER_ACCESSED\n");
            Status = STATUS_INVALID_DEVICE_REQUEST;
            break;

        case FSCTL_INVALIDATE_VOLUMES:
            Status = invalidate_volumes(Irp);
            break;

        case FSCTL_QUERY_FAT_BPB:
            WARN("STUB: FSCTL_QUERY_FAT_BPB\n");
            Status = STATUS_INVALID_DEVICE_REQUEST;
            break;

        case FSCTL_FILESYSTEM_GET_STATISTICS:
            Status = fs_get_statistics(Irp->AssociatedIrp.SystemBuffer, IrpSp->Parameters.FileSystemControl.OutputBufferLength, &Irp->IoStatus.Information);
            break;

        case FSCTL_GET_NTFS_VOLUME_DATA:
            WARN("STUB: FSCTL_GET_NTFS_VOLUME_DATA\n");
            Status = STATUS_INVALID_DEVICE_REQUEST;
            break;

        case FSCTL_GET_NTFS_FILE_RECORD:
            WARN("STUB: FSCTL_GET_NTFS_FILE_RECORD\n");
            Status = STATUS_INVALID_DEVICE_REQUEST;
            break;

        case FSCTL_GET_VOLUME_BITMAP:
            WARN("STUB: FSCTL_GET_VOLUME_BITMAP\n");
            Status = STATUS_INVALID_DEVICE_REQUEST;
            break;

        case FSCTL_GET_RETRIEVAL_POINTERS:
            WARN("STUB: FSCTL_GET_RETRIEVAL_POINTERS\n");
            Status = STATUS_INVALID_DEVICE_REQUEST;
            break;

        case FSCTL_MOVE_FILE:
            WARN("STUB: FSCTL_MOVE_FILE\n");
            Status = STATUS_INVALID_DEVICE_REQUEST;
            break;

        case FSCTL_IS_VOLUME_DIRTY:
            Status = is_volume_dirty(DeviceObject->DeviceExtension, Irp);
            break;

        case FSCTL_ALLOW_EXTENDED_DASD_IO:
            Status = allow_extended_dasd_io(DeviceObject->DeviceExtension, IrpSp->FileObject);
            break;

        case FSCTL_FIND_FILES_BY_SID:
            WARN("STUB: FSCTL_FIND_FILES_BY_SID\n");
            Status = STATUS_INVALID_DEVICE_REQUEST;
            break;

        case FSCTL_SET_OBJECT_ID:
            WARN("STUB: FSCTL_SET_OBJECT_ID\n");
            Status = STATUS_INVALID_DEVICE_REQUEST;
            break;

        case FSCTL_GET_OBJECT_ID:
            Status = get_object_id(DeviceObject->DeviceExtension, IrpSp->FileObject, Irp->UserBuffer,
                                   IrpSp->Parameters.FileSystemControl.OutputBufferLength, &Irp->IoStatus.Information);
            break;

        case FSCTL_DELETE_OBJECT_ID:
            WARN("STUB: FSCTL_DELETE_OBJECT_ID\n");
            Status = STATUS_INVALID_DEVICE_REQUEST;
            break;

        case FSCTL_SET_REPARSE_POINT:
            Status = set_reparse_point(DeviceObject, Irp);
            break;

        case FSCTL_GET_REPARSE_POINT:
            Status = get_reparse_point(DeviceObject, IrpSp->FileObject, Irp->AssociatedIrp.SystemBuffer,
                                       IrpSp->Parameters.FileSystemControl.OutputBufferLength, &Irp->IoStatus.Information);
            break;

        case FSCTL_DELETE_REPARSE_POINT:
            Status = delete_reparse_point(DeviceObject, Irp);
            break;

        case FSCTL_ENUM_USN_DATA:
            WARN("STUB: FSCTL_ENUM_USN_DATA\n");
            Status = STATUS_INVALID_DEVICE_REQUEST;
            break;

        case FSCTL_SECURITY_ID_CHECK:
            WARN("STUB: FSCTL_SECURITY_ID_CHECK\n");
            Status = STATUS_INVALID_DEVICE_REQUEST;
            break;

        case FSCTL_READ_USN_JOURNAL:
            WARN("STUB: FSCTL_READ_USN_JOURNAL\n");
            Status = STATUS_INVALID_DEVICE_REQUEST;
            break;

        case FSCTL_SET_OBJECT_ID_EXTENDED:
            WARN("STUB: FSCTL_SET_OBJECT_ID_EXTENDED\n");
            Status = STATUS_INVALID_DEVICE_REQUEST;
            break;

        case FSCTL_CREATE_OR_GET_OBJECT_ID:
            Status = get_object_id(DeviceObject->DeviceExtension, IrpSp->FileObject, Irp->UserBuffer,
                                   IrpSp->Parameters.FileSystemControl.OutputBufferLength, &Irp->IoStatus.Information);
            break;

        case FSCTL_SET_SPARSE:
            Status = set_sparse(DeviceObject->DeviceExtension, IrpSp->FileObject, Irp->AssociatedIrp.SystemBuffer,
                                IrpSp->Parameters.FileSystemControl.InputBufferLength, Irp);
            break;

        case FSCTL_SET_ZERO_DATA:
            Status = set_zero_data(DeviceObject->DeviceExtension, IrpSp->FileObject, Irp->AssociatedIrp.SystemBuffer,
                                   IrpSp->Parameters.FileSystemControl.InputBufferLength, Irp);
            break;

        case FSCTL_QUERY_ALLOCATED_RANGES:
            Status = query_ranges(IrpSp->FileObject, IrpSp->Parameters.FileSystemControl.Type3InputBuffer,
                                  IrpSp->Parameters.FileSystemControl.InputBufferLength, Irp->UserBuffer,
                                  IrpSp->Parameters.FileSystemControl.OutputBufferLength, &Irp->IoStatus.Information);
            break;

        case FSCTL_ENABLE_UPGRADE:
            WARN("STUB: FSCTL_ENABLE_UPGRADE\n");
            Status = STATUS_INVALID_DEVICE_REQUEST;
            break;

        case FSCTL_SET_ENCRYPTION:
            WARN("STUB: FSCTL_SET_ENCRYPTION\n");
            Status = STATUS_INVALID_DEVICE_REQUEST;
            break;

        case FSCTL_ENCRYPTION_FSCTL_IO:
            WARN("STUB: FSCTL_ENCRYPTION_FSCTL_IO\n");
            Status = STATUS_INVALID_DEVICE_REQUEST;
            break;

        case FSCTL_WRITE_RAW_ENCRYPTED:
            WARN("STUB: FSCTL_WRITE_RAW_ENCRYPTED\n");
            Status = STATUS_INVALID_DEVICE_REQUEST;
            break;

        case FSCTL_READ_RAW_ENCRYPTED:
            WARN("STUB: FSCTL_READ_RAW_ENCRYPTED\n");
            Status = STATUS_INVALID_DEVICE_REQUEST;
            break;

        case FSCTL_CREATE_USN_JOURNAL:
            WARN("STUB: FSCTL_CREATE_USN_JOURNAL\n");
            Status = STATUS_INVALID_DEVICE_REQUEST;
            break;

        case FSCTL_READ_FILE_USN_DATA:
            WARN("STUB: FSCTL_READ_FILE_USN_DATA\n");
            Status = STATUS_INVALID_DEVICE_REQUEST;
            break;

        case FSCTL_WRITE_USN_CLOSE_RECORD:
            WARN("STUB: FSCTL_WRITE_USN_CLOSE_RECORD\n");
            Status = STATUS_INVALID_DEVICE_REQUEST;
            break;

        case FSCTL_EXTEND_VOLUME:
            WARN("STUB: FSCTL_EXTEND_VOLUME\n");
            Status = STATUS_INVALID_DEVICE_REQUEST;
            break;

        case FSCTL_QUERY_USN_JOURNAL:
            WARN("STUB: FSCTL_QUERY_USN_JOURNAL\n");
            Status = STATUS_INVALID_DEVICE_REQUEST;
            break;

        case FSCTL_DELETE_USN_JOURNAL:
            WARN("STUB: FSCTL_DELETE_USN_JOURNAL\n");
            Status = STATUS_INVALID_DEVICE_REQUEST;
            break;

        case FSCTL_MARK_HANDLE:
            WARN("STUB: FSCTL_MARK_HANDLE\n");
            Status = STATUS_INVALID_DEVICE_REQUEST;
            break;

        case FSCTL_SIS_COPYFILE:
            WARN("STUB: FSCTL_SIS_COPYFILE\n");
            Status = STATUS_INVALID_DEVICE_REQUEST;
            break;

        case FSCTL_SIS_LINK_FILES:
            WARN("STUB: FSCTL_SIS_LINK_FILES\n");
            Status = STATUS_INVALID_DEVICE_REQUEST;
            break;

        case FSCTL_RECALL_FILE:
            WARN("STUB: FSCTL_RECALL_FILE\n");
            Status = STATUS_INVALID_DEVICE_REQUEST;
            break;

        case FSCTL_READ_FROM_PLEX:
            WARN("STUB: FSCTL_READ_FROM_PLEX\n");
            Status = STATUS_INVALID_DEVICE_REQUEST;
            break;

        case FSCTL_FILE_PREFETCH:
            WARN("STUB: FSCTL_FILE_PREFETCH\n");
            Status = STATUS_INVALID_DEVICE_REQUEST;
            break;

#if _WIN32_WINNT >= 0x0600
        case FSCTL_MAKE_MEDIA_COMPATIBLE:
            WARN("STUB: FSCTL_MAKE_MEDIA_COMPATIBLE\n");
            Status = STATUS_INVALID_DEVICE_REQUEST;
            break;

        case FSCTL_SET_DEFECT_MANAGEMENT:
            WARN("STUB: FSCTL_SET_DEFECT_MANAGEMENT\n");
            Status = STATUS_INVALID_DEVICE_REQUEST;
            break;

        case FSCTL_QUERY_SPARING_INFO:
            WARN("STUB: FSCTL_QUERY_SPARING_INFO\n");
            Status = STATUS_INVALID_DEVICE_REQUEST;
            break;

        case FSCTL_QUERY_ON_DISK_VOLUME_INFO:
            WARN("STUB: FSCTL_QUERY_ON_DISK_VOLUME_INFO\n");
            Status = STATUS_INVALID_DEVICE_REQUEST;
            break;

        case FSCTL_SET_VOLUME_COMPRESSION_STATE:
            WARN("STUB: FSCTL_SET_VOLUME_COMPRESSION_STATE\n");
            Status = STATUS_INVALID_DEVICE_REQUEST;
            break;

        case FSCTL_TXFS_MODIFY_RM:
            WARN("STUB: FSCTL_TXFS_MODIFY_RM\n");
            Status = STATUS_INVALID_DEVICE_REQUEST;
            break;

        case FSCTL_TXFS_QUERY_RM_INFORMATION:
            WARN("STUB: FSCTL_TXFS_QUERY_RM_INFORMATION\n");
            Status = STATUS_INVALID_DEVICE_REQUEST;
            break;

        case FSCTL_TXFS_ROLLFORWARD_REDO:
            WARN("STUB: FSCTL_TXFS_ROLLFORWARD_REDO\n");
            Status = STATUS_INVALID_DEVICE_REQUEST;
            break;

        case FSCTL_TXFS_ROLLFORWARD_UNDO:
            WARN("STUB: FSCTL_TXFS_ROLLFORWARD_UNDO\n");
            Status = STATUS_INVALID_DEVICE_REQUEST;
            break;

        case FSCTL_TXFS_START_RM:
            WARN("STUB: FSCTL_TXFS_START_RM\n");
            Status = STATUS_INVALID_DEVICE_REQUEST;
            break;

        case FSCTL_TXFS_SHUTDOWN_RM:
            WARN("STUB: FSCTL_TXFS_SHUTDOWN_RM\n");
            Status = STATUS_INVALID_DEVICE_REQUEST;
            break;

        case FSCTL_TXFS_READ_BACKUP_INFORMATION:
            WARN("STUB: FSCTL_TXFS_READ_BACKUP_INFORMATION\n");
            Status = STATUS_INVALID_DEVICE_REQUEST;
            break;

        case FSCTL_TXFS_WRITE_BACKUP_INFORMATION:
            WARN("STUB: FSCTL_TXFS_WRITE_BACKUP_INFORMATION\n");
            Status = STATUS_INVALID_DEVICE_REQUEST;
            break;

        case FSCTL_TXFS_CREATE_SECONDARY_RM:
            WARN("STUB: FSCTL_TXFS_CREATE_SECONDARY_RM\n");
            Status = STATUS_INVALID_DEVICE_REQUEST;
            break;

        case FSCTL_TXFS_GET_METADATA_INFO:
            WARN("STUB: FSCTL_TXFS_GET_METADATA_INFO\n");
            Status = STATUS_INVALID_DEVICE_REQUEST;
            break;

        case FSCTL_TXFS_GET_TRANSACTED_VERSION:
            WARN("STUB: FSCTL_TXFS_GET_TRANSACTED_VERSION\n");
            Status = STATUS_INVALID_DEVICE_REQUEST;
            break;

        case FSCTL_TXFS_SAVEPOINT_INFORMATION:
            WARN("STUB: FSCTL_TXFS_SAVEPOINT_INFORMATION\n");
            Status = STATUS_INVALID_DEVICE_REQUEST;
            break;

        case FSCTL_TXFS_CREATE_MINIVERSION:
            WARN("STUB: FSCTL_TXFS_CREATE_MINIVERSION\n");
            Status = STATUS_INVALID_DEVICE_REQUEST;
            break;

        case FSCTL_TXFS_TRANSACTION_ACTIVE:
            WARN("STUB: FSCTL_TXFS_TRANSACTION_ACTIVE\n");
            Status = STATUS_INVALID_DEVICE_REQUEST;
            break;

        case FSCTL_SET_ZERO_ON_DEALLOCATION:
            WARN("STUB: FSCTL_SET_ZERO_ON_DEALLOCATION\n");
            Status = STATUS_INVALID_DEVICE_REQUEST;
            break;

        case FSCTL_SET_REPAIR:
            WARN("STUB: FSCTL_SET_REPAIR\n");
            Status = STATUS_INVALID_DEVICE_REQUEST;
            break;

        case FSCTL_GET_REPAIR:
            WARN("STUB: FSCTL_GET_REPAIR\n");
            Status = STATUS_INVALID_DEVICE_REQUEST;
            break;

        case FSCTL_WAIT_FOR_REPAIR:
            WARN("STUB: FSCTL_WAIT_FOR_REPAIR\n");
            Status = STATUS_INVALID_DEVICE_REQUEST;
            break;

        case FSCTL_INITIATE_REPAIR:
            WARN("STUB: FSCTL_INITIATE_REPAIR\n");
            Status = STATUS_INVALID_DEVICE_REQUEST;
            break;

        case FSCTL_CSC_INTERNAL:
            WARN("STUB: FSCTL_CSC_INTERNAL\n");
            Status = STATUS_INVALID_DEVICE_REQUEST;
            break;

        case FSCTL_SHRINK_VOLUME:
            WARN("STUB: FSCTL_SHRINK_VOLUME\n");
            Status = STATUS_INVALID_DEVICE_REQUEST;
            break;

        case FSCTL_SET_SHORT_NAME_BEHAVIOR:
            WARN("STUB: FSCTL_SET_SHORT_NAME_BEHAVIOR\n");
            Status = STATUS_INVALID_DEVICE_REQUEST;
            break;

        case FSCTL_DFSR_SET_GHOST_HANDLE_STATE:
            WARN("STUB: FSCTL_DFSR_SET_GHOST_HANDLE_STATE\n");
            Status = STATUS_INVALID_DEVICE_REQUEST;
            break;

        case FSCTL_TXFS_LIST_TRANSACTION_LOCKED_FILES:
            WARN("STUB: FSCTL_TXFS_LIST_TRANSACTION_LOCKED_FILES\n");
            Status = STATUS_INVALID_DEVICE_REQUEST;
            break;

        case FSCTL_TXFS_LIST_TRANSACTIONS:
            WARN("STUB: FSCTL_TXFS_LIST_TRANSACTIONS\n");
            Status = STATUS_INVALID_DEVICE_REQUEST;
            break;

        case FSCTL_QUERY_PAGEFILE_ENCRYPTION:
            WARN("STUB: FSCTL_QUERY_PAGEFILE_ENCRYPTION\n");
            Status = STATUS_INVALID_DEVICE_REQUEST;
            break;

        case FSCTL_RESET_VOLUME_ALLOCATION_HINTS:
            WARN("STUB: FSCTL_RESET_VOLUME_ALLOCATION_HINTS\n");
            Status = STATUS_INVALID_DEVICE_REQUEST;
            break;

        case FSCTL_TXFS_READ_BACKUP_INFORMATION2:
            WARN("STUB: FSCTL_TXFS_READ_BACKUP_INFORMATION2\n");
            Status = STATUS_INVALID_DEVICE_REQUEST;
            break;

        case FSCTL_CSV_CONTROL:
            WARN("STUB: FSCTL_CSV_CONTROL\n");
            Status = STATUS_INVALID_DEVICE_REQUEST;
            break;
#endif
        // TRACE rather than WARN because Windows 10 spams this undocumented fsctl
        case FSCTL_QUERY_VOLUME_CONTAINER_STATE:
            TRACE("STUB: FSCTL_QUERY_VOLUME_CONTAINER_STATE\n");
            Status = STATUS_INVALID_DEVICE_REQUEST;
            break;

        case FSCTL_GET_INTEGRITY_INFORMATION:
            Status = get_integrity_information(DeviceObject->DeviceExtension, IrpSp->FileObject, map_user_buffer(Irp, NormalPagePriority),
                                               IrpSp->Parameters.FileSystemControl.OutputBufferLength);
            break;

        case FSCTL_SET_INTEGRITY_INFORMATION:
            Status = set_integrity_information(IrpSp->FileObject, Irp->AssociatedIrp.SystemBuffer, IrpSp->Parameters.FileSystemControl.InputBufferLength);
            break;

        case FSCTL_DUPLICATE_EXTENTS_TO_FILE:
            Status = duplicate_extents(DeviceObject->DeviceExtension, IrpSp->FileObject, Irp->AssociatedIrp.SystemBuffer,
                                       IrpSp->Parameters.FileSystemControl.InputBufferLength, Irp);
            break;

        case FSCTL_BTRFS_GET_FILE_IDS:
            Status = get_file_ids(IrpSp->FileObject, map_user_buffer(Irp, NormalPagePriority), IrpSp->Parameters.FileSystemControl.OutputBufferLength);
            break;

        case FSCTL_BTRFS_CREATE_SUBVOL:
            Status = create_subvol(DeviceObject->DeviceExtension, IrpSp->FileObject, Irp->AssociatedIrp.SystemBuffer, IrpSp->Parameters.FileSystemControl.InputBufferLength, Irp);
            break;

        case FSCTL_BTRFS_CREATE_SNAPSHOT:
            Status = create_snapshot(DeviceObject->DeviceExtension, IrpSp->FileObject, Irp->AssociatedIrp.SystemBuffer, IrpSp->Parameters.FileSystemControl.InputBufferLength, Irp);
            break;

        case FSCTL_BTRFS_GET_INODE_INFO:
            Status = get_inode_info(IrpSp->FileObject, map_user_buffer(Irp, NormalPagePriority), IrpSp->Parameters.FileSystemControl.OutputBufferLength);
            break;

        case FSCTL_BTRFS_SET_INODE_INFO:
            Status = set_inode_info(IrpSp->FileObject, Irp->AssociatedIrp.SystemBuffer, IrpSp->Parameters.FileSystemControl.InputBufferLength, Irp);
            break;

        case FSCTL_BTRFS_GET_DEVICES:
            Status = get_devices(DeviceObject->DeviceExtension, map_user_buffer(Irp, NormalPagePriority), IrpSp->Parameters.FileSystemControl.OutputBufferLength);
            break;

        case FSCTL_BTRFS_GET_USAGE:
            Status = get_usage(DeviceObject->DeviceExtension, map_user_buffer(Irp, NormalPagePriority), IrpSp->Parameters.FileSystemControl.OutputBufferLength, Irp);
            break;

        case FSCTL_BTRFS_START_BALANCE:
            Status = start_balance(DeviceObject->DeviceExtension, Irp->AssociatedIrp.SystemBuffer, IrpSp->Parameters.FileSystemControl.InputBufferLength, Irp->RequestorMode);
            break;

        case FSCTL_BTRFS_QUERY_BALANCE:
            Status = query_balance(DeviceObject->DeviceExtension, map_user_buffer(Irp, NormalPagePriority), IrpSp->Parameters.FileSystemControl.OutputBufferLength);
            break;

        case FSCTL_BTRFS_PAUSE_BALANCE:
            Status = pause_balance(DeviceObject->DeviceExtension, Irp->RequestorMode);
            break;

        case FSCTL_BTRFS_RESUME_BALANCE:
            Status = resume_balance(DeviceObject->DeviceExtension, Irp->RequestorMode);
            break;

        case FSCTL_BTRFS_STOP_BALANCE:
            Status = stop_balance(DeviceObject->DeviceExtension, Irp->RequestorMode);
            break;

        case FSCTL_BTRFS_ADD_DEVICE:
            Status = add_device(DeviceObject->DeviceExtension, Irp, Irp->RequestorMode);
            break;

        case FSCTL_BTRFS_REMOVE_DEVICE:
            Status = remove_device(DeviceObject->DeviceExtension, Irp->AssociatedIrp.SystemBuffer, IrpSp->Parameters.FileSystemControl.InputBufferLength, Irp->RequestorMode);
            break;

        case FSCTL_BTRFS_GET_UUID:
            Status = query_uuid(DeviceObject->DeviceExtension, map_user_buffer(Irp, NormalPagePriority), IrpSp->Parameters.FileSystemControl.OutputBufferLength);
            break;

        case FSCTL_BTRFS_START_SCRUB:
            Status = start_scrub(DeviceObject->DeviceExtension, Irp->RequestorMode);
            break;

        case FSCTL_BTRFS_QUERY_SCRUB:
            Status = query_scrub(DeviceObject->DeviceExtension, Irp->RequestorMode, map_user_buffer(Irp, NormalPagePriority), IrpSp->Parameters.FileSystemControl.OutputBufferLength);
            break;

        case FSCTL_BTRFS_PAUSE_SCRUB:
            Status = pause_scrub(DeviceObject->DeviceExtension, Irp->RequestorMode);
            break;

        case FSCTL_BTRFS_RESUME_SCRUB:
            Status = resume_scrub(DeviceObject->DeviceExtension, Irp->RequestorMode);
            break;

        case FSCTL_BTRFS_STOP_SCRUB:
            Status = stop_scrub(DeviceObject->DeviceExtension, Irp->RequestorMode);
            break;

        case FSCTL_BTRFS_RESET_STATS:
            Status = reset_stats(DeviceObject->DeviceExtension, Irp->AssociatedIrp.SystemBuffer, IrpSp->Parameters.FileSystemControl.InputBufferLength, Irp->RequestorMode);
            break;

        case FSCTL_BTRFS_MKNOD:
            Status = mknod(DeviceObject->DeviceExtension, IrpSp->FileObject, Irp->AssociatedIrp.SystemBuffer, IrpSp->Parameters.FileSystemControl.InputBufferLength, Irp);
            break;

        case FSCTL_BTRFS_RECEIVED_SUBVOL:
            Status = recvd_subvol(DeviceObject->DeviceExtension, IrpSp->FileObject, Irp->AssociatedIrp.SystemBuffer,
                                  IrpSp->Parameters.FileSystemControl.InputBufferLength, Irp->RequestorMode);
            break;

        case FSCTL_BTRFS_GET_XATTRS:
            Status = fsctl_get_xattrs(DeviceObject->DeviceExtension, IrpSp->FileObject, Irp->UserBuffer, IrpSp->Parameters.FileSystemControl.OutputBufferLength, Irp->RequestorMode);
            break;

        case FSCTL_BTRFS_SET_XATTR:
            Status = fsctl_set_xattr(DeviceObject->DeviceExtension, IrpSp->FileObject, Irp->AssociatedIrp.SystemBuffer,
                                     IrpSp->Parameters.FileSystemControl.InputBufferLength, Irp);
            break;

        case FSCTL_BTRFS_RESERVE_SUBVOL:
            Status = reserve_subvol(DeviceObject->DeviceExtension, IrpSp->FileObject, Irp);
            break;

        case FSCTL_BTRFS_FIND_SUBVOL:
            Status = find_subvol(DeviceObject->DeviceExtension, Irp->AssociatedIrp.SystemBuffer, IrpSp->Parameters.FileSystemControl.InputBufferLength,
                                 Irp->UserBuffer, IrpSp->Parameters.FileSystemControl.OutputBufferLength, Irp);
            break;

        case FSCTL_BTRFS_SEND_SUBVOL:
            Status = send_subvol(DeviceObject->DeviceExtension, Irp->AssociatedIrp.SystemBuffer, IrpSp->Parameters.FileSystemControl.InputBufferLength,
                                 IrpSp->FileObject, Irp);
            break;

        case FSCTL_BTRFS_READ_SEND_BUFFER:
            Status = read_send_buffer(DeviceObject->DeviceExtension, IrpSp->FileObject, map_user_buffer(Irp, NormalPagePriority), IrpSp->Parameters.FileSystemControl.OutputBufferLength,
                                      &Irp->IoStatus.Information, Irp->RequestorMode);
            break;

        case FSCTL_BTRFS_RESIZE:
            Status = resize_device(DeviceObject->DeviceExtension, Irp->AssociatedIrp.SystemBuffer,
                                   IrpSp->Parameters.FileSystemControl.InputBufferLength, Irp);
            break;

        default:
            WARN("unknown control code %x (DeviceType = %x, Access = %x, Function = %x, Method = %x)\n",
                          IrpSp->Parameters.FileSystemControl.FsControlCode, (IrpSp->Parameters.FileSystemControl.FsControlCode & 0xff0000) >> 16,
                          (IrpSp->Parameters.FileSystemControl.FsControlCode & 0xc000) >> 14, (IrpSp->Parameters.FileSystemControl.FsControlCode & 0x3ffc) >> 2,
                          IrpSp->Parameters.FileSystemControl.FsControlCode & 0x3);
            Status = STATUS_INVALID_DEVICE_REQUEST;
            break;
    }

    return Status;
}