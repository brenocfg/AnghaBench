#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32 ;
struct stat {int st_mode; int st_size; int /*<<< orphan*/  st_ctime; int /*<<< orphan*/  st_mtime; int /*<<< orphan*/  st_atime; } ;
struct fileinfo {char* path; int /*<<< orphan*/  pattern; int /*<<< orphan*/ * pdir; } ;
struct dirent {char* d_name; } ;
typedef  int /*<<< orphan*/  fstat ;
struct TYPE_4__ {struct fileinfo* fileinfo; } ;
typedef  int /*<<< orphan*/  STREAM ;
typedef  TYPE_1__ RDPCLIENT ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  size_t NTHANDLE ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
#define  EACCES 131 
#define  ELOOP 130 
#define  ENOENT 129 
 int FILE_ATTRIBUTE_DIRECTORY ; 
 int FILE_ATTRIBUTE_HIDDEN ; 
 int FILE_ATTRIBUTE_NORMAL ; 
 int FILE_ATTRIBUTE_READONLY ; 
#define  FileBothDirectoryInformation 128 
 int PATH_MAX ; 
 int /*<<< orphan*/  STATUS_INVALID_PARAMETER ; 
 int /*<<< orphan*/  STATUS_NO_MORE_FILES ; 
 int /*<<< orphan*/  STATUS_NO_SUCH_FILE ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  S_ISDIR (int) ; 
 int S_IWUSR ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fnmatch (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_create_time (struct stat*) ; 
 int /*<<< orphan*/  memset (struct stat*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  out_uint32_le (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  out_uint8 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  out_uint8s (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  rdp_out_unistr (TYPE_1__*,int /*<<< orphan*/ ,char*,int) ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rewinddir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  seconds_since_1970_to_filetime (int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,char*) ; 
 int /*<<< orphan*/  stat (char*,struct stat*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strrchr (char*,char) ; 
 int /*<<< orphan*/  unimpl (char*,int) ; 

NTSTATUS
disk_query_directory(RDPCLIENT * This, NTHANDLE handle, uint32 info_class, char *pattern, STREAM out)
{
	uint32 file_attributes, ft_low, ft_high;
	char *dirname, fullpath[PATH_MAX];
	DIR *pdir;
	struct dirent *pdirent;
	struct stat fstat;
	struct fileinfo *pfinfo;

	pfinfo = &(This->fileinfo[handle]);
	pdir = pfinfo->pdir;
	dirname = pfinfo->path;
	file_attributes = 0;

	switch (info_class)
	{
		case FileBothDirectoryInformation:

			/* If a search pattern is received, remember this pattern, and restart search */
			if (pattern[0] != 0)
			{
				strncpy(pfinfo->pattern, 1 + strrchr(pattern, '/'), PATH_MAX - 1);
				rewinddir(pdir);
			}

			/* find next dirent matching pattern */
			pdirent = readdir(pdir);
			while (pdirent && fnmatch(pfinfo->pattern, pdirent->d_name, 0) != 0)
				pdirent = readdir(pdir);

			if (pdirent == NULL)
				return STATUS_NO_MORE_FILES;

			/* Get information for directory entry */
			sprintf(fullpath, "%s/%s", dirname, pdirent->d_name);

			if (stat(fullpath, &fstat))
			{
				switch (errno)
				{
					case ENOENT:
					case ELOOP:
					case EACCES:
						/* These are non-fatal errors. */
						memset(&fstat, 0, sizeof(fstat));
						break;
					default:
						/* Fatal error. By returning STATUS_NO_SUCH_FILE,
						   the directory list operation will be aborted */
						perror(fullpath);
						out_uint8(out, 0);
						return STATUS_NO_SUCH_FILE;
				}
			}

			if (S_ISDIR(fstat.st_mode))
				file_attributes |= FILE_ATTRIBUTE_DIRECTORY;
			if (pdirent->d_name[0] == '.')
				file_attributes |= FILE_ATTRIBUTE_HIDDEN;
			if (!file_attributes)
				file_attributes |= FILE_ATTRIBUTE_NORMAL;
			if (!(fstat.st_mode & S_IWUSR))
				file_attributes |= FILE_ATTRIBUTE_READONLY;

			/* Return requested information */
			out_uint8s(out, 8);	/* unknown zero */

			seconds_since_1970_to_filetime(get_create_time(&fstat), &ft_high, &ft_low);
			out_uint32_le(out, ft_low);	/* create time */
			out_uint32_le(out, ft_high);

			seconds_since_1970_to_filetime(fstat.st_atime, &ft_high, &ft_low);
			out_uint32_le(out, ft_low);	/* last_access_time */
			out_uint32_le(out, ft_high);

			seconds_since_1970_to_filetime(fstat.st_mtime, &ft_high, &ft_low);
			out_uint32_le(out, ft_low);	/* last_write_time */
			out_uint32_le(out, ft_high);

			seconds_since_1970_to_filetime(fstat.st_ctime, &ft_high, &ft_low);
			out_uint32_le(out, ft_low);	/* change_write_time */
			out_uint32_le(out, ft_high);

			out_uint32_le(out, fstat.st_size);	/* filesize low */
			out_uint32_le(out, 0);	/* filesize high */
			out_uint32_le(out, fstat.st_size);	/* filesize low */
			out_uint32_le(out, 0);	/* filesize high */
			out_uint32_le(out, file_attributes);
			out_uint8(out, 2 * strlen(pdirent->d_name) + 2);	/* unicode length */
			out_uint8s(out, 7);	/* pad? */
			out_uint8(out, 0);	/* 8.3 file length */
			out_uint8s(out, 2 * 12);	/* 8.3 unicode length */
			rdp_out_unistr(This, out, pdirent->d_name, 2 * strlen(pdirent->d_name));
			break;

		default:
			/* FIXME: Support FileDirectoryInformation,
			   FileFullDirectoryInformation, and
			   FileNamesInformation */

			unimpl("IRP Query Directory sub: 0x%x\n", info_class);
			return STATUS_INVALID_PARAMETER;
	}

	return STATUS_SUCCESS;
}