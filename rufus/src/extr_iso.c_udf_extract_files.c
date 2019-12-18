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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  udf_t ;
typedef  int /*<<< orphan*/  udf_dirent_t ;
typedef  scalar_t__ int64_t ;
struct TYPE_4__ {scalar_t__ is_cfg; scalar_t__* is_old_c32; } ;
typedef  scalar_t__ HANDLE ;
typedef  TYPE_1__ EXTRACT_PROPS ;
typedef  scalar_t__ DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CREATE_ALWAYS ; 
 scalar_t__ CopyFileU (char*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ CreateFileU (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ ERROR_ACCESS_DENIED ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FILES_DIR ; 
 int /*<<< orphan*/  FILE_ATTRIBUTE_NORMAL ; 
 int /*<<< orphan*/  FILE_SHARE_READ ; 
 scalar_t__ FormatStatus ; 
 int GENERIC_READ ; 
 int GENERIC_WRITE ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  IGNORE_RETVAL (int /*<<< orphan*/ ) ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  ISO_BLOCKING (int /*<<< orphan*/ ) ; 
 scalar_t__ IsFileInDB (char*) ; 
 scalar_t__ MIN (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  MSG_231 ; 
 size_t NB_OLD_C32 ; 
 int /*<<< orphan*/  OP_FILE_COPY ; 
 int PROGRESS_THRESHOLD ; 
 int /*<<< orphan*/  SetFileTime (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int UDF_BLOCKSIZE ; 
 int /*<<< orphan*/  UpdateProgressWithInfo (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UpdateProgressWithInfoInit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_RETRIES ; 
 char* WindowsErrorString () ; 
 int /*<<< orphan*/  WriteFileWithRetry (scalar_t__,int /*<<< orphan*/ *,scalar_t__,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _mkdirU (char*) ; 
 int _snprintf (char*,int,char*,char const*,char const*,char const*) ; 
 int /*<<< orphan*/  autorun_name ; 
 scalar_t__ calloc (int,int) ; 
 scalar_t__ check_iso_props (char const*,scalar_t__,char const*,char*,TYPE_1__*) ; 
 int /*<<< orphan*/ * embedded_sl_version_str ; 
 int /*<<< orphan*/  fix_config (char*,char const*,char const*,TYPE_1__*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nb_blocks ; 
 int /*<<< orphan*/ * old_c32_name ; 
 int /*<<< orphan*/  preallocate_filesize (scalar_t__,scalar_t__) ; 
 scalar_t__ preserve_timestamps ; 
 int /*<<< orphan*/  print_extracted_file (char*,scalar_t__) ; 
 char const* psz_extract_dir ; 
 int /*<<< orphan*/  safe_closehandle (scalar_t__) ; 
 int /*<<< orphan*/  safe_free (char*) ; 
 scalar_t__ safe_strcmp (char*,int /*<<< orphan*/ ) ; 
 char* sanitize_filename (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scan_only ; 
 int /*<<< orphan*/  set_directory_timestamp (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  static_sprintf (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t strlen (char const*) ; 
 int /*<<< orphan*/  stupid_antivirus ; 
 int /*<<< orphan*/  to_filetime (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  total_blocks ; 
 int /*<<< orphan*/  udf_dirent_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udf_get_access_time (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udf_get_attribute_time (int /*<<< orphan*/ *) ; 
 scalar_t__ udf_get_file_length (int /*<<< orphan*/ *) ; 
 char* udf_get_filename (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udf_get_modification_time (int /*<<< orphan*/ *) ; 
 scalar_t__ udf_is_dir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * udf_opendir (int /*<<< orphan*/ *) ; 
 scalar_t__ udf_read_block (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * udf_readdir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uprintf (char*,...) ; 
 scalar_t__* use_own_c32 ; 

__attribute__((used)) static int udf_extract_files(udf_t *p_udf, udf_dirent_t *p_udf_dirent, const char *psz_path)
{
	HANDLE file_handle = NULL;
	DWORD buf_size, wr_size, err;
	EXTRACT_PROPS props;
	BOOL r, is_identical;
	int length;
	size_t i;
	char tmp[128], *psz_fullpath = NULL, *psz_sanpath = NULL;
	const char* psz_basename;
	udf_dirent_t *p_udf_dirent2;
	uint8_t buf[UDF_BLOCKSIZE];
	int64_t read, file_length;

	if ((p_udf_dirent == NULL) || (psz_path == NULL))
		return 1;

	if (psz_path[0] == 0)
		UpdateProgressWithInfoInit(NULL, TRUE);
	while ((p_udf_dirent = udf_readdir(p_udf_dirent)) != NULL) {
		if (FormatStatus) goto out;
		psz_basename = udf_get_filename(p_udf_dirent);
		if (strlen(psz_basename) == 0)
			continue;
		length = (int)(3 + strlen(psz_path) + strlen(psz_basename) + strlen(psz_extract_dir) + 24);
		psz_fullpath = (char*)calloc(sizeof(char), length);
		if (psz_fullpath == NULL) {
			uprintf("Error allocating file name");
			goto out;
		}
		length = _snprintf(psz_fullpath, length, "%s%s/%s", psz_extract_dir, psz_path, psz_basename);
		if (length < 0) {
			goto out;
		}
		if (udf_is_dir(p_udf_dirent)) {
			if (!scan_only) {
				psz_sanpath = sanitize_filename(psz_fullpath, &is_identical);
				IGNORE_RETVAL(_mkdirU(psz_sanpath));
				if (preserve_timestamps) {
					set_directory_timestamp(psz_sanpath, to_filetime(udf_get_attribute_time(p_udf_dirent)),
						to_filetime(udf_get_access_time(p_udf_dirent)), to_filetime(udf_get_modification_time(p_udf_dirent)));
				}
				safe_free(psz_sanpath);
			}
			p_udf_dirent2 = udf_opendir(p_udf_dirent);
			if (p_udf_dirent2 != NULL) {
				if (udf_extract_files(p_udf, p_udf_dirent2, &psz_fullpath[strlen(psz_extract_dir)]))
					goto out;
			}
		} else {
			file_length = udf_get_file_length(p_udf_dirent);
			if (check_iso_props(psz_path, file_length, psz_basename, psz_fullpath, &props)) {
				safe_free(psz_fullpath);
				continue;
			}
			print_extracted_file(psz_fullpath, file_length);
			for (i=0; i<NB_OLD_C32; i++) {
				if (props.is_old_c32[i] && use_own_c32[i]) {
					static_sprintf(tmp, "%s/syslinux-%s/%s", FILES_DIR, embedded_sl_version_str[0], old_c32_name[i]);
					if (CopyFileU(tmp, psz_fullpath, FALSE)) {
						uprintf("  Replaced with local version %s", IsFileInDB(tmp)?"✓":"✗");
						break;
					}
					uprintf("  Could not replace file: %s", WindowsErrorString());
				}
			}
			if (i < NB_OLD_C32)
				continue;
			psz_sanpath = sanitize_filename(psz_fullpath, &is_identical);
			if (!is_identical)
				uprintf("  File name sanitized to '%s'", psz_sanpath);
			file_handle = CreateFileU(psz_sanpath, GENERIC_READ | GENERIC_WRITE,
				FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
			if (file_handle == INVALID_HANDLE_VALUE) {
				err = GetLastError();
				uprintf("  Unable to create file: %s", WindowsErrorString());
				if ((err == ERROR_ACCESS_DENIED) && (safe_strcmp(&psz_sanpath[3], autorun_name) == 0))
					uprintf(stupid_antivirus);
				else
					goto out;
			} else {
				preallocate_filesize(file_handle, file_length);
				while (file_length > 0) {
					if (FormatStatus) goto out;
					memset(buf, 0, UDF_BLOCKSIZE);
					read = udf_read_block(p_udf_dirent, buf, 1);
					if (read < 0) {
						uprintf("  Error reading UDF file %s", &psz_fullpath[strlen(psz_extract_dir)]);
						goto out;
					}
					buf_size = (DWORD)MIN(file_length, read);
					ISO_BLOCKING(r = WriteFileWithRetry(file_handle, buf, buf_size, &wr_size, WRITE_RETRIES));
					if (!r) {
						uprintf("  Error writing file: %s", WindowsErrorString());
						goto out;
					}
					file_length -= read;
					if (nb_blocks++ % PROGRESS_THRESHOLD == 0)
						UpdateProgressWithInfo(OP_FILE_COPY, MSG_231, nb_blocks, total_blocks);
				}
			}
			if ((preserve_timestamps) && (!SetFileTime(file_handle, to_filetime(udf_get_attribute_time(p_udf_dirent)),
				to_filetime(udf_get_access_time(p_udf_dirent)), to_filetime(udf_get_modification_time(p_udf_dirent)))))
				uprintf("  Could not set timestamp: %s", WindowsErrorString());

			// If you have a fast USB 3.0 device, the default Windows buffering does an
			// excellent job at compensating for our small blocks read/writes to max out the
			// device's bandwidth.
			// The drawback however is with cancellation. With a large file, CloseHandle()
			// may take forever to complete and is not interruptible. We try to detect this.
			ISO_BLOCKING(safe_closehandle(file_handle));
			if (props.is_cfg)
				fix_config(psz_sanpath, psz_path, psz_basename, &props);
			safe_free(psz_sanpath);
		}
		safe_free(psz_fullpath);
	}
	return 0;

out:
	if (p_udf_dirent != NULL)
		udf_dirent_free(p_udf_dirent);
	ISO_BLOCKING(safe_closehandle(file_handle));
	safe_free(psz_sanpath);
	safe_free(psz_fullpath);
	return 1;
}