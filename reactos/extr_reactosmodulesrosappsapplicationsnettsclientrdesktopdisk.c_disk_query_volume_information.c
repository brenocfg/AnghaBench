#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32 ;
struct fileinfo {int /*<<< orphan*/  path; } ;
struct STATFS_T {int f_blocks; int f_bfree; int f_bsize; } ;
struct TYPE_7__ {int serial; int /*<<< orphan*/  type; int /*<<< orphan*/  label; } ;
struct TYPE_6__ {struct fileinfo* fileinfo; } ;
typedef  int /*<<< orphan*/  STREAM ;
typedef  TYPE_1__ RDPCLIENT ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  size_t NTHANDLE ;
typedef  TYPE_2__ FsInfoType ;

/* Variables and functions */
 int FS_CASE_IS_PRESERVED ; 
 int FS_CASE_SENSITIVE ; 
 int F_NAMELEN (struct STATFS_T) ; 
#define  FileFsAttributeInformation 136 
#define  FileFsControlInformation 135 
#define  FileFsDeviceInformation 134 
#define  FileFsFullSizeInformation 133 
#define  FileFsLabelInformation 132 
#define  FileFsMaximumInformation 131 
#define  FileFsObjectIdInformation 130 
#define  FileFsSizeInformation 129 
#define  FileFsVolumeInformation 128 
 TYPE_2__* FsVolumeInfo (int /*<<< orphan*/ ) ; 
 scalar_t__ STATFS_FN (int /*<<< orphan*/ ,struct STATFS_T*) ; 
 int /*<<< orphan*/  STATUS_ACCESS_DENIED ; 
 int /*<<< orphan*/  STATUS_INVALID_PARAMETER ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  out_uint32_le (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  out_uint8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  rdp_out_unistr (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unimpl (char*,int) ; 

NTSTATUS
disk_query_volume_information(RDPCLIENT * This, NTHANDLE handle, uint32 info_class, STREAM out)
{
	struct STATFS_T stat_fs;
	struct fileinfo *pfinfo;
	FsInfoType *fsinfo;

	pfinfo = &(This->fileinfo[handle]);

	if (STATFS_FN(pfinfo->path, &stat_fs) != 0)
	{
		perror("statfs");
		return STATUS_ACCESS_DENIED;
	}

	fsinfo = FsVolumeInfo(pfinfo->path);

	switch (info_class)
	{
		case FileFsVolumeInformation:

			out_uint32_le(out, 0);	/* volume creation time low */
			out_uint32_le(out, 0);	/* volume creation time high */
			out_uint32_le(out, fsinfo->serial);	/* serial */

			out_uint32_le(out, 2 * strlen(fsinfo->label));	/* length of string */

			out_uint8(out, 0);	/* support objects? */
			rdp_out_unistr(This, out, fsinfo->label, 2 * strlen(fsinfo->label) - 2);
			break;

		case FileFsSizeInformation:

			out_uint32_le(out, stat_fs.f_blocks);	/* Total allocation units low */
			out_uint32_le(out, 0);	/* Total allocation high units */
			out_uint32_le(out, stat_fs.f_bfree);	/* Available allocation units */
			out_uint32_le(out, 0);	/* Available allowcation units */
			out_uint32_le(out, stat_fs.f_bsize / 0x200);	/* Sectors per allocation unit */
			out_uint32_le(out, 0x200);	/* Bytes per sector */
			break;

		case FileFsAttributeInformation:

			out_uint32_le(out, FS_CASE_SENSITIVE | FS_CASE_IS_PRESERVED);	/* fs attributes */
			out_uint32_le(out, F_NAMELEN(stat_fs));	/* max length of filename */

			out_uint32_le(out, 2 * strlen(fsinfo->type));	/* length of fs_type */
			rdp_out_unistr(This, out, fsinfo->type, 2 * strlen(fsinfo->type) - 2);
			break;

		case FileFsLabelInformation:
		case FileFsDeviceInformation:
		case FileFsControlInformation:
		case FileFsFullSizeInformation:
		case FileFsObjectIdInformation:
		case FileFsMaximumInformation:

		default:

			unimpl("IRP Query Volume Information class: 0x%x\n", info_class);
			return STATUS_INVALID_PARAMETER;
	}
	return STATUS_SUCCESS;
}