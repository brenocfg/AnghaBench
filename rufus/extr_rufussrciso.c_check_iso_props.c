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
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int64_t ;
struct TYPE_7__ {int has_efi; scalar_t__* reactos_path; scalar_t__* efi_img_path; size_t wininst_index; int winpe; void* has_4GB_file; void** has_old_c32; int /*<<< orphan*/ * wininst_path; void* has_kolibrios; void* has_grub4dos; void* has_bootmgr_efi; void* has_bootmgr; void* has_grub2; void* has_efi_syslinux; } ;
struct TYPE_6__ {void** is_old_c32; void* is_syslinux_cfg; void* is_grub_cfg; void* is_cfg; } ;
typedef  TYPE_1__ EXTRACT_PROPS ;
typedef  void* BOOL ;

/* Variables and functions */
 size_t ARRAYSIZE (char**) ; 
 void* FALSE ; 
 scalar_t__ FOUR_GIGABYTES ; 
 int /*<<< orphan*/  HAS_EFI_IMG (TYPE_3__) ; 
 scalar_t__ ISO_BLOCKSIZE ; 
 size_t MAX_WININST ; 
 size_t NB_OLD_C32 ; 
 int /*<<< orphan*/  StrArrayAdd (int /*<<< orphan*/ *,char const*,void*) ; 
 void* TRUE ; 
 char* bootmgr_efi_name ; 
 char* bootmgr_name ; 
 int /*<<< orphan*/  config_path ; 
 char** efi_bootname ; 
 char* efi_dirname ; 
 char* grldr_name ; 
 char* grub_cfg ; 
 char* grub_dirname ; 
 void* has_ldlinux_c32 ; 
 TYPE_3__ img_report ; 
 char** isolinux_bin ; 
 int /*<<< orphan*/  isolinux_path ; 
 char* kolibri_name ; 
 char* ldlinux_c32 ; 
 int /*<<< orphan*/  ldlinux_name ; 
 size_t max (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 char** old_c32_name ; 
 scalar_t__* old_c32_threshold ; 
 char** pe_dirname ; 
 char** pe_file ; 
 char* reactos_name ; 
 scalar_t__ safe_strcmp (char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ safe_stricmp (char const*,char*) ; 
 int safe_strlen (char const*) ; 
 scalar_t__ safe_strnicmp (char const*,char*,int) ; 
 scalar_t__ scan_only ; 
 char* sources_str ; 
 int /*<<< orphan*/  static_sprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  static_strcpy (scalar_t__*,char const*) ; 
 int strlen (char const*) ; 
 char** syslinux_cfg ; 
 scalar_t__ total_blocks ; 
 int /*<<< orphan*/  uprintf (char*,int /*<<< orphan*/ ) ; 
 char** wininst_name ; 

__attribute__((used)) static BOOL check_iso_props(const char* psz_dirname, int64_t file_length, const char* psz_basename,
	const char* psz_fullpath, EXTRACT_PROPS *props)
{
	size_t i, j, len;
	// Check for an isolinux/syslinux config file anywhere
	memset(props, 0, sizeof(EXTRACT_PROPS));
	for (i=0; i<ARRAYSIZE(syslinux_cfg); i++) {
		if (safe_stricmp(psz_basename, syslinux_cfg[i]) == 0) {
			props->is_cfg = TRUE;	// Required for "extlinux.conf"
			props->is_syslinux_cfg = TRUE;
			if ((scan_only) && (i == 1) && (safe_stricmp(psz_dirname, efi_dirname) == 0))
				img_report.has_efi_syslinux = TRUE;
		}
	}

	// Check for an old incompatible c32 file anywhere
	for (i=0; i<NB_OLD_C32; i++) {
		if ((safe_stricmp(psz_basename, old_c32_name[i]) == 0) && (file_length <= old_c32_threshold[i]))
			props->is_old_c32[i] = TRUE;
	}

	// Check for config files that may need patching
	if (!scan_only) {
		len = safe_strlen(psz_basename);
		if ((len >= 4) && safe_stricmp(&psz_basename[len-4], ".cfg") == 0)
			props->is_cfg = TRUE;
	}

	// Check for GRUB artifacts
	if (scan_only) {
		if (safe_stricmp(psz_dirname, grub_dirname) == 0)
			img_report.has_grub2 = TRUE;
	} else if (safe_stricmp(psz_basename, grub_cfg) == 0) {
		props->is_grub_cfg = TRUE;
	}

	if (scan_only) {
		// Check for a syslinux v5.0+ file anywhere
		if (safe_stricmp(psz_basename, ldlinux_c32) == 0) {
			has_ldlinux_c32 = TRUE;
		}

		// Check for various files in root (psz_dirname = "")
		if ((psz_dirname != NULL) && (psz_dirname[0] == 0)) {
			if (safe_stricmp(psz_basename, bootmgr_name) == 0) {
				img_report.has_bootmgr = TRUE;
			}
			if (safe_stricmp(psz_basename, bootmgr_efi_name) == 0) {
				img_report.has_bootmgr_efi = TRUE;
			}
			if (safe_stricmp(psz_basename, grldr_name) == 0) {
				img_report.has_grub4dos = TRUE;
			}
			if (safe_stricmp(psz_basename, kolibri_name) == 0) {
				img_report.has_kolibrios = TRUE;
			}
			if (safe_stricmp(psz_basename, bootmgr_efi_name) == 0) {
				img_report.has_efi |= 1;
			}
		}

		// Check for ReactOS' setupldr.sys anywhere
		if ((img_report.reactos_path[0] == 0) && (safe_stricmp(psz_basename, reactos_name) == 0))
			static_strcpy(img_report.reactos_path, psz_fullpath);

		// Check for the first 'efi*.img' we can find (that hopefully contains EFI boot files)
		if (!HAS_EFI_IMG(img_report) && (safe_strlen(psz_basename) >= 7) &&
			(safe_strnicmp(psz_basename, "efi", 3) == 0) &&
			(safe_stricmp(&psz_basename[strlen(psz_basename) - 4], ".img") == 0))
			static_strcpy(img_report.efi_img_path, psz_fullpath);

		// Check for the EFI boot entries
		if (safe_stricmp(psz_dirname, efi_dirname) == 0) {
			for (i=0; i<ARRAYSIZE(efi_bootname); i++)
				if (safe_stricmp(psz_basename, efi_bootname[i]) == 0)
					img_report.has_efi |= (2<<i);	// start at 2 since "bootmgr.efi" is bit 0
		}

		// Check for "install.###" in "###/sources/"
		if (psz_dirname != NULL) {
			if (safe_stricmp(&psz_dirname[max(0, ((int)safe_strlen(psz_dirname)) - ((int)strlen(sources_str)))], sources_str) == 0) {
				for (i = 0; i < ARRAYSIZE(wininst_name); i++) {
					if (safe_stricmp(psz_basename, wininst_name[i]) == 0) {
						if (img_report.wininst_index < MAX_WININST) {
							static_sprintf(img_report.wininst_path[img_report.wininst_index], "?:%s", psz_fullpath);
							img_report.wininst_index++;
						}
					}
				}
			}
		}

		// Check for PE (XP) specific files in "/i386", "/amd64" or "/minint"
		for (i=0; i<ARRAYSIZE(pe_dirname); i++)
			if (safe_stricmp(psz_dirname, pe_dirname[i]) == 0)
				for (j=0; j<ARRAYSIZE(pe_file); j++)
					if (safe_stricmp(psz_basename, pe_file[j]) == 0)
						img_report.winpe |= (1<<j)<<(ARRAYSIZE(pe_dirname)*i);

		if (props->is_syslinux_cfg) {
			// Maintain a list of all the isolinux/syslinux configs identified so far
			StrArrayAdd(&config_path, psz_fullpath, TRUE);
		}
		for (i=0; i<ARRAYSIZE(isolinux_bin); i++) {
			if (safe_stricmp(psz_basename, isolinux_bin[i]) == 0) {
				// Maintain a list of all the isolinux.bin files found
				StrArrayAdd(&isolinux_path, psz_fullpath, TRUE);
			}
		}

		for (i=0; i<NB_OLD_C32; i++) {
			if (props->is_old_c32[i])
				img_report.has_old_c32[i] = TRUE;
		}
		if (file_length >= FOUR_GIGABYTES)
			img_report.has_4GB_file = TRUE;
		// Compute projected size needed
		total_blocks += file_length / ISO_BLOCKSIZE;
		// NB: ISO_BLOCKSIZE = UDF_BLOCKSIZE
		if ((file_length != 0) && (file_length % ISO_BLOCKSIZE != 0))
			total_blocks++;
		return TRUE;
	}
	// In case there's an ldlinux.sys on the ISO, prevent it from overwriting ours
	if ((psz_dirname != NULL) && (psz_dirname[0] == 0) && (safe_strcmp(psz_basename, ldlinux_name) == 0)) {
		uprintf("skipping % file from ISO image\n", ldlinux_name);
		return TRUE;
	}
	return FALSE;
}