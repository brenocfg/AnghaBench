#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32 ;
typedef  void* time_t ;
struct utimbuf {void* modtime; void* actime; } ;
struct stat {int st_mode; void* st_atime; void* st_mtime; } ;
struct fileinfo {size_t device_id; int accessmask; void* delete_on_close; int /*<<< orphan*/  path; } ;
struct STATFS_T {int f_bfree; int f_bsize; } ;
struct TYPE_6__ {TYPE_1__* rdpdr_device; void* notify_stamp; struct fileinfo* fileinfo; } ;
struct TYPE_5__ {char* local_path; } ;
typedef  int /*<<< orphan*/  STREAM ;
typedef  TYPE_2__ RDPCLIENT ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  size_t NTHANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  EPERM ; 
 int FILE_ATTRIBUTE_READONLY ; 
 int FILE_COMPLETE_IF_OPLOCKED ; 
 int FILE_DELETE_ON_CLOSE ; 
#define  FileAllocationInformation 132 
#define  FileBasicInformation 131 
#define  FileDispositionInformation 130 
#define  FileEndOfFileInformation 129 
#define  FileRenameInformation 128 
 void* MIN (void*,void*) ; 
 int PATH_MAX ; 
 int /*<<< orphan*/  STATFS_FN (char*,struct STATFS_T*) ; 
 int /*<<< orphan*/  STATUS_ACCESS_DENIED ; 
 int /*<<< orphan*/  STATUS_DISK_FULL ; 
 int /*<<< orphan*/  STATUS_INVALID_PARAMETER ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int S_IWGRP ; 
 int S_IWOTH ; 
 int S_IWUSR ; 
 void* True ; 
 void* convert_1970_to_filetime (int,int) ; 
 int /*<<< orphan*/  convert_to_unix_filename (char*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fchmod (size_t,int) ; 
 int /*<<< orphan*/  fstat (size_t,struct stat*) ; 
 int /*<<< orphan*/  ftruncate_growable (size_t,int) ; 
 int /*<<< orphan*/  in_uint32_le (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  in_uint8s (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  rdp_in_unistr (TYPE_2__*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  rename (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,char*) ; 
 int /*<<< orphan*/  unimpl (char*,int) ; 
 int /*<<< orphan*/  utime (int /*<<< orphan*/ ,struct utimbuf*) ; 

NTSTATUS
disk_set_information(RDPCLIENT * This, NTHANDLE handle, uint32 info_class, STREAM in, STREAM out)
{
	uint32 length, file_attributes, ft_high, ft_low, delete_on_close;
	char newname[PATH_MAX], fullpath[PATH_MAX];
	struct fileinfo *pfinfo;
	int mode;
	struct stat filestat;
	time_t write_time, change_time, access_time, mod_time;
	struct utimbuf tvs;
	struct STATFS_T stat_fs;

	pfinfo = &(This->fileinfo[handle]);
	This->notify_stamp = True;

	switch (info_class)
	{
		case FileBasicInformation:
			write_time = change_time = access_time = 0;

			in_uint8s(in, 4);	/* Handle of root dir? */
			in_uint8s(in, 24);	/* unknown */

			/* CreationTime */
			in_uint32_le(in, ft_low);
			in_uint32_le(in, ft_high);

			/* AccessTime */
			in_uint32_le(in, ft_low);
			in_uint32_le(in, ft_high);
			if (ft_low || ft_high)
				access_time = convert_1970_to_filetime(ft_high, ft_low);

			/* WriteTime */
			in_uint32_le(in, ft_low);
			in_uint32_le(in, ft_high);
			if (ft_low || ft_high)
				write_time = convert_1970_to_filetime(ft_high, ft_low);

			/* ChangeTime */
			in_uint32_le(in, ft_low);
			in_uint32_le(in, ft_high);
			if (ft_low || ft_high)
				change_time = convert_1970_to_filetime(ft_high, ft_low);

			in_uint32_le(in, file_attributes);

			if (fstat(handle, &filestat))
				return STATUS_ACCESS_DENIED;

			tvs.modtime = filestat.st_mtime;
			tvs.actime = filestat.st_atime;
			if (access_time)
				tvs.actime = access_time;


			if (write_time || change_time)
				mod_time = MIN(write_time, change_time);
			else
				mod_time = write_time ? write_time : change_time;

			if (mod_time)
				tvs.modtime = mod_time;


			if (access_time || write_time || change_time)
			{
#if WITH_DEBUG_RDP5
				printf("FileBasicInformation access       time %s",
				       ctime(&tvs.actime));
				printf("FileBasicInformation modification time %s",
				       ctime(&tvs.modtime));
#endif
				if (utime(pfinfo->path, &tvs) && errno != EPERM)
					return STATUS_ACCESS_DENIED;
			}

			if (!file_attributes)
				break;	/* not valid */

			mode = filestat.st_mode;

			if (file_attributes & FILE_ATTRIBUTE_READONLY)
				mode &= ~(S_IWUSR | S_IWGRP | S_IWOTH);
			else
				mode |= S_IWUSR;

			mode &= 0777;
#if WITH_DEBUG_RDP5
			printf("FileBasicInformation set access mode 0%o", mode);
#endif

			if (fchmod(handle, mode))
				return STATUS_ACCESS_DENIED;

			break;

		case FileRenameInformation:

			in_uint8s(in, 4);	/* Handle of root dir? */
			in_uint8s(in, 0x1a);	/* unknown */
			in_uint32_le(in, length);

			if (length && (length / 2) < 256)
			{
				rdp_in_unistr(This, in, newname, length);
				convert_to_unix_filename(newname);
			}
			else
			{
				return STATUS_INVALID_PARAMETER;
			}

			sprintf(fullpath, "%s%s", This->rdpdr_device[pfinfo->device_id].local_path,
				newname);

			if (rename(pfinfo->path, fullpath) != 0)
			{
				perror("rename");
				return STATUS_ACCESS_DENIED;
			}
			break;

		case FileDispositionInformation:
			/* As far as I understand it, the correct
			   thing to do here is to *schedule* a delete,
			   so it will be deleted when the file is
			   closed. Subsequent
			   FileDispositionInformation requests with
			   DeleteFile set to FALSE should unschedule
			   the delete. See
			   http://www.osronline.com/article.cfm?article=245. */

			in_uint32_le(in, delete_on_close);

			if (delete_on_close ||
			    (pfinfo->
			     accessmask & (FILE_DELETE_ON_CLOSE | FILE_COMPLETE_IF_OPLOCKED)))
			{
				pfinfo->delete_on_close = True;
			}

			break;

		case FileAllocationInformation:
			/* Fall through to FileEndOfFileInformation,
			   which uses ftrunc. This is like Samba with
			   "strict allocation = false", and means that
			   we won't detect out-of-quota errors, for
			   example. */

		case FileEndOfFileInformation:
			in_uint8s(in, 28);	/* unknown */
			in_uint32_le(in, length);	/* file size */

			/* prevents start of writing if not enough space left on device */
			if (STATFS_FN(This->rdpdr_device[pfinfo->device_id].local_path, &stat_fs) == 0)
				if (stat_fs.f_bfree * stat_fs.f_bsize < length)
					return STATUS_DISK_FULL;

			if (ftruncate_growable(handle, length) != 0)
			{
				return STATUS_DISK_FULL;
			}

			break;
		default:

			unimpl("IRP Set File Information class: 0x%x\n", info_class);
			return STATUS_INVALID_PARAMETER;
	}
	return STATUS_SUCCESS;
}