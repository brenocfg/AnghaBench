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
struct TYPE_4__ {int /*<<< orphan*/  FileSysType; int /*<<< orphan*/  BootSignature; int /*<<< orphan*/  FATSz32; } ;
struct TYPE_3__ {int /*<<< orphan*/  FileSysType; int /*<<< orphan*/  BootSignature; } ;
struct fat_boot_sector {TYPE_2__ bs32; TYPE_1__ bs16; int /*<<< orphan*/  bsFATsecs; int /*<<< orphan*/  bsFATs; int /*<<< orphan*/  bsRootDirEnts; int /*<<< orphan*/  bsResSectors; int /*<<< orphan*/  bsHugeSectors; int /*<<< orphan*/  bsSectors; int /*<<< orphan*/  bsSecPerClust; int /*<<< orphan*/  bsBytesPerSec; } ;

/* Variables and functions */
 int VFAT ; 
 long long get_16 (int /*<<< orphan*/ *) ; 
 long long get_32 (int /*<<< orphan*/ *) ; 
 int get_8 (int /*<<< orphan*/ *) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static const char *check_fat_bootsect(const void *bs, int *fs_type)
{
    int sectorsize;
    const struct fat_boot_sector *sectbuf = bs;
    long long sectors, fatsectors, dsectors;
    long long clusters;
    int rootdirents, clustersize;

    sectorsize = get_16(&sectbuf->bsBytesPerSec);

    clustersize = get_8(&sectbuf->bsSecPerClust);
    if (clustersize == 0 || (clustersize & (clustersize - 1)))
	return "impossible cluster size on an FAT volume";

    sectors = get_16(&sectbuf->bsSectors);
    sectors = sectors ? sectors : get_32(&sectbuf->bsHugeSectors);

    dsectors = sectors - get_16(&sectbuf->bsResSectors);

    fatsectors = get_16(&sectbuf->bsFATsecs);
    fatsectors = fatsectors ? fatsectors : get_32(&sectbuf->bs32.FATSz32);
    fatsectors *= get_8(&sectbuf->bsFATs);
    dsectors -= fatsectors;

    rootdirents = get_16(&sectbuf->bsRootDirEnts);
    dsectors -= (rootdirents + sectorsize / 32 - 1) / sectorsize;

    if (dsectors < 0)
	return "negative number of data sectors on an FAT volume";

    clusters = dsectors / clustersize;

    fatsectors = get_16(&sectbuf->bsFATsecs);
    fatsectors = fatsectors ? fatsectors : get_32(&sectbuf->bs32.FATSz32);
    fatsectors *= get_8(&sectbuf->bsFATs);

    if (!fatsectors)
	return "zero FAT sectors";

    if (clusters < 0xFFF5) {
	/* FAT12 or FAT16 */
	if (!get_16(&sectbuf->bsFATsecs))
	    return "zero FAT sectors (FAT12/16)";

	if (get_8(&sectbuf->bs16.BootSignature) == 0x29) {
	    if (!memcmp(&sectbuf->bs16.FileSysType, "FAT12   ", 8)) {
		if (clusters >= 0xFF5)
		    return "more than 4084 clusters but claims FAT12";
	    } else if (!memcmp(&sectbuf->bs16.FileSysType, "FAT16   ", 8)) {
		if (clusters < 0xFF5)
		    return "less than 4084 clusters but claims FAT16";
	    } else if (!memcmp(&sectbuf->bs16.FileSysType, "FAT32   ", 8)) {
		return "less than 65525 clusters but claims FAT32";
	    } else if (memcmp(&sectbuf->bs16.FileSysType, "FAT     ", 8)) {
		static char fserr[] = "filesystem type \"????????\" not "
		    "supported";
		memcpy(fserr + 17, &sectbuf->bs16.FileSysType, 8);
		return fserr;
	    }
	}
    } else if (clusters < 0x0FFFFFF5) {
	/*
	 * FAT32...
	 *
	 * Moving the FileSysType and BootSignature was a lovely stroke
	 * of M$ idiocy...
	 */
	if (get_8(&sectbuf->bs32.BootSignature) != 0x29 ||
	    memcmp(&sectbuf->bs32.FileSysType, "FAT32   ", 8))
	    return "missing FAT32 signature";
    } else {
	return "impossibly large number of clusters on an FAT volume";
    }

    if (fs_type)
	*fs_type = VFAT;

    return NULL;
}