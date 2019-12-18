#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32 ;
struct stat {int st_mode; int st_size; int st_nlink; int /*<<< orphan*/  st_ctime; int /*<<< orphan*/  st_mtime; int /*<<< orphan*/  st_atime; } ;
struct TYPE_5__ {TYPE_1__* fileinfo; } ;
struct TYPE_4__ {char* path; } ;
typedef  int /*<<< orphan*/  STREAM ;
typedef  TYPE_2__ RDPCLIENT ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  size_t NTHANDLE ;

/* Variables and functions */
 int FILE_ATTRIBUTE_DIRECTORY ; 
 int FILE_ATTRIBUTE_HIDDEN ; 
 int FILE_ATTRIBUTE_NORMAL ; 
 int FILE_ATTRIBUTE_READONLY ; 
#define  FileBasicInformation 130 
#define  FileObjectIdInformation 129 
#define  FileStandardInformation 128 
 int /*<<< orphan*/  STATUS_ACCESS_DENIED ; 
 int /*<<< orphan*/  STATUS_INVALID_PARAMETER ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 scalar_t__ S_ISDIR (int) ; 
 int S_IWUSR ; 
 scalar_t__ fstat (size_t,struct stat*) ; 
 int /*<<< orphan*/  get_create_time (struct stat*) ; 
 int /*<<< orphan*/  out_uint32_le (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  out_uint8 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  seconds_since_1970_to_filetime (int /*<<< orphan*/ ,int*,int*) ; 
 char* strrchr (char*,char) ; 
 int /*<<< orphan*/  unimpl (char*,int) ; 

NTSTATUS
disk_query_information(RDPCLIENT * This, NTHANDLE handle, uint32 info_class, STREAM out)
{
	uint32 file_attributes, ft_high, ft_low;
	struct stat filestat;
	char *path, *filename;

	path = This->fileinfo[handle].path;

	/* Get information about file */
	if (fstat(handle, &filestat) != 0)
	{
		perror("stat");
		out_uint8(out, 0);
		return STATUS_ACCESS_DENIED;
	}

	/* Set file attributes */
	file_attributes = 0;
	if (S_ISDIR(filestat.st_mode))
		file_attributes |= FILE_ATTRIBUTE_DIRECTORY;

	filename = 1 + strrchr(path, '/');
	if (filename && filename[0] == '.')
		file_attributes |= FILE_ATTRIBUTE_HIDDEN;

	if (!file_attributes)
		file_attributes |= FILE_ATTRIBUTE_NORMAL;

	if (!(filestat.st_mode & S_IWUSR))
		file_attributes |= FILE_ATTRIBUTE_READONLY;

	/* Return requested data */
	switch (info_class)
	{
		case FileBasicInformation:
			seconds_since_1970_to_filetime(get_create_time(&filestat), &ft_high,
						       &ft_low);
			out_uint32_le(out, ft_low);	/* create_access_time */
			out_uint32_le(out, ft_high);

			seconds_since_1970_to_filetime(filestat.st_atime, &ft_high, &ft_low);
			out_uint32_le(out, ft_low);	/* last_access_time */
			out_uint32_le(out, ft_high);

			seconds_since_1970_to_filetime(filestat.st_mtime, &ft_high, &ft_low);
			out_uint32_le(out, ft_low);	/* last_write_time */
			out_uint32_le(out, ft_high);

			seconds_since_1970_to_filetime(filestat.st_ctime, &ft_high, &ft_low);
			out_uint32_le(out, ft_low);	/* last_change_time */
			out_uint32_le(out, ft_high);

			out_uint32_le(out, file_attributes);
			break;

		case FileStandardInformation:

			out_uint32_le(out, filestat.st_size);	/* Allocation size */
			out_uint32_le(out, 0);
			out_uint32_le(out, filestat.st_size);	/* End of file */
			out_uint32_le(out, 0);
			out_uint32_le(out, filestat.st_nlink);	/* Number of links */
			out_uint8(out, 0);	/* Delete pending */
			out_uint8(out, S_ISDIR(filestat.st_mode) ? 1 : 0);	/* Directory */
			break;

		case FileObjectIdInformation:

			out_uint32_le(out, file_attributes);	/* File Attributes */
			out_uint32_le(out, 0);	/* Reparse Tag */
			break;

		default:

			unimpl("IRP Query (File) Information class: 0x%x\n", info_class);
			return STATUS_INVALID_PARAMETER;
	}
	return STATUS_SUCCESS;
}