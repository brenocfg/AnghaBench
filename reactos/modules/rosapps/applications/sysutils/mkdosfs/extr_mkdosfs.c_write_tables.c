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
struct msdos_boot_sector {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  info_sector; int /*<<< orphan*/  fat32_length; } ;
struct TYPE_4__ {TYPE_1__ fat32; int /*<<< orphan*/  fat_length; } ;

/* Variables and functions */
 int CF_LE_L (int /*<<< orphan*/ ) ; 
 int CF_LE_W (int /*<<< orphan*/ ) ; 
 int backup_boot ; 
 char* blank_sector ; 
 TYPE_2__ bs ; 
 char* fat ; 
 int /*<<< orphan*/  free (char*) ; 
 char* info_sector ; 
 int nr_fats ; 
 int reserved_sectors ; 
 char* root_dir ; 
 int sector_size ; 
 int /*<<< orphan*/  seekto (int,char*) ; 
 int size_fat ; 
 int size_root_dir ; 
 int /*<<< orphan*/  writebuf (char*,int,char*) ; 

__attribute__((used)) static void
write_tables (void)
{
  int x;
  int fat_length;
#ifdef _WIN32
  int blk;
#endif

  fat_length = (size_fat == 32) ?
	       CF_LE_L(bs.fat32.fat32_length) : CF_LE_W(bs.fat_length);

  seekto( 0, "start of device" );
  /* clear all reserved sectors */
  for( x = 0; x < reserved_sectors; ++x )
    writebuf( blank_sector, sector_size, "reserved sector" );
  /* seek back to sector 0 and write the boot sector */
  seekto( 0, "boot sector" );
  writebuf( (char *) &bs, sizeof (struct msdos_boot_sector), "boot sector" );
  /* on FAT32, write the info sector and backup boot sector */
  if (size_fat == 32)
    {
      seekto( CF_LE_W(bs.fat32.info_sector)*sector_size, "info sector" );
      writebuf( info_sector, 512, "info sector" );
      if (backup_boot != 0)
	{
	  seekto( backup_boot*sector_size, "backup boot sector" );
	  writebuf( (char *) &bs, sizeof (struct msdos_boot_sector),
		    "backup boot sector" );
	}
    }
  /* seek to start of FATS and write them all */
  seekto( reserved_sectors*sector_size, "first FAT" );
  for (x = 1; x <= nr_fats; x++)
#ifdef _WIN32
	  /*
	   * WIN32 appearently has problems writing very large chunks directly
	   * to disk devices. To not produce errors because of resource shortages
	   * split up the write in sector size chunks.
	   */
	  for (blk = 0; blk < fat_length; blk++)
		  writebuf(fat+blk*sector_size, sector_size, "FAT");
#else
    writebuf( fat, fat_length * sector_size, "FAT" );
#endif
  /* Write the root directory directly after the last FAT. This is the root
   * dir area on FAT12/16, and the first cluster on FAT32. */
  writebuf( (char *) root_dir, size_root_dir, "root directory" );

  if (info_sector) free( info_sector );
  free (root_dir);   /* Free up the root directory space from setup_tables */
  free (fat);  /* Free up the fat table space reserved during setup_tables */
}