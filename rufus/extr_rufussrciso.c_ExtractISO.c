#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint16_t ;
typedef  int /*<<< orphan*/  udf_t ;
typedef  int /*<<< orphan*/  udf_dirent_t ;
struct __stat64 {scalar_t__ st_size; } ;
typedef  int /*<<< orphan*/  path ;
typedef  int iso_extension_mask_t ;
typedef  int /*<<< orphan*/  iso9660_t ;
typedef  int /*<<< orphan*/  iso9660_pvd_t ;
typedef  int int64_t ;
struct TYPE_13__ {char* label; int projected_size; char* cfg_path; scalar_t__ sl_version; char* sl_version_ext; char* sl_version_str; int has_efi; int winpe; int has_grub2; scalar_t__* grub2_version; scalar_t__ needs_syslinux_overwrite; int /*<<< orphan*/  wininst_version; int /*<<< orphan*/  uses_minint; scalar_t__ mismatch_size; scalar_t__ has_symlinks; scalar_t__ has_long_filename; } ;
struct TYPE_12__ {size_t Index; char** String; } ;
typedef  int /*<<< orphan*/  FILE ;
typedef  int BOOL ;

/* Variables and functions */
 int APPERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  APPLICATION_NAME ; 
 int /*<<< orphan*/  DeleteFileU (char const*) ; 
 int /*<<< orphan*/  DumpFatDir (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR_ISO_EXTRACT ; 
 int /*<<< orphan*/  ERROR_ISO_SCAN ; 
 int ERROR_SEVERITY_ERROR ; 
 scalar_t__ ExtractISOFile (char const*,char*,char const*,int /*<<< orphan*/ ) ; 
 int FAC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FACILITY_STORAGE ; 
 int FALSE ; 
 int /*<<< orphan*/  FILE_ATTRIBUTE_NORMAL ; 
 int FormatStatus ; 
 int /*<<< orphan*/  GetGrubVersion (char*,size_t) ; 
 int /*<<< orphan*/  GetInstallWimVersion (char const*) ; 
 void* GetSyslinuxVersion (char*,size_t,char**) ; 
 scalar_t__ GetTempFileNameU (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ GetTempPathU (int,char*) ; 
 scalar_t__ HAS_EFI_IMG (TYPE_2__) ; 
 scalar_t__ HAS_SYSLINUX (TYPE_2__) ; 
 scalar_t__ HAS_WININST (TYPE_2__) ; 
 scalar_t__ HAS_WINPE (TYPE_2__) ; 
 scalar_t__ HasEfiImgBootLoaders () ; 
 int /*<<< orphan*/  IGNORE_RETVAL (int /*<<< orphan*/ ) ; 
 int ISO_BLOCKSIZE ; 
 int ISO_EXTENSION_ALL ; 
 int ISO_EXTENSION_JOLIET ; 
 int ISO_EXTENSION_ROCK_RIDGE ; 
 int /*<<< orphan*/  IS_EFI_BOOTABLE (TYPE_2__) ; 
 int /*<<< orphan*/  IsStrArrayEmpty (TYPE_1__) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  MSG_202 ; 
 int /*<<< orphan*/  MSG_231 ; 
 int /*<<< orphan*/  PBS_MARQUEE ; 
 int /*<<< orphan*/  PrintInfo (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int SL_MAJOR (void*) ; 
 int /*<<< orphan*/  SL_MINOR (void*) ; 
 int /*<<< orphan*/  SendMessage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StrArrayCreate (TYPE_1__*,int) ; 
 int /*<<< orphan*/  StrArrayDestroy (TYPE_1__*) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  UM_PROGRESS_EXIT ; 
 int /*<<< orphan*/  UM_PROGRESS_INIT ; 
 int WINPE_AMD64 ; 
 int WINPE_I386 ; 
 int /*<<< orphan*/  _chdirU (int /*<<< orphan*/ ) ; 
 scalar_t__ _stat64U (char const*,struct __stat64*) ; 
 scalar_t__ _stricmp (char*,char*) ; 
 int /*<<< orphan*/  app_dir ; 
 scalar_t__ calloc (size_t,int) ; 
 int /*<<< orphan*/  cdio_log_set_handler (int /*<<< orphan*/ ) ; 
 TYPE_1__ config_path ; 
 void** embedded_sl_version ; 
 int /*<<< orphan*/  enable_iso ; 
 int /*<<< orphan*/  enable_joliet ; 
 scalar_t__ enable_rockridge ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  fread (char*,int,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* get_token_data_file (char*,char const*) ; 
 int /*<<< orphan*/  hMainDialog ; 
 int has_ldlinux_c32 ; 
 TYPE_2__ img_report ; 
 int /*<<< orphan*/  iso9660_close (int /*<<< orphan*/ *) ; 
 scalar_t__ iso9660_get_pvd_space_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iso9660_ifs_get_joliet_level (int /*<<< orphan*/ *) ; 
 scalar_t__ iso9660_ifs_get_volume_id (int /*<<< orphan*/ *,char**) ; 
 scalar_t__ iso9660_ifs_read_pvd (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * iso9660_open (char const*) ; 
 int /*<<< orphan*/ * iso9660_open_ext (char const*,int) ; 
 int iso_blocking_status ; 
 int iso_extract_files (int /*<<< orphan*/ *,char*) ; 
 TYPE_1__ isolinux_path ; 
 scalar_t__ isspaceU (char) ; 
 int /*<<< orphan*/  joliet_level ; 
 int /*<<< orphan*/  log_handler ; 
 int /*<<< orphan*/  memset (char*,char,int) ; 
 scalar_t__ nb_blocks ; 
 char const* psz_extract_dir ; 
 int /*<<< orphan*/  rename (char*,char*) ; 
 int /*<<< orphan*/  safe_free (char*) ; 
 scalar_t__ safe_strcmp (char*,char*) ; 
 int safe_strlen (char*) ; 
 scalar_t__ safe_strnicmp (char*,char*,size_t) ; 
 int scan_only ; 
 int /*<<< orphan*/  static_sprintf (char*,char*,...) ; 
 int /*<<< orphan*/  static_strcpy (char*,char*) ; 
 size_t strlen (char*) ; 
 int /*<<< orphan*/ * strstr (char*,char*) ; 
 char const* temp_dir ; 
 scalar_t__ tolower (char) ; 
 int total_blocks ; 
 int /*<<< orphan*/  udf_close (int /*<<< orphan*/ *) ; 
 int udf_extract_files (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 scalar_t__ udf_get_logical_volume_id (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/ * udf_get_root (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * udf_open (char const*) ; 
 int /*<<< orphan*/  uprintf (char*,...) ; 

BOOL ExtractISO(const char* src_iso, const char* dest_dir, BOOL scan)
{
	size_t i, j, size, sl_index = 0;
	uint16_t sl_version;
	FILE* fd;
	int r = 1;
	iso9660_t* p_iso = NULL;
	iso9660_pvd_t pvd;
	udf_t* p_udf = NULL;
	udf_dirent_t* p_udf_root;
	char *tmp, *buf, *ext;
	char path[MAX_PATH], path2[16];
	const char* basedir[] = { "i386", "amd64", "minint" };
	const char* tmp_sif = ".\\txtsetup.sif~";
	iso_extension_mask_t iso_extension_mask = ISO_EXTENSION_ALL;
	char* spacing = "  ";

	if ((!enable_iso) || (src_iso == NULL) || (dest_dir == NULL))
		return FALSE;

	scan_only = scan;
	if (!scan_only)
		spacing = "";
	cdio_log_set_handler(log_handler);
	psz_extract_dir = dest_dir;
	// Change progress style to marquee for scanning
	if (scan_only) {
		uprintf("ISO analysis:");
		SendMessage(hMainDialog, UM_PROGRESS_INIT, PBS_MARQUEE, 0);
		total_blocks = 0;
		has_ldlinux_c32 = FALSE;
		// String array of all isolinux/syslinux locations
		StrArrayCreate(&config_path, 8);
		StrArrayCreate(&isolinux_path, 8);
		PrintInfo(0, MSG_202);
	} else {
		uprintf("Extracting files...\n");
		IGNORE_RETVAL(_chdirU(app_dir));
		PrintInfo(0, MSG_231);
		if (total_blocks == 0) {
			uprintf("Error: ISO has not been properly scanned.\n");
			FormatStatus = ERROR_SEVERITY_ERROR|FAC(FACILITY_STORAGE)|APPERR(ERROR_ISO_SCAN);
			goto out;
		}
		nb_blocks = 0;
		iso_blocking_status = 0;
	}

	// First try to open as UDF - fallback to ISO if it failed
	p_udf = udf_open(src_iso);
	if (p_udf == NULL)
		goto try_iso;
	uprintf("%sImage is an UDF image", spacing);

	p_udf_root = udf_get_root(p_udf, true, 0);
	if (p_udf_root == NULL) {
		uprintf("%sCould not locate UDF root directory", spacing);
		goto out;
	}
	if (scan_only) {
		if (udf_get_logical_volume_id(p_udf, img_report.label, sizeof(img_report.label)) <= 0)
			img_report.label[0] = 0;
		// Open the UDF as ISO so that we can perform size checks
		p_iso = iso9660_open(src_iso);
	}
	r = udf_extract_files(p_udf, p_udf_root, "");
	goto out;

try_iso:
	// Perform our first scan with Joliet disabled (if Rock Ridge is enabled), so that we can find if
	// there exists a Rock Ridge file with a name > 64 chars or if there are symlinks. If that is the
	// case then we also disable Joliet during the extract phase.
	if ((!enable_joliet) || (enable_rockridge && (scan_only || img_report.has_long_filename || img_report.has_symlinks))) {
		iso_extension_mask &= ~ISO_EXTENSION_JOLIET;
	}
	if (!enable_rockridge) {
		iso_extension_mask &= ~ISO_EXTENSION_ROCK_RIDGE;
	}

	p_iso = iso9660_open_ext(src_iso, iso_extension_mask);
	if (p_iso == NULL) {
		uprintf("%s'%s' doesn't look like an ISO image", spacing, src_iso);
		r = 1;
		goto out;
	}
	uprintf("%sImage is an ISO9660 image", spacing);
	joliet_level = iso9660_ifs_get_joliet_level(p_iso);
	if (scan_only) {
		if (iso9660_ifs_get_volume_id(p_iso, &tmp)) {
			static_strcpy(img_report.label, tmp);
			safe_free(tmp);
		} else
			img_report.label[0] = 0;
	} else {
		if (iso_extension_mask & (ISO_EXTENSION_JOLIET|ISO_EXTENSION_ROCK_RIDGE))
			uprintf("%sThis image will be extracted using %s extensions (if present)", spacing,
				(iso_extension_mask & ISO_EXTENSION_JOLIET)?"Joliet":"Rock Ridge");
		else
			uprintf("%sThis image will not be extracted using any ISO extensions", spacing);
	}
	r = iso_extract_files(p_iso, "");

out:
	iso_blocking_status = -1;
	if (scan_only) {
		struct __stat64 stat;
		// Find if there is a mismatch between the ISO size, as reported by the PVD, and the actual file size
		if ((iso9660_ifs_read_pvd(p_iso, &pvd)) && (_stat64U(src_iso, &stat) == 0))
			img_report.mismatch_size = (int64_t)(iso9660_get_pvd_space_size(&pvd)) * ISO_BLOCKSIZE - stat.st_size;
		// Remove trailing spaces from the label
		for (j=safe_strlen(img_report.label)-1; ((j>0)&&(isspaceU(img_report.label[j]))); j--)
			img_report.label[j] = 0;
		// We use the fact that UDF_BLOCKSIZE and ISO_BLOCKSIZE are the same here
		img_report.projected_size = total_blocks * ISO_BLOCKSIZE;
		// We will link the existing isolinux.cfg from a syslinux.cfg we create
		// If multiple config files exist, choose the one with the shortest path
		// (so that a '/syslinux.cfg' is preferred over a '/isolinux/isolinux.cfg')
		if (!IsStrArrayEmpty(config_path)) {
			// Set the img_report.cfg_path string to maximum length, so that we don't have to
			// do a special case for StrArray entry 0.
			memset(img_report.cfg_path, '_', sizeof(img_report.cfg_path)-1);
			img_report.cfg_path[sizeof(img_report.cfg_path)-1] = 0;
			for (i=0; i<config_path.Index; i++) {
				// OpenSuse based Live image have a /syslinux.cfg that doesn't work, so we enforce
				// the use of the one in '/boot/[i386|x86_64]/loader/isolinux.cfg' if present.
				// Note that, because the openSuse live script are not designed to handle anything but
				// an ISO9660 filesystem for the live device, this still won't allow for proper boot.
				// See https://github.com/openSUSE/kiwi/issues/354
				if ( (_stricmp(config_path.String[i], "/boot/i386/loader/isolinux.cfg") == 0) ||
					 (_stricmp(config_path.String[i], "/boot/x86_64/loader/isolinux.cfg") == 0)) {
					static_strcpy(img_report.cfg_path, config_path.String[i]);
					img_report.needs_syslinux_overwrite = TRUE;
					break;
				}
				// Tails uses an '/EFI/BOOT/isolinux.cfg' along with a '/isolinux/isolinux.cfg'
				// which are the exact same length. However, only the /isolinux one will work,
				// so for now, at equal length, always pick the latest.
				// We may have to revisit this and prefer a path that contains '/isolinux' if
				// this hack is not enough for other images.
				if (safe_strlen(img_report.cfg_path) >= safe_strlen(config_path.String[i]))
					static_strcpy(img_report.cfg_path, config_path.String[i]);
			}
			uprintf("  Will use '%s' for Syslinux", img_report.cfg_path);
			// Extract all of the isolinux.bin files we found to identify their versions
			for (i=0; i<isolinux_path.Index; i++) {
				char isolinux_tmp[MAX_PATH];
				static_sprintf(isolinux_tmp, "%s\\isolinux.tmp", temp_dir);
				size = (size_t)ExtractISOFile(src_iso, isolinux_path.String[i], isolinux_tmp, FILE_ATTRIBUTE_NORMAL);
				if (size == 0) {
					uprintf("  Could not access %s", isolinux_path.String[i]);
				} else {
					buf = (char*)calloc(size, 1);
					if (buf == NULL) break;
					fd = fopen(isolinux_tmp, "rb");
					if (fd == NULL) {
						free(buf);
						continue;
					}
					fread(buf, 1, size, fd);
					fclose(fd);
					sl_version = GetSyslinuxVersion(buf, size, &ext);
					if (img_report.sl_version == 0) {
						static_strcpy(img_report.sl_version_ext, ext);
						img_report.sl_version = sl_version;
						sl_index = i;
					} else if ((img_report.sl_version != sl_version) || (safe_strcmp(img_report.sl_version_ext, ext) != 0)) {
						uprintf("  Found conflicting isolinux versions:\n  '%s' (%d.%02d%s) vs '%s' (%d.%02d%s)",
							isolinux_path.String[sl_index], SL_MAJOR(img_report.sl_version), SL_MINOR(img_report.sl_version),
							img_report.sl_version_ext, isolinux_path.String[i], SL_MAJOR(sl_version), SL_MINOR(sl_version), ext);
						// Workaround for Antergos and other ISOs, that have multiple Syslinux versions.
						// Where possible, prefer to the one that resides in the same directory as the config file.
						for (j=safe_strlen(img_report.cfg_path); (j>0) && (img_report.cfg_path[j]!='/'); j--);
						if (safe_strnicmp(img_report.cfg_path, isolinux_path.String[i], j) == 0) {
							static_strcpy(img_report.sl_version_ext, ext);
							img_report.sl_version = sl_version;
							sl_index = i;
						}
					}
					free(buf);
				}
				DeleteFileU(isolinux_tmp);
			}
			if (img_report.sl_version != 0) {
				static_sprintf(img_report.sl_version_str, "%d.%02d",
					SL_MAJOR(img_report.sl_version), SL_MINOR(img_report.sl_version));
				uprintf("  Detected Syslinux version: %s%s (from '%s')",
					img_report.sl_version_str, img_report.sl_version_ext, isolinux_path.String[sl_index]);
				if ( (has_ldlinux_c32 && (SL_MAJOR(img_report.sl_version) < 5))
				  || (!has_ldlinux_c32 && (SL_MAJOR(img_report.sl_version) >= 5)) )
					uprintf("  Warning: Conflict between Isolinux version and the presence of ldlinux.c32...");
			} else {
				// Couldn't find a version from isolinux.bin. Force set to the versions we embed
				img_report.sl_version = embedded_sl_version[has_ldlinux_c32?1:0];
				static_sprintf(img_report.sl_version_str, "%d.%02d",
					SL_MAJOR(img_report.sl_version), SL_MINOR(img_report.sl_version));
				uprintf("  Warning: Could not detect Isolinux version - Forcing to %s (embedded)",
					img_report.sl_version_str);
			}
		}
		if (!IS_EFI_BOOTABLE(img_report) && HAS_EFI_IMG(img_report) && HasEfiImgBootLoaders()) {
			img_report.has_efi = 0x80;
		}
		if (HAS_WINPE(img_report)) {
			// In case we have a WinPE 1.x based iso, we extract and parse txtsetup.sif
			// during scan, to see if /minint was provided for OsLoadOptions, as it decides
			// whether we should use 0x80 or 0x81 as the disk ID in the MBR
			static_sprintf(path, "/%s/txtsetup.sif",
				basedir[((img_report.winpe&WINPE_I386) == WINPE_I386)?0:((img_report.winpe&WINPE_AMD64) == WINPE_AMD64?1:2)]);
			ExtractISOFile(src_iso, path, tmp_sif, FILE_ATTRIBUTE_NORMAL);
			tmp = get_token_data_file("OsLoadOptions", tmp_sif);
			if (tmp != NULL) {
				for (i=0; i<strlen(tmp); i++)
					tmp[i] = (char)tolower(tmp[i]);
				uprintf("  Checking txtsetup.sif:\n  OsLoadOptions = %s", tmp);
				img_report.uses_minint = (strstr(tmp, "/minint") != NULL);
			}
			DeleteFileU(tmp_sif);
			safe_free(tmp);
		}
		if (HAS_WININST(img_report)) {
			img_report.wininst_version = GetInstallWimVersion(src_iso);
		}
		if (img_report.has_grub2) {
			// In case we have a GRUB2 based iso, we extract boot/grub/i386-pc/normal.mod to parse its version
			img_report.grub2_version[0] = 0;
			if ((GetTempPathU(sizeof(path), path) != 0) && (GetTempFileNameU(path, APPLICATION_NAME, 0, path) != 0)) {
				size = (size_t)ExtractISOFile(src_iso, "boot/grub/i386-pc/normal.mod", path, FILE_ATTRIBUTE_NORMAL);
				buf = (char*)calloc(size, 1);
				fd = fopen(path, "rb");
				if ((size == 0) || (buf == NULL) || (fd == NULL)) {
					uprintf("  Could not read Grub version from 'boot/grub/i386-pc/normal.mod'");
				} else {
					fread(buf, 1, size, fd);
					fclose(fd);
					GetGrubVersion(buf, size);
				}
				free(buf);
				DeleteFileU(path);
			}
			if (img_report.grub2_version[0] != 0)
				uprintf("  Detected Grub version: %s", img_report.grub2_version);
			else {
				uprintf("  Could not detect Grub version");
				img_report.has_grub2 = FALSE;
			}
		}
		StrArrayDestroy(&config_path);
		StrArrayDestroy(&isolinux_path);
		SendMessage(hMainDialog, UM_PROGRESS_EXIT, 0, 0);
	} else {
		// Solus and other ISOs only provide EFI boot files in a FAT efi.img
		if (img_report.has_efi == 0x80)
			DumpFatDir(dest_dir, 0);
		if (HAS_SYSLINUX(img_report)) {
			static_sprintf(path, "%s\\syslinux.cfg", dest_dir);
			// Create a /syslinux.cfg (if none exists) that points to the existing isolinux cfg
			fd = fopen(path, "r");
			if (fd != NULL && img_report.needs_syslinux_overwrite) {
				fclose(fd);
				fd = NULL;
				static_sprintf(path2, "%s\\syslinux.org", dest_dir);
				uprintf("Renaming: %s ➔ %s", path, path2);
				IGNORE_RETVAL(rename(path, path2));
			}
			if (fd == NULL) {
				fd = fopen(path, "w");	// No "/syslinux.cfg" => create a new one
				if (fd == NULL) {
					uprintf("Unable to create %s - booting from USB will not work", path);
					r = 1;
				} else {
					fprintf(fd, "DEFAULT loadconfig\n\nLABEL loadconfig\n  CONFIG %s\n", img_report.cfg_path);
					for (i = safe_strlen(img_report.cfg_path); (i > 0) && (img_report.cfg_path[i] != '/'); i--);
					if (i > 0) {
						img_report.cfg_path[i] = 0;
						fprintf(fd, "  APPEND %s/\n", img_report.cfg_path);
						img_report.cfg_path[i] = '/';
					}
					uprintf("Created: %s", path);
				}
			}
			if (fd != NULL)
				fclose(fd);
		}
	}
	if (p_iso != NULL)
		iso9660_close(p_iso);
	if (p_udf != NULL)
		udf_close(p_udf);
	if ((r != 0) && (FormatStatus == 0))
		FormatStatus = ERROR_SEVERITY_ERROR|FAC(FACILITY_STORAGE)|APPERR((scan_only?ERROR_ISO_SCAN:ERROR_ISO_EXTRACT));
	return (r == 0);
}