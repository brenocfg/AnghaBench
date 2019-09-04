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
typedef  int /*<<< orphan*/  udf_t ;
typedef  int /*<<< orphan*/  udf_dirent_t ;
typedef  scalar_t__ ssize_t ;
typedef  scalar_t__ lsn_t ;
typedef  int /*<<< orphan*/  iso9660_t ;
struct TYPE_5__ {TYPE_2__* psz_symlink; } ;
struct TYPE_6__ {size_t extents; scalar_t__* extsize; TYPE_1__ rr; scalar_t__* lsn; } ;
typedef  TYPE_2__ iso9660_stat_t ;
typedef  scalar_t__ int64_t ;
typedef  scalar_t__ HANDLE ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CREATE_ALWAYS ; 
 scalar_t__ CreateFileU (char const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FILE_SHARE_READ ; 
 int GENERIC_READ ; 
 int GENERIC_WRITE ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 scalar_t__ ISO_BLOCKSIZE ; 
 scalar_t__ MIN (scalar_t__,scalar_t__) ; 
 int UDF_BLOCKSIZE ; 
 int /*<<< orphan*/  WRITE_RETRIES ; 
 unsigned long WindowsErrorString () ; 
 int /*<<< orphan*/  WriteFileWithRetry (scalar_t__,char*,scalar_t__,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iso9660_close (int /*<<< orphan*/ *) ; 
 TYPE_2__* iso9660_ifs_stat_translate (int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ iso9660_iso_seek_read (int /*<<< orphan*/ *,char*,scalar_t__,int) ; 
 int /*<<< orphan*/ * iso9660_open (char const*) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  safe_closehandle (scalar_t__) ; 
 int /*<<< orphan*/  safe_free (TYPE_2__*) ; 
 int /*<<< orphan*/  udf_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udf_dirent_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * udf_fopen (int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ udf_get_file_length (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * udf_get_root (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * udf_open (char const*) ; 
 scalar_t__ udf_read_block (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  uprintf (char*,...) ; 

int64_t ExtractISOFile(const char* iso, const char* iso_file, const char* dest_file, DWORD attributes)
{
	size_t i, j;
	ssize_t read_size;
	int64_t file_length, extent_length, r = 0;
	char buf[UDF_BLOCKSIZE];
	DWORD buf_size, wr_size;
	iso9660_t* p_iso = NULL;
	udf_t* p_udf = NULL;
	udf_dirent_t *p_udf_root = NULL, *p_udf_file = NULL;
	iso9660_stat_t *p_statbuf = NULL;
	lsn_t lsn;
	HANDLE file_handle = INVALID_HANDLE_VALUE;

	file_handle = CreateFileU(dest_file, GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ, NULL, CREATE_ALWAYS, attributes, NULL);
	if (file_handle == INVALID_HANDLE_VALUE) {
		uprintf("  Could not create file %s: %s", dest_file, WindowsErrorString());
		goto out;
	}

	// First try to open as UDF - fallback to ISO if it failed
	p_udf = udf_open(iso);
	if (p_udf == NULL)
		goto try_iso;

	p_udf_root = udf_get_root(p_udf, true, 0);
	if (p_udf_root == NULL) {
		uprintf("Could not locate UDF root directory");
		goto out;
	}
	p_udf_file = udf_fopen(p_udf_root, iso_file);
	if (!p_udf_file) {
		uprintf("Could not locate file %s in ISO image", iso_file);
		goto out;
	}
	file_length = udf_get_file_length(p_udf_file);
	while (file_length > 0) {
		memset(buf, 0, UDF_BLOCKSIZE);
		read_size = udf_read_block(p_udf_file, buf, 1);
		if (read_size < 0) {
			uprintf("Error reading UDF file %s", iso_file);
			goto out;
		}
		buf_size = (DWORD)MIN(file_length, read_size);
		if (!WriteFileWithRetry(file_handle, buf, buf_size, &wr_size, WRITE_RETRIES)) {
			uprintf("  Error writing file %s: %s", dest_file, WindowsErrorString());
			goto out;
		}
		file_length -= read_size;
		r += read_size;
	}
	goto out;

try_iso:
	p_iso = iso9660_open(iso);
	if (p_iso == NULL) {
		uprintf("Unable to open image '%s'", iso);
		goto out;
	}

	p_statbuf = iso9660_ifs_stat_translate(p_iso, iso_file);
	if (p_statbuf == NULL) {
		uprintf("Could not get ISO-9660 file information for file %s", iso_file);
		goto out;
	}

	for (j = 0; j < p_statbuf->extents; j++) {
		extent_length = p_statbuf->extsize[j];
		for (i = 0; extent_length > 0; i++) {
			memset(buf, 0, ISO_BLOCKSIZE);
			lsn = p_statbuf->lsn[j] + (lsn_t)i;
			if (iso9660_iso_seek_read(p_iso, buf, lsn, 1) != ISO_BLOCKSIZE) {
				uprintf("  Error reading ISO9660 file %s at LSN %lu", iso_file, (long unsigned int)lsn);
				goto out;
			}
			buf_size = (DWORD)MIN(extent_length, ISO_BLOCKSIZE);
			if (!WriteFileWithRetry(file_handle, buf, buf_size, &wr_size, WRITE_RETRIES)) {
				uprintf("  Error writing file %s: %s", dest_file, WindowsErrorString());
				goto out;
			}
			extent_length -= ISO_BLOCKSIZE;
			r += ISO_BLOCKSIZE;
		}
	}

out:
	safe_closehandle(file_handle);
	if (p_statbuf != NULL)
		safe_free(p_statbuf->rr.psz_symlink);
	safe_free(p_statbuf);
	if (p_udf_root != NULL)
		udf_dirent_free(p_udf_root);
	if (p_udf_file != NULL)
		udf_dirent_free(p_udf_file);
	if (p_iso != NULL)
		iso9660_close(p_iso);
	if (p_udf != NULL)
		udf_close(p_udf);
	return r;
}