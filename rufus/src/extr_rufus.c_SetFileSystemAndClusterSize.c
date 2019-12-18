#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int ULONG ;
struct TYPE_4__ {int DiskSize; scalar_t__ MediaType; int SectorSize; int FSType; TYPE_1__* ClusterSize; } ;
struct TYPE_3__ {int Allowed; int Default; } ;
typedef  int LONGLONG ;
typedef  int LONG ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ComboBox_AddStringU (int /*<<< orphan*/ ,char*) ; 
 int ComboBox_GetCount (int /*<<< orphan*/ ) ; 
 int ComboBox_GetCurSel (int /*<<< orphan*/ ) ; 
 size_t ComboBox_GetItemData (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ComboBox_ResetContent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ComboBox_SetCurSel (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ComboBox_SetItemData (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int FAT32_CLUSTER_THRESHOLD ; 
 size_t FS_EXFAT ; 
 size_t FS_EXT2 ; 
 size_t FS_EXT3 ; 
 size_t FS_FAT16 ; 
 size_t FS_FAT32 ; 
 int FS_MAX ; 
 size_t FS_NTFS ; 
 size_t FS_REFS ; 
 size_t FS_UDF ; 
 int FS_UNKNOWN ; 
 char** FileSystemLabel ; 
 scalar_t__ FixedMedia ; 
 int GB ; 
 int /*<<< orphan*/  IGNORE_RETVAL (int /*<<< orphan*/ ) ; 
 int KB ; 
 int LARGE_FAT32_SIZE ; 
 float MAX_FAT32_SIZE ; 
 int MB ; 
 int /*<<< orphan*/  MSG_030 ; 
 void* SINGLE_CLUSTERSIZE_DEFAULT ; 
 TYPE_2__ SelectedDrive ; 
 int /*<<< orphan*/  SetAllowedFileSystems () ; 
 int /*<<< orphan*/  SetClusterSizeLabels () ; 
 int /*<<< orphan*/  SetClusterSizes (int) ; 
 int /*<<< orphan*/  SetComboEntry (int /*<<< orphan*/ ,int) ; 
 float TB ; 
 scalar_t__ WINDOWS_8_1 ; 
 scalar_t__ advanced_mode_format ; 
 scalar_t__* allowed_filesystem ; 
 int default_fs ; 
 scalar_t__ force_large_fat32 ; 
 int /*<<< orphan*/  hClusterSize ; 
 int /*<<< orphan*/  hFileSystem ; 
 char* lmprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memset (TYPE_1__**,int /*<<< orphan*/ ,int) ; 
 scalar_t__ nWindowsVersion ; 
 scalar_t__ safe_strcmp (char*,char*) ; 
 scalar_t__ safe_strlen (char*) ; 
 size_t selected_fs ; 
 int /*<<< orphan*/  static_strcat (char*,char*) ; 

__attribute__((used)) static BOOL SetFileSystemAndClusterSize(char* fs_name)
{
	int fs_index;
	LONGLONG i;
	char tmp[128] = "", *entry;

	IGNORE_RETVAL(ComboBox_ResetContent(hFileSystem));
	IGNORE_RETVAL(ComboBox_ResetContent(hClusterSize));
	default_fs = FS_UNKNOWN;
	memset(&SelectedDrive.ClusterSize, 0, sizeof(SelectedDrive.ClusterSize));

/*
 * See https://support.microsoft.com/en-gb/help/140365/default-cluster-size-for-ntfs--fat--and-exfat
 * The following are MS's allowed cluster sizes for FAT16 and FAT32:
 *
 * FAT16
 * 31M  :  512 - 4096
 * 63M  : 1024 - 8192
 * 127M : 2048 - 16k
 * 255M : 4096 - 32k
 * 511M : 8192 - 64k
 * 1023M:  16k - 64k
 * 2047M:  32k - 64k
 * 4095M:  64k
 * 4GB+ : N/A
 *
 * FAT32
 * 31M  : N/A
 * 63M  : N/A			(NB unlike MS, we're allowing 512-512 here)
 * 127M :  512 - 1024
 * 255M :  512 - 2048
 * 511M :  512 - 4096
 * 1023M:  512 - 8192
 * 2047M:  512 - 16k
 * 4095M: 1024 - 32k
 * 7GB  : 2048 - 64k
 * 15GB : 4096 - 64k
 * 31GB : 8192 - 64k This is as far as Microsoft's FormatEx goes...
 * 63GB :  16k - 64k ...but we can go higher using fat32format from RidgeCrop.
 * 2TB+ : N/A
 *
 */

	// FAT 16
	if (SelectedDrive.DiskSize < 4*GB) {
		SelectedDrive.ClusterSize[FS_FAT16].Allowed = 0x00001E00;
		for (i=32; i<=4096; i<<=1) {			// 8 MB -> 4 GB
			if (SelectedDrive.DiskSize < i*MB) {
				SelectedDrive.ClusterSize[FS_FAT16].Default = 16*(ULONG)i;
				break;
			}
			SelectedDrive.ClusterSize[FS_FAT16].Allowed <<= 1;
		}
		SelectedDrive.ClusterSize[FS_FAT16].Allowed &= 0x0001FE00;
	}

	// FAT 32
	// > 32GB FAT32 is not supported by MS and FormatEx but is achieved using fat32format
	// See: http://www.ridgecrop.demon.co.uk/index.htm?fat32format.htm
	// < 32 MB FAT32 is not allowed by FormatEx, so we don't bother
	if ((SelectedDrive.DiskSize >= 32*MB) && (1.0f*SelectedDrive.DiskSize < 1.0f*MAX_FAT32_SIZE*TB)) {
		SelectedDrive.ClusterSize[FS_FAT32].Allowed = 0x000001F8;
		for (i=32; i<=(32*1024); i<<=1) {			// 32 MB -> 32 GB
			if (SelectedDrive.DiskSize*1.0f < i*MB*FAT32_CLUSTER_THRESHOLD) {	// MS
				SelectedDrive.ClusterSize[FS_FAT32].Default = 8*(ULONG)i;
				break;
			}
			SelectedDrive.ClusterSize[FS_FAT32].Allowed <<= 1;
		}
		SelectedDrive.ClusterSize[FS_FAT32].Allowed &= 0x0001FE00;

		// Default cluster sizes in the 256MB to 32 GB range do not follow the rule above
		if ((SelectedDrive.DiskSize >= 256*MB) && (SelectedDrive.DiskSize < 32*GB)) {
			for (i=8; i<=32; i<<=1) {				// 256 MB -> 32 GB
				if (SelectedDrive.DiskSize*1.0f < i*GB*FAT32_CLUSTER_THRESHOLD) {
					SelectedDrive.ClusterSize[FS_FAT32].Default = ((ULONG)i/2)*KB;
					break;
				}
			}
		}
		// More adjustments for large drives
		if (SelectedDrive.DiskSize >= 32*GB) {
			SelectedDrive.ClusterSize[FS_FAT32].Allowed &= 0x0001C000;
			SelectedDrive.ClusterSize[FS_FAT32].Default = 0x00008000;
		}
	}

	if (SelectedDrive.DiskSize < 256*TB) {
		// NTFS
		SelectedDrive.ClusterSize[FS_NTFS].Allowed = 0x0001FE00;
		for (i=16; i<=256; i<<=1) {				// 7 MB -> 256 TB
			if (SelectedDrive.DiskSize < i*TB) {
				SelectedDrive.ClusterSize[FS_NTFS].Default = ((ULONG)i/4)*KB;
				break;
			}
		}

		// exFAT
		SelectedDrive.ClusterSize[FS_EXFAT].Allowed = 0x03FFFE00;
		if (SelectedDrive.DiskSize < 256*MB)	// < 256 MB
			SelectedDrive.ClusterSize[FS_EXFAT].Default = 4*KB;
		else if (SelectedDrive.DiskSize < 32*GB)	// < 32 GB
			SelectedDrive.ClusterSize[FS_EXFAT].Default = 32*KB;
		else
			SelectedDrive.ClusterSize[FS_EXFAT].Default = 128*KB;

		// UDF
		SelectedDrive.ClusterSize[FS_UDF].Allowed = SINGLE_CLUSTERSIZE_DEFAULT;
		SelectedDrive.ClusterSize[FS_UDF].Default = 1;

		// ext2/ext3/ext4
		if (advanced_mode_format) {
			SelectedDrive.ClusterSize[FS_EXT2].Allowed = SINGLE_CLUSTERSIZE_DEFAULT;
			SelectedDrive.ClusterSize[FS_EXT2].Default = 1;
			SelectedDrive.ClusterSize[FS_EXT3].Allowed = SINGLE_CLUSTERSIZE_DEFAULT;
			SelectedDrive.ClusterSize[FS_EXT3].Default = 1;
		}

		// ReFS (only supported for Windows 8.1 and later and for fixed disks)
		// TODO: Check later versions of Windows 10 for disabled ReFS (IVdsService::QueryFileSystemTypes?)
		if (SelectedDrive.DiskSize >= 512*MB) {
			if ((nWindowsVersion >= WINDOWS_8_1) && (SelectedDrive.MediaType == FixedMedia)) {
				SelectedDrive.ClusterSize[FS_REFS].Allowed = SINGLE_CLUSTERSIZE_DEFAULT;
				SelectedDrive.ClusterSize[FS_REFS].Default = 1;
			}
		}
	}

	// Only add the filesystems we can service
	SetAllowedFileSystems();
	SetClusterSizeLabels();

	for (fs_index = 0; fs_index < FS_MAX; fs_index++) {
		// Remove all cluster sizes that are below the sector size
		if (SelectedDrive.ClusterSize[fs_index].Allowed != SINGLE_CLUSTERSIZE_DEFAULT) {
			SelectedDrive.ClusterSize[fs_index].Allowed &= ~(SelectedDrive.SectorSize - 1);
			if ((SelectedDrive.ClusterSize[fs_index].Default & SelectedDrive.ClusterSize[fs_index].Allowed) == 0)
				// We lost our default => Use rightmost bit to select the new one
				SelectedDrive.ClusterSize[fs_index].Default =
				SelectedDrive.ClusterSize[fs_index].Allowed & (-(LONG)SelectedDrive.ClusterSize[fs_index].Allowed);
		}

		if (SelectedDrive.ClusterSize[fs_index].Allowed != 0) {
			tmp[0] = 0;
			// Tell the user if we're going to use Large FAT32 or regular
			if ((fs_index == FS_FAT32) && ((SelectedDrive.DiskSize > LARGE_FAT32_SIZE) || (force_large_fat32)))
				static_strcat(tmp, "Large ");
			static_strcat(tmp, FileSystemLabel[fs_index]);
			if (default_fs == FS_UNKNOWN) {
				entry = lmprintf(MSG_030, tmp);
				default_fs = fs_index;
			} else {
				entry = tmp;
			}
			if (allowed_filesystem[fs_index]) {
				IGNORE_RETVAL(ComboBox_SetItemData(hFileSystem,
					ComboBox_AddStringU(hFileSystem, entry), fs_index));
			}
		}
	}

	// re-select existing FS if it's one we know
	SelectedDrive.FSType = FS_UNKNOWN;
	if (safe_strlen(fs_name) != 0) {
		for (SelectedDrive.FSType = FS_MAX - 1; SelectedDrive.FSType >= 0; SelectedDrive.FSType--) {
			if (safe_strcmp(fs_name, FileSystemLabel[SelectedDrive.FSType]) == 0) {
				break;
			}
		}
	} else {
		// Re-select last user-selected FS
		SelectedDrive.FSType = selected_fs;
	}

	for (i = 0; i<ComboBox_GetCount(hFileSystem); i++) {
		if (ComboBox_GetItemData(hFileSystem, i) == SelectedDrive.FSType) {
			IGNORE_RETVAL(ComboBox_SetCurSel(hFileSystem, i));
			break;
		}
	}

	if (i == ComboBox_GetCount(hFileSystem)) {
		// failed to reselect => pick default
		SetComboEntry(hFileSystem, default_fs);
	}

	return SetClusterSizes((int)ComboBox_GetItemData(hFileSystem, ComboBox_GetCurSel(hFileSystem)));
}