#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_7__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct libfat_filesystem {int dummy; } ;
struct libfat_direntry {int* entry; } ;
typedef  int /*<<< orphan*/  iso9660_t ;
struct TYPE_9__ {TYPE_2__* psz_symlink; } ;
struct TYPE_10__ {TYPE_1__ rr; int /*<<< orphan*/ **** lsn; int /*<<< orphan*/  buf; int /*<<< orphan*/ * p_iso; scalar_t__ sec_start; } ;
typedef  TYPE_2__ iso9660_stat_t ;
typedef  TYPE_2__ iso9660_readfat_private ;
typedef  scalar_t__ int32_t ;
struct TYPE_11__ {char* efi_img_path; } ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int ARRAYSIZE (char**) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  HAS_EFI_IMG (TYPE_7__) ; 
 int ISO_BLOCKSIZE ; 
 int ISO_NB_BLOCKS ; 
 scalar_t__ TRUE ; 
 char** efi_bootname ; 
 char* image_path ; 
 TYPE_7__ img_report ; 
 int /*<<< orphan*/  iso9660_close (int /*<<< orphan*/ *) ; 
 TYPE_2__* iso9660_ifs_stat_translate (int /*<<< orphan*/ *,char*) ; 
 int iso9660_iso_seek_read (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ***,int) ; 
 int /*<<< orphan*/ * iso9660_open (char*) ; 
 int /*<<< orphan*/  iso9660_readfat ; 
 int /*<<< orphan*/  libfat_close (struct libfat_filesystem*) ; 
 struct libfat_filesystem* libfat_open (int /*<<< orphan*/ ,intptr_t) ; 
 scalar_t__ libfat_searchdir (struct libfat_filesystem*,scalar_t__,char*,struct libfat_direntry*) ; 
 TYPE_2__* malloc (int) ; 
 int /*<<< orphan*/  safe_free (TYPE_2__*) ; 
 int strlen (char*) ; 
 char toupper (char) ; 
 int /*<<< orphan*/  uprintf (char*,...) ; 

BOOL HasEfiImgBootLoaders(void)
{
	BOOL ret = FALSE;
	iso9660_t* p_iso = NULL;
	iso9660_stat_t* p_statbuf = NULL;
	iso9660_readfat_private* p_private = NULL;
	int32_t dc, c;
	struct libfat_filesystem *lf_fs = NULL;
	struct libfat_direntry direntry;
	char name[12] = { 0 };
	int i, j, k;

	if ((image_path == NULL) || !HAS_EFI_IMG(img_report))
		return FALSE;

	p_iso = iso9660_open(image_path);
	if (p_iso == NULL) {
		uprintf("Could not open image '%s' as an ISO-9660 file system", image_path);
		goto out;
	}
	p_statbuf = iso9660_ifs_stat_translate(p_iso, img_report.efi_img_path);
	if (p_statbuf == NULL) {
		uprintf("Could not get ISO-9660 file information for file %s\n", img_report.efi_img_path);
		goto out;
	}
	p_private = malloc(sizeof(iso9660_readfat_private));
	if (p_private == NULL)
		goto out;
	p_private->p_iso = p_iso;
	p_private->lsn = p_statbuf->lsn[0];	// Image should be small enough not to use multiextents
	p_private->sec_start = 0;
	// Populate our intial buffer
	if (iso9660_iso_seek_read(p_private->p_iso, p_private->buf, p_private->lsn, ISO_NB_BLOCKS) != ISO_NB_BLOCKS * ISO_BLOCKSIZE) {
		uprintf("Error reading ISO-9660 file %s at LSN %lu\n", img_report.efi_img_path, (long unsigned int)p_private->lsn);
		goto out;
	}
	lf_fs = libfat_open(iso9660_readfat, (intptr_t)p_private);
	if (lf_fs == NULL) {
		uprintf("FAT access error");
		goto out;
	}

	// Navigate to /EFI/BOOT
	if (libfat_searchdir(lf_fs, 0, "EFI        ", &direntry) < 0)
		goto out;
	dc = direntry.entry[26] + (direntry.entry[27] << 8);
	if (libfat_searchdir(lf_fs, dc, "BOOT       ", &direntry) < 0)
		goto out;
	dc = direntry.entry[26] + (direntry.entry[27] << 8);

	for (i = 0; i < ARRAYSIZE(efi_bootname); i++) {
		// Sanity check in case the EFI forum comes up with a 'bootmips64.efi' or something...
		if (strlen(efi_bootname[i]) > 12) {
			uprintf("Internal error: FAT 8.3");
			continue;
		}
		for (j = 0, k = 0; efi_bootname[i][j] != 0; j++) {
			if (efi_bootname[i][j] == '.') {
				while (k < 8)
					name[k++] = ' ';
			} else
				name[k++] = toupper(efi_bootname[i][j]);
		}
		c = libfat_searchdir(lf_fs, dc, name, &direntry);
		if (c > 0) {
			if (!ret)
				uprintf("  Detected EFI bootloader(s) (from '%s'):", img_report.efi_img_path);
			uprintf("  ● '%s'", efi_bootname[i]);
			ret = TRUE;
		}
	}

out:
	if (lf_fs != NULL)
		libfat_close(lf_fs);
	if (p_statbuf != NULL)
		safe_free(p_statbuf->rr.psz_symlink);
	safe_free(p_statbuf);
	safe_free(p_private);
	if (p_iso != NULL)
		iso9660_close(p_iso);
	return ret;
}